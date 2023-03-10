#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_proportion 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* proportionS */
#define S_LONG 2
#define S_SHORT 1

/**
 *  * struct fmt - Struct op
 *   *
 *    * @fmt: The format.
 *     * @fn: The function associated.
 *      */
struct fmt
{
	    char fmt;
	        int (*fn)(va_list, char[], int, int, int, int);
};

/**
 *  * typedef struct fmt fmt_t - Struct op
 *    * @fmt: The format.
 *     * @fm_t: The function which is associated.
 *      */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i,
va_list list, char buffer[], int flags, int width, int specific, int proportion);
int print_char(va_list types, char buffer[],
		               int flags, int width, int specific, int proportion);
int print_string(va_list types, char buffer[],
		                 int flags, int width, int specific, int proportion);
int print_percent(va_list types, char buffer[],
		                  int flags, int width, int specific, int proportion);

int print_int(va_list types, char buffer[],
		              int flags, int width, int specific, int proportion);
int print_binary(va_list types, char buffer[],
		                 int flags, int width, int specific, int proportion);
int print_unsigned(va_list types, char buffer[],
		                   int flags, int width, int specific, int proportion);
int print_octal(va_list types, char buffer[],
		                int flags, int width, int specific, int proportion);
int print_hexadecimal(va_list types, char buffer[],
		                      int flags, int width, int specific, int proportion);
int print_hexa_upper(va_list types, char buffer[],
		         int flags, int width, int specific, int proportion);
int print_hexa(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int specific, int proportion);
int print_non_printable(va_list types, char buffer[],
		                        int flags, int width, int specific, int proportion);
int print_pointer(va_list types, char buffer[],
		                  int flags, int width, int specific, int proportion);
int get_flags(const char *format, int *x);
int get_width(const char *format, int *x, va_list list);
int get_specific(const char *format, int *x, va_list list);
int get_proportion(const char *format, int *x);

int print_reverse(va_list types, char buffer[],
		           int flags, int width, int specific, int proportion);
int print_rot13string(va_list types, char buffer[],
		            int flags, int width, int specific, int proportion);

int handle_write_char(char c, char buffer[],
		                      int flags, int width, int specific, int proportion);
int write_number(int is_positive, int ind, char buffer[],
		                 int flags, int width, int specific, int proportion);
int write_num(int ind, char bff[], int flags, int width, int specific,
		              int length, char padd, char extra_c);
int write_pointer(char buffer[], int ind, int length,
		                  int width, int flags, char padd, char extra_c, int padd_start);

int write_unsgnd(int is_negative, int ind,
		                 char buffer[],
				                  int flags, int width, int specific, int proportion);

int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_proportion_number(long int num, int proportion);
long int convert_proportion_unsgnd(unsigned long int num, int proportion);

#endif /* MAIN_H */
