#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#define SERVER_IP "10.0.3.239"
char message[] = "AABBCCDDEEFF\n0123456789\nTest network write EEPROM\nVersion 0.1\n";
char buf[sizeof(message)];

int main()
{
    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425); // или любой другой порт...
    //addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	//inet_aton(SERVER_IP, addr.sin_addr.s_addr);
	//printf("addr %d\n",INADDR_LOOPBACK);
	printf("addr %x\n",addr.sin_addr.s_addr);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

    send(sock, message, sizeof(message), 0);
    recv(sock, buf, sizeof(message), 0);
    
    printf(buf);
    close(sock);

    return 0;
}
