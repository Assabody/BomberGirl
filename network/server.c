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
  int sock;
  int client1;
  int client2;
  int client_addr_len;
  struct sockaddr_in server;
  struct sockaddr_in client_addr;

  fd_set readfs;
  struct timeval timeout;
  char buff[10];

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
  {
    perror("socket()");
    return 1;
  }

  server.sin_addr.s_addr = htonl(INADDR_ANY);
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
  puts("waiting for accept");
  client_addr_len = sizeof(client_addr);
  client1 = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);
  client2 = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);

  if (client1 < 0 || client2 < 0)
  {
    perror("accept()");
    return 1;
  }
  puts("new clients");
  while (1)
  {
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    FD_ZERO(&readfs);
    FD_SET(client1, &readfs);
    FD_SET(client2, &readfs);

    select(client2 + 1, &readfs, NULL, NULL, &timeout);
      //int client_len = sizeof(client_addr);
      //client_sock = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);
    if (FD_ISSET(client1, &readfs))
    {
      if (read_client(client1) == -1)
      {
        puts("client 1 disconnected");
        close(client1);
        client1 = -1;
      }
    } else if (FD_ISSET(client2, &readfs)) {
      if (read_client(client2) == -1)
      {
        puts("client 2 disconnected");
        close(client2);
        client2 = -1;
      }
    }

    if (client1 == -1 && client2 == -1)
    {
      break;
    }
    puts("looping");  
  }
  close(sock);
  return 0;
}
