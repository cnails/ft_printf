/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_lf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmetallo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:40:53 by dmetallo          #+#    #+#             */
/*   Updated: 2020/01/30 16:41:01 by dmetallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			col_lf(t_printf *a, long double d)
{
	char	*str;
	char	*tmp;

	a->space = a->one_s && a->space ? a->space-- : a->space++;
	if (a->one_s && a->dot && d >= 0 && !a->sign)
	{
		a->buf = a->buf ? a->buf : ft_strset(' ', 0);
		if (a->space)
			a->space = a->space + (a->align ? 1 : -1);
		tmp = ft_strjoin(a->buf, " ");
		a->len++;
		free(a->buf);
		a->buf = tmp;
	}
	if (d < 0)
		tmp = ft_strdup("-");
	else
		tmp = (a->sign) ? ft_strdup("+") : ft_strdup("");
	str = ft_lftoa(a, d < 0 ? d * -1 : d, (!a->dot ? 6 : a->space_2));
	if (a->dot == 3)
		a->dot = 2;
	collect(a, ft_strjoin(tmp, str), ft_strlen(str) + ((d < 0 || a->sign) ?\
		1 : 0));
}

char			*ft_lftoa(t_printf *a, long double f, int n)
{
	char		*str[2];
	long double	l[2];

	l[0] = n;
	l[1] = (f - (long long)f);
	f = lrounding(f, l[0]);
	if (f != f)
		return ("nan");
	str[0] = ft_itoa((long long)(f));
	l[1] = lrounding(l[1], l[0]);
	while (n-- > 0)
		l[1] *= 10;
	if (n && (a->space_2 || !a->dot))
	{
		str[1] = ft_strjoin(str[0], ".");
		free(str[0]);
		str[0] = post_dot(l[1], str[1], l[0]);
	}
	else if (a->sharp)
	{
		str[1] = ft_strjoin(str[0], ".");
		free(str[0]);
		str[0] = str[1];
	}
	return (str[0]);
}

long double		lrounding(long double nb, int l)
{
	int			i;
	long double	tmp;

	tmp = nb - (unsigned long int)nb;
	i = -1;
	while (++i != l)
		tmp *= 10;
	tmp += 0.5;
	while (--l >= 0)
		tmp /= 10;
	return ((unsigned long int)nb + tmp);
}
