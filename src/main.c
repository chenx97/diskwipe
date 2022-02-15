#include <fcntl.h>
#include <math.h>
#include <nproc.h>
#include <pthread.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

int64_t buf[1024];
pthread_t *threads;
int running = 1;

void cleanup(int val)
{
  if (running)
  {
    printf("\nGraceful shutdown...\n");
    fflush(stdout);
    running = 0;
  }
  else
    exit(130);
}

void *write_data(void *num)
{
  int id = (size_t)num;
  size_t str_len = (log10(id + 1) + 1) + 4;
  char *filename = malloc(str_len + 1);
  sprintf(filename, "dump%d", id);

  FILE *fd = fopen(filename, "w");

  while (running)
  {
    fwrite(buf, sizeof(buf), 1, fd);
  }
  fclose(fd);
  free(filename);
  return NULL;
}

int main()
{
  signal(SIGINT, cleanup);
  for (int i = 0; i < 1024; i++)
  {
    buf[i] = -1;
  }
  size_t nproc = get_nproc();
  if (nproc < 1)
  {
    exit(EXIT_FAILURE);
  }

  threads = malloc(nproc * sizeof(pthread_t));
  printf("Using %ld threads to write to your disk drive\n", nproc);

  for (int i = 0; i < nproc; i++)
  {
    pthread_create(&threads[i], NULL, write_data, (void *)(size_t)i);
  }
  for (int i = 0; i < nproc; i++)
  {
    pthread_join(threads[i], NULL);
  }
  free(threads);
  return 0;
}
