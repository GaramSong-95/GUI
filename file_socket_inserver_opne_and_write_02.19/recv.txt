#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char *message);
int main(int argc, char* argv[])
{
	int sock,n;
	struct sockaddr_in serv_addr;
	char message[30];
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

		//복사파일을 보낸다.
		write(sock,argv[3],strlen(argv[3]));
		n=read(sock,message,sizeof(message)-1);
		if(n==0){printf("server disconnect\n"); }
		else if(n<0) {perror("server");}
		printf("success write\n");	
		//서버에서 복사가 완료될 때까지 대기
		n=read(sock,message,sizeof(message));
        if(n==0){printf("server disconnect\n"); }
        else if(n<0) {perror("server");}
		printf("%s\n",message);
		write(sock,"OK",3);
		
		

	close(sock);
	return 0;
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
