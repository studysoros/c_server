#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (tcp_socket == -1) {
        perror("socket");
        return 1;
    }
    printf("socket created\n");

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int rc = bind(tcp_socket, (const struct sockaddr*)&server_addr, sizeof(server_addr));
    if (rc < 0) {
        perror("bind()");
        return 1;
    }
    printf("bind succeeded\n");

    rc = listen(tcp_socket, SOMAXCONN);
    if (rc < 0) {
        perror("listen()");
        return 1;
    }
    printf("listen succeeded\n");
}