#include "defs.h"
typedef struct foo
{
	int x, y;
} my_state;
my_state state;
sigset_t set;

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
		sigset_t old_set;
		sigprocmask(SIG_BLOCK, &set, &old_set);
		update_state(&state);
		sigprocmask(SIG_SETMASK, &old_set, 0);
		compute_more;
	}
}

void handler(int signo){
	display(&state);
}

int main(){
	state.x = state.y = 0;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigset(SIGINT, handler);
	long_running_proc();
	return 0; 
}