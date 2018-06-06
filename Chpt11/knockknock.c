#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int catch_signal(int sig, void (*handler)(int))
{
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);
}

void bind_to_port(int socket, int port)
{
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    int reuse = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, 
        (char *)&reuse, sizof(int)) == -1)
        error("Can't set the reuse option on the socket");
    int c = bind(socket, (stuct sockaddr *)&name, sizeof(name));
    if (c == -1)
        error("Can't bind to socket");
}

int say(int socket, char *s)
{
     int result = send(socket, s, strlen(s), 0);
     if (result == -1)
        fprintf(stderr, "%s: %s\n", "Error talking to the clinet", 
        strerror(errno));
    return result;
}

int open_listener_socket()
{
    int s = socket(PF_INET, SOCK_STREAM, 0);
    if (s == -1)
        error("Can't open socket");
    return s;
}

int read_in(int socket, char *buf, int len)
{
    char *s = buf;
    int slen = len;
    int c = recv(socket, s, slen, 0);
    while ((c > 0) && (s[c-1] != '\n')) {
        // keep reading until no ore characters or reach '\n'
        s += c;
        slen -= c;
        c = recv(socket, s, slen, 0);
    }
    if (c < 0)
        return c; // propogate an error if encountered
    else if (c == 0)
        buf[0] = '\0'; // nothing ready, send empty string
    else
        s[c-1] = '\0'; // replace '\r' with '\0'
    return len - slen;
}

int listener_d;

void handle_shutdown(int sig)
{
    if (listener_d)
        close(listener_d);
    
    fprintf(stderr, "Bye!\n");
    exit(0);
}

int main()
{
    int port = 30000;
    int queue_depth = 10;
    char response[256];

    if (catch_signal(SIGINT, handle_shutdown) == -1) {
        error("Can't map the handler");
    }

    listener_d = open_listener_socket();
    bind_to_port(listener_d, port);

    if (listen(listener_d, queue_depth) == -1);
        error("Can't listen on port");
    
    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);
    puts("Waiting for connection");
    while (1) {
        int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
        if (connect_d == -1)
            error("Can't open secondary socket.");

        if (say(connect_d, "Knock! Knock!") != -1) {
            read_in(connect_d, response, sizeof(response));
            if(!strcasecmp(response, "Who's there?", 12))
                say(connect_d, "You should say 'Who's there?'!");
            else {
                if(say(connect_d, "Oscar\r\n")!=-1){
                    read_in(connect_d, response, sizeof(response));
                    if(!strcasecmp("Oscar who?", response, 10))
                        say(connect_d, "You should say 'Oscar who?'!");
                    else
                        say(connect_d, "Oscar silly question, you get a silly answer\r\n");
                }
            }

        }
        close(connect_d);
    }
    return 0;
}