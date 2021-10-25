#include <stdio.h>
#include <errno.h>
#include <string.h>
//Uname
#include <sys/utsname.h>

int main(){

  struct utsname strUname;

  if (uname (&strUname) == -1){

     printf("ERROR(%d): %s\n", errno, strerror(errno));

     return -1;
  }
  else {

    printf("SysName: %s\n", strUname.sysname);
    printf("NodeName: %s\n", strUname.nodename);
    printf("Release: %s\n", strUname.release);
    printf("Version: %s\n", strUname.version);
    printf("Machine: %s\n", strUname.machine);
    printf("DomainName: %s\n", strUname.__domainname);
  }

  return 1;
}