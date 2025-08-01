#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int handle_client(int client_socket) {
  ssize_t n = 0;
  char buff[100];

  printf("\n---\n");
  for (;;) {
    memset(buff, 0, sizeof(buff));

    n = read(client_socket, buff, sizeof(buff)-1);
    if (n < 0) {
      perror("read(client_socket)");
      return -1;
    }
    if (n == 0) {
      printf("connection closed");
      break;
    }

    printf("%s\n", buff);
  }
  printf("\n---\n");

  return 0;
}

int main(void) {
    int tcp_socket = 0;
    struct sockaddr_in server_addr;
    int rc = 0;
    int ret = 0;
    int client_socket = 0;

    memset(&server_addr, 0, sizeof(server_addr));
    
    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket == -1) {
        perror("socket");
        return 1;
    }
    printf("socket created\n");
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int rc = bind(tcp_socket, (const struct sockaddr*)&server_addr, sizeof(server_addr));
    if (rc < 0) {
        perror("bind()");
        ret = 1;
        goto exit;
    }
    printf("bind succeeded\n");

    rc = listen(tcp_socket, SOMAXCONN);
    if (rc < 0) {
        perror("listen()");
        ret = 1;
        goto exit;
    }
    printf("listen succeeded\n");

    for (;;) {
        printf("waiting for connections...\n");
        client_socket = accept(tcp_socket, NULL, NULL);
        
        printf("got a connection!\n");
        rc = handle_client(client_socket);
    }

exit:
    close(tcp_socket);
    return ret;
}