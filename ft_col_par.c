/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_col_par.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:27:35 by cnails            #+#    #+#             */
/*   Updated: 2019/11/28 12:37:47 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	col_d(t_printf *a, int nb)
{
	int i;
	int f;
	int tmp;
	char sign;

	tmp = nb;
	i = 1;
	if ((f = (tmp < 0) ? 1 : 0))
		tmp *= -1;
	while ((tmp /= 10))
		i++;
	sign = (a->sign ? (nb > 0 ? '+' : '-') : '-'); // stop, it is illegal
	if (sign == '+')
		collect(a, ft_strjoin(&sign, ft_itoa(nb)), i + f + 1);
	else
		collect(a, ft_itoa(nb), i + f);
}

void	col_s(t_printf *a, char *str)
{
	int u;

	if (a->space && a->dot == 1)
	{
		a->s = a->space;
		a->space = 0;
	}
	if (ft_strlen(str) > a->s && a->dot == 1)
		u = a->s;
	else
		u = ft_strlen(str);
	collect(a, str, u);
}

void	col_c(t_printf *a, char c)
{
	collect(a, &c, 1);
}

void	col_f(t_printf *a, long double ld)
{
	char	*str;

	str = ft_dtoa(ld, a->nbr + 7);
	collect(a, str, ft_strlen(str));
	a->nbr = -1;
}

void	col_x(t_printf *a, void *str, char c)
{
	char	*s;
	int		u;

	s = ft_itoa_base((int)str, 16);
	if (c == 'p')
		if (a->dot)
		{
			if (a->space)
			{
				u = a->space;
				a->space = 0;
			}
			collect(a, "0x", 2);
			a->space = u;
			col_space(a, str, ft_strlen(s));
			collect(a, ft_strjoin("", s), ft_strlen(s));
		}
		else
			collect(a, ft_strjoin("0x", s), ft_strlen(s) + 2);
	else
		collect(a, s, ft_strlen(s));
	free(s);
}

void	dot_space(t_printf *a)
{
	char	*str;
	int		n;

	a->str = (*a->str == '.') ? a->str + 1 : a->str;
	str = a->str;
	while (*(a->str) >= '0' && *(a->str) <= '9')
		a->str++;
	if (*a->str == '.')
		a->str++;
	n = ft_atoi(str);
	n *= (a->align) ? -1 : 1;
	// if (*(str - 1) == '.')
		// a->nbr = n;
	// if (*(str - 1) == '%')
	a->space = n;
	// printf("n = %d\n", n);
}

void	col_plus_min_sl(t_printf *a)
{
	if (*a->str == '-')
		a->align = 1;
	if (*a->str == '+')
		a->sign = 1;
	// printf("in col = %c\n", *a->str);
	a->str++;
	// printf("in col = %c\n", *a->str);
	if (*a->str == '-' || *a->str == '+' || *a->str == '\'')
		col_plus_min_sl(a);
	// col_par(a);
}

void	col_dot(t_printf *a)
{
	if (*a->str == '.')
		a->dot = 1;
	else
		a->dot = 2;
	a->str++;
}

void	col_par(t_printf *a)
{

//	if ((*a->str >= '0' && *a->str <= '9') || *a->str == '-' || *a->str == '.')

	if (*a->str == '+' || *a->str == '-' || *a->str == '\'')
		col_plus_min_sl(a);
	// printf("c = %c\n", *a->str);
	if (*a->str == '.' || *a->str == '0')
		col_dot(a);
	// printf("c = %c\n", *a->str);
	if (*a->str >= '0' && *a->str <= '9' && !(a->align))
		dot_space(a);
	if (*a->str == 'd' || *a->str == 'i' || *a->str == 'D' || *a->str == 'I')
		col_d(a, va_arg(a->va, int));
	if (*a->str == 's' || *a->str == 'S')
		col_s(a, va_arg(a->va, char *));
	if (*a->str == 'c' || *a->str == 'C')
		col_c(a, va_arg(a->va, int));
	if (*a->str == '%')
		collect(a, "%", 1);
	if (*a->str == 'f')
		col_f(a, va_arg(a->va, double));
	if (*a->str == 'x' || *a->str == 'p')
		col_x(a, va_arg(a->va, void *), *a->str);
	// if (*a->str == '\'' && *a->str + 1 == 'd')
	// {
		// printf("1\n");
		// col_f(a, va_arg(a->va, int));
	// }
}

