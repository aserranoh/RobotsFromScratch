
#include "mongoose.h"
#include "utils.h"

#include <err.h>

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
struct mg_connection *udp_conn;

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
            char x[32] = "", y[32] = "";
            if (mg_http_get_var(&hm->body, "x", x, sizeof(x)) <= 0
                || mg_http_get_var(&hm->body, "y", y, sizeof(y)) <= 0)
            {
                warnx("cannot get x or y parameters");
                mg_http_reply(c, 400, "", "Missing x or y parameters\r\n");
            } else {
                // Convert x and y parameters to numbers
                long lx, ly;
                toulong(x, &lx);
                toulong(y, &ly);

                // Send the message
                mg_printf(udp_conn, ":%ld,%ld\n", lx, ly);
                mg_http_reply(c, 204, "", "");
            }
        } else {
            warnx("unknown content");
            mg_http_reply(c, 404, "", "Content not found\r\n");
        }
    }
}

/* read_environ
   Read the environment variables that contain the input parameters.
 */
static void
read_environ()
{
    // Get HTTP port
    char *s_port = getenv("HTTP_PORT");
    if (!s_port)
        http_port = DEFAULT_HTTP_PORT;
    else if (toushort(s_port, &http_port))
        errx(1, "wrong HTTP port %s", s_port);

    // Get destination address
    dst_addr = getenv("DST_ADDR");
    if (!dst_addr)
        dst_addr = DEFAULT_DST_ADDR;

    // Get UDP port
    s_port = getenv("UDP_PORT");
    if (!s_port)
        udp_port = DEFAULT_UDP_PORT;
    else if (toushort(s_port, &udp_port))
        errx(1, "wrong UDP port %s", s_port);

    // Get joystick color
    joystick_color = getenv("JOYSTICK_COLOR");
    if (!joystick_color)
        joystick_color = DEFAULT_JOYSTICK_COLOR;
}

int
main(int argc, char *argv[])
{
    struct mg_mgr mgr;
    char addr[ADDR_LENGTH];

    // Read input variables
    read_environ();

    // Load the main.html file on memory
    if (!(main_page = loadfile("main.html")))
        err(1, "cannot load 'main.html'");

    mg_mgr_init(&mgr);

    // Initialize the UDP socket
    snprintf(addr, ADDR_LENGTH, "udp://%s:%hu", dst_addr, udp_port);
    if (!(udp_conn = mg_connect(&mgr, addr, callback, NULL)))
        err(1, "cannot connect to address %s", addr);

    // Initialize HTTP server
    snprintf(addr, ADDR_LENGTH, "http://0.0.0.0:%hu", http_port);
    if (!mg_http_listen(&mgr, addr, callback, &mgr))
        err(1, "cannot listen at address %s", addr);

    // Main loop
    for (;;)
        mg_mgr_poll(&mgr, 1000);

    // Cleanup
    mg_mgr_free(&mgr);
    free((void *)main_page);
    return 0;
}

