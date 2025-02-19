#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
void error_handling(char *message);
int main(int argc, char* argv[])
{
	int sock,n,in;
	struct sockaddr_in serv_addr;
	char message[100];
	int str_len;
	if(argc!=4){
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	sock=socket(PF_INET, SOCK_STREAM, 0);
	if(sock < 0)
		error_handling("socket() error");
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) 
		error_handling("connect() error!");

	if((in=open(argv[3],O_RDONLY)) < 0){ perror(argv[3]); return 1;}
	
		do {
              //파일을 복사한다.
              n=read(in,message,sizeof(message));
              printf("read : %d\n",n);
 
              if(n>0) write(sock,message,n);
              else if(n==0){ break;}
              else { perror("read()"); break; }
 
 
      } while(1);


		printf("send complete\n");
		
		
	close(in);
	close(sock);
	return 0;
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
