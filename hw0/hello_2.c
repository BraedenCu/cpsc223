#include <stdio.h>

int main(int argc, char *argv[]) {
	char name[126];
	printf("Enter your name: ");
	scanf("%s", name);
	printf("Hello, %s\n", name);
	return 0;
}

	
