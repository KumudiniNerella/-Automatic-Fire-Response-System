// Copyright (c) 2014 Adafruit Industries
// Author: Tony DiCola

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef COMMON_DHT_READ_H
#define COMMON_DHT_READ_H

#include <stdint.h>
#include "bbb_dht_read.h"
#include <unistd.h>
// Define errors and return values.
#define DHT_ERROR_TIMEOUT -1
#define DHT_ERROR_CHECKSUM -2
#define DHT_ERROR_ARGUMENT -3
#define DHT_ERROR_GPIO -4
#define DHT_SUCCESS 0

// Define sensor types.
#define DHT11 11
#define DHT22 22
#define AM2302 22


//Definitions to solve timercmp error
#define timerisset(tvp)   ((tvp)->tv_sec || (tvp)->tv_usec)
#define timerclear(tvp)   ((tvp)->tv_sec = (tvp)->tv_usec = 0)
#define timercmp(a, b, CMP)                        \
  (((a)->tv_sec == (b)->tv_sec) ?                  \
   ((a)->tv_usec CMP (b)->tv_usec) :               \
   ((a)->tv_sec CMP (b)->tv_sec))
#define timeradd(a, b, result)                  \
  do {                                                    \
    (result)->tv_sec = (a)->tv_sec + (b)->tv_sec;             \
    (result)->tv_usec = (a)->tv_usec + (b)->tv_usec;          \
    if ((result)->tv_usec >= 1000000)                         \
      {                                                       \
        ++(result)->tv_sec;                                   \
        (result)->tv_usec -= 1000000;                         \
      }                                                       \
  } while (0)
#define timersub(a, b, result)                  \
  do {                                                    \
    (result)->tv_sec = (a)->tv_sec - (b)->tv_sec;             \
    (result)->tv_usec = (a)->tv_usec - (b)->tv_usec;          \
    if ((result)->tv_usec < 0) {                              \
      --(result)->tv_sec;                                     \
      (result)->tv_usec += 1000000;                           \
    }                                                         \
  } while (0)

//End Definitions to solve timercmp error



// Busy wait delay for most accurate timing, but high CPU usage.
// Only use this for short periods of time (a few hundred milliseconds at most)!
void busy_wait_milliseconds(uint32_t millis);

// General delay that sleeps so CPU usage is low, but accuracy is potentially bad.
void sleep_milliseconds(uint32_t millis);

// Increase scheduling priority and algorithm to try to get 'real time' results.
void set_max_priority(void);

// Drop scheduling priority back to normal/default.
void set_default_priority(void);

int readRetry(int sensore,int gpio_base,int gpio_number,float *umidit,float * temper);
#endif
