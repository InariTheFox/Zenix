        .module crt0
        .z180

        .area _CODE
        .area _HOME
        .area _CODE2
        .area _CONST
        .area _GSINIT
        .area _GSFINAL
        .area _INITIALIZED
        .area _DATA
        .area _BSEG
        .area _BSS
        .area _HEAP
        .area _BUFFERS
        .area _DISCARD
        .area _COMMONMEM
        .area _INITIALIZER

        .globl _main
        .globl s__INITIALIZER
        .globl s__COMMONMEM
        .globl l__COMMONMEM
        .globl s__DISCARD
        .globl l__DISCARD
        .globl s__DATA
        .globl l__DATA
        .globl kstack_top

        .area _CODE
init:
        di

	    ld	a,#0xFE
	    out	(0x0D),a
        ld	sp, #kstack_top

        ; move the common memory where it belongs
        ld	hl, #s__DATA
        ld	de, #s__COMMONMEM
        ld	bc, #l__COMMONMEM
        ldir

         ; and the discard
        ld	de, #s__DISCARD
        ld	bc, #l__DISCARD-1
        add	hl,bc
        ex	de,hl
        add	hl,bc
        ex	de,hl
        inc	bc
        lddr

        ; then zero the data area
        ld	hl, #s__DATA
        ld	de, #s__DATA + 1
        ld	bc, #l__DATA - 1
        ld	(hl), #0
        ldir

        call _main

        di
stop:   halt
        jr stop