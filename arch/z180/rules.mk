export AS 		= sdasz80
export AR		= sdar
export CC 		= sdcc
export ASFLAGS 	= -plosff
export CFLAGS 	= -c --std-sdcc99 --no-std-crt0 --nostdlib --nostdinc --Werror -m$(TARGET) -Iarch/$(TARGET)/include -Iinclude --opt-code-size --constseg CONST
export LD 		= sdldz80
export LDFLAGS	= -f

ASRCS = arch/z180/crt0.s
CSRCS += arch/z180/kernel/out.c arch/z180/kernel/in.c
LIBSRCS += arch/z180/lib/itoa.c