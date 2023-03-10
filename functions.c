#include "main.h"

/************************* PRINT CHAR *************************/

/**
 *  * print_char - Prints a char
 *   * @types: List a of arguments
 *    * @buffer: Buffer array to handle print
 *     * @flags:  Calculates active flags
 *      * @width: Width
 *       * @specific: specific specification
 *        * @proportion: proportion specifier
 *         * Return: Number of chars printed
 *          */
int print_char(va_list types, char buffer[],
		            int flags, int width, int specific, int proportion)
{
	    char c = va_arg(types, int);
return (handle_write_char(c, buffer, flags, width, specific, proportion));
}

/************************* PRINT INT *************************/
/**
 *  * print_int - Print int
 *   * @types: Lista of arguments
 *    * @buffer: Buffer array to handle print
 *     * @flags:  Calculates active flags
 *      * @width: get width.
 *       * @specific: specific specification
 *        * @proportion: proportion specifier
 *         * Return: Number of chars printed
 *          */
int print_int(va_list types, char buffer[],
		              int flags, int width, int specific, int proportion)
{
	    int i = BUFF_proportion - 2;
	        int is_negative = 0;
		    long int n = va_arg(types, long int);
		        unsigned long int num;

			    n = convert_proportion_number(n, proportion);
			        if (n == 0)
					        buffer[i--] = '0';
				    buffer[BUFF_proportion - 1] = '\0';
				        num = (unsigned long int)n;

					    if (n < 0)
						        {
								        num = (unsigned long int)((-1) * n);
									        is_negative = 1;
										    }
					        while (num > 0)
							    {
	buffer[i--] = (num % 10) + '0';					            num /= 10;
										        }
						    i++;
						        return (write_number(is_negative, i, buffer, flags, width, specific, proportion));
}

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 *  * print_unsigned - Prints an unsigned number
 *   * @types: List a of arguments
 *    * @buffer: Buffer array to handle print
 *     * @flags:  Calculates active flags
 *      * @width: get width
 *       * @specific: specific specification
 *        * @proportion: proportion specifier
 *         * Return: Number of chars printed.
 *          */
int print_unsigned(va_list types, char buffer[],
		                   int flags, int width, int specific, int proportion)
{
	    int i = BUFF_proportion - 2;
	        unsigned long int num = va_arg(types, unsigned long int);
		    num = convert_size_unsgnd(num, proportion);

		        if (num == 0)
				        buffer[i--] = '0';
			    buffer[BUFF_proportion - 1] = '\0';

			        while (num > 0)
					    {
						            buffer[i--] = (num % 10) + '0';
							            num /= 10;
								        }
				    i++;
				        return (write_unsgnd(0, i, buffer, flags, width, specific, proportion));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 *  * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 *   * @types: Lista of arguments
 *    * @buffer: Buffer array to handle print
 *     * @flags:  Calculates active flags
 *      * @width: get width
 *       * @specific: specific specification
 *        * @proportion: proportion specifier
 *         * Return: Number of chars printed
 *          */
int print_hexadecimal(va_list types, char buffer[],
		                      int flags, int width, int specific, int proportion)
{
	    return (print_hexa(types, "0123456789abcdef", buffer,
				                           flags, 'x', width, specific, proportion));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 *  * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 *   * @types: Lista of arguments
 *    * @buffer: Buffer array to handle print
 *     * @flags:  Calculates active flag
 *      * @width: get width
 *       * @specific: specific specification
 *        * @proportion: proportion specifier
 *         * Return: Number of chars printed
 *          */
int print_hexa_upper(va_list types, char buffer[],
		                     int flags, int width, int specific, int proportion)
{
	    return (print_hexa(types, "0123456789ABCDEF", buffer,
				                           flags, 'X', width, specific, proportion));
}
