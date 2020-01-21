/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:24:10 by cnails            #+#    #+#             */
/*   Updated: 2020/01/20 18:20:54 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <stdarg.h>

typedef	struct	s_printf
{
	size_t			len;
	int				fd;
	char			ch;
	char			*buf;
	char			*str;
	int				nbr;
	int				space;
	int				space_2;
	int				sign;
	int				align;
	int				dot;
	int				s;
	int				h;
	int				l;
	int				sharp;
	int				one_s;
	va_list			va;
}				t_printf;

void	col_d(t_printf *a, void *nb);
void	col_s(t_printf *a, char *str);
void	col_c(t_printf *a, char c);
void	col_f(t_printf *a, long double ld);
void	col_par(t_printf *a);
void	col_dot(t_printf *a);
void	col_space(t_printf *a, char *str, size_t len);
void	collect(t_printf *a, char *str, size_t len);
void	dot_space(t_printf *a);
void	ft_printbits(unsigned long int octet);
void	col_ld(t_printf *a, long int nb, char c);

#endif
