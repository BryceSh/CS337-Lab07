#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

char convert(char in) {
  if (('A' <= in) && (in <= 'Z'))
    in+= ('a' - 'A');
  else if (('a' <= in) && (in <= 'z'))
    in-= ('a' - 'A');  
  return in;
}

int main(int argc, char **argu) {
  if (argc < 3) {
    return -1;
    }
  int fd = open(argu[1], O_RDONLY, 0);
  int out = open(argu[2], O_WRONLY | O_CREAT, 0777);
  if (fd > 0) {
    char buffer[16];
    int count = 16;
    while (count == 16) {
      count = read(fd, buffer, 16);
      int i;
      for (i = 0; i<count; i++) {
        buffer[i] = convert(buffer[i]);
      }
      int x = write(out, buffer, count);
      if (x == -1) {
        perror("Something happened writing the file!\n");
      }
    }
  } else {
    perror("Invalid file\n");
    return -1;
  }
  return 0;
}
