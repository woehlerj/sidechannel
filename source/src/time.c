// This file is based on the server file from diehard from lab07

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

// Override __stack_chk_fail to suppress stack smashing messages
void __stack_chk_fail(void) {
    write(4, "Thank you for submitting feedback\n", 34);
    exit(EXIT_FAILURE);
}

// function to fork
void start(int fd) {
  // Allocate buffers for welcome message and buffer address on the heap
  // so it's no need to overwrite them.
  char* welcome_buf = malloc(500);
  char* buf_addr = malloc(58);
  char buf[32];

  // Print welcome message
  int welcome_fd = open("/welcome-message.txt", 0);
  int welcome_len = read(welcome_fd, welcome_buf, 499);
  write(fd, welcome_buf, welcome_len);

  // print buffer address to make it doable
  sprintf(buf_addr, "Hint: your feedback will be stored here: %p\n> ", &buf);
  write(fd, buf_addr, 58);

  // read in buffer
  memset(buf, 0, sizeof(buf));
  read(fd, buf, 256);

  return;
}

int main(int argc, char *argv[])
{
  // general server setup
  int port = 28014;
  int server_sockfd, client_sockfd;
  socklen_t server_len, client_len;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;

  if (argc == 2) {
    port = atoi(argv[1]);
  }

  server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
  int yes = 1;
  if (setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0) {
    perror("setsockopt");
    exit(-1);
  }

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(port);
  server_len = sizeof(server_address);
  if (bind(server_sockfd, (struct sockaddr *)&server_address,server_len) < 0) {
    perror("bind");
    exit(-1);
  }

  /* Create a connection queue, ignore child exit details and wait for
     clients. */

  listen(server_sockfd, 5);
  signal(SIGCHLD, SIG_IGN);

  while(1) {
    /* Accept connection. */

    client_len = sizeof(client_address);
    client_sockfd = accept(server_sockfd,\
                      (struct sockaddr *)&client_address, &client_len);

    /* Fork to create a process for this client and perform a test to see
       whether we're the parent or the child. */

    if (fork() == 0) {
      alarm(1000);
      /* If we're the child, we can now read/write to the client on
         client_sockfd.
         The five second delay is just for this demonstration. */

      // Run start function. In case of no buffer overflow, wait for 0.5 s and then send the message.
      // In case of buffer overflow, this thread will not end, but the stk_check_fail
      // handler will be executed, so the same message will be sent but without delay.
      start(client_sockfd);
      usleep(500000);
      write(client_sockfd, "Thank you for submitting feedback\n", 34);
      close(server_sockfd);
      close(client_sockfd);
      return 0;
    }

    /* Otherwise, we must be the parent and our work for this client is
       finished. */

    else {
      close(client_sockfd);
    }
  }

  return 0;
}
