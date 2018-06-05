#include <stdarg.h>

enum drink {
  MUDSLIDE, FUZZY_NAVEL, MONKEY_GLAND, ZOMBIE
};

double price(enum drink d)
{
  switch(d) {
  case MUDSLIDE:
    return 6.79;
  case FUZZY_NAVEL:
    return 5.31;
  case MONKEY_GLAND:
    return 4.82;
  case ZOMBIE:
    return 5.89;
  }
  return 0;
}

void print_ints(int args, ...)
{
    va_list ap;
    va_start(ap, args);
    int i;
    for (i = 0; i < args; i++) {
        printf("argument: %i\n", va_arg(ap, int));
    }
    va_end(ap);
}

double total(int args, ...)
{
    double total = 0;
    va_list ap;
    va_start(ap, args);
    int i;
    for (i=0; i < args; i++){
        total += price(va_arg(ap, drink));
    }
    va_end(ap);
  return total;
}