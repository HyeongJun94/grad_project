#include <cstdio>

void print_hello(){
  printf("Hello\n");
}

void AccessAcc(){
  printf("AccessAcc\n");
}

int main(){
	printf("Before Call\n");
 // print_hello();
  AccessAcc();
  printf("After Call\n");
	return 0;
}
