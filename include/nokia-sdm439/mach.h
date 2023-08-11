#ifndef _NOKIA_SDM439_MACH_H
#define _NOKIA_SDM439_MACH_H

enum nokia_sdm439_mach_types {
	NOKIA_SDM439_MACH_UNKNOWN = 0,

	NOKIA_SDM439_MACH_DEADPOOL,
	NOKIA_SDM439_MACH_PANTHER,

	NOKIA_SDM439_MACH_MAX,
};

#if IS_ENABLED(CONFIG_MACH_NOKIA_SDM439)
extern enum nokia_sdm439_mach_types nokia_sdm439_mach_get(void);
#else
static inline enum nokia_sdm439_mach_types nokia_sdm439_mach_get(void) { return NOKIA_SDM439_MACH_UNKNOWN; }
#endif

#endif
