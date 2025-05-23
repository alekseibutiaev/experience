/* getchar example : typewriter */
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

char getch1() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
            perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
            perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
            perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
            perror ("tcsetattr ~ICANON");
    return (buf);
}

int main ()
{
  int c;
  puts ("Enter text. Include a dot ('.') in a sentence to exit:");
  do {
    c=getch1();
    printf("char is : %c\n", c);
  } while (c != '.');
  return 0;
}

