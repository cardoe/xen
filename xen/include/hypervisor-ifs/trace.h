/******************************************************************************
 * include/hypervisor-ifs/trace.h
 */

#ifndef __HYPERVISOR_IFS_TRACE_H__
#define __HYPERVISOR_IFS_TRACE_H__

/* This structure represents a single trace buffer record. */
struct t_rec {
    u64 cycles;               /* 64 bit cycle counter timestamp */
    u32 event;                /* 32 bit event ID                */
    u32 d1, d2, d3, d4, d5;   /* event data items               */
};

/*
 * This structure contains the metadata for a single trace buffer.  The head
 * field, indexes into an array of struct t_rec's.
 */
struct t_buf {
    struct t_rec *data;     /* pointer to data area.  physical address
                             * for convenience in user space code            */

    unsigned int size;      /* size of the data area, in t_recs              */
    unsigned int head;      /* array index of the most recent record         */

#ifdef __KERNEL__
    struct t_rec *head_ptr; /* pointer to the head record                    */
    struct t_rec *vdata;    /* virtual address pointer to data               */
    spinlock_t lock;        /* ensure mutually exlusive access (for inserts) */
#endif

    /* never add anything here - the kernel stuff must be the last elements */
};

#endif /* __HYPERVISOR_IFS_TRACE_H__ */
