#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
int
main ()
{
    char buff[64];
    int num;
    int fd;
    int i = 0;

    fd = open("foo.txt",O_RDONLY);
    read(fd,&num,sizeof(int));

    sprintf(buff,"%d\n",num);
    write(1,buff,strlen(buff));
}
