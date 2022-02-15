#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_nproc()
{
  long nprocs = -1;
  long nprocs_max = -1;
#ifdef _WIN32
#ifndef _SC_NPROCESSORS_ONLN
  SYSTEM_INFO info;
  GetSystemInfo(&info);
#define sysconf(a) info.dwNumberOfProcessors
#define _SC_NPROCESSORS_ONLN
#endif
#endif
#ifdef _SC_NPROCESSORS_ONLN
  nprocs = sysconf(_SC_NPROCESSORS_ONLN);
  if (nprocs < 1)
  {
    fprintf(stderr, "Could not determine number of CPUs online:\n%s\n",
            strerror(errno));
    return -1;
  }
  nprocs_max = sysconf(_SC_NPROCESSORS_CONF);
  if (nprocs_max < 1)
  {
    fprintf(stderr, "Could not determine number of CPUs configured:\n%s\n",
            strerror(errno));
    return -1;
  }
  return nprocs;
#else
  fprintf(stderr, "Could not determine number of CPUs");
  return -1;
#endif
}