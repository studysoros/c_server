#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    int tcp_socket = 0;
    struct sockaddr_in server_addr;
    int rc = 0;

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
        goto exit;
    }
    printf("bind succeeded\n");

    rc = listen(tcp_socket, SOMAXCONN);
    if (rc < 0) {
        perror("listen()");
        goto exit;
    }
    printf("listen succeeded\n");

exit:
    close(tcp_socket);
}