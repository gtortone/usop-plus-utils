#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* memwrite.c -- Demonstrate write to a Xillybus dual port memory

This simple command-line application is given three arguments: The
device file to write to, the address (a decimal number between 0 and 31)
and data to be written (a decimal number between 0 and 255).

The application sends a seek command to the device file and writes the
character. These two operations create a write operation on the given address
on the FPGA's dual port RAM.

The use of allwrite() is an overkill when a single byte is written. For
longer writes it's the adequate way to do what most programmers expect:
Write all data, or never return.

See http://www.xillybus.com/doc/ for usage examples an information.

*/

void allwrite(int fd, unsigned char *buf, int len);

int main(int argc, char *argv[]) {

  int fd;
  int address;
  unsigned long value;
  unsigned char data[4];

  if (argc!=4) {
    fprintf(stderr, "Usage: %s <devfile> <address> <data>\n", argv[0]);
    fprintf(stderr, "(address in decimal format)\n");
    fprintf(stderr, "(data in hex format e.g. 0xab12)\n");
    exit(1);
  }

  address = atoi(argv[2]);
  value = strtoul(argv[3], NULL, 16);

  data[3] = (unsigned char)  (value & 0x000000FF);
  data[2] = (unsigned char) ((value & 0x0000FF00) >> 8);
  data[1] = (unsigned char) ((value & 0x00FF0000) >> 16);
  data[0] = (unsigned char) ((value & 0xFF000000) >> 24);

  printf("address = 0x%X\n", address);
  printf("value = 0x%lX\n", value);
  printf("data[0] = 0x%X\n", data[0]);
  printf("data[1] = 0x%X\n", data[1]);
  printf("data[2] = 0x%X\n", data[2]);
  printf("data[3] = 0x%X\n", data[3]);

  fd = open(argv[1], O_WRONLY);

  if (fd < 0) {
    if (errno == ENODEV)
      fprintf(stderr, "(Maybe %s a read-only file?)\n", argv[1]);

    perror("Failed to open devfile");
    exit(1);
  }

  if (lseek(fd, address, SEEK_SET) < 0) {
    perror("Failed to seek");
    exit(1);
  }

  allwrite(fd, data, 4);

  return 0;
}



/*
   Plain write() may not write all bytes requested in the buffer, so
   allwrite() loops until all data was indeed written, or exits in
   case of failure, except for EINTR. The way the EINTR condition is
   handled is the standard way of making sure the process can be suspended
   with CTRL-Z and then continue running properly.

   The function has no return value, because it always succeeds (or exits
   instead of returning).

   The function doesn't expect to reach EOF either.
*/

void allwrite(int fd, unsigned char *buf, int len) {
  int sent = 0;
  int rc;

  while (sent < len) {
    rc = write(fd, buf + sent, len - sent);

    if ((rc < 0) && (errno == EINTR))
      continue;

    if (rc < 0) {
      perror("allwrite() failed to write");
      exit(1);
    }

    if (rc == 0) {
      fprintf(stderr, "Reached write EOF (?!)\n");
      exit(1);
    }

    sent += rc;
  }
}
