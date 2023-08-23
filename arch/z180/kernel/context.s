    .module context
    .z180

    .globl _context_get_sp
    .globl _context_set_sp

    .area _CODE

_context_get_sp:
    ld ix, #0 
    ex de, hl 
    add ix, de 
    ld e, -10 (ix)
    ld d, -11 (ix)

    ret

_context_set_sp:
    ld ix, #0 
    ld c, l 
    ld b, h 
    add ix, bc 
    ld - 10(ix), e 
    ld - 11(ix), d

    ret