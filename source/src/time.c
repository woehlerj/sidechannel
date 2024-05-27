#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <err.h>


// Override __stack_chk_fail to suppress stack smashing messages
void __stack_chk_fail(void) {
    // Do nothing or handle the error as you wish
    printf("Thank you for submitting feedback\n");
    exit(EXIT_FAILURE);
}
void start() {
  printf("Welcome to Cafe Grazie\n");
  printf("Please enter your feedback:\n");

  char buf[32];
  memset(buf, 0, sizeof(buf));
  read(0, buf, 256);
  return;
}

int main(int argc, char *argv[])
{
  setregid(getegid(), getegid());
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);

  start();
  usleep(500000);
  printf("Thank you for submitting feedback\n");
  return 0;
}
