// UTF-8 encoding
/**
 * @brief	AT 명령어를 생성하기 위한 함수들을 정의
 * @author	Jaewon Choi <jwonee1343@gmail.com>
 */
#include "atcmd.h"
#include "str.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

/**
 * @brief	"AT"를 버퍼에 쓰는 함수
 * @param	s	문자열 버퍼
 * @return 	문자열 길이
 */
static inline uint32_t putat(char s[])
{
	uint32_t len = 0;

	s[len++] = 'A';
	s[len++] = 'T';
	s[len] = '\0';

	return len;
}

/**
 * @brief	AT Command의 명령어를 버퍼에 쓰는 함수
 * @param	s	문자열 버퍼
 * @param	cmd	명령어
 * @return	문자열 길이
 */
static inline uint32_t putcmd(char s[], const char *cmd)
{
	uint32_t len = 0;

	s[len++] = '+';
	while (*cmd) {
		s[len++] = *cmd++;
	}
	s[len] = '\0';

	return len;
}

/**
 * @brief	AT Command의 파라미터를 버퍼에 쓰는 함수
 * @param	s	문자열 버퍼
 * @param	param	파라미터 값	
 * @return	문자열 길이
 */
static inline uint32_t putparam(char s[], const char *param, bool first)
{
	uint32_t len = 0;

	s[len++] = first ? '=' : ',';
	while (*param) {
		s[len++] = *param++;
	}
	s[len] = '\0';

	return len;
}

/**
 * @brief	AT Command의 파라미터를 버퍼에 쓰는 함수
 * @param	s	문자열 버퍼
 * @param	param	파라미터 값	
 * @return	문자열 길이
 */
#include <stdio.h>
static inline uint32_t putparam_int(char s[], int64_t param, bool first)
{
	uint32_t len = 0;

	s[len++] = first ? '=' : ',';
	printf ("%d\n\n\n\n", int_to_str(param, s + len));
	len += int_to_str(param, s + len);

	return len;
}

/**
 * @brief	AT Command의 파라미터를 버퍼에 쓰는 함수
 * @param	s	문자열 버퍼
 * @param	param	파라미터 값	
 * @return	문자열 길이
 */
static inline uint32_t putparam_ch(char s[], char param, bool first)
{
	uint32_t len = 0;

	s[len++] = first ? '=' : ',';
	s[len++] = param;
	s[len] ='\0';

	return len;
}

/**
 * @brief	"\r\n"을 버퍼에 쓰는 함수
 * @param	s	문자열 버퍼
 * @param	param	파라미터 값	
 * @return	문자열 길이
 */
static inline uint32_t putcrlf(char s[])
{
	uint32_t len = 0;

	s[len++] = '\r';
	s[len++] = '\n';
	s[len] = '\0';

	return len;
}

/**
 * @brief	가변인자를 받아 AT 명령어를 생성하는 함수
 * @param	s	문자열 버퍼
 * @param	cmd	명령어
 * @param	fmt	파라미터 출력 형식 \n
 * 			%d = 정수, %s = 문자열, %c = 문자 \n
 * 			(예 - "%d%s%c" -> "=정수,문자열,문자")
 * @param	params	파라미터들
 * @return	문자열 길이
 */
int64_t atcmd_vprintf(char s[], const char *cmd, 
		const char *restrict fmt, va_list params)
{
	uint32_t len = 0;

	len += putat(s + len);
	if (cmd) {
		len += putcmd(s + len, cmd);
		if (fmt) {
			bool first = true;

			while (*fmt) {
				if (*fmt++ != '%') {
					return -1;
				}

				switch (*fmt++) {
				case 'd':
					len += putparam_int(s + len, 
							va_arg(params, int), 
							first);
					break;
				case 's':
					len += putparam(s + len, 
							va_arg(params, char *), 
							first);
					break;
				case 'c':
					len += putparam_ch(s + len, 
							va_arg(params, int), 
							first);
					break;
				default:
					return -1;
				}
				first = false;
			}
		}
	}
	len += putcrlf(s + len);

	return len;
}

/**
 * @brief	가변인자를 받아 AT 명령어를 생성하는 함수
 * @param	s	문자열 버퍼
 * @param	cmd	명령어
 * @param	fmt	파라미터 출력 형식 \n
 * 			%d = 정수, %s = 문자열, %c = 문자 \n
 * 			(예 - "%d%s%c" -> "=정수,문자열,문자")
 * @param	...	파라미터들
 * @return	문자열 길이
 */
int64_t atcmd_printf(char s[], const char *restrict cmd,
		const char *restrict fmt, ...)
{
	int64_t len = 0;
	va_list params = { 0, };

	va_start(params, fmt);
	len = atcmd_vprintf(s, cmd, fmt, params);
	va_end(params);

	return len;
}
