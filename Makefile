ifeq ($(CONFIG_MACH_NOKIA_SDM439),y)
obj-$(CONFIG_MACH_NOKIA_SDM439) += mach/

else
ccflags-y := -Wno-unused-function
obj-y := stub.o
endif
