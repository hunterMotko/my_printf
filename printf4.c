#include <stdio.h>
#include <stdarg.h>

void Myprintf(char *, ...);       //Our printf function
char *convert(unsigned int, int); //Convert integer number into octal, hex, etc.

int main()
{
  Myprintf(" char: %c\n", 'C');
  Myprintf(" str:  %s\n", "Hunter Motko");
  Myprintf(" d: %d\n", 9);
  Myprintf(" d0: %d\n", 0);
  Myprintf(" int: i %i\n", 9);
  Myprintf(" int0: i %i\n", 0);
  Myprintf(" x: %x\n", 9);
  Myprintf(" x0: %x\n", 0);

  return 0;
}

void Myprintf(char *format, ...)
{
  char *traverse;
  unsigned int i;
  char *s;

  //Module 1: Initializing Myprintf's arguments
  va_list arg;
  va_start(arg, format);

  for (traverse = format; *traverse != '\0'; traverse++)
  {
    while (*traverse != '%')
    {
      putchar(*traverse);
      traverse++;
    }

    traverse++;

    //Module 2: Fetching and executing arguments
    switch (*traverse)
    {
    case 'c':
      i = va_arg(arg, int); //Fetch char argument
      putchar(i);
      break;

    case 'd':
      i = va_arg(arg, int); //Fetch Decimal/Integer argument
      if (i < 0)
      {
        i = -i;
        putchar('-');
      }
      puts(convert(i, 10));
      break;

    case 'o':
      i = va_arg(arg, unsigned int); //Fetch Octal representation
      puts(convert(i, 8));
      break;

    case 's':
      s = va_arg(arg, char *); //Fetch string
      puts(s);
      break;

    case 'x':
      i = va_arg(arg, unsigned int); //Fetch Hexadecimal representation
      puts(convert(i, 16));
      break;
    }
  }

  //Module 3: Closing argument list to necessary clean-up
  va_end(arg);
}

char *convert(unsigned int num, int base)
{
  static char Representation[] = "0123456789ABCDEF";
  static char buffer[50];
  char *ptr;

  ptr = &buffer[49];
  *ptr = '\0';

  do
  {
    *--ptr = Representation[num % base];
    num /= base;
  } while (num != 0);

  return (ptr);
}
