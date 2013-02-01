#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if(argc == 1 || argv[1] == "-h" || argv[1] == "--help")
    {
        printf("Usage: %s <interface1> <interface2> ...\n", argv[0]);
        return 0;
    }
  char *interface;
  
  struct ifreq s;
  int fd = socket(AF_INET, SOCK_DGRAM, 0);

  int i;
  for(i = 1; i < argc; i++){
      interface = argv[i];

    strcpy(s.ifr_name, interface);
    if (0 == ioctl(fd, SIOCGIFHWADDR, &s)) {
        int j;
        printf("%s ==> ", interface);
        for (j = 0; j < 6; ++j){
          printf("%02x ",(unsigned char) s.ifr_addr.sa_data[j]);
        }
    }
    printf("\n");
  }
  return 0;
}
