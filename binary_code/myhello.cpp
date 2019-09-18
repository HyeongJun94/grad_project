#include <cstdio>

void print_hello();

void print_hello(){
	printf("Hello\n");
}

int main(){
	printf("Before Call\n");
	print_hello();
	printf("After Call\n");
	return 0;
}
