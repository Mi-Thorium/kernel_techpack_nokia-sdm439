ifeq ($(CONFIG_MACH_NOKIA_SDM439),y)
obj-$(CONFIG_MACH_NOKIA_SDM439) += mach/

obj-$(CONFIG_FB_MSM_MDSS) += display/
obj-y += fingerprint/
obj-$(CONFIG_INPUT_TOUCHSCREEN) += touchscreen/
else
ccflags-y := -Wno-unused-function
obj-y := stub.o
endif
