#include <stdarg.h>

int print_d();

char print_c();

char *print_s();

int my_printf(char *str, ...)
{
  va_list args;
  int res;
  va_start(args, str);
  va_end(args);
  return res;
}

int main(int argc, char **argv)
{

  return 0;
}
