#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>



int main (int c, char **v)
{
	unsigned int port;
	if (c!=2)
		return -1;
	else 
		port=atoi(v[1]);

	//printf("%d\n",port);
    int sock;
    struct sockaddr_in addr;
    char buf[4096];
    int bytes_read;
	
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    while(1)
    {
        bytes_read = recvfrom(sock, buf, 1024, 0, NULL, NULL);
        buf[bytes_read] = '\0';
		
		if(!strcmp(buf,"OFF\n"))
			break;
		else
       		printf(buf);
    }
    
    return 0;
}
/*
        while(1)
        {
            bytes_read = recv(sock, buf, 1024, 0);
           // if(bytes_read <= 0) break;
			//printf("%s\n",buf);            
			//send(sock, buf, bytes_read, 0);
			if(!strcmp(buf,"OFF\n"))
				break;
			else
				printf("%s\n",buf);
        }
    
      //  close(sock);
   // }
    
    return 0;
}
*/
