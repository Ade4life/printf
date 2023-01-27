#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 *
 *  * handle_write_char - Prints a string
 *   * @c: char types.
 *    * @buffer: Buffer array to handle print
 *     * @flags:  Calculates active flags.
 *      * @width: get width.
 *       * @specific: specific specifier
 *        * @proportion: Proportion specifie.
 *          * Return: Number of chars printed.
 *           */
int handle_write_char(char c, char buffer[],
		                      int flags, int width, int specific, int proportion)
{
	    /* char is stored at left and paddind at buffer's right */
	    int i = 0;
	        char padd = ' ';

		    UNUSED(specific);
		        UNUSED(proportion);
			    if (flags & F_ZERO)
				            padd = '0';
			        buffer[i++] = c;
				    buffer[i] = '\0';
				        if (width > 1)
						    {
							            buffer[BUFF_proportion - 1] = '\0';
								            for (i = 0; i < width - 1; i++)
										                buffer[BUFF_proportion - i - 2] = padd;
									            if (flags & F_MINUS)
											                return (write(1, &buffer[0], 1) +
															                    write(1, &buffer[BUFF_proportion - i - 1], width - 1));
										            else
												                return (write(1, &buffer[BUFF_proportion - i - 1], width - 1) +
																                    write(1, &buffer[0], 1));
											        }

					    return (write(1, &buffer[0], 1));
}

/**
 *  * write_unsgnd - Writes an unsigned number
 *   * @is_negative: Number indicating if the num is negative
 *    * @ind: Index at which the number starts in the buffer
 *     * @buffer: Array of chars
 *      * @flags: Flags specifiers
 *       * @width: Width specifier
 *        * @specific: Specific specifier
 *         * @proportion: Proportion specifier
 *           * Return: Number of written chars.
 *            */
int write_unsgnd(int is_negative, int ind,
		                 char buffer[],
				                  int flags, int width, int specific, int proportion)
{
	/* The number is stored at the bufer's right and starts at position i */
	    int length = BUFF_proportion - ind - 1, i = 0;
	        char padd = ' ';
		    UNUSED(is_negative);
		        UNUSED(proportion);
			    if (specific == 0 && ind == BUFF_proportion - 2 && buffer[ind] == '0')
				            return (0); /* printf(".0d", 0)  no char is printed */
			        if (specific > 0 && specific < length)
					        padd = ' ';
				    while (specific > length)
					        {
							   uffer[--ind] = '0';
								      length++;
									    }
				     if ((flags & F_ZERO) && !(flags & F_MINUS))
						        padd = '0';

					    if (width > length)
						        {
			for (i = 0; i < width - length; i++)
									            buffer[i] = padd;
									        buffer[i] = '\0';
										if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
												        {
										return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
															            }
											        else /* Asign extra char to left of padding [padd>buffer]*/
													        {
											return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
																            }
												    }
					        return (write(1, &buffer[ind], length));
}

/**
 *  * write_pointer - Write a memory address
 *   * @buffer: Arrays of chars
 *    * @ind: Index at which the number starts in the buffer
 *     * @length: Length of number
 *      * @width: Wwidth specifier
 *       * @flags: Flags specifier
 *        * @padd: Char representing the padding
 *         * @extra_c: Char representing extra char
 *          * @padd_start: Index at which padding should start
 *            * Return: Number of written chars.
 *             */
int write_pointer(char buffer[], int ind, int length,
		                  int width, int flags, char padd, char extra_c, int padd_start)
{
	    int i;
	        if (width > length)
			    {
				     for (i = 3; i < width - length + 3; i++)
						              buffer[i] = padd;
					            buffer[i] = '\0';
						            if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
								            {										                buffer[--ind] = 'x';
												            buffer[--ind] = '0';
													                if (extra_c)
																     buffer[--ind] = extra_c;
															            return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
																            }
							            else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
									            {
											                buffer[--ind] = 'x';
													            buffer[--ind] = '0';
														                if (extra_c)
																	                buffer[--ind] = extra_c;
																            return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
																	            }
								            else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
										            {
												                if (extra_c)
															        buffer[--padd_start] = extra_c;
														            buffer[1] = '0';
															                buffer[2] = 'x';
																	            return (write(1, &buffer[padd_start], i - padd_start) +
																				                        write(1, &buffer[ind], length - (1 - padd_start) - 2));
																		            }
									        }
		    buffer[--ind] = 'x';
		        buffer[--ind] = '0';
			    if (extra_c)
				            buffer[--ind] = extra_c;
return (write(1, &buffer[ind], BUFF_proportion - ind - 1));
}



/**
 *  * handle_print - Prints an argument based on its type
 *   * @fmt: Formatted string in which is to print the arguments.
 *    * @list: List of arguments to be printed.
 *     * @ind: ind.
 *      * @buffer: Buffer array to handle print.
 *       * @flags: Calculates active flags
 *        * @width: get width.
 *         * @specific: Specific specification
 *          * @proportion: Proportion specifier
 *           * Return: 1 or 2;
 *            */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
		                 int flags, int width, int specific, int proportion)
{
	    int i, unknow_len = 0, printed_chars = -1;
	        fmt_t fmt_types[] =
			    {
				            {'c', print_char}, {'s', print_string}, {'%', print_percent},
					            {'i', print_int}, {'d', print_int}, {'b', print_binary},
						            {'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
							            {'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
								            {'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
					        };
		    for (i = 0; fmt_types[i].fmt != '\0'; i++)
			            if (fmt[*ind] == fmt_types[i].fmt)
					                return (fmt_types[i].fn(list, buffer, flags, width, specific, proportion));

		        if (fmt_types[i].fmt == '\0')
				    {
					            if (fmt[*ind] == '\0')
							           return (-1);
						            unknow_len += write(1, "%%", 1);
							            if (fmt[*ind - 1] == ' ')
									                unknow_len += write(1, " ", 1);
								            else if (width)
										            {
												                --(*ind);
														 while (fmt[*ind] != ' ' && fmt[*ind] != '%')
													                    --(*ind);

															                if (fmt[*ind] == ' ')
																		                --(*ind);
																	            return (1);
																		            }
									            unknow_len += write(1, &fmt[*ind], 1);
										            return (unknow_len);
											        }
			    return (printed_chars);
}
