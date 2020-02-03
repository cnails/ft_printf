/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmetallo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:43:50 by dmetallo          #+#    #+#             */
/*   Updated: 2020/01/30 16:43:50 by dmetallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft/libft.h"
# include <stdarg.h>

typedef	struct		s_printf
{
	size_t			len;
	int				fd;
	char			ch;
	char			*buf;
	char			*str;
	int				space;
	int				space_2;
	int				sign;
	int				align;
	int				dot;
	int				s;
	int				h;
	int				new_len;
	int				l;
	int				big_l;
	int				sharp;
	int				one_s;
	int				n;
	va_list			va;
}					t_printf;

void				col_d(t_printf *a, void *nb);
void				col_u(t_printf *a, void *nb);
void				col_s(t_printf *a, char *str);
void				col_c(t_printf *a, char c);
void				col_b(t_printf *a, void *nb);
void				col_o(t_printf *a, void *c);
void				col_f(t_printf *a, double d);
void				col_k(t_printf *a, unsigned long long k);
void				col_lf(t_printf *a, long double d);
void				col_p(t_printf *a, void *str, char c);
void				col_x(t_printf *a, void *str, char c);
void				dot_space(t_printf *a);
void				col_plus_min_sl(t_printf *a);
void				col_hl(t_printf *a);
void				col_par(t_printf *a);
void				col_dot(t_printf *a);
void				collect_space(t_printf *a);
void				col_space(t_printf *a, size_t len);
void				collect(t_printf *a, char *str, size_t len);
void				dot_space(t_printf *a);
long long			ret_nb(t_printf *a, void *nb);
void				ft_printbits(unsigned long int octet);
void				col_ld(t_printf *a, long int nb, char c);
void				col_with_sign(t_printf *a, long long *l, char *sign);
void				one_more_costil(t_printf *a, long long *l);
char				*post_dot(double f, char *str, int l);
long double			lrounding(long double nb, int l);
double				rounding(double nb, int l);
char				*ft_qitoa(unsigned long int n, int l);
char				*ft_ftoa(t_printf *a, double f, int n);
char				*ft_lftoa(t_printf *a, long double f, int n);
char				*ret_s(t_printf *a, void *str, char c);
char				*ret_us(t_printf *a, void *str, char c);
char				*ft_uitoa_base(unsigned long long int nbr,\
								int base, char a);
void				dop_c(t_printf *a);
void				col_o_one_more(t_printf *a, char *str);
void				col_astr(t_printf *a, int nb);
void				dop_p(t_printf *a, char *s);
void				show(t_printf *a);
void				col_par_third(t_printf *a);

#endif
