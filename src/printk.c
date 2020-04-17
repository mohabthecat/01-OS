/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Copyright 2020, Anuradha Weeraman
 */

#include <stdarg.h>
#include "printk.h"

// Reference: https://www.eskimo.com/~scs/cclass/int/sx11b.html
void printk(const char *fmt, ...) {
  const char *p;
  uint32_t ui;
  int32_t i;
  char *str;
  char print_buf[128];

  va_list arg;
  va_start(arg, fmt);

  for(p = fmt; *p != '\0'; p++) {
    if(*p != '%') {
      printc(*p);
      continue;
    }

    switch(*++p) {
      case 'c':
        i = va_arg(arg, int);
        printc(i);
        break;

      case 'd':
        i = va_arg(arg, int32_t);
        if (i < 0) {
          i *= -1;
          printc('-');
        }
        prints(uitoa((int32_t) i, print_buf, 10));
        break;

      case 's':
        str = va_arg(arg, char*);
        prints(str);
        break;

      case 'u':
        ui = va_arg(arg, uint32_t);
        prints(uitoa((uint32_t) ui, print_buf, 16));
        break;

      case '%':
        prints("%");
        break;
    }
  }

  va_end(arg);
}