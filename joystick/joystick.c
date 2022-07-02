
#include "mongoose.h"

#include <err.h>
#include <stdio.h>
#include <unistd.h>

// Default constants
#define DEFAULT_HTTP_PORT       8888
#define DEFAULT_DST_ADDR        "localhost"
#define DEFAULT_UDP_PORT        5555
#define DEFAULT_JOYSTICK_COLOR  "red"

#define ADDR_LENGTH             128
#define MSG_LENGTH              128

// Global variables
unsigned short http_port;
const char *dst_addr;
unsigned short udp_port;
const char *joystick_color;
const char *main_page;
int sock;
struct sockaddr_in sockaddr;

/* load_file
   Loads a whole file onto a buffer.
 */
static const char *
load_file(const char *path)
{
    int fd = -1;
    char *buffer = 0;

    // Open the file to load
    if ((fd = open(path, O_RDONLY)) < 0) {
        warn("cannot open file %s", path);
        goto cleanup;
    }

    // Get the size of the file
    off_t size = lseek(fd, 0, SEEK_END);
    if (size < 0) {
        warn("cannot get size of file %s", path);
        goto cleanup;
    }

    // Return to the beginning of the file
    lseek(fd, 0, SEEK_SET);

    // Create a buffer to read the file (allocate 1 extra byte to store a
    // null character at the end)
    if (!(buffer = malloc(size + 1))) {
        err(1, "cannot allocate memory");
    }

    // Read the whole file
    off_t total_read = 0, r;
    while (total_read < size) {
        r = read(fd, buffer + total_read, size - total_read);
        if (r < 0) {
            warn("cannot read file %s", path);
            free(buffer);
            buffer = 0;
            goto cleanup;
        }
        total_read += r;
    }
    buffer[size] = '\0';
cleanup:
    if (fd >= 0) {
        close(fd);
    }
    return buffer;
}

/* callback
   Callback where the HTTP resources are served.
 */
static void
callback(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *)ev_data;
        if (mg_http_match_uri(hm, "/")) {
            // Redirect to main.html
            mg_http_reply(c, 302, "Location: /main.html\r\n", "");
        } else if (mg_http_match_uri(hm, "/main.html")) {
            // Serve the main HTML page. It is a template
            mg_http_reply(c, 200, "Content-Type: text/html\r\n",
                main_page, joystick_color);
        } else if (mg_http_match_uri(hm, "/joy.js")
            || mg_http_match_uri(hm, "/joystick-base.png"))
        {
            // Serve static files
            struct mg_http_serve_opts opts = {
                .root_dir = ".",
                .mime_types = "js=text/javascript,png=image/x-png"
            };
            mg_http_serve_dir(c, hm, &opts);
        } else if (mg_http_match_uri(hm, "/position")) {
            char x[32] = "";
            char y[32] = "";
            int xres = mg_http_get_var(&hm->body, "x", x, sizeof(x));
            int yres = mg_http_get_var(&hm->body, "y", y, sizeof(y));
            if (xres <= 0 || yres <= 0) {
                warnx("cannot get x or y parameters");
                mg_http_reply(c, 400, "", "Missing x or y parameters\r\n");
            } else {
                // Convert x and y parameters to numbers
                long lx = strtoul(x, 0, 0);
                long ly = strtoul(y, 0, 0);

                // Create the message
                char msg[MSG_LENGTH];
                size_t n = snprintf(msg, sizeof(msg), ":%ld,%ld\n", lx, ly);

                // Send the message
                sendto(sock, msg, n, 0, (const struct sockaddr *)&sockaddr,
                    sizeof(sockaddr));
                mg_http_reply(c, 200, "", "");
            }
        } else {
            // Unknown content
            warnx("unknown content");
            mg_http_reply(c, 404, "", "Content not found\r\n");
        }
    }
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
    http_port = get_port("HTTP_PORT", DEFAULT_HTTP_PORT);

    // Get destination address
    dst_addr = get_str("DST_ADDR", DEFAULT_DST_ADDR);

    // Get UDP port
    udp_port = get_port("UDP_PORT", DEFAULT_UDP_PORT);

    // Get joystick color
    joystick_color = get_str("JOYSTICK_COLOR", DEFAULT_JOYSTICK_COLOR);
}

int
main(int argc, char *argv[])
{
    struct mg_mgr mgr;
    char http_addr[ADDR_LENGTH];

    // Read input variables
    read_environ();

    // Load the main.html file on memory
    if (!(main_page = load_file("main.html"))) {
        exit(1);
    }

    // Initialize the UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        err(1, "udp socket creation failed");
    }
    struct hostent *he;
    if ((he = gethostbyname(dst_addr)) == NULL) {
        fprintf(stderr, "error: cannot get destination address '%s'\n",
            dst_addr);
        exit(1);
    }
    memcpy(&sockaddr.sin_addr, he->h_addr_list[0], he->h_length);
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(udp_port);

    // Initialize server
    mg_mgr_init(&mgr);
    snprintf(http_addr, ADDR_LENGTH, "http://0.0.0.0:%hu", http_port);
    mg_http_listen(&mgr, http_addr, callback, &mgr);

    // Main loop
    for (;;) mg_mgr_poll(&mgr, 1000);

    // Cleanup
    mg_mgr_free(&mgr);
    free((void *)main_page);
    return 0;
}

