
#ifndef UTILS_H
#define UTILS_H

/* load_file
   Loads a whole file onto a buffer.
   Return NULL on error.
 */
const char *
loadfile(const char *path);

/* toulong
   Convert a string to a unsigned long.
   Return 0 if the conversion is OK, -1 otherwise.
 */
int
toulong(const char *s, unsigned long *n);

/* toushort
   Convert a string to a unsigned short.
   Return 0 if the conversion is OK, -1 otherwise.
 */
int
toushort(const char *s, unsigned short *n);

#endif

