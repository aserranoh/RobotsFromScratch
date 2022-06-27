
#include <arpa/inet.h>
#include <limits.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXDATA 1024

unsigned short in_port;
char *out_addr;
unsigned short out_port;
int in_sock;
int out_sock;
struct sockaddr_in outaddr;

/* toshort
   Convert a c-string to a number.
 */
long
toint(const char *s, int *error)
{
    char *endptr;
    long number = strtol(s, &endptr, 0);

    if (*s == '\0' || *endptr != '\0'
        || number == LONG_MIN || number == LONG_MAX)
    {
        *error = 1;
        return 0;
    }
    *error = 0;
    return number;
}

void
init(int argc, char *argv[])
{
    // Get the parameters
    if (argc < 4) {
        fprintf(stderr, "usage: control IN_PORT OUT_ADDRESS OUT_PORT\n");
        exit(1);
    }
    int e;
    long l = toint(argv[1], &e);
    if (e || l < 0 || l > USHRT_MAX) {
        fprintf(stderr, "error: wrong in_port\n");
        exit(1);
    }
    in_port = l;
    out_addr = argv[2];
    l = toint(argv[3], &e);
    if (e || l < 0 || l > USHRT_MAX) {
        fprintf(stderr, "error: wrong out_port\n");
        exit(1);
    }
    out_port = l;

    // Open input socket
    struct sockaddr_in servaddr;
    in_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (in_sock < 0) {
        perror("input socket creation failed");
        exit(1);
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(in_port);
    if (bind(in_sock, (const struct sockaddr *)&servaddr,
        sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(1);
    }

    // Open output socket
    out_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (out_sock < 0) {
        perror("output socket creation failed");
        exit(1);
    }
    struct hostent *he;
    if ((he = gethostbyname(out_addr)) == NULL) {
        fprintf(stderr, "error: cannot get destination address '%s'\n",
            out_addr);
        exit(1);
    }
    memcpy(&outaddr.sin_addr, he->h_addr_list[0], he->h_length);
    outaddr.sin_family = AF_INET;
    outaddr.sin_port = htons(out_port);
}

int
main(int argc, char *argv[])
{
    init(argc, argv);

    char buffer[MAXDATA];
    while (1) {
        // Receive data
        int n = recv(in_sock, (char *)buffer, MAXDATA, 0);

        // Check the data and get the fields
        if (!n) {
            continue;
        }
        if (buffer[0] != ':' || buffer[n - 1] != '\n') {
            fprintf(stderr, "wrong data (no header or footer)\n");
            continue;
        }
        buffer[n - 1] = '\0';
        char *ptr = strchr(buffer + 1, ',');
        if (!ptr) {
            fprintf(stderr, "wrong data (no field separator)\n");
            continue;
        }
        *ptr = '\0';
        int e;
        long l = toint(buffer + 1, &e);
        if (e || l < -UCHAR_MAX || l > UCHAR_MAX) {
            fprintf(stderr, "error: wrong speed\n");
            continue;
        }
        short turn = l;
        l = toint(ptr + 1, &e);
        if (e || l < -UCHAR_MAX || l > UCHAR_MAX) {
            fprintf(stderr, "error: wrong turn\n");
            continue;
        }
        short speed = l;

        // Build the message to send
        n = sprintf(buffer, ":mv,%hd,%hd\n", speed, turn);

        // Send the message
        sendto(out_sock, buffer, n, 0, (const struct sockaddr *)&outaddr,
            sizeof(outaddr));
    }
}

