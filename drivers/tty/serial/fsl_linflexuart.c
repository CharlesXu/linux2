/*
 * Freescale linflexuart serial port driver
 *
 * Copyright 2012-2015 Freescale Semiconductor, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#if defined(CONFIG_SERIAL_FSL_LINFLEXUART_CONSOLE) && defined(CONFIG_MAGIC_SYSRQ)
#define SUPPORT_SYSRQ
#endif

#include <linux/clk.h>
#include <linux/console.h>
#include <linux/dma-mapping.h>
#include <linux/dmaengine.h>
#include <linux/dmapool.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_dma.h>
#include <linux/serial_core.h>
#include <linux/slab.h>
#include <linux/tty_flip.h>

/* All registers are 32-bit width */

#define LINCR1	0x0000 /* LIN control register				*/
#define LINIER	0x0004 /* LIN interrupt enable register			*/
#define LINSR	0x0008 /* LIN status register				*/
#define LINESR	0x000C /* LIN error status register			*/
#define UARTCR	0x0010 /* UART mode control register			*/
#define UARTSR	0x0014 /* UART mode status register			*/
#define LINTCSR 0x0018 /* LIN timeout control status register		*/
#define LINOCR	0x001C /* LIN output compare register			*/
#define LINTOCR 0x0020 /* LIN timeout control register			*/
#define LINFBRR 0x0024 /* LIN fractional baud rate register		*/
#define LINIBRR 0x0028 /* LIN integer baud rate register		*/
#define LINCFR	0x002C /* LIN checksum field register			*/
#define LINCR2	0x0030 /* LIN control register 2			*/
#define BIDR	0x0034 /* Buffer identifier register			*/
#define BDRL	0x0038 /* Buffer data register least significant	*/
#define BDRM	0x003C /* Buffer data register most significant		*/
#define IFER	0x0040 /* Identifier filter enable register		*/
#define IFMI	0x0044 /* Identifier filter match index			*/
#define IFMR	0x0048 /* Identifier filter mode register		*/
#define IFCR0	0x004C /* Identifier filter control register 0		*/
#define IFCR1	0x0050 /* Identifier filter control register 1		*/
#define IFCR2	0x0054 /* Identifier filter control register 2		*/
#define IFCR3	0x0058 /* Identifier filter control register 3		*/
#define IFCR4	0x005C /* Identifier filter control register 4		*/
#define IFCR5	0x0060 /* Identifier filter control register 5		*/
#define IFCR6	0x0064 /* Identifier filter control register 6		*/
#define IFCR7	0x0068 /* Identifier filter control register 7		*/
#define IFCR8	0x006C /* Identifier filter control register 8		*/
#define IFCR9	0x0070 /* Identifier filter control register 9		*/
#define IFCR10	0x0074 /* Identifier filter control register 10		*/
#define IFCR11	0x0078 /* Identifier filter control register 11		*/
#define IFCR12	0x007C /* Identifier filter control register 12		*/
#define IFCR13	0x0080 /* Identifier filter control register 13		*/
#define IFCR14	0x0084 /* Identifier filter control register 14		*/
#define IFCR15	0x0088 /* Identifier filter control register 15		*/
#define GCR	0x008C /* Global control register			*/
#define UARTPTO 0x0090 /* UART preset timeout register			*/
#define UARTCTO 0x0094 /* UART current timeout register			*/
#define DMATXE	0x0098 /* DMA Tx enable register			*/
#define DMARXE	0x009C /* DMAx enable register				*/

/*
**	CONSTANT DEFINITIONS
*/

#define LINFLEXD_LINCR1_INIT		(1<<0)

#define LINFLEXD_LINIER_SZIE		(1<<15)
#define LINFLEXD_LINIER_OCIE		(1<<14)
#define LINFLEXD_LINIER_BEIE		(1<<13)
#define LINFLEXD_LINIER_CEIE		(1<<12)
#define LINFLEXD_LINIER_HEIE		(1<<11)
#define LINFLEXD_LINIER_FEIE		(1<<8)
#define LINFLEXD_LINIER_BOIE		(1<<7)
#define LINFLEXD_LINIER_LSIE		(1<<6)
#define LINFLEXD_LINIER_WUIE		(1<<5)
#define LINFLEXD_LINIER_DBFIE		(1<<4)
#define LINFLEXD_LINIER_DBEIETOIE	(1<<3)
#define LINFLEXD_LINIER_DRIE		(1<<2)
#define LINFLEXD_LINIER_DTIE		(1<<1)
#define LINFLEXD_LINIER_HRIE		(1<<0)

#if defined(PSP_MPXD10)
#define LINFLEXD_UARTCR_TDFLTFC_MASK	(0x6000)
#define LINFLEXD_UARTCR_RDFLRFC_MASK	(0xc00)
#else
#define LINFLEXD_UARTCR_TDFLTFC_MASK	(0xe000)
#define LINFLEXD_UARTCR_RDFLRFC_MASK	(0x1c00)
#endif

#define LINFLEXD_UARTCR_TDFLTFC_SHIFT	(13)
#define LINFLEXD_UARTCR_RDFLRFC_SHIFT	(10)

#define LINFLEXD_UARTCR_TDFLTFC		(1<<13)
#define LINFLEXD_UARTCR_RDFLRFC		(1<<10)

#define LINFLEXD_UARTCR_RFBM		(1<<9)
#define LINFLEXD_UARTCR_TFBM		(1<<8)
#define LINFLEXD_UARTCR_WL1		(1<<7)
#define LINFLEXD_UARTCR_PC1		(1<<6)

#define LINFLEXD_UARTCR_RXEN		(1<<5)
#define LINFLEXD_UARTCR_TXEN		(1<<4)
#define LINFLEXD_UARTCR_PC0		(1<<3)

#define LINFLEXD_UARTCR_PCE		(1<<2)
#define LINFLEXD_UARTCR_WL0		(1<<1)
#define LINFLEXD_UARTCR_UART		(1<<0)

#define LINFLEXD_UARTSR_SZF		(1<<15)
#define LINFLEXD_UARTSR_OCF		(1<<14)
#define LINFLEXD_UARTSR_PE3		(1<<13)
#define LINFLEXD_UARTSR_PE2		(1<<12)
#define LINFLEXD_UARTSR_PE1		(1<<11)
#define LINFLEXD_UARTSR_PE0		(1<<10)
#define LINFLEXD_UARTSR_RMB		(1<<9)
#define LINFLEXD_UARTSR_FEF		(1<<8)
#define LINFLEXD_UARTSR_BOF		(1<<7)
#define LINFLEXD_UARTSR_RPS		(1<<6)
#define LINFLEXD_UARTSR_WUF		(1<<5)
#define LINFLEXD_UARTSR_4		(1<<4)

#define LINFLEXD_UARTSR_TO		(1<<3)

#define LINFLEXD_UARTSR_DRFRFE		(1<<2)
#define LINFLEXD_UARTSR_DTFTFF		(1<<1)
#define LINFLEXD_UARTSR_NF		(1<<0)
#define LINFLEXD_UARTSR_PE		(LINFLEXD_UARTSR_PE0|LINFLEXD_UARTSR_PE1|LINFLEXD_UARTSR_PE2|LINFLEXD_UARTSR_PE3)

#define DMA_MAXBURST			(16)
#define DMA_MAXBURST_MASK		(DMA_MAXBURST - 1)
#define FSL_UART_RX_DMA_BUFFER_SIZE	(64)


#define DRIVER_NAME	"fsl-linflexuart"
#define DEV_NAME	"ttyLF"
#define UART_NR		2

#define prd_info(a)	;//pr_info(a);

struct linflex_port {
	struct uart_port	port;
	struct clk		*clk;
	unsigned int		txfifo_size;
	unsigned int		rxfifo_size;
	bool			linflex_dma_use;
};

static struct of_device_id linflex_dt_ids[] = {
	{
		.compatible = "fsl,s32v234-linflexuart",
	},
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, linflex_dt_ids);


static void linflex_stop_tx(struct uart_port *port)
{
	unsigned int temp;
	temp = readl(port->membase + LINIER);
	temp &= ~(LINFLEXD_LINIER_DTIE);
	writel(temp, port->membase + LINIER);
}

 static void linflex_stop_rx(struct uart_port *port)
{
	unsigned int temp;
	temp = readb(port->membase + LINIER);
	writeb(temp & ~LINFLEXD_LINIER_DRIE, port->membase + LINIER);
}
 static void linflex_enable_ms(struct uart_port *port)
{
}
static inline void linflex_transmit_buffer(struct linflex_port *sport)
{
	//volatile unsigned int i;
	struct circ_buf *xmit = &sport->port.state->xmit;
	unsigned char c;

	while (!uart_circ_empty(xmit)) {
		c = xmit->buf[xmit->tail];
		writeb(c, sport->port.membase + BDRL);
		while(( readb(sport->port.membase + UARTSR) & LINFLEXD_UARTSR_DTFTFF)!=LINFLEXD_UARTSR_DTFTFF){
		 //for (i = 0; i < 100000; i++);
		}
		/* waiting for data transmission completed - TODO: add a timeout */
		writeb( (readb(sport->port.membase + UARTSR)|LINFLEXD_UARTSR_DTFTFF), sport->port.membase + UARTSR);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
	}

	while (!uart_circ_empty(xmit)) {
		writeb(xmit->buf[xmit->tail], sport->port.membase + BDRL);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		sport->port.icount.tx++;
	}

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(&sport->port);

	if (uart_circ_empty(xmit))
		linflex_stop_tx(&sport->port);
}

static void linflex_start_tx(struct uart_port *port)
{
	struct linflex_port *sport = container_of(port,
			struct linflex_port, port);
	unsigned int temp;

	temp = readl(port->membase + LINIER);

	writel(temp | LINFLEXD_LINIER_DTIE, port->membase + LINIER);

	linflex_transmit_buffer(sport);
}


static irqreturn_t linflex_txint(int irq, void *dev_id)
{
	struct linflex_port *sport = dev_id;
	struct circ_buf *xmit = &sport->port.state->xmit;
	unsigned long flags, status;

	status = readl(sport->port.membase + UARTSR);
	status = status | LINFLEXD_UARTSR_DTFTFF;
	writel(status, sport->port.membase + UARTSR);
	spin_lock_irqsave(&sport->port.lock, flags);

	if (sport->port.x_char) {
		writeb(sport->port.x_char, sport->port.membase + BDRL);
		goto out;
	}

	if (uart_circ_empty(xmit) || uart_tx_stopped(&sport->port)) {
		linflex_stop_tx(&sport->port);
		goto out;
	}

	linflex_transmit_buffer(sport);

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(&sport->port);

out:
	spin_unlock_irqrestore(&sport->port.lock, flags);
	return IRQ_HANDLED;
}

static irqreturn_t linflex_rxint(int irq, void *dev_id)
{
	struct linflex_port *sport = dev_id;
	unsigned int flg;
	struct tty_port *port = &sport->port.state->port;
	unsigned long flags;
	unsigned char rx;
	unsigned long status;

	spin_lock_irqsave(&sport->port.lock, flags);

	status = readl(sport->port.membase + UARTSR);
	while (status & LINFLEXD_UARTSR_DRFRFE) {

		status = readl(sport->port.membase + UARTSR);
		status = status | LINFLEXD_UARTSR_DRFRFE;
		writel(status, sport->port.membase + UARTSR);

		status = readl(sport->port.membase + UARTSR);
		if (status & (LINFLEXD_UARTSR_BOF|LINFLEXD_UARTSR_SZF|LINFLEXD_UARTSR_FEF|LINFLEXD_UARTSR_PE)) {

			if (status & LINFLEXD_UARTSR_SZF) {
				status |= LINFLEXD_UARTSR_SZF;
			}
			if (status & LINFLEXD_UARTSR_BOF) {
				status |= LINFLEXD_UARTSR_BOF;
			}
			if (status & LINFLEXD_UARTSR_FEF) {
				status |= LINFLEXD_UARTSR_FEF;
			}
			if (status & LINFLEXD_UARTSR_PE) {
				status |=  LINFLEXD_UARTSR_PE;
			}
		}

		rx = readl(sport->port.membase + BDRM);

		writel( readl(sport->port.membase + UARTSR)|LINFLEXD_UARTSR_RMB, sport->port.membase + UARTSR);

		flg = TTY_NORMAL;
		sport->port.icount.rx++;

		if (uart_handle_sysrq_char(&sport->port, (unsigned char)rx))
			continue;

		#ifdef SUPPORT_SYSRQ
			sport->port.sysrq = 0;
		#endif
			tty_insert_flip_char(port, rx, flg);
		status = readl(sport->port.membase + UARTSR);
	}

	spin_unlock_irqrestore(&sport->port.lock, flags);

	tty_flip_buffer_push(port);

	return IRQ_HANDLED;
}

static irqreturn_t linflex_int(int irq, void *dev_id)
{
	struct linflex_port *sport = dev_id;
	unsigned int status;

	status = readl(sport->port.membase + UARTSR);

	if (status & LINFLEXD_UARTSR_DRFRFE) {
		linflex_rxint(irq, dev_id);
	}
	if (status & LINFLEXD_UARTSR_DTFTFF ) {
		linflex_txint(irq, dev_id);
	}


	return IRQ_HANDLED;
}

/* return TIOCSER_TEMT when transmitter is not busy */
static unsigned int linflex_tx_empty(struct uart_port *port)
{
	return (readb(port->membase + UARTSR) & LINFLEXD_UARTSR_DTFTFF) ?
		TIOCSER_TEMT : 0;

}

static unsigned int linflex_get_mctrl(struct uart_port *port)
{
	return 0;
}

static void linflex_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
}
static void linflex_break_ctl(struct uart_port *port, int break_state)
{
}
static void linflex_setup_watermark(struct linflex_port *sport)
{
	unsigned long cr, ier, cr1;
	unsigned long cr_saved ;

	cr = readl(sport->port.membase + UARTCR);
	cr_saved = cr;

	/* Disable transmission/reception */
	cr &= ~(LINFLEXD_UARTCR_RXEN | LINFLEXD_UARTCR_TXEN);

	writel(cr, sport->port.membase + UARTCR);

	/* Enter initialization mode by setting INIT bit */
	cr1=readl(sport->port.membase + LINCR1);

	cr1 |= LINFLEXD_LINCR1_INIT;

	writel(cr1, sport->port.membase + LINCR1);

	/* determine FIFO size and enable FIFO mode from UARTCR */
	/* TO BE DONE

	sport->txfifo_size = 0x1 << (((val >> UARTPFIFO_TXSIZE_OFF) &
		UARTPFIFO_FIFOSIZE_MASK) + 1);

	sport->rxfifo_size = 0x1 << (((val >> UARTPFIFO_RXSIZE_OFF) &
		UARTPFIFO_FIFOSIZE_MASK) + 1);

	writeb(val | UARTPFIFO_TXFE | UARTPFIFO_RXFE,
			sport->port.membase + UARTPFIFO);

	// flush Tx and Rx FIFO
	writeb(UARTCFIFO_TXFLUSH | UARTCFIFO_RXFLUSH,
			sport->port.membase + UARTCFIFO);

	writeb(0, sport->port.membase + UARTTWFIFO);
	writeb(1, sport->port.membase + UARTRWFIFO);
	*/

	/*
		UART = 0x1;		- Linflex working in UART mode
		TXEN = 0x1;		- Enable transmission of data now
		RXEn = 0x1;		- Receiver enabled
		WL0 = 0x1;		- 8 bit data
		PCE = 0x0;		- No parity
	*/

	/* Disable FIFO mode set by u-boot until UART FIFO mode support is
	implemented by the current driver */
	cr_saved &= ~(LINFLEXD_UARTCR_RFBM | LINFLEXD_UARTCR_TFBM);

	cr_saved |= (LINFLEXD_UARTCR_UART|LINFLEXD_UARTCR_RXEN | LINFLEXD_UARTCR_TXEN|
				LINFLEXD_UARTCR_PCE|LINFLEXD_UARTCR_WL0);


	/* Restore cr2 */
	writel(cr_saved, sport->port.membase + UARTCR);

	cr1 &= ~(LINFLEXD_LINCR1_INIT);

	writel(cr1, sport->port.membase + LINCR1);

	ier = readl(sport->port.membase + LINIER);
	ier |= (LINFLEXD_LINIER_DTIE | LINFLEXD_LINIER_DRIE);
	writel(ier, sport->port.membase + LINIER);
}


static int linflex_startup(struct uart_port *port)
{
	struct linflex_port *sport = container_of(port, struct linflex_port, port);
	int ret;
	unsigned long flags;

	/* No support for dma in the current driver */
	sport->linflex_dma_use = false;

	ret = devm_request_irq(port->dev, port->irq, linflex_int, 0,
				DRIVER_NAME, sport);

	if (ret)
		return ret;

	spin_lock_irqsave(&sport->port.lock, flags);

	linflex_setup_watermark(sport);

	spin_unlock_irqrestore(&sport->port.lock, flags);
	return 0;
}

static void linflex_shutdown(struct uart_port *port)
{
	struct linflex_port *sport = container_of(port, struct linflex_port, port);
	unsigned long cr, ier;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);

	/* disable Rx/Tx and interrupts*/
	ier = readl(port->membase + LINIER);

	ier &= ~(LINFLEXD_LINIER_DTIE | LINFLEXD_LINIER_DRIE );
	writel(ier, port->membase + LINIER);
	cr = readl(port->membase + UARTCR);

	cr &= ~(LINFLEXD_UARTCR_RXEN |	LINFLEXD_UARTCR_TXEN);
	writel(ier, port->membase + UARTCR);

	spin_unlock_irqrestore(&port->lock, flags);

	devm_free_irq(port->dev, port->irq, sport);

}

static void
linflex_set_termios(struct uart_port *port, struct ktermios *termios,
			struct ktermios *old )
{
#ifndef CONFIG_S32V234_PALLADIUM
	/*on Palladium we trust the configuration provided by u-boot*/
	struct linflex_port *sport = container_of(port, struct linflex_port, port);
	unsigned long flags;
	/*unsigned char cr1, old_cr1, old_cr2, cr4, bdh, modem;*/
	unsigned long cr, old_cr, cr1;
	unsigned int  baud;
	unsigned int old_csize = old ? old->c_cflag & CSIZE : CS8;
	unsigned long ibr, fbr, divisr, dividr;

	cr = old_cr = readl(sport->port.membase + UARTCR);

	/* Enter initialization mode by setting INIT bit */
	cr1=readl(sport->port.membase + LINCR1);

	cr1 |= LINFLEXD_LINCR1_INIT;

	writel(cr1, sport->port.membase + LINCR1);

	/*
	 * only support CS8 and CS7, and for CS7 must enable PE.
	 * supported mode:
	 *	- (7,e/o,1)
	 *	- (8,n,1)
	 *	- (8,m/s,1)
	 *	- (8,e/o,1)
	 */
	/* enter the UART into configuration mode */

	while ((termios->c_cflag & CSIZE) != CS8 &&
	(termios->c_cflag & CSIZE) != CS7) {
		termios->c_cflag &= ~CSIZE;
		termios->c_cflag |= old_csize;
		old_csize = CS8;
	}

	if ((termios->c_cflag & CSIZE) == CS7 ){
	/* Word lenght: WL1WL0:00 */
	cr = old_cr & ~LINFLEXD_UARTCR_WL1 & ~LINFLEXD_UARTCR_WL0;
	}

	if ((termios->c_cflag & CSIZE) == CS8 ){
		/* Word lenght: WL1WL0:01 */
		cr = (old_cr | LINFLEXD_UARTCR_WL0)& ~LINFLEXD_UARTCR_WL1;
	}

	if (termios->c_cflag & CMSPAR) {
		if ((termios->c_cflag & CSIZE) != CS8) {
			termios->c_cflag &= ~CSIZE;
			termios->c_cflag |= CS8;
		}
		/* has a space/sticky bit */
		cr |= LINFLEXD_UARTCR_WL0;
	}

	if (termios->c_cflag & CSTOPB)
		termios->c_cflag &= ~CSTOPB;

	/* parity must be enabled when CS7 to match 8-bits format */
	if ((termios->c_cflag & CSIZE) == CS7)
		termios->c_cflag |= PARENB;

	if ((termios->c_cflag & PARENB)) {
		if (termios->c_cflag & CMSPAR) {
			cr &= ~LINFLEXD_UARTCR_PCE;

		}
		else {

			cr |= LINFLEXD_UARTCR_PCE;
			if ((termios->c_cflag & CSIZE) == CS8)
			{
				if (termios->c_cflag & PARODD)
					cr = (cr | LINFLEXD_UARTCR_PC0 )&(~LINFLEXD_UARTCR_PC1);
				else
					cr = cr & (~LINFLEXD_UARTCR_PC1 & ~LINFLEXD_UARTCR_PC0);
			}
		}
	}

	/* ask the core to calculate the divisor */
	baud = uart_get_baud_rate(port, termios, old, 50, port->uartclk / 16);

	spin_lock_irqsave(&sport->port.lock, flags);

	sport->port.read_status_mask = 0;

	if (termios->c_iflag & INPCK)
		sport->port.read_status_mask |=	(LINFLEXD_UARTSR_FEF | LINFLEXD_UARTSR_PE0|LINFLEXD_UARTSR_PE1
										|LINFLEXD_UARTSR_PE2|LINFLEXD_UARTSR_PE3);
	if (termios->c_iflag & (IGNBRK | BRKINT | PARMRK))
		sport->port.read_status_mask |= LINFLEXD_UARTSR_FEF;

	/* characters to ignore */
	sport->port.ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		sport->port.ignore_status_mask |= LINFLEXD_UARTSR_PE;
	if (termios->c_iflag & IGNBRK) {
		sport->port.ignore_status_mask |= LINFLEXD_UARTSR_PE;
		/*
		 * if we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			sport->port.ignore_status_mask |= LINFLEXD_UARTSR_BOF;
	}

	/* update the per-port timeout */
	uart_update_timeout(port, termios->c_cflag, baud);

	/* disable transmit and receive */
	writel(old_cr & ~(LINFLEXD_UARTCR_RXEN | LINFLEXD_UARTCR_TXEN),
		sport->port.membase + UARTCR);

	divisr = sport->port.uartclk;	//freq in Hz
	dividr = (baud * 16);

	ibr = divisr/dividr;

	fbr = (divisr%dividr)*16;

	writel(ibr, sport->port.membase + LINIBRR);
	writel(fbr, sport->port.membase + LINFBRR);

	writel(cr, sport->port.membase + UARTCR);

	cr1 &= ~(LINFLEXD_LINCR1_INIT);

	writel(cr1, sport->port.membase + LINCR1);

	spin_unlock_irqrestore(&sport->port.lock, flags);
#endif

}

static const char *linflex_type(struct uart_port *port)
{
	return "FSL_LINFLEX";
}

static void linflex_release_port(struct uart_port *port)
{
	/* nothing to do */
}

static int linflex_request_port(struct uart_port *port)
{
	return 0;
}

/* configure/auto-configure the port */
static void linflex_config_port(struct uart_port *port, int flags)
{
	if (flags & UART_CONFIG_TYPE)
		port->type = PORT_LINFLEXUART;
}

static int linflex_verify_port(struct uart_port *port, struct serial_struct *ser)
{
	int ret = 0;
	if (ser->type != PORT_UNKNOWN && ser->type != PORT_LINFLEXUART)
		ret = -EINVAL;
	if (port->irq != ser->irq)
		ret = -EINVAL;
	if (ser->io_type != UPIO_MEM)
		ret = -EINVAL;
	if (port->uartclk / 16 != ser->baud_base)
		ret = -EINVAL;
	if (port->iobase != ser->port)
		ret = -EINVAL;
	if (ser->hub6 != 0)
		ret = -EINVAL;
	return ret;
}

static struct uart_ops linflex_pops = {
	.tx_empty	= linflex_tx_empty,
	.set_mctrl	= linflex_set_mctrl,
	.get_mctrl	= linflex_get_mctrl,
	.stop_tx	= linflex_stop_tx,
	.start_tx	= linflex_start_tx,
	.stop_rx	= linflex_stop_rx,
	.enable_ms	= linflex_enable_ms,
	.break_ctl	= linflex_break_ctl,
	.startup	= linflex_startup,
	.shutdown	= linflex_shutdown,
	.set_termios	= linflex_set_termios,
	.type		= linflex_type,
	.request_port	= linflex_request_port,
	.release_port	= linflex_release_port,
	.config_port	= linflex_config_port,
	.verify_port	= linflex_verify_port,
};

static struct linflex_port *linflex_ports[UART_NR];

#ifdef CONFIG_SERIAL_FSL_LINFLEXUART_CONSOLE
static void linflex_console_putchar(struct uart_port *port, int ch)
{
	//volatile unsigned int;
	writeb(ch, port->membase + BDRL);

	while(( readb(port->membase + UARTSR) & LINFLEXD_UARTSR_DTFTFF)!=LINFLEXD_UARTSR_DTFTFF){
		//for (i = 0; i < 100000; i++);
	}
	/* waiting for data transmission completed - TODO: add a timeout */

	writeb( (readb(port->membase + UARTSR)|LINFLEXD_UARTSR_DTFTFF), port->membase + UARTSR);

}
static void
linflex_console_write(struct console *co, const char *s, unsigned int count)
{
	struct linflex_port *sport = linflex_ports[co->index];
	/*unsigned char	 old_cr2, cr2;*/
	unsigned long cr, ier, old_ier;

	/* first save CR2 and then disable interrupts */
	ier = old_ier = readl(sport->port.membase + LINIER);

	cr = readl(sport->port.membase + UARTCR);
	cr |= (LINFLEXD_UARTCR_RXEN |  LINFLEXD_UARTCR_TXEN);
	ier &= ~(LINFLEXD_LINIER_DTIE | LINFLEXD_LINIER_DRIE);

	writeb(ier, sport->port.membase + LINIER);
	writeb(cr, sport->port.membase + UARTCR);

	uart_console_write(&sport->port, s, count, linflex_console_putchar);

	/* wait for transmitter finish complete and restore CR2 */
	/*
	while(!( readl(sport->port.membase + UARTSR) & LINFLEXD_UARTSR_DTFTFF))
		barrier();
	*/
	//writeb(old_cr2, sport->port.membase + UARTCR2);
	writeb(old_ier, sport->port.membase + LINIER);

}

/*
 * if the port was already initialised (eg, by a boot loader),
 * try to determine the current setup.
 */
static void __init
linflex_console_get_options(struct linflex_port *sport, int *baud,
				int *parity, int *bits)
{
#ifndef CONFIG_S32V234_PALLADIUM
	/*unsigned char cr, bdh, bdl, brfa;*/
	unsigned long cr, fbr, ibr;
	unsigned int uartclk, baud_raw;

	prd_info("8\n");
	cr = readl(sport->port.membase + UARTCR);
	cr &= LINFLEXD_UARTCR_RXEN | LINFLEXD_UARTCR_TXEN;

	if (!cr)
		return;

	/* ok, the port was enabled */

	*parity = 'n';
	if (cr & LINFLEXD_UARTCR_PCE) {
		if (cr & LINFLEXD_UARTCR_PC0)
			*parity = 'o';
		else
			*parity = 'e';
	}

	if ( (cr & LINFLEXD_UARTCR_WL0) && ((cr & LINFLEXD_UARTCR_WL1) == 0)){
		if( cr & LINFLEXD_UARTCR_PCE )
			*bits = 9;
		else
			*bits = 8;
	}

	fbr = readl(sport->port.membase + LINFBRR);

	ibr = readl(sport->port.membase + LINIBRR);

	uartclk = clk_get_rate(sport->clk);

	baud_raw = uartclk / (16 * ibr);

	if (*baud != baud_raw)
		printk(KERN_INFO "Serial: Console linflex rounded baud rate"
				"from %d to %d\n", baud_raw, *baud);
	#endif
}

static int __init linflex_console_setup(struct console *co, char *options)
{
	struct linflex_port *sport;
	int baud = 115200;
	int bits = 8;
	int parity = 'n';
	int flow = 'n';
	/*
	 * check whether an invalid uart number has been specified, and
	 * if so, search for the first available port that does have
	 * console support.
	 */
	if (co->index == -1 || co->index >= ARRAY_SIZE(linflex_ports))
		co->index = 0;

	sport = linflex_ports[co->index];
	if (sport == NULL)
		return -ENODEV;

	if (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	else
		linflex_console_get_options(sport, &baud, &parity, &bits);

	linflex_setup_watermark(sport);

	writel( (readl(sport->port.membase + LINIER) | (LINFLEXD_LINIER_DRIE) ), sport->port.membase + LINIER);

	return uart_set_options(&sport->port, co, baud, parity, bits, flow);
}

static struct uart_driver linflex_reg;
static struct console linflex_console = {
	.name		= DEV_NAME,
	.write		= linflex_console_write,
	.device		= uart_console_device,
	.setup		= linflex_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &linflex_reg,
};

#define LINFLEX_CONSOLE	(&linflex_console)
#else
#define LINFLEX_CONSOLE	NULL
#endif

static struct uart_driver linflex_reg = {
	.owner		= THIS_MODULE,
	.driver_name	= DRIVER_NAME,
	.dev_name	= DEV_NAME,
	.nr		= ARRAY_SIZE(linflex_ports),
	.cons		= LINFLEX_CONSOLE,
};

static int linflex_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct linflex_port *sport;
	struct resource *res;
	int ret;

	sport = devm_kzalloc(&pdev->dev, sizeof(*sport), GFP_KERNEL);
	if (!sport)
		return -ENOMEM;

	ret = of_alias_get_id(np, "serial");
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to get alias id, errno %d\n", ret);
		return ret;
	}
	sport->port.line = ret;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;

	sport->port.mapbase = res->start;
	sport->port.membase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(sport->port.membase))
		return PTR_ERR(sport->port.membase);

	sport->port.dev = &pdev->dev;
	sport->port.type = PORT_LINFLEXUART;
	sport->port.iotype = UPIO_MEM;
	sport->port.irq = platform_get_irq(pdev, 0);
	sport->port.ops = &linflex_pops;
	sport->port.flags = UPF_BOOT_AUTOCONF;
#ifndef CONFIG_S32V234_PALLADIUM
	sport->clk = devm_clk_get(&pdev->dev, "lin");
	if (IS_ERR(sport->clk)) {
		ret = PTR_ERR(sport->clk);
		dev_err(&pdev->dev, "failed to get uart clk: %d\n", ret);
		return ret;
	}

	ret = clk_prepare_enable(sport->clk);
	if (ret) {
		dev_err(&pdev->dev, "failed to enable uart clk: %d\n", ret);
		return ret;
	}

	sport->port.uartclk = clk_get_rate(sport->clk);
#endif
	linflex_ports[sport->port.line] = sport;

	platform_set_drvdata(pdev, &sport->port);

	ret = uart_add_one_port(&linflex_reg, &sport->port);
	if (ret) {
		clk_disable_unprepare(sport->clk);
		return ret;
	}
	return 0;
}

static int linflex_remove(struct platform_device *pdev)
{
	struct linflex_port *sport = platform_get_drvdata(pdev);
	uart_remove_one_port(&linflex_reg, &sport->port);

	clk_disable_unprepare(sport->clk);

	return 0;
}

#ifdef CONFIG_PM_SLEEP
static int linflex_suspend(struct device *dev)
{
	struct linflex_port *sport = dev_get_drvdata(dev);
	uart_suspend_port(&linflex_reg, &sport->port);

	return 0;
}

static int linflex_resume(struct device *dev)
{
	struct linflex_port *sport = dev_get_drvdata(dev);
	uart_resume_port(&linflex_reg, &sport->port);

	return 0;
}
#endif

static SIMPLE_DEV_PM_OPS(linflex_pm_ops, linflex_suspend, linflex_resume);

static struct platform_driver linflex_driver = {
	.probe		= linflex_probe,
	.remove		= linflex_remove,
	.driver		= {
		.name	= DRIVER_NAME,
		.owner	= THIS_MODULE,
		.of_match_table	= linflex_dt_ids,
		.pm	= &linflex_pm_ops,
	},
};

static int __init linflex_serial_init(void)
{
	int ret;

	prd_info("serial: Freescale linflex driver\n");
	ret = uart_register_driver(&linflex_reg);
	if (ret)
		return ret;

	ret = platform_driver_register(&linflex_driver);
	if (ret)
		uart_unregister_driver(&linflex_reg);

	return ret;
}

static void __exit linflex_serial_exit(void)
{
	platform_driver_unregister(&linflex_driver);
	uart_unregister_driver(&linflex_reg);
}

module_init(linflex_serial_init);
module_exit(linflex_serial_exit);

MODULE_DESCRIPTION("Freescale linflex serial port driver");
MODULE_LICENSE("GPL v2");
