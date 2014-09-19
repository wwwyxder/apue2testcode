#include <stdio.h>
union A{
long l;
char arr[4];
};
int main()
{
    union A a;
	a.l = 1;
	if(a.arr[0]==1) {
	    printf("Little Endian.\n");
	} else {
	    printf("Big Endian.\n");
	}
	return 0;
}
