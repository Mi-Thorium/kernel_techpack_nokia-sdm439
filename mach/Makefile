ifeq ($(shell test -d $(srctree)/arch/arm64/boot/dts/nokia-sdm439/.git; echo $$?),0)
NOKIA439_DT_GIT_VER := $(shell cd $(srctree)/arch/arm64/boot/dts/nokia-sdm439; /usr/bin/env PATH="$$PATH":/usr/bin:/usr/local/bin git rev-parse --short HEAD)
$(info - Nokia SDM439 device tree git version: $(NOKIA439_DT_GIT_VER))
ccflags-y += -DNOKIA439_DT_GIT_VER=\"$(NOKIA439_DT_GIT_VER)\"
else
ccflags-y += -DNOKIA439_DT_GIT_VER=\"Unknown\"
endif

ifeq ($(shell test -d $(srctree)/$(src)/../.git; echo $$?),0)
NOKIA439_MODULE_GIT_VER := $(shell cd $(srctree)/$(src); /usr/bin/env PATH="$$PATH":/usr/bin:/usr/local/bin git rev-parse --short HEAD)
$(info - Nokia SDM439 module git version: $(NOKIA439_MODULE_GIT_VER))
ccflags-y += -DNOKIA439_MODULE_GIT_VER=\"$(NOKIA439_MODULE_GIT_VER)\"
else
ccflags-y += -DNOKIA439_MODULE_GIT_VER=\"Unknown\"
endif

obj-$(CONFIG_MACH_NOKIA_SDM439) += mach_detect.o
