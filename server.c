#include <sys/socket.h>
#include <stdio.h>

int main(void) {
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (tcp_socket == -1) {
        perror("socket");
        return 1;
    }
    printf("socket created\n");
}