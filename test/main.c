#include <stdio.h>
#include <stdint.h>
#include "atcmd.h"

int main(int argc, char *argv[])
{
	char buff[0xff] = "";
	
	printf("atcmd -> len = %lld, s = %s\n", 
			atcmd_printf(buff, "CMD1", "PARAM"), buff);

	printf("atcmd -> len = %lld, s = %s\n", 
			atcmd_printf(buff, "CMD1", "%s", "PARAM"), buff);

	printf("atcmd -> len = %lld, s = %s\n", 
			atcmd_printf(buff, NULL, NULL), buff);

	printf("atcmd -> len = %lld, s = %s\n", 
			atcmd_printf(buff, "HELLO", NULL), buff);

	printf("atcmd -> len = %lld, s = %s\n", 
			atcmd_printf(buff, "HELLO", "WORLD"), buff);

	printf("atcmd -> len = %lld, s = %s\n", 
			atcmd_printf(buff, "INT", "%d", -12345), buff);

	printf("atcmd -> len = %lld, s = %s\n", 
			atcmd_printf(buff, "STR", "%s", "STRING!"), buff);

	printf("atcmd -> len = %lld, s = %s\n", 
			atcmd_printf(buff, "CHAR", "%c", 'A'), buff);


	return 0;
}
