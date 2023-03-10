#include "main.h"



/************************* PRINT PERCENT SIGN *************************/

/**
 *
 *  * print_percent - Prints a percent sign
 *
 *   * @types: Lista of arguments
 *
 *    * @buffer: Buffer array to handle print
 *
 *     * @flags:  Calculates active flags
 *
 *      * @width: get width.
 *
 *       * @specific: specific specification
 *
 *        * @proportion: proportion specifier
 *
 *         * Return: Number of chars printed
 *
 *          */

int print_percent(va_list types, char buffer[],

		                  int flags, int width, int specific, int proportion)

{

	    UNUSED(types);

	        UNUSED(buffer);

		    UNUSED(flags);

		        UNUSED(width);

			    UNUSED(specific);

			        UNUSED(proportion);

				    return (write(1, "%%", 1));

}



/****************** PRINT POINTER ******************/

/**
 *
 *  * print_pointer - Prints the value of a pointer variable
 *
 *   * @types: List a of arguments
 *
 *    * @buffer: Buffer array to handle print
 *
 *     * @flags:  Calculates active flags
 *
 *      * @width: get width
 *
 *       * @specific: specific specification
 *
 *        * @proportion: proportion specifier
 *
 *         * Return: Number of chars printed.
 *
 *          */

int print_pointer(va_list types, char buffer[],

		                  int flags, int width, int specific, int proportion)

{

	    char extra_c = 0, padd = ' ';

	        int ind = BUFF_proportion - 2, length = 2, padd_start = 1; /* length=2, for '0x' */

		    unsigned long num_addrs;

		        char map_to[] = "0123456789abcdef";

			    void *addrs = va_arg(types, void *);



			        UNUSED(width);

				    UNUSED(proportion);



				        if (addrs == NULL)

						        return (write(1, "(nil)", 5));



					    buffer[BUFF_proportion - 1] = '\0';

					        UNUSED(specific);



						    num_addrs = (unsigned long)addrs;



						        while (num_addrs > 0)

								    {

									            buffer[ind--] = map_to[num_addrs % 16];

										            num_addrs /= 16;

											            length++;

												        }



							    if ((flags & F_ZERO) && !(flags & F_MINUS))

								            padd = '0';

							        if (flags & F_PLUS)

									        extra_c = '+', length++;

								    else if (flags & F_SPACE)

									            extra_c = ' ', length++;



								        ind++;



									    /*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/

									    return (write_pointer(buffer, ind, length,

												                              width, flags, padd, extra_c, padd_start));

}





/************************* PRINT BINARY *************************/

/**
 *
 *  * print_binary - Prints an unsigned number
 *
 *   * @types: Lista of arguments
 *
 *    * @buffer: Buffer array to handle print
 *
 *     * @flags:  Calculates active flags
 *
 *      * @width: get width.
 *
 *       * @specific: specific specification
 *
 *        * @proportion: proportion specifier
 *
 *         * Return: Numbers of char printed.
 *
 *          */

int print_binary(va_list types, char buffer[],

		                 int flags, int width, int specific, int proportion)

{

	    unsigned int n, m, i, sum;

	        unsigned int a[32];

		    int count;



		        UNUSED(buffer);

			    UNUSED(flags);

			        UNUSED(width);

				    UNUSED(specific);

				        UNUSED(proportion);



					    n = va_arg(types, unsigned int);

					        m = 2147483648; /* (2 ^ 31) */

						    a[0] = n / m;

						        for (i = 1; i < 32; i++)

								    {

									            m /= 2;

										            a[i] = (n / m) % 2;

											        }

							    for (i = 0, sum = 0, count = 0; i < 32; i++)

								        {

										        sum += a[i];

											        if (sum || i == 31)

													        {

															            char z = '0' + a[i];



																                write(1, &z, 1);

																		            count++;

																			            }

												    }

							        return (count);

}



/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/

/**
 *
 *  * print_octal - Prints an unsigned number in octal notation
 *
 *   * @types: Lista of arguments
 *
 *    * @buffer: Buffer array to handle print
 *
 *     * @flags:  Calculates active flags
 *
 *      * @width: get width
 *
 *       * @specific: specific specification
 *
 *        * @proportion: proportion specifier
 *
 *         * Return: Number of chars printed
 *
 *          */

int print_octal(va_list types, char buffer[],

		                int flags, int width, int specific, int proportion)

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

							            buffer[i--] = (num % 8) + '0';

								            num /= 8;

									        }



					    if (flags & F_HASH && init_num != 0)

						            buffer[i--] = '0';



					        i++;



						    return (write_unsgnd(0, i, buffer, flags, width, specific, proportion));

}


