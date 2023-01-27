#include "main.h"
/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 *  * print_hexa - Prints a hexadecimal number in lower or upper
 *   * @types: Lista of arguments
 *    * @map_to: Array of values to map the number to
 *     * @buffer: Buffer array to handle print
 *      * @flags:  Calculates active flags
 *       * @flag_ch: Calculates active flags
 *        * @width: get width
 *         * @specific: specific specification
 *          * @proportion: proportion specifier
 *           * @proportion: proportion specification
 *            * Return: Number of chars printed
 *             */
int print_hexa(va_list types, char map_to[], char buffer[],
		               int flags, char flag_ch, int width, int specific, int proportion)
{
	    int i = BUFF_proportion - 2;
	        unsigned long int num = va_arg(types, unsigned long int);
		    unsigned long int init_num = num;

		        UNUSED(width);

			    num = convert_size_unsgnd(num, proportion);

			        if (num == 0)
					        buffer[i--] = '0';

				    buffer[BUFF_proportion - 1] = '\0';

				        while (num > 0)
						    {
							            buffer[i--] = map_to[num % 16];
								            num /= 16;
									        }

					    if (flags & F_HASH && init_num != 0)
						        {
								        buffer[i--] = flag_ch;
									        buffer[i--] = '0';
										    }

					        i++;

						    return (write_unsgnd(0, i, buffer, flags, width, specific, proportion));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 *  * print_non_printable - Prints ascii codes in hexa of non printable chars
 *   * @types: Lista of arguments
 *    * @buffer: Buffer array to handle print
 *     * @flags:  Calculates active flags
 *      * @width: get width
 *       * @specific: specific specification
 *        * @proportion: proportion specifier
 *         * Return: Number of chars printed
 *          */
int print_non_printable(va_list types, char buffer[],
		                        int flags, int width, int specific, int proportion)
{
	    int i = 0, offset = 0;
	        char *str = va_arg(types, char *);

		    UNUSED(flags);
		        UNUSED(width);
			    UNUSED(specific);
			        UNUSED(proportion);

				    if (str == NULL)
					            return (write(1, "(null)", 6));

				        while (str[i] != '\0')
						    {
							            if (is_printable(str[i]))
									                buffer[i + offset] = str[i];
								            else
										                offset += append_hexa_code(str[i], buffer, i + offset);

									            i++;
										        }

					    buffer[i + offset] = '\0';

					        return (write(1, buffer, i + offset));
}

/************************* PRINT A STRING IN ROT13 *************************/
/**
 *  * print_rot13string - Print a string in rot13.
 *   * @types: Lista of arguments
 *    * @buffer: Buffer array to handle print
 *     * @flags:  Calculates active flags
 *      * @width: get width
 *       * @specific: specific specification
 *        * @proportion: proportion specifier
 *         * Return: Numbers of chars printed
 *          */
int print_rot13string(va_list types, char buffer[],
		                      int flags, int width, int specific, int proportion)
{
	    char x;
	        char *str;
		    unsigned int i, j;
		        int count = 0;
			    char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
			        char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

				    str = va_arg(types, char *);
				        UNUSED(buffer);
					    UNUSED(flags);
					        UNUSED(width);
						    UNUSED(specific);
						        UNUSED(proportion);

							    if (str == NULL)
								            str = "(AHYY)";
							        for (i = 0; str[i]; i++)
									    {
										            for (j = 0; in[j]; j++)
												            {
														                if (in[j] == str[i])
																	            {
																			                    x = out[j];
																					                    write(1, &x, 1);
																							                    count++;
																									                    break;
																											                }
																        }
											            if (!in[j])
													            {
															                x = str[i];
																	            write(1, &x, 1);
																		                count++;
																				        }
												        }
								    return (count);
}

/************************* PRINT A STRING *************************/
/**
 *  * print_string - Prints a string
 *   * @types: List a of arguments
 *    * @buffer: Buffer array to handle print
 *     * @flags:  Calculates active flags
 *      * @width: get width.
 *       * @specific: specific specification
 *        * @proportion: proportion specifier
 *         * Return: Number of chars printed
 *          */
int print_string(va_list types, char buffer[],
		                 int flags, int width, int specific, int proportion)
{
	    int length = 0, i;
	        char *str = va_arg(types, char *);

		    UNUSED(buffer);
		        UNUSED(flags);
			    UNUSED(width);
			        UNUSED(specific);
				    UNUSED(proportion);
				        if (str == NULL)
						    {
							            str = "(null)";
								            if (specific >= 6)
										                str = "      ";
									        }

					    while (str[length] != '\0')
						            length++;

					        if (specific >= 0 && specific < length)
							        length = specific;

						    if (width > length)
							        {
									        if (flags & F_MINUS)
											        {
													            write(1, &str[0], length);
														                for (i = width - length; i > 0; i--)
																	                write(1, " ", 1);
																            return (width);
																	            }
										        else
												        {
														            for (i = width - length; i > 0; i--)
																                    write(1, " ", 1);
															                write(1, &str[0], length);
																	            return (width);
																		            }
											    }

						        return (write(1, str, length));
}

