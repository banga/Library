#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define MT 1

#define MAXQ 100000
int q_in[MAXQ], q_out[MAXQ];
int q_in_cnt = 0, q_out_cnt = 0;
pthread_mutex_t q_in_mutex = PTHREAD_MUTEX_INITIALIZER;

void* process(void*) {
  clock_t t = clock();
#if MT
  pthread_mutex_lock(&q_in_mutex);
#endif
  for(int i = 0; i < q_in_cnt; i++) {
    float s = 0;
    for(float e = 0; e < 10; e += 0.1f)
      s += pow(q_in[i], e);
    q_out[i] = (int)s;
  }
  q_out_cnt = q_in_cnt;
#if MT
  pthread_mutex_unlock(&q_in_mutex);
#endif
  printf("process: %.2fs\n", (clock()-t) / (float)CLOCKS_PER_SEC);

  return NULL;
}

void process2() {
  clock_t t = clock();
  float a[MAXQ];
  for(int i = 0; i < MAXQ; i++) {
    for(int k = 1; k <= 50; k++)
      a[i] += sin(i) * cos(k*i) - cos(i) * sin(k*i);
  }
  printf("process2: %.2fs\n", (clock()-t) / (float)CLOCKS_PER_SEC);
}

void doImage() {
  clock_t t = clock();
#if MT
  pthread_t processThread;
#endif

  /* Fill in the data to process parallely */
#if MT
  pthread_mutex_lock(&q_in_mutex);
  pthread_create(&processThread, NULL, process, NULL);
#endif

  for(int i = 0; i < MAXQ; i++)
    q_in[i] = i+1;
  q_in_cnt = MAXQ;
#if MT
  pthread_mutex_unlock(&q_in_mutex);
#else
  process(NULL);
#endif

  process2();

#if MT
  pthread_join(processThread, NULL);
#endif

  printf("doImage: %.2fs\n", (clock()-t) / (float)CLOCKS_PER_SEC);
  return;
}

int main() {
  doImage();

  return 0;
}
