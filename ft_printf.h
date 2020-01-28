/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:24:10 by cnails            #+#    #+#             */
/*   Updated: 2020/01/27 19:03:53 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
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
	int				l;
	int				big_l;
	int				sharp;
	int				one_s;
	va_list			va;
}					t_printf;

static char			*ft_ftoa(t_printf *a, double f, int n);
static char			*ft_lftoa(t_printf *a, long double f, int n);
void				col_d(t_printf *a, void *nb);
void				col_u(t_printf *a, void *nb, char c);
void				col_s(t_printf *a, char *str);
void				col_c(t_printf *a, char c);
void				col_o(t_printf *a, long long int c);
void				col_f(t_printf *a, double d);
void				col_lf(t_printf *a, long double d);
void				col_p(t_printf *a, void *str, char c);
void				col_x(t_printf *a, void *str, char c);
void				dot_space(t_printf *a);
void				col_plus_min_sl(t_printf *a);
void				col_hl(t_printf *a);
void				col_par(t_printf *a);
void				col_dot(t_printf *a);
void				collect_space(t_printf *a);
void				col_space(t_printf *a, char *str, size_t len);
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

#endif
