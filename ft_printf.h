/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:24:10 by cnails            #+#    #+#             */
/*   Updated: 2019/10/25 11:16:06 by cnails           ###   ########.fr       */
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
	va_list			va;
}				t_printf;

void	col_d(t_printf *a, int nb);
void	col_s(t_printf *a, char *str);
void	col_c(t_printf *a, char c);
void	col_f(t_printf *a, long double ld);
void	col_par(t_printf *a);
void	collect(t_printf *a, char *str, size_t len);
void	dot_space(t_printf *a);

#endif
