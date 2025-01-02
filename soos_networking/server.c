// server.c 
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h> 
#include <signal.h>

#define PORT "3490" // the port users will be connecting to
#define BACKLOG 10  // how many pending connections queue will hold

void handle_sigint(int sig);
struct addrinfo* setup_addrinfo();
int bind_to_socket(struct addrinfo *server_info);
void start_listening(int listen_fd);
int await_client_connections(int listen_fd);
void* get_in_addr(struct sockaddr *sa);
void handle_client(int connection_fd);

int main() {

    signal(SIGINT, handle_sigint); // handle if the user enters ctrl+c

    struct addrinfo *server_info = setup_addrinfo(); // retrieve a linked list of IP addresses the server can use

    int listen_fd = bind_to_socket(server_info); // create a socket that will be used to listen for client connections

    freeaddrinfo(server_info); // don't need this now that we have a listening socket, so we can free the linked list
    
    start_listening(listen_fd);

    while (1) { // will run in an infinite loop until ctrl+c is entered
        int connection_fd = await_client_connections(listen_fd); // wait for a client to connect and get the connection socket
        handle_client(connection_fd);
    }
    
    return 0;
}

void handle_sigint(int sig) {
    printf("\nServer: Shutting down gracefully...\n");
    exit(0);
}

struct addrinfo* setup_addrinfo() {
    struct addrinfo hints, *server_info; // hints is used to specify the type of IP addresses we want; server_info will be where we store our results 
    memset(&hints, 0, sizeof hints);     // Must null out hints to avoid undefined behavior
    hints.ai_family = AF_UNSPEC;         // saying AF_UNSPEC makes our code IP version agnostic; can be either IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;     // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;         // Allow the server to bind to any local address
    int result = getaddrinfo(NULL, PORT, &hints, &server_info); // getaddrinfo creates a linked list of struct addrinfo's we can use, each node containing a potential IP address
    if (result != 0) {  // exit if an error occurred
        fprintf(stderr, "Server: getaddrinfo error: %s\n", gai_strerror(result));
        exit(1);
    }
    return server_info; // we can return this pointer because behind the scenes getaddrinfo malloc'ed for us
}

int bind_to_socket(struct addrinfo *server_info) {
    struct addrinfo *current; // used to iterate through linked list
    int listen_fd; // where we will store the socket we are trying to create

    // Iterate through the linked list until we find an IP address we can successfully make a socket for and bind.
    for (current = server_info; current != NULL; current = current->ai_next) {
        listen_fd = socket(current->ai_family, current->ai_socktype, current->ai_protocol);
        if (listen_fd == -1) {  // failed to create socket
            perror("Server: socket");
            continue; // try the next IP address
        }
        int yes=1;
        if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1) { // lose the pesky "Address already in use" error message
            perror("Server: setsockopt");
            close(listen_fd);
            continue;
        }
        if (bind(listen_fd, current->ai_addr, current->ai_addrlen) == -1) { // failed to bind to socket
            perror("Server: bind");
            close(listen_fd);
            continue; // try the next IP address
        }
        break; // We have successfully binded to a socket
    }
    // We have failed to bind to any socket, so exit with error
    if (current == NULL) {
        fprintf(stderr, "Server: Failed to bind to a socket\n");
        freeaddrinfo(server_info);
        exit(1);
    }
    // Successfully binded to socket
    return listen_fd;
}

void start_listening(int listen_fd) {
    if (listen(listen_fd, BACKLOG) == -1) {
        perror("Server: listen");
        close(listen_fd);
        exit(1);
    }
    printf("Server: Listening on port %s\n", PORT);
}

int await_client_connections(int socket_fd) {
    struct sockaddr_storage client_addr; // will hold client address once a connection is made
    socklen_t client_addr_size = sizeof client_addr;
    int connection_fd; // will hold the connection socket once a client connects
    printf("Server: Awaiting client connection...\n");

    // Main accept loop will run until either a client makes a connection or ctrl+c is entered
    while (1) {
        // accept is a blocking call, meaning program stops execution until a connection attempt happens
        int connection_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_addr_size); // wait for a connection and store the connection socket in connection_fd so we can communicate with the client
        if (connection_fd == -1) {  // accept failure
            perror("Server: accept");
            continue; // go back to listening
        }
        // if we made it here, we accepted a connection successfully :D
        // print the successful connection
        char ip_str[INET6_ADDRSTRLEN];
        inet_ntop(client_addr.ss_family, get_in_addr((struct sockaddr *)&client_addr), ip_str, sizeof(ip_str)); // convert IP address into a string so we can print it
        printf("Server: Accepted connection from %s\n", ip_str);
        return connection_fd; // we are ready to handle the client's request
    }
}

void* get_in_addr(struct sockaddr *sa) {
    void *addr;
    if (sa->sa_family == AF_INET) { // IPv4
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)sa;
        addr = &(ipv4->sin_addr);
    }
    else {  // IPv6
        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)sa;
        addr = &(ipv6->sin6_addr);
    }
    return addr;
}

void handle_client(int connection_fd) {
    char client_msg[256];
    FILE *file = fopen("test.txt", "w");
    while (1) {
        ssize_t bytes_received = recv(connection_fd, client_msg, sizeof(client_msg), 0);
        if (bytes_received == -1) { // check for errors
            perror("Server: recv");
            close(connection_fd);
            return;
        }
        if (bytes_received == 0) {
            printf("Server: Client closed connection\n");
            break;
        }
        fprintf(file, "%s", client_msg);
    }
    
    printf("Server: Received file successfully\n");
    
    close(connection_fd);
}
