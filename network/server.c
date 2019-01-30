/**
 * \file recv.c
 * \brief simple TCP receiver
 * \author Emmanuel VALETTE
 * \date 04 May 2018
 */


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>

int read_client(int client)
{
  int n;
  char  buff[128];
  if (client == -1) {
    return 1;
  }

  n = 0;
  memset(buff, '\0', 128);
  while ( (n = recv(client, buff, 128, 0)) >= 0 ) {
    if (n == 0) {
      return -1;
    }
    printf("message received: '%s'", buff);
    if (buff[n - 1] == '\n') {
      memset(buff, '\0', 128);
      break;
    }
  }
  return 0;
}

/**
 * \fn main
 * \brief main function for our program
 *
 * \return int
 */
int main()
{
  int n;
  int sock;
  int client_sock;
  socklen_t client_addr_len;
  struct sockaddr_in server;
  struct sockaddr_in client_addr;
  char buff[10];

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
    {
      perror("socket()");
      return 1;
    }

  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_family = AF_INET;
  server.sin_port = htons(1234);

  if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
      perror("bind()");
      return 1;
    }
            
  listen(sock, 5);
  memset(buff, '\0', 10);

  puts("waiting clients...");
  while (1)
    {
      puts("waiting for accept");
      //int client_len = sizeof(client_addr);
      client_sock = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);
      if (client_sock < 0)
        {
          perror("accept()");
          return 1;
        }
      puts("new client");
      read_client(client_sock);
    }
  close(sock);
  return 0;
}
