VER 		= 1
PATCHLEVEL 	= 0

TARGET = z180

export AS
export CC

include arch/$(TARGET)/rules.mk

CSRCS = init/main.c init/version.c
CSRCS += kernel/dma.c kernel/exit.c kernel/fork.c kernel/panic.c kernel/printk.c kernel/sched.c kernel/signal.c kernel/time.c kernel/uname.c

LIBSRCS = lib/ctype.c lib/string/strlen.c lib/stdlib/sprintf.c

AOBJS = $(ASRCS:.s=.rel)
COBJS = $(CSRCS:.c=.rel)
LIBOBJS = $(LIBSRCS:.c=.rel)

OBJS = $(AOBJS) $(COBJS)

all: ver $(LIBOBJS) include/sys/version.h $(OBJS) cstd.lib zenix.ihx

ver: dummy
	rm -f include/sys/version.h

$(AOBJS): %.rel: %.s
	$(AS) $(ASFLAGS) $<

$(COBJS): %.rel: %.c
	$(CC) $(CFLAGS) $<

$(LIBOBJS): %.rel: %.c
	$(CC) $(CFLAGS) $<

include/sys/version.h: dummy
	@if [ ! -f .version ]; then \
		echo 1 > .version; \
	else \
		expr 0`cat .version` + 1 > .version; \
	fi
	@if [ -f .name ]; then \
		echo \#define UTS_VERSION \"\#$(VER)-`cat .name` `date`\"; \
	else \
		echo \#define UTS_VERSION \"\#$(VER) `date`\"; \
	fi >> .ver
	@echo \#define UTS_RELEASE \"$(VER).$(PATCHLEVEL).`cat .version`\" >> .ver
	@echo \#define ZENIX_COMPILE_TIME \"`date +%T`\" >> .ver
	@echo \#define ZENIX_COMPILE_BY \"`whoami`\" >> .ver
	@echo \#define ZENIX_COMPILER \"$(CC)\" >> .ver
	@mv -f .ver $@

cstd.lib:
	$(AR) -rc cstd.lib ctype.rel strlen.rel sprintf.rel

zenix.ihx: arch/$(TARGET)/zenix.lnk
	$(LD) $(LDFLAGS) arch/$(TARGET)/zenix.lnk -L cstd

clean: 
	rm -f .version include/sys/version.h
	rm -f *~ *.rel *.asm *.lst *.sym *.o *.map *.noi *.bin *.lk *.rst *.cdb *.ihx *.lib
	rm -f arch/$(TARGET)/*.rel arch/$(TARGET)/*.asm arch/$(TARGET)/*.lst arch/$(TARGET)/*.sym arch/$(TARGET)/*.rst
	rm -f zenix

dummy: