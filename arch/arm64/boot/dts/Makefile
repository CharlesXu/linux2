dtb-$(CONFIG_ARCH_THUNDER) += thunder-88xx.dtb
dtb-$(CONFIG_ARCH_VEXPRESS) += rtsm_ve-aemv8a.dtb foundation-v8.dtb A53.dtb
dtb-$(CONFIG_ARCH_S32) += s32v234-evb.dtb
dtb-$(CONFIG_ARCH_S32) += s32v234-evbbcm.dtb
dtb-$(CONFIG_ARCH_S32) += s32v234-palladium.dtb
dtb-$(CONFIG_ARCH_S32) += s32v234-pcie.dtb
dtb-$(CONFIG_ARCH_S32) += s32v234-simulator.dtb
dtb-$(CONFIG_ARCH_S32) += s32v234-tmdp.dtb
tb-$(CONFIG_ARCH_XGENE) += apm-mustang.dtb

targets += dtbs
targets += $(dtb-y)

dtbs: $(addprefix $(obj)/, $(dtb-y))

clean-files := *.dtb
