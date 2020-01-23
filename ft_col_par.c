/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_col_par.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:27:35 by cnails            #+#    #+#             */
/*   Updated: 2020/01/23 15:59:28 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	col_f(t_printf *a, long double ld)
{
	char	*str;

	str = ft_dtoa(ld, a->nbr + 7);
	collect(a, str, ft_strlen(str));
	a->nbr = -1;
}

void	dot_space(t_printf *a)
{
	char	*str;
	int		n;

	a->str = (*a->str == '.') ? a->str + 1 : a->str;
	str = a->str;
	while (*(a->str) >= '0' && *(a->str) <= '9' && *(a->str + 1))
		a->str++;
	n = ft_atoi(str);
	n *= (a->align) ? -1 : 1;
	if (a->dot != 0 && a->dot != 2)
		a->space_2 = n > 0 ? n : -n;
	else
		a->space = n;
	if (*a->str == '.')
		col_dot(a);
}

void	col_par_second(t_printf *a)
{
	if (*(a->str - 1) == ' ')
		a->one_s = 1;
	if (*a->str == '+' || *a->str == '-' || *a->str == '\'')
		col_plus_min_sl(a);
	if (*a->str == '.' || *a->str == '0' || *a->str == '#')
		col_dot(a);
	if (*a->str >= '0' && *a->str <= '9')
		dot_space(a);
	if (*a->str == 'h' || *a->str == 'l')
		col_hl(a);
}

void	col_par(t_printf *a)
{
	col_par_second(a);
	if (*a->str == 'd' || *a->str == 'i' || *a->str == 'D' || *a->str == 'I')
		col_d(a, va_arg(a->va, void *));
	else if (*a->str == 's' || *a->str == 'S')
		col_s(a, va_arg(a->va, char *));
	else if (*a->str == 'u')
		col_u(a, va_arg(a->va, void *), 'u');
	else if (*a->str == 'c' || *a->str == 'C')
		col_c(a, va_arg(a->va, int));
	else if (*a->str == 'o')
		col_o(a, va_arg(a->va, long long int));
	else if (*a->str == '%')
		col_c(a, '%');
	else if (*a->str == 'f')
		col_f(a, va_arg(a->va, double));
	else if (*a->str == 'x' || *a->str == 'X')
		col_x(a, va_arg(a->va, void *), *a->str);
	else if (*a->str == 'p')
		col_p(a, va_arg(a->va, void *), *a->str);
	else
		collect(a, a->str, 1);
}
