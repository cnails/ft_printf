/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_lf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:32:55 by dmetallo          #+#    #+#             */
/*   Updated: 2020/01/29 16:33:28 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	char		*str;
	char		*tmp;
	int			l;
	long double	f_2;

	l = n;
	f_2 = (f - (long long)f);
	f = lrounding(f, l);
	if (f != f)
		return ("nan");
	str = ft_itoa((long long)(f));
	f_2 = lrounding(f_2, l);
	while (n-- > 0)
		f_2 *= 10;
	if (n && (a->space_2 || !a->dot))
	{
		tmp = ft_strjoin(str, ".");
		free(str);
		str = post_dot(f_2, tmp, l);
	}
	else if (a->sharp)
	{
		tmp = ft_strjoin(str, ".");
		free(str);
		str = tmp;
	}
	return (str);
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
