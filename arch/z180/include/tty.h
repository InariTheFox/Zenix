#ifndef __ARCH_Z180_TTY_H__
#define __ARCH_Z180_TTY_H__

struct termio
{
    unsigned int iflag; /* input modes */
    unsigned int oflag; /* output modes */
    unsigned int cflag; /* control modes */
    unsigned int lflag; /* local modes */
};

#define S7N1 0x00 /* Start + 7-bit data + 1 stop */
#define S7N2 0x01 /* Start + 7-bit data + 2 stop */
#define S7P1 0x02 /* Start + 7-bit data + parity + 1 stop */
#define S7P2 0x03 /* Start + 7-bit data + parity + 2 stop */
#define S8N1 0x04 /* Start + 8-bit data + 1 stop */
#define S8N2 0x05 /* Start + 8-bit data + 2 stop */
#define S8P1 0x06 /* Start + 8-bit data + parity + 1 stop */
#define S8P2 0x07 /* Start + 8-bit data + parity + 2 stop */
#define MPBR 0x08 /* Mutli-Processor Bit Receive */
#define RTS0 0x10 /* Request to Send Channel 0 */
#define TE   0x20 /* Transmit Enable */
#define RE   0x40 /* Receive Enable */
#define MPE  0x80 /* Multi-Processor Mode Enable */

#define S1   0x00 /* ÷1 */
#define S2   0x01 /* ÷2 */
#define S4   0x02 /* ÷4 */
#define S8   0x03 /* ÷8 */
#define S16  0x04 /* ÷16 */
#define S32  0x05 /* ÷32 */
#define S64  0x06 /* ÷64 */
#define SEXT 0x07 /* External clock */
#define DR   0x80 /* Divide Ratio (÷64) */
#define PEO  0x10 /* Parity Odd */
#define PS   0x20 /* Prescale */
#define MP   0x40 /* Multi-Processor Mode */
#define MPBT 0x80 /* Multi-Processor Bit Transmit */

#define ECHO

#define TIOCM_LE  0x001
#define TIOCM_DTR 0x002
#define TIOCM_RTS 0x004
#define TIOCM_ST  0x008
#define TIOCM_SR  0x010
#define TIOCM_CTS 0x020
#define TIOCM_CAR 0x040
#define TIOCM_RNG 0x080
#define TIOCM_DSR 0x100

#endif