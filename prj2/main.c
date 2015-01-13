#include "bcd-float.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** main program: check command-line args and call appropriate
 *  decode or encode routine.
 */
int
main(int argc, const char *argv[])
{
  bool isDone = false;
  FILE *in = stdin, *out = stdout;
  enum { MAX_LINE_LENGTH = 80 };
  while (!isDone) {
    fprintf(out, "enter decimal number without space (^D for EOF): ");
    fflush(out);
    char text[MAX_LINE_LENGTH + 1];
    if (fgets(text, MAX_LINE_LENGTH, in) == NULL) {
      if (ferror(in)) {
        fprintf(stderr, "i/o error\n");
        exit(1);
      }
      else {
        break;
      }
    }
    int n = strlen(text);
    if (n == 1) continue;
    text[strlen(text) - 1] = '\0';
    BcdFloat f = text_to_bcd_float(text);
    if (f == BCD_FLOAT_ERROR) {
      fprintf(out, "conversion error\n");
      continue;
    }
    bcd_float_to_text(f, text);
    fprintf(out, "bcd float hex = \"0x%" PRIxLEAST64
            "\"; back to string as \"%s\"\n",
            f, text);
  }
}