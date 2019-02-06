#include "defs.h"
typedef struct foo
{
	int x, y;
} my_state;
my_state state;

void update_state(my_state *ptr){
	ptr->x++;
	usleep(100000);
	ptr->y++;
}

void compute_more(){
	usleep(100000);
}

void long_running_proc(){
	int i = 0;
	for (i = 0; i < 100; i++){
		update_state(&state);
		compute_more;
	}
}

void display(my_state *ptr){
	printf("x = %1d\n", ptr->x);
	usleep(1000);
	printf("y = %1d\n", ptr->y);
}

void handler(int signo){
	display(&state);
}

int main(){
	state.x = state.y = 0;
	sigset(SIGINT, handler);
	long_running_proc();
	return 0;
}

