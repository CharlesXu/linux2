#ifndef FSL_VIULITE_IOCTL_H
#define FSL_VIULITE_IOCTL_H

/************************************************
    VARIOUS TYPES
*************************************************/
typedef enum {
	VIU_ON,
	VIU_OFF,
} VIU_BOOL;

typedef struct {
	uint16_t  nmb_lines;
	uint16_t  nmb_pixells;
} VIU_FRAME_SIZE;

typedef struct {
	uint16_t  x_origin;
	uint16_t  y_origin;
	uint16_t  x_size;
	uint16_t  y_size;
} VIU_IMAGE_PARAMS;

typedef enum {
	PARALLEL_MODE = 0,
	ITU_MODE,
} in_mode_t;

typedef enum {
	WIDE_8_BITS = 0,
	WIDE_10_BITS,
	WIDE_12_BITS,
	WIDE_14_BITS,
	WIDE_16_BITS,
	WIDE_20_BITS = 6,
} in_width_t;

typedef struct {
	in_mode_t  mode;
	in_width_t width;
	uint8_t    clocks_per_pixell;
} VIU_INPUT_FORMAT;

typedef struct {
	uint8_t  pclk_pol;
	uint8_t  vsync_pol;
	uint8_t  hsync_pol;
	uint8_t  endianness;
} VIU_DATA_INTERFACE;

typedef enum {
	NO_ERR = 0,
	DMA_VERT_ERR,
	DMA_ACT_ERR,
	LINE_TOO_LONG_ERR,
	LINES_TOO_MANY_ERR,
	LINE_TOO_SHORT_ERR,
	LINES_TOO_LESS_ERR,
	FIFO_OVFLW_ERR,
	FIFO_UNFLW_ERR,
	ECC_1BIT_ERR,
	ECC_2BITS_ERR,
	SUBCH_DATA_ERR,
	SUBCH_REEN_ERR,
} VIU_ITU_ERR;

typedef struct {
	uint32_t  buff_addr;
	uint16_t  tx_size;
	uint16_t  nmb_lines;
	uint16_t  nmb_pixells;
	uint16_t  frame_inc;
	uint8_t   alpha_val;
} DMA_CONFIG;

typedef struct {
	uint8_t  vsync;
	uint8_t  hsync;
} VIU_SYNC_STATUS;

/************************************************
    VIULITE IOCTL function codes
*************************************************/

/********   Set Data Input Format   *************/
#define VIULITE_IOCTL_SET_VIDEOIN_FORMAT        3

/********   Get Data Input Format   *************/
#define VIULITE_IOCTL_GET_VIDEOIN_FORMAT       10

/***********    Set Data Interface   ************/
#define VIULITE_IOCTL_SET_DATA_INTERFACE       15

/***********    Get Data Interface   ************/
#define VIULITE_IOCTL_GET_DATA_INTERFACE       16

/********   DMA Configuring   *******************/
#define VIULITE_IOCTL_DMA_CONFIG                1

/********   DMA Start         *******************/
#define VIULITE_IOCTL_DMA_START                 2

/********   DMA Get Status    *******************/
#define VIULITE_IOCTL_DMA_GET_STATUS            4

/******   Get Interrupt Status Flags   **********/
#define VIULITE_IOCTL_GET_IRQSTATUS            12

/*******   Reset Interrupt Status Flags    ******/
#define VIULITE_IOCTL_RESET_IRQSTATUS          14

/********   Set ITU Error Code    ***************/
#define VIULITE_IOCTL_SET_ITU_ERRCODE           5

/********   Get ITU Error Code    ***************/
#define VIULITE_IOCTL_GET_ITU_ERRCODE           9

/********      Get Field Number   ***************/
#define VIULITE_IOCTL_GET_FIELDNUM              6

/*********  Get Sync Signals Status   ***********/
#define VIULITE_IOCTL_GET_SYNC                  7

/****************    Sw Reset    ****************/
#define VIULITE_IOCTL_SW_RESET                  8

/*****   Get Frame Size: lines and pixels   *****/
#define VIULITE_IOCTL_GET_FRAME_SIZE           11

/*********   Set Clipping Data    ***************/
#define VIULITE_IOCTL_SET_CLIPPING             17

/*********   Get Clipping Data    ***************/
#define VIULITE_IOCTL_GET_CLIPPING             18


/************************************************
    VIULITE Registers Offset
*************************************************/
#define SCR_OFFSET                      (0x00)
#define INTR_OFFSET                     (0x04)
#define DMA_SIZE_OFFSET                 (0x10)
#define DMA_ADDR_OFFSET                 (0x14)
#define DMA_INC_OFFSET                  (0x18)
#define INVSZ_OFFSET                    (0x1C)
#define ALPHA_OFFSET                    (0x24)
#define ACTORG_OFFSET                   (0x28)
#define ACTSIZE_OFFSET                  (0x2C)

#define SCR_VSYNC_OFFSET                  30
#define SCR_VSYNC_MASK          (uint32_t)(1 << SCR_VSYNC_OFFSET)
#define SCR_HSYNC_OFFSET                  29
#define SCR_HSYNC_MASK          (uint32_t)(1 << SCR_HSYNC_OFFSET)
#define SCR_FIELDNO_OFFSET                28
#define SCR_FIELDNO_MASK        (uint32_t)(1 << SCR_FIELDNO_OFFSET)
#define SCR_ACT_OFFSET                    27
#define SCR_DMA_ACT_MASK        (uint32_t)(1 << SCR_ACT_OFFSET)
#define SCR_ITUMODE_OFFSET                13
#define SCR_ITU_MODE_MASK       (uint32_t)(1 << SCR_ITUMODE_OFFSET)
#define SCR_CPP_OFFSET                    11
#define SCR_CPP_MASK            (uint32_t)(3 << SCR_CPP_OFFSET)
#define SCR_INWIDTH_OFFSET                 8
#define SCR_INWIDTH_MASK        (uint32_t)(7 << SCR_INWIDTH_OFFSET)
#define SCR_PCLK_POL_OFFSET                6
#define SCR_PCLK_POL_MASK       (uint32_t)(1 << SCR_PCLK_POL_OFFSET)
#define SCR_VSYNC_POL_OFFSET               5
#define SCR_VSYNC_POL_MASK      (uint32_t)(1 << SCR_VSYNC_POL_OFFSET)
#define SCR_HSYNC_POL_OFFSET               4
#define SCR_HSYNC_POL_MASK      (uint32_t)(1 << SCR_HSYNC_POL_OFFSET)
#define SCR_ECCEN_OFFSET                   2
#define SCR_ECCEN_MASK          (uint32_t)(1 << SCR_ECCEN_OFFSET)
#define SCR_ENDIANNESS_OFFSET               1
#define SCR_ENDIANNESS_MASK      (uint32_t)(1 << SCR_ENDIANNESS_OFFSET)
#define SCR_SWRESET_MASK        ((uint32_t)1)

#define INTR_ITUERR_OFFSET                28
#define INTR_ITUERR_MASK        (uint32_t)(0x0F << INTR_ITUERR_OFFSET)
#define INTR_STATUS_OFFSET                16
#define INTR_STATUS_MASK        (uint32_t)(0xFF << INTR_STATUS_OFFSET)
#define INTR_FIELD_BIT          (uint32_t)(0x01)
#define INTR_VSYNC_BIT          (uint32_t)(0x02)
#define INTR_HSYNC_BIT          (uint32_t)(0x04)
#define INTR_VSTART_BIT         (uint32_t)(0x08)
#define INTR_DMA_END_BIT        (uint32_t)(0x10)
#define INTR_ERR_BIT            (uint32_t)(0x20)
#define INTR_LINE_END_BIT       (uint32_t)(0x40)
#define INTR_FRAME_END_BIT      (uint32_t)(0x80)

#define MAX_ALPHA_VAL                  (0x0100)
#define CLIPP_HIGH16_MASK          (0xFFFF0000)
#define CLIPP_LOW16_MASK           (0x0000FFFF)

#endif /* FSL_VIULITE_IOCTL_H */
