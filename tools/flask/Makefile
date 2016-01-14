XEN_ROOT = $(CURDIR)/../..
include $(XEN_ROOT)/tools/Rules.mk

SUBDIRS-y := utils policy

.PHONY: all clean install distclean
all clean install distclean: %: subdirs-%

