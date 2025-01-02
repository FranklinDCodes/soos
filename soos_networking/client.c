// client.c
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT "3490"
#define SERVER_IP NULL // will run on loopback address if you set it to NULL
#define FILENAME "test.txt"

struct addrinfo* setup_addrinfo();
int connect_to_server(struct addrinfo *server_info);
void print_addr(struct addrinfo *current);
void communicate_with_server(int connection_fd);

int main() {
    
    struct addrinfo *server_info = setup_addrinfo();

    int socket_fd = connect_to_server(server_info);

    freeaddrinfo(server_info);  // don't need this anymore since we have made our connection

    communicate_with_server(socket_fd);

    return 0;
}

struct addrinfo* setup_addrinfo() {
    struct addrinfo hints, *server_info;

    // Zero out hints to avoid undefined behavior
    memset(&hints, 0, sizeof hints);
    
    // Setup hints fields
    hints.ai_family = AF_UNSPEC;       // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;   // TCP stream sockets

    int result = getaddrinfo(SERVER_IP, PORT, &hints, &server_info);
    if (result != 0) {
        fprintf(stderr, "Client: getaddrinfo error: %s\n", gai_strerror(result));
        exit(1);
    };
    return server_info;
}

int connect_to_server(struct addrinfo *server_info) {
    int socket_fd;
    struct addrinfo *current;

    // Iterate through the linked list of server IP addresses.
    // We go until we find an address we a valid IP address.
    for (current = server_info; current != NULL; current = current->ai_next) {
        socket_fd = socket(current->ai_family, current->ai_socktype, current->ai_protocol);   // try to create the socket
        if (socket_fd == -1) {  // socket creation failure
            perror("Client: socket");
            continue; // try the next IP address
        }
        if (connect(socket_fd, current->ai_addr, current->ai_addrlen) == -1) { // connection failed, so close the socket and continue the loop to search for another IP address
            perror("Client: connect");
            close(socket_fd);
            continue; // try the next IP address
        }
        break; // connection established, so we don't need to check IP addresses anymore
    }

    // No connection was established, so exit with error.
    if (current == NULL) {
        fprintf(stderr, "Client: Failed to connect to server\n");
        freeaddrinfo(server_info);
        exit(2);
    }

    // We have successfully established a connection
    print_addr(current);
    
    return socket_fd;
}

void print_addr(struct addrinfo *current) {
    // We need to determine if we are using IPv4 or IPv6 for the inet_ntop() function
    void *addr;
    if (current->ai_family == AF_INET) { // We are using IPv4
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)current->ai_addr;
        addr = &(ipv4->sin_addr);
    } else { // We are using IPv6
        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)current->ai_addr;
        addr = &(ipv6->sin6_addr);
    }
    char ip_str[INET6_ADDRSTRLEN];
    inet_ntop(current->ai_family, addr, ip_str, sizeof ip_str);   // convert the IP address to a string so we can print the connection status
    printf("Client: Connection established to %s\n", ip_str);
}

void communicate_with_server(int connection_fd) {
    // get the filename
    FILE *file = fopen(FILENAME, "r");
    // iterate through each of the file's lines one at a time and send them
    // TODO: Fix naiive implementation that assumes each line is 256 bytes
    char line[256];
    void *end;
    while (fgets(line, sizeof(line), file) != NULL) {
        send(connection_fd, line, sizeof(line), 0);
    }
    
    close(connection_fd);
    fclose(file);
}