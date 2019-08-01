#include <stdio.h>
#include <stdint.h>

int main(){
	unsigned int v = 7;
	unsigned int c;
	for(c = 0; v; c++){
		v &= v -1;
	}
	printf("%d %d",v,c);
}

