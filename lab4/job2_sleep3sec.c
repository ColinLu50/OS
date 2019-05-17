// Sleep in c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  printf("Sleeping for 2 seconds\n");
  fflush(stdout);
  sleep(3);
  printf("Woke up!!\n");
  return 0;
}