#ifndef KTIME_H
#define KTIME_H

typedef struct
{
  unsigned char second;
  unsigned char minute;
  unsigned char hour;
  unsigned char day;
  unsigned char month;
  unsigned int year;
} time_t;

time_t read_rtc();

#endif
