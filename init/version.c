#include "sys/version.h"
#include "sys/utsname.h"

#define version(a)        Version_##a
#define version_string(a) version(a)

const char *banner = 
    "Zenix version " UTS_RELEASE " (" ZENIX_COMPILE_BY "@" ZENIX_COMPILE_TIME ") (" ZENIX_COMPILER ")" UTS_VERSION "\n";