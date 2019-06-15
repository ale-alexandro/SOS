#include <rtc.h>
#include <libk/stdlib.h>
#define CURRENT_YEAR 2017// Change this each year!
#define UTC 3

int century_register = 0x00;

enum {
      cmos_address = 0x70,
      cmos_data    = 0x71
};

int get_update_in_progress_flag() {
      outb(cmos_address, 0x0A);
      int a;
      inb(cmos_data, a);
      return a & 0x80;
}

unsigned char get_RTC_register(int reg) {
      outb(cmos_address, reg);
      int a;
      inb(cmos_data, a);
      return a;
}

time_t read_rtc() {
      time_t tm;
      unsigned char century;
      unsigned char last_second;
      unsigned char last_minute;
      unsigned char last_hour;
      unsigned char last_day;
      unsigned char last_month;
      unsigned char last_year;
      unsigned char last_century;
      unsigned char registerB;

      // Note: This uses the "read registers until you get the same values twice in a row" technique
      //       to avoid getting dodgy/inconsistent values due to RTC updates

      while (get_update_in_progress_flag());                // Make sure an update isn't in progress
      tm.second = get_RTC_register(0x00);
      tm.minute = get_RTC_register(0x02);
      tm.hour = get_RTC_register(0x04);
      tm.day = get_RTC_register(0x07);
      tm.month = get_RTC_register(0x08);
      tm.year = get_RTC_register(0x09);
      if(century_register != 0) {
            century = get_RTC_register(century_register);
      }

      do {
            last_second = tm.second;
            last_minute = tm.minute;
            last_hour = tm.hour;
            last_day = tm.day;
            last_month = tm.month;
            last_year = tm.year;
            last_century = century;

            while (get_update_in_progress_flag());           // Make sure an update isn't in progress
            tm.second = get_RTC_register(0x00);
            tm.minute = get_RTC_register(0x02);
            tm.hour = get_RTC_register(0x04);
            tm.day = get_RTC_register(0x07);
            tm.month = get_RTC_register(0x08);
            tm.year = get_RTC_register(0x09);
            if(century_register != 0) {
                  century = get_RTC_register(century_register);
            }
      } while( (last_second != tm.second) || (last_minute != tm.minute) || (last_hour != tm.hour) ||
               (last_day != tm.day) || (last_month != tm.month) || (last_year != tm.year) ||
               (last_century != century) );

      registerB = get_RTC_register(0x0B);

      // Convert BCD to binary values if necessary

      if (!(registerB & 0x04)) {
            tm.second = (tm.second & 0x0F) + ((tm.second / 16) * 10);
            tm.minute = (tm.minute & 0x0F) + ((tm.minute / 16) * 10);
            tm.hour = ( (tm.hour & 0x0F) + (((tm.hour & 0x70) / 16) * 10) ) | (tm.hour & 0x80);
            tm.day = (tm.day & 0x0F) + ((tm.day / 16) * 10);
            tm.month = (tm.month & 0x0F) + ((tm.month / 16) * 10);
            tm.year = (tm.year & 0x0F) + ((tm.year / 16) * 10);
            if(century_register != 0) {
                  century = (century & 0x0F) + ((century / 16) * 10);
            }
      }

      // Convert 12 hour clock to 24 hour clock if necessary

      if (!(registerB & 0x02) && (tm.hour & 0x80)) {
            tm.hour = ((tm.hour & 0x7F) + 12) % 24;
      }

      // Calculate the full (4-digit) year

      if(century_register != 0) {
            tm.year += century * 100;
      } else {
            tm.year += (CURRENT_YEAR / 100) * 100;
            if(tm.year < CURRENT_YEAR) tm.year += 100;
      }

      tm.hour += UTC;
      if(tm.hour >= 24)
      {
	tm.hour -= 24;
        tm.day++;
      }
      return tm;
}
