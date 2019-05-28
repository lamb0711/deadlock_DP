#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <execinfo.h>
#include <pthread.h>

typedef struct t_hread *Thread;
Thread pthread_info;


int thr_num = 0;

int rockcount = 0;
int unrockcount = 0;
int total = 0;


int pthread_mutex_lock(pthread_mutex_t *mutex){
  int (*real_pthread_mutex_lock)(pthread_mutex_t *mutex);
  char * error ;

  real_pthread_mutex_lock = dlsym(RTLD_NEXT, "pthread_mutex_lock");

  if ((error = dlerror()) != 0x0)
		exit(1) ;
  int ptr = real_pthread_mutex_lock(mutex);
  rockcount++;
  total++;
  char buf[100];
  char buff[50];

	snprintf(buf, 100, "rock : mutex(%d)  thread(%d) , count : %d, total : %d\n",mutex,pthread_self(),rockcount,total) ;
  fputs(buf, stderr) ;
  int i = thr_num;

	return ptr ;

}

int pthread_mutex_unlock(pthread_mutex_t *mutex){
  int (*real_pthread_mutex_unlock)(pthread_mutex_t *mutex);
	char * error;

  real_pthread_mutex_unlock = dlsym(RTLD_NEXT, "pthread_mutex_unlock");
  if ((error = dlerror()) != 0x0)
		exit(1) ;
  int ptr = real_pthread_mutex_unlock(mutex);
 unrockcount++;
 total--;
  char buf[100];
  char buff[50];
  snprintf(buf, 100, "unrock : mutex(%d)  thread(%d) , count : %d,total : %d\n",mutex,pthread_self(),unrockcount,total) ;
  fputs(buf, stderr) ;

	return ptr;
}
