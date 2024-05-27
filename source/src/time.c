#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// Override __stack_chk_fail to suppress stack smashing messages
void __stack_chk_fail(void) {
    write(4, "Thank you for submitting feedback\n", 34);
    exit(EXIT_FAILURE);
}

void start(int fd) {
  write(fd, "Welcome to Cafe Grazie\n", 23);
  write(fd, "Please enter your feedback:\n", 28);

  char buf[32];
  memset(buf, 0, sizeof(buf));
  read(fd, buf, 256);
  return;
}

int main(int argc, char *argv[])
{
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
      alarm(10);
      /* If we're the child, we can now read/write to the client on
         client_sockfd.
         The five second delay is just for this demonstration. */

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
