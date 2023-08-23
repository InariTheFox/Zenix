# Zenix
An 8-bit operating system that provides Unix System V/Linux capabilities.

## Summary

Zenix is an attempt to create a *nix like operating system from scratch that targets the Z80 and Z180 processors. Eventually, support for 8080 and other 8-bit systems will be added.

Unlike other systems which are built upon CP/M or utilize RomWBW for example, Zenix will utilize it's own BIOS and Boot Loader similar to GRUB.

## Requirements

- SDCC v4.2 or greater
- Make
- z80-pack from Udo Monk (debugging/simulation)

## Where things are now

Currently the operating system is in its infancy, and many things have yet to be even built.

Right now, the system is dependent upon Udo Monk's z80-pack simulator to run.

## Where things are going

### Features wanted

- Bourne-like shell
- Full GNU-lib C library
- Modular driver system
  with Support for the following hardware:
    - Z180 UART (CSIO)
    - Z180 DMA
    - Z180 MMU
    - Z80 SIO
    - Z80 PIO
    - Z80 CTC
    - Z80 DART (Dual UART)
    - Z80 DMA
    - Ti 74x610/611/612/613 MMU
    - 8250 UART
    - 16550 UART
    - 6551 UART
    - Yamaha OPL Sound Generators
    - TMS9918 Video Display Processor
    - Yamaha V9938/58 Video Display Processors
    - NEC uPD7220 Graphics Display Controller
    - Propeller Microcontroller (as GPU)
    - IDE hard disk drives
    - 5-1/4" and 3-1/2" floppy disk drives
    - SPI and I2C support
    - PS/2 support for keyboards and mice
- GCC like compiler