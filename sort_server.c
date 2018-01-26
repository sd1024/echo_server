#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>

int srvn(const void *c1, const void *c2)
{
return (*(char*)c2 - *(char*)c1);
}

int main (int c, char **v)
{
	unsigned int port;
	if (c!=2)
		return -1;
	else 
		port=atoi(v[1]);

	//printf("%d\n",port);
    int sock, listener;
    struct sockaddr_in addr;
    char buf[4096];
    int bytes_read;
	
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
		printf("error listener\n");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
		printf("error bind\n");
        perror("bind");
        exit(2);
    }

listen(listener, 1);
    

    while(1)
    {
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
			printf("error accept\n");
            perror("accept");
            exit(3);
        }
        while(1)
    {
        bytes_read = recvfrom(sock, buf, 1024, 0, NULL, NULL);
      	 buf[bytes_read] = '\0';
		
//printf("%s\n",buf);
		if(!strcmp(buf,"OFF\n"))
			return 1;
		else
			
			//if(bytes_read <= 0) break;
			qsort(buf,strlen(buf),1,srvn);
		 	//buf[bytes_read] = '\n';
            send(sock, buf, bytes_read, 0);
			//send(sock, "\0", 1, 0);
			//send(sock, "\n", 1, 0);
	
  //     		printf("%s\n",buf);
    }

            
        close(sock);
   }    
    return 0;
}





