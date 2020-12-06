#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	system("whoami");
	printf("uid: %d", getuid());
	return 0;
}
