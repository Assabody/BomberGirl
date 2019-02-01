#include "network.h"

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

int main()
{
  int sock;
  int client1;
  int client2;
  int client_addr_len;
  struct sockaddr_in server;
  struct sockaddr_in client_addr;
  int i;
  fd_set active_fd_set, read_fd_set;
  struct timeval timeout;

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
  FD_ZERO(&active_fd_set);
  FD_SET(sock, &active_fd_set);
  while (1)
  {
    read_fd_set = active_fd_set;
    if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0)
    {
      perror ("select");
      exit (-1);
    }

    for (i = 0; i < FD_SETSIZE; ++i)
    {
      if (FD_ISSET (i, &read_fd_set))
      {
        if (i == sock) {
          int new;
          int client_len = sizeof(client_addr);
          new = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);
          if (new < 0)
          {
            perror ("accept");
            exit (EXIT_FAILURE);
          }
          printf ("Server: connect from host %s, port %hd.\n",
                  inet_ntoa (client_addr.sin_addr),
                  ntohs (client_addr.sin_port));
          FD_SET (new, &active_fd_set);
        } else {
          if (read_client(i) == -1)
          {
            printf("client %s disconnected\n", inet_ntoa(client_addr.sin_addr));
            close(i);
            FD_CLR(i, &active_fd_set);
          }
        }
      }
    }
    puts("Looping");
  }    
  close(sock);
  return 0;
}
