/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libftprintf.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 15:23:27 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/27 08:05:28 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <stdarg.h>
# include <wchar.h>

/*
**	This struct holds all the info about a flag for a conversion character.
**	Form is either normal (0) or alternate (1).
**	Padding is either blank (0), zero (1) or left (2).
**	Sign is none (0), space (32) or plus (43).
**	Grouping is off (0) or on (1).
**	Minimum_width is the minimum width of the field.
**	Precision is the precision of the field.
**	Modifier is the length modifier. 0 for none, 1 for l, 2 for ll,
**		3 for h, 4 for hh.
**	Conversion is the type of conversion to be done.
*/
typedef struct		s_flag
{
	int				form;
	int				padding;
	char			sign;
	int				grouping;
	size_t			min_width;
	int				precision;
	int				precision_given;
	int				modifier;
	char			conversion;
	int				remove_trailing_zeroes;
}					t_flag;

/*
**	ft_printf.c
*/
int					ft_printf(const char *format, ...);
int					length_to_flag(const char *s);
int					print_text(const char *s);
int					print_conversion(t_flag *flag, va_list args, int printed);
int					print_error(t_flag *flag, va_list args);

/*
**	convert_c.c
*/
int					convert_c(t_flag *flag, va_list args);

/*
**	convert_s.c
*/
int					convert_s(t_flag *flag, va_list args);

/*
**	convert_i.c
*/
int					convert_i(t_flag *flag, va_list args);

/*
**	convert_u.c
*/
int					convert_u(t_flag *flag, va_list args);

/*
**	convert_x.c
*/
int					convert_x(t_flag *flag, va_list args);

/*
**	convert_p.c
*/
int					convert_p(t_flag *flag, va_list args);

/*
**	convert_f.c
*/
int					convert_f(t_flag *flag, va_list args);
char				*trim_zeroes_in_fraction(char *source);

/*
**	convert_n.c
*/
int					convert_n(t_flag *flag, va_list args, int printed);

/*
**	convert_e.c
*/
int					convert_e(t_flag *flag, va_list args);

/*
**	convert_g.c
*/
int					convert_g(t_flag *flag, va_list args);

/*
**	flag_functions.c
*/
t_flag				*create_flag(const char *s, va_list args);
t_flag				*create_empty_flag(void);
int					get_flags(t_flag *flag, const char *s);
int					get_width(t_flag *flag, const char *s, va_list args);
int					get_precision(t_flag *flag, const char *s, va_list args);

/*
**	flag_functions2.c
*/
int					get_length_modifier(t_flag *flag, const char *s);
int					is_flag_character(char c);
int					is_conversion_character(char c);
int					flag_length(const char *s);

/*
**	string_functions.c
*/
void				fill_string(char *string, char c, int start, int length);
size_t				amount_digits(long long num, int grouping_mode);
size_t				amount_udigits(unsigned long long num, int grouping_mode);
size_t				amount_digits_hex(unsigned long long num);
char				*join_and_free(char *s1, char *s2);

/*
**	print_functions.c
*/
int					print_and_free(char *result, int amount);
int					wprint_and_free(wchar_t *result, int amount);
void				wchar_to_utf8_string(unsigned char *result, wchar_t *src,
						int amount);
int					single_wchar_to_utf8(unsigned char *result, wchar_t src);
int					count_bytes(wchar_t *string, int amount);

/*
**	format_functions.c
*/
char				*format_numeric_string(char *tmp, t_flag *flag,
						char sign, size_t len);

/*
**	float_functions.c
*/
int					get_dbl_sign(double num);
int					get_dbl_exp(double num);
unsigned long long	get_dbl_man(double num);
int					is_special_case(double num);
char				*handle_special_case(double num, t_flag *flag);

/*
**	exponent_functions.c
*/
int					get_exponent(double num);
double				raise_exponent(double num, int exponent);
int					fraction_all_zeroes(double num);

/*
**	libft_functions
*/

void				*ft_memcpy(void *dst, const void *src, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
int					ft_isdigit(int c);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
int					ft_max(int a, int b);
char				*ft_lltoa(long long num, int length, int grouping_mode);
char				*ft_ulltoa(unsigned long long num, int length,
						int grouping_mode);
char				*ft_itoa_base(unsigned long long n, unsigned char base,
						int length, int capital);
double				ft_n_times_ten(double num, int amount);
long long			ft_n_divided_by_ten(long long num, int amount);
int					ft_wcbytelen(wchar_t c);
size_t				ft_wstrlen(const wchar_t *s);
wchar_t				*ft_wstrdup(wchar_t *source);

#endif
