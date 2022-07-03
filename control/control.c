
#include <arpa/inet.h>
#include <err.h>
#include <limits.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Default constants
#define DEFAULT_JOYSTICK_PORT   5555
#define DEFAULT_CTL_ADDR        "localhost"
#define DEFAULT_CTL_PORT        5556

#define MAXDATA 1024

unsigned short joystick_port;
const char *ctl_addr;
unsigned short ctl_port;
int in_sock;
int out_sock;
struct sockaddr_in outaddr;

/* toint
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

/* get_port
   Return a port number from a environtment variable.
 */
static unsigned short
get_port(const char *var, unsigned short default_port)
{
    char *s = getenv(var);
    unsigned short port;

    if (!s || *s == '\0') {
        // If the variable is not defined or empty, return the default port
        port = default_port;
    } else {
        char *end_ptr;
        unsigned long l = strtoul(s, &end_ptr, 0);
        if (l > USHRT_MAX || *end_ptr != '\0') {
            errx(1, "wrong port %s", var);
        } else {
            port = (unsigned short)l;
        }
    }
    return port;
}

/* get_str
   Return a string from a environtment variable.
 */
static const char *
get_str(const char *var, const char *default_str)
{
    const char *s = getenv(var);

    if (!s || *s == '\0') {
        // If the variable is not defined or empty, return the default string
        s = default_str;
    }
    return s;
}

/* read_environ
   Read the environment variables that contain the input parameters.
 */
static void
read_environ()
{
    // Get HTTP port
    joystick_port = get_port("JOYSTICK_PORT", DEFAULT_JOYSTICK_PORT);

    // Get destination address
    ctl_addr = get_str("CTL_ADDR", DEFAULT_CTL_ADDR);

    // Get CTL port
    ctl_port = get_port("CTL_PORT", DEFAULT_CTL_PORT);
}

/* init
   Initialize the application.
 */
void
init()
{
    // Read input variables
    read_environ();

    // Open input socket
    struct sockaddr_in servaddr;
    in_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (in_sock < 0) {
        err(1, "input socket creation failed");
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(joystick_port);
    if (bind(in_sock, (const struct sockaddr *)&servaddr,
        sizeof(servaddr)) < 0)
    {
        err(1, "bind failed");
    }

    // Open output socket
    out_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (out_sock < 0) {
        err(1, "output socket creation failed");
    }
    struct hostent *he;
    if ((he = gethostbyname(ctl_addr)) == NULL) {
        errx(1, "cannot get destination address '%s'", ctl_addr);
    }
    memcpy(&outaddr.sin_addr, he->h_addr_list[0], he->h_length);
    outaddr.sin_family = AF_INET;
    outaddr.sin_port = htons(ctl_port);
}

/* get_component
   Get a component (turn, speed) from the message.
 */
short
get_component(const char *ptr)
{
    int e;
    long l = toint(ptr, &e);
    if (e) {
        warnx("error: wrong value %s", ptr);
        return -300;
    }
    if (l > 100) {
        l = 100;
    } else if (l < -100) {
        l = -100;
    }
    return l*255/100;
}

int
main()
{
    init();

    char buffer[MAXDATA];
    while (1) {
        // Receive data
        int n = recv(in_sock, (char *)buffer, MAXDATA, 0);

        // Check the data and get the fields
        if (!n) continue;
        if (buffer[0] != ':' || buffer[n - 1] != '\n') {
            warnx("wrong data (no header or footer)");
            continue;
        }
        buffer[n - 1] = '\0';
        char *ptr = strchr(buffer + 1, ',');
        if (!ptr) {
            warnx("wrong data (no field separator)");
            continue;
        }
        *ptr = '\0';
        short turn, speed;
        if ((turn = get_component(buffer + 1)) < -UCHAR_MAX
            || (speed = get_component(ptr + 1)) < -UCHAR_MAX)
        {
            continue;
        }

        // Build the message to send
        n = sprintf(buffer, ":mv,%hd,%hd\n", speed, turn);

        // Send the message
        sendto(out_sock, buffer, n, 0, (const struct sockaddr *)&outaddr,
            sizeof(outaddr));
    }
}

