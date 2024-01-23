#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

void unsigned_num_to_str(uint64_t num, int base, char *buffer)
{
  if (num == 0)
  {
    *buffer++ = '0';
    *buffer = 0;
    return;
  }

  char buf[65];
  for (int i = 0; i < 65; i++)
  {
    buf[i] = 0;
  }
  int cur = 0;
  while (num)
  {
    int d = num % base;
    if (d >= 10)
    {
      buf[cur++] = 'a' + (d - 10);
    }
    else
    {
      buf[cur++] = '0' + d;
    }
    num /= base;
  }
  for (int i = cur - 1; i != 0; i--)
  {
    *buffer++ = buf[i];
  }
  *buffer = buf[0];
  *buffer = 0;
}

void num_to_str(uint64_t num, int base, char *buffer)
{
  if (num < 0)
  {
    *buffer++ = '-';
    num = -num;
  }
  unsigned_num_to_str(num, base, buffer);
}

// STATE 0: reg, 1: Escape;
void vprintk(const char *fmt, va_list args)
{
  int state = 0;
  char num_buf[65];

  while (*fmt)
  {
    if (state == 0)
    {
      if (*fmt == '%')
      {
        state = 1;
      }
      else
      {
        putchar(*fmt);
      }
    }
    else if (state == 1)
    {
      switch (*fmt)
      {
      case 'c':
      {
        char ch = va_arg(args, int);
        putchar(ch);
        break;
      }
      case 's':
      {
        const char *s = va_arg(args, const char *);
        while (*s)
        {
          putchar(*s++);
        }
        break;
      }
      case 'd':
      {
        int n = va_arg(args, int);
        num_to_str(n, 10, num_buf);
        for (int i = 0; num_buf[i]; i++)
        {
          putchar(num_buf[i]);
        }
        break;
      }
      case 'i':
      {
        /* code */
        break;
      }
      case 'x':
      {
        int n = va_arg(args, int);
        unsigned_num_to_str(n, 16, num_buf);
        for (int i = 0; num_buf[i]; i++)
        {
          putchar(num_buf[i]);
        }
        break;
      }
      case 'p':
      {
        putchar('0');
        putchar('x');
        void *n = va_arg(args, void *);
        unsigned_num_to_str((uint64_t)n, 16, num_buf);
        for (int i = 0; num_buf[i]; i++)
        {
          putchar(num_buf[i]);
        }
        break;
      }
      default:
        break;
      }
      state = 0;
    }
    fmt++;
  }
}

void printk(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vprintk(fmt, args);
  // val = va_arg(vl, double);
  va_end(args);
}

int main()
{
  void *ptr_to_main = (void *)main;
  uint64_t n = (uint64_t)-1;
  printk("Print a char: %c. Done\n", 'H');
  printk("Print a char: %s. Done\n", "Hunter Motko");
  printk("Print a int: %d. Done\n", 10);
  printk("Print a -int: %d. Done\n", -10);
  printk("Print a zero: %d. Done\n", 0);
  printk("Print a hex int: %x. Done\n", 10);
  printk("Print a zero hex int: %x. Done\n", 0);
  printk("Print a pointer: %p. Done\n", ptr_to_main);

  printk("Largest 64b val: %d, %x. Done\n", n, n);

  return 0;
}
