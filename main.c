#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int fd, size, i;
  unsigned long long int sum = 0;
  char* mapped;

  fd = open(argv[1], O_RDONLY|O_CLOEXEC);
  size = lseek(fd, 0, SEEK_END);
  mapped = mmap(0, size, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, fd, 0);
// mprotect(0x7f7b93d93000, 48443392, PROT_NONE) = 0
// mmap(0x7f7b93d93000, 39927808, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2c2000) = 0x7f7b93d93000
// mmap(0x7f7b963a7000, 8511488, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28d6000) = 0x7f7b963a7000
// mmap(0x7f7b96bc6000, 2011136, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x30f4000) = 0x7f7b96bc6000
// mmap(0x7f7b96db1000, 169384, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f7b96db1000
  for (i = 0; i < size; ++i) {
    sum += mapped[i];
  }

  printf("Sum: %llu", sum);
  munmap(mapped, size);
  close(fd);
  return 0;
}
