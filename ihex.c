#include <stdint.h>
#include <stdbool.h>

bool char_is_hex(char ch)
{
	return (ch >= '0' && ch <= '9') ||
			(ch >= 'a' && ch <= 'f') ||
			(ch >= 'A' && ch <= 'F');
}

int16_t char_to_hex(char ch)
{
	if (ch >= '0' && ch <= '9') {
		return (ch - '0') & 0xf;
	} else if (ch >= 'a' && ch <= 'f') {
		return (ch - 'a' + 0xa) & 0xf;
	} else if (ch >= 'A' && ch <= 'F') {
		return (ch - 'A' + 0xa) & 0xf;
	} else {
		return -1;
	}
}

uint32_t ihex_read(char *s, uint8_t buff[])
{
	uint8_t checksum = 0;
	uint32_t i = 0;

	if (*s == ':') {
		s++;
		for (i = 0; s[i] && (i / 2) < (4 + buff[0] + 1); i++) {
			if (!char_is_hex(s[i])) {
				return 0; // error
			}

			buff[i / 2] <<= 4;
			buff[i / 2] |= char_to_hex(s[i]);
		}

		for (i = 0; i < (4 + buff[0] + 1); i++) {
			checksum += buff[i];
		}
		checksum = ~checksum + 1;

		if (checksum != buff[i]) {
			return 0; // error
		}
	}

	return i;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	static char s[BUFSIZ] = "";
	uint8_t bytes[BUFSIZ] = { 0, };
	uint32_t i = 0;
	uint32_t len = 0;

	fp = fopen("test.hex", "r");
	if (!fp) {
		return -1;
	}

	while (fgets(s, BUFSIZ, fp)) {
		s[strlen(s) - 1] = '\0';
		//s[strlen(s) - 2] = '\0';
		printf("%s\n", s);
		len = ihex_read(s, bytes);
		if (len > 0) {
				printf(" ");
			for (i = 0; i < len; i++) {
				printf("%02x", bytes[i]);
			}
			printf("\n");
		} else {
			printf("Error\n");
		}
	}

	return 0;
}
