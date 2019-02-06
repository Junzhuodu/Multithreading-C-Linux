#include "defs.h"
void handler(int signo)
{
  printf("Got signal %1d.  Whoopee!!\n", signo);
}
int main(int argc, char *argv[])
{
  sigset(SIGINT, handler);
  for (;;) { }
  return 1;
}