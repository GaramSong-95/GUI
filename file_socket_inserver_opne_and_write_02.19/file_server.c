#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
void error_handling(char *message);
int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;
	char message[100];
	char* copy_file;
	int str_len,in,out,n;

	if(argc!=3){
		printf("Usage : %s <port> <file>\n", argv[0]);
		exit(1);
	}
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock < 0)
		error_handling("socket() error");
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr) )< 0 )
		error_handling("bind() error"); 
	if(listen(serv_sock, 5) < 0)
		error_handling("listen() error");
	clnt_addr_size=sizeof(clnt_addr);
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	printf("new connected\n");


	//복사파일을 가져온다.
	str_len=read(clnt_sock,message,sizeof(message));
	if(str_len<0){ perror("read()\n");}
	copy_file=message;
	write(clnt_sock,message,str_len);
	printf("read success\n");
	//복사될 파일을 연다
	if((in=open(copy_file,O_RDONLY)) < 0){ perror(copy_file); return 1;}
	//복사파일을 연다
	if((out=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644)) < 0) { perror(argv[2]);return 1; }




	do {
			//파일을 복사한다.
			n=read(in,message,sizeof(message));
			printf("read : %d\n",n);
			
			if(n>0) write(out,message,n);
			else if(n==0) break;
			else { perror("read()"); break; }


	} while(1);
		// 복사완료 후 완료 메세지 전송.
		printf("copy complete\n");
		sprintf(message,"copy complete");
		write(clnt_sock,message,sizeof(message));
		read(clnt_sock,message,sizeof(message));
		if(str_len<0){ perror("read()\n");}
 		printf("%s\n",message);

	close(clnt_sock);
	printf("disconnected\n");

	close(serv_sock);
	return 0;
}
void error_handling(char *message)
{
	perror("error_handing()");
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
