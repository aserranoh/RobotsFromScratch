
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

/* loadfile
   Loads a whole file onto a buffer.
 */
const char *
loadfile(const char *path)
{
    int fd = -1;
    char *buffer = 0;
    int tmperrno;

    // Open the file to load
    if ((fd = open(path, O_RDONLY)) < 0)
        return NULL;

    // Get the size of the file
    off_t size = lseek(fd, 0, SEEK_END);
    if (size < 0)
        goto cleanup;

    // Return to the beginning of the file
    lseek(fd, 0, SEEK_SET);

    // Create a buffer to read the file (allocate 1 extra byte to store a
    // null character at the end)
    if (!(buffer = malloc(size + 1)))
        goto cleanup;

    // Read the whole file
    off_t total_read = 0, r;
    while (total_read < size) {
        r = read(fd, buffer + total_read, size - total_read);
        if (r < 0) {
            free(buffer);
            buffer = 0;
            goto cleanup;
        }
        total_read += r;
    }
    buffer[size] = '\0';

cleanup:
    if (fd >= 0) {
        tmperrno = errno;
        close(fd);
        errno = tmperrno;
    }
    return buffer;
}

/* toulong
   Convert a string to a unsigned long.
   Return 0 if the conversion is OK, -1 otherwise.
 */
int
toulong(const char *s, unsigned long *n)
{
    char *endptr;
    if (!s)
        return -1;
    *n = strtoul(s, &endptr, 0);
    if (!(*s) || *endptr || *n == ULONG_MAX)
        return -1;
    return 0;
}

/* toushort
   Convert a string to a unsigned short.
   Return 0 if the conversion is OK, -1 otherwise.
 */
int
toushort(const char *s, unsigned short *n)
{
    unsigned long ul;
    if (toulong(s, &ul))
        return -1;
    if (ul <= USHRT_MAX)
        *n = (unsigned short)ul;
    else
        return -1;
    return 0;
}

