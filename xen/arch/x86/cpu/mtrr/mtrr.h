/*
 * local mtrr defines.
 */

#define MTRR_CHANGE_MASK_FIXED     0x01
#define MTRR_CHANGE_MASK_VARIABLE  0x02
#define MTRR_CHANGE_MASK_DEFTYPE   0x04

void mtrr_generic_get(unsigned int reg, unsigned long *base,
        unsigned long *size, mtrr_type *type);
int mtrr_generic_get_free_region(unsigned long base, unsigned long size,
        int replace_reg);
int mtrr_generic_validate_add_page(unsigned long base, unsigned long size,
        unsigned int type);
void mtrr_generic_set_all(void);
void mtrr_generic_set(unsigned int reg, unsigned long base,
        unsigned long size, mtrr_type type);
int mtrr_generic_have_wrcomb(void);

void get_mtrr_state(void);

extern u64 size_or_mask, size_and_mask;

extern unsigned int num_var_ranges;

void mtrr_state_warn(void);
