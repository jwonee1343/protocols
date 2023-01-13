// UTF-8 encoding
/**
 * @brief	AT 명령어를 생성하기 위한 함수 선언
 * @author	Jaewon Choi <jwonee1343@gmail.com>
 */
#ifndef __ATCMD_H
#define __ATCMD_H

#include <stdint.h>
#include <stdarg.h>

int64_t atcmd_vprintf(char s[], const char *cmd, 
		const char *restrict fmt, va_list params);

int64_t atcmd_printf(char s[], const char *restrict cmd, 
		const char *restrict fmt, ...);

#endif // __ATCMD_H
