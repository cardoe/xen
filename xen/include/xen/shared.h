#ifndef __XEN_SHARED_H__
#define __XEN_SHARED_H__

#ifdef CONFIG_COMPAT

#include <compat/xen.h>

/*
 * This the same as compat_shared_info expect there are additional
 * (larger) arrays for up to 128 event channel pending and mask words,
 * allowing for up to 4096 event channels (32x128).
 *
 * This is used for dom0 only (hence the name).
 *
 * FIXME: There is no way to turn this feature on and there is no way
 * to notify the dom0 kernel that this feature is used, so this
 * version of Xen requries a matched dom0 kernel.
 */
struct compat0_shared_info {
    struct compat_vcpu_info vcpu_info[COMPAT_LEGACY_MAX_VCPUS];
    unsigned int domu_evtchn_pending[sizeof(unsigned int) * 8];
    unsigned int domu_evtchn_mask[sizeof(unsigned int) * 8];

    uint32_t wc_version;
    uint32_t wc_sec;
    uint32_t wc_nsec;

    struct compat_arch_shared_info arch;

    unsigned int evtchn_pending[128]; /* 32x128 = 4096 event channels */
    unsigned int evtchn_mask[128];    /* 32x128 = 4096 event channels */

    /*
     * These two fields are for use by the guest kernel only.  They
     * may be set to to point the currently active set of pending and
     * mask arrays (depending on whether it is dom0 or a domU).
     */
    unsigned int *evtchn_pending_ptr;
    unsigned int *evtchn_mask_ptr;
};

typedef union {
    struct shared_info native;
    struct compat_shared_info compat;
    struct compat0_shared_info compat0; /* for 32-bit dom0 with 4096 event channels */
} shared_info_t;

/*
 * Compat field is never larger than native field, so cast to that as it
 * is the largest memory range it is safe for the caller to modify without
 * further discrimination between compat and native cases.
 */
#define __shared_info(d, s, field)                      \
    (*(!has_32bit_shinfo(d) ?                           \
       (typeof(&(s)->compat.field))&(s)->native.field : \
        ((d)->domain_id == 0 ?                             \
            (typeof(&(s)->compat.field))&(s)->compat0.field : \
            (typeof(&(s)->compat.field))&(s)->compat.field    \
        )  \
    ))

typedef union {
    struct vcpu_info native;
    struct compat_vcpu_info compat;
} vcpu_info_t;

/* As above, cast to compat field type. */
#define __vcpu_info(v, i, field)                        \
    (*(!has_32bit_shinfo((v)->domain) ?                 \
       (typeof(&(i)->compat.field))&(i)->native.field : \
       &(i)->compat.field))

#else

typedef struct shared_info shared_info_t;
#define __shared_info(d, s, field) ((s)->field)

typedef struct vcpu_info vcpu_info_t;
#define __vcpu_info(v, i, field)   ((i)->field)

#endif

extern vcpu_info_t dummy_vcpu_info;

#define shared_info(d, field)      __shared_info(d, (d)->shared_info, field)
#define vcpu_info(v, field)        __vcpu_info(v, (v)->vcpu_info, field)

#endif /* __XEN_SHARED_H__ */
