#include "defs.h"
typedef struct foo
{
	int x, y;	
} my_state;
my_state state;
sigset_t set;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void update_state(my_state *ptr){
	ptr->x++;
	usleep(100000);
	ptr->y++;
}

void compute_more(){
	usleep(100000);
}

void display(my_state *ptr){
	printf("x = %1d\n", ptr->x);
	usleep(1000);
	printf("y = %1d\n", ptr->y);
}

void long_running_proc(){
	int i = 0;
	for (i = 0; i < 100; i++){
		pthread_mutex_lock(&m);
		update_state(&state);
		pthread_mutex_unlock(&m);
		compute_more();
	}
}

void *monitor(void *arg){
	int sig = 0;
	for (;;){
		sigwait(&set, &sig);
		pthread_mutex_lock(&m);
		display(&state);
		pthread_mutex_unlock(&m);
	}
	return 0;
}

int main(){
	pthread_t thr;
	state.x = state.y = 0;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_BLOCK, &set, 0);
	pthread_create(&thr, 0, monitor, 0);
	long_running_proc();
	return 0;
}