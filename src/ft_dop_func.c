/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dop_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmetallo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:42:32 by dmetallo          #+#    #+#             */
/*   Updated: 2020/01/30 16:42:34 by dmetallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	col_plus_min_sl(t_printf *a)
{
	if (*a->str == '-')
		a->align = 1;
	if (*a->str == '+')
		a->sign = 1;
	if (*a->str == ' ')
		a->one_s = 1;
	a->str++;
	if (*a->str == '-' || *a->str == '+' || *a->str == '\'' || *a->str == ' ')
		col_plus_min_sl(a);
}

void	col_dot(t_printf *a)
{
	if (*a->str == '#')
	{
		a->sharp = 1;
		a->str++;
	}
	if (*a->str == '.')
	{
		a->dot = 1 + a->dot;
		a->str++;
	}
	else if (*a->str == '0')
	{
		a->dot = 2;
		a->str++;
	}
	if (*a->str == '-')
	{
		a->dot = 0;
		col_plus_min_sl(a);
	}
	if (*a->str == '+')
		col_plus_min_sl(a);
	if (*a->str >= '0' && *a->str <= '9')
		dot_space(a);
}

void	col_hl(t_printf *a)
{
	if (*a->str == 'h')
	{
		if (a->h == 1)
			a->h = 2;
		else
			a->h = 1;
	}
	if (*a->str == 'l')
	{
		if (a->l == 1)
			a->l = 2;
		else
			a->l = 1;
	}
	a->str++;
	if (*a->str == 'h' || *a->str == 'l')
		col_hl(a);
}

char	*ft_qitoa(unsigned long int n, int l)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * (l + 1))))
		return (NULL);
	str[l--] = '\0';
	while (l != -1)
	{
		str[l--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

void	show(t_printf *a)
{
	if (a->n)
	{
		write(a->fd, "\nlen = ", 7);
		ft_putnbr_fd(a->len + a->new_len, a->fd);
	}
}
