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
    printf("Invalid Usage! ./ {source} {destination}\n");
    return -1;
  }
  int allowedBytes = 16;
  int fd = open(argu[1], O_RDONLY, 0);
  int out = open(argu[2], O_WRONLY | O_CREAT, 0777);
  if (fd > 0) {
    char buffer[allowedBytes];
    int count = allowedBytes;
    while (count == allowedBytes) {
      count = read(fd, buffer, allowedBytes);
      int i;
      for (i = 0; i<count; i++) {
        buffer[i] = convert(buffer[i]);
      }
      int x = write(out, buffer, count);
      if (x == -1) {
        printf("Something happened writing the file!\n");
      }
    }
  } else {
    printf("Invalid source file! Please try again!\n");
    return -1;
  }
  return 0;
}
