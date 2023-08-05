export AS=sdasz80
export CC=sdcc
export CFLAGS=-c --std-sdcc99 --no-std-crt0 -m$(TARGET) -I$(ROOT_DIR)/arch/$(TARGET) -I$(ROOT_DIR)/include --opt-code-size --constseg CONST