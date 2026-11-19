
ifeq ($(CONFIG_SAMSUNG_PRODUCT_SHIP), y)
  obj-$(CONFIG_TOUCHSCREEN_SEC_TS_Y79A_C)   += sec_ts.o sec_ts_fw.o sec_ts_fn.o sec_ts_ioctl.o
else
  obj-$(CONFIG_TOUCHSCREEN_SEC_TS_Y79A_C)   += sec_ts.o sec_ts_fw.o sec_ts_fn.o sec_ts_ioctl.o sec_ts_only_vendor.o
endif
ccflags-$(CONFIG_SAMSUNG_TUI)	+= -Idrivers/misc/tui
ccflags-y += -Wformat

# Unified kernel: keep Y79A_C symbols distinct from the Y79A driver.
ccflags-y += -include $(srctree)/drivers/input/touchscreen/sec_ts/y79a_c/sec_ts_rename.h
