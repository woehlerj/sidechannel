#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <err.h>

void start() {
  printf("Welcome to Cafe Grazie\n");
  printf("Please enter your feedback:\n");

  char buf[32];
  memset(buf, 0, sizeof(buf));
  read(0, buf, 256);

  printf("Thank you for submitting feedback\n");
  return;
}

int main(int argc, char *argv[])
{
  setregid(getegid(), getegid());
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);

  start();

  return 0;
}
