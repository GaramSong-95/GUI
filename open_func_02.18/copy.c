#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char **argv)
{
	int n,in,out,i=0,j=0;
	char buf[1024];
	if(argc!=3){
		write(2,"Usage : copy file1 file2\n",25);
		printf("Usage : %s file1 file2\n",argv[0]);
		return 1;
	}
	while(argv[i] != 0)
	{
		printf("%s\n",argv[i]);
		for(j=0;j<strlen(argv[i]);j++) printf("%c\n",argv[i][j]);
		printf("\n");
		i++;
	}
	for(i=0;i<argc;i++)
    {
        printf("%s\n",argv[i]);
        for(j=0;j<strlen(argv[i]);j++)
				//printf("%c\n",argv[i][j]);
				printf("%c\n",*(*(argv+i)+j));
        printf("\n");
    }
	while(*argv != 0)
	{
		printf("%s\n",*argv);
		argv++;
	}	
	if((in=open(argv[1],O_RDONLY)) < 0) {
		perror(argv[1]);
		return 2;
	}

	if((out=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR))<0) {
		perror(argv[2]);
		return 3;
	}

	while((n=read(in,buf,sizeof(buf))) > 0) write(out,buf,n);

	close(out);
	close(in);

	return 0;

}
