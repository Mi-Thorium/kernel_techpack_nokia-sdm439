#include <linux/export.h>
#include <linux/kobject.h>
#include <linux/init.h>
#include <linux/of.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <nokia-sdm439/mach.h>

typedef struct nokia_sdm439_mach_info {
	const char *codename;
} nokia_sdm439_mach_info_t;

static const nokia_sdm439_mach_info_t nokia_sdm439_mach_table[NOKIA_SDM439_MACH_MAX] = {
	[NOKIA_SDM439_MACH_DEADPOOL] = {"deadpool"},
	[NOKIA_SDM439_MACH_PANTHER] = {"panther"},
};

const char *nokia_sdm439_variant_str = NULL;
static enum nokia_sdm439_mach_types saved_mach = NOKIA_SDM439_MACH_UNKNOWN;
static struct kobject *nokia_sdm439_mach_kobj;

enum nokia_sdm439_mach_types nokia_sdm439_mach_get(void) {
	return saved_mach;
}
EXPORT_SYMBOL(nokia_sdm439_mach_get);

static ssize_t nokia_sdm439_mach_codename_show(struct kobject *kobj,
						struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%s\n", nokia_sdm439_mach_table[saved_mach].codename);
}

static struct kobj_attribute nokia_sdm439_mach_codename_attr = {
	.attr = {
		.name = "codename",
		.mode = 0444,
	},
	.show = nokia_sdm439_mach_codename_show,
};

static bool nokia_sdm439_mach_detect(void) {
	int i, rc;
	char of_compatible[32];

	for (i=1; i<NOKIA_SDM439_MACH_MAX; ++i) {
		snprintf(of_compatible, sizeof(of_compatible), "nokia,%s", nokia_sdm439_mach_table[i].codename);
		rc = of_machine_is_compatible(of_compatible);
		if (rc) {
			saved_mach = i;
			return true;
		}
	}

	pr_err("%s: Unrecognized Nokia SDM439 machine\n", __func__);
	return false;
}

static int __init nokia_sdm439_mach_detect_init(void) {
	int rc;

	// Detect
	rc = nokia_sdm439_mach_detect();
	if (!rc) {
		pr_err("%s: Could not detect Nokia SDM439 machine\n", __func__);
		goto fail;
	}

	// Print the current machine
	pr_info("%s: Current machine: %s (%s)\n", __func__,
			nokia_sdm439_mach_table[saved_mach].codename,
			nokia_sdm439_variant_str);

	// Create sysfs dir
	nokia_sdm439_mach_kobj = kobject_create_and_add("nokia-sdm439-mach", NULL);
	if (!nokia_sdm439_mach_kobj) {
		pr_err("%s: Failed to create sysfs dir\n", __func__);
		goto fail;
	}

	// Create sysfs files
	rc = sysfs_create_file(nokia_sdm439_mach_kobj,
			&nokia_sdm439_mach_codename_attr.attr);
	if (rc < 0)
		pr_err("%s: Failed to create sysfs file codename, rc=%d\n", __func__, rc);

	return 0;
fail:
	return rc;
}
core_initcall(nokia_sdm439_mach_detect_init);
