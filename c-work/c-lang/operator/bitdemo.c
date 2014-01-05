/*
 * bitdemo.c
 * used to demonstrate the bitwise operation.
 */
#include <stdio.h>

int main( void ) {
	int num = 0xabcd34;
	int bits = 5;
	printf( " %x %d %o \n", num, num, num );
	printf( " %x | %x is: %x\n", num, num, num | num );
	printf( " %x & %x is: %x\n", num, num, num & num );
	printf( " %x ^ %x is: %x\n", num, num, num ^ num );
	printf( " ~ %x is: %x\n", num, ~num );
	printf( " %x >> %x is: %x\n", num, bits, num >> bits );
	printf( " %x << %x is: %x\n", num, bits, num << num );
	return 0;
}
