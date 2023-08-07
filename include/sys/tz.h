#ifndef __SYS_TZ_H__
#define __SYS_TZ_H__

#define SECSPERMIN   60
#define MINSPERHOUR  60
#define HOURSPERDAY  24
#define DAYSPERWEEK  7
#define DAYSPERNYEAR 365
#define DAYSPERLYEAR 366
#define SECSPERHOUR  3600
#define SECSPERDAY   86400
#define MONSPERYEAR  12

#define TM_SUNDAY    0
#define TM_MONDAY    1
#define TM_TUESDAY   2
#define TM_WEDNESDAY 3
#define TM_THURSDAY  4
#define TM_FRIDAY    5
#define TM_SATURDAY  6

#define TM_JANUARY   0
#define TM_FEBRUARY  1
#define TM_MARCH     2
#define TM_APRI      3
#define TM_MAY       4
#define TM_JUNE      5
#define TM_JULY      6
#define TM_AUGUST    7
#define TM_SEPTEMBER 8
#define TM_OCTOBER   9
#define TM_NOVEMBER  10
#define TM_DECEMBER  11

#define TM_YEAR_BASE 1900
#define EPOCH_YEAR   1970
#define EPOCH_WDAY   TM_THURSDAY

#define isleap(y) (((y) % 4) == 0 && (((y) % 100) != 0 || ((y) % 400) == 0))

#define isleap_sum(a, b) isleap((a) % 400 + (b) % 400)

#endif