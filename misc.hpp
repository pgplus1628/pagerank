#pragma once 
#include <sys/time.h>

#define TIMER(val) do { \
  struct timeval tm; \
  gettimeofday(&tm, NULL); \
  val = tm.tv_sec * 1000 + tm.tv_usec/1000; \
} while(0)


