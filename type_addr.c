#include <netdb.h>
#include <stdio.h>

int main (int c, char **v)
{
	if (c!=2)
		return -1;
	
	struct hostent *h;
	h = gethostbyname(v[1]);

	if(NULL == h)
	{
		printf("Error\n");
		return -1;
	}

	printf("Canonical name %s\n", h->h_name);
	printf("Type=%s len=%d\n", (h->h_addrtype == AF_INET) ? "ipv4" : "ipv6", h->h_length);
}
