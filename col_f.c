/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmetallo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:21:59 by dmetallo          #+#    #+#             */
/*   Updated: 2020/01/27 13:22:06 by dmetallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				col_f(t_printf *a, double d)
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
	str = ft_ftoa(a, d < 0 ? d * -1 : d, (!a->dot ? 6 : a->space_2));
	if (a->dot == 3)
		a->dot = 2;
	collect(a, ft_strjoin(tmp, str), ft_strlen(str) + ((d < 0 || a->sign) ?\
		1 : 0));
}

double				rounding(double nb, int l)
{
	int		i;
	double	tmp;

	tmp = nb - (unsigned long int)nb;
	i = -1;
	while (++i != l)
		tmp *= 10;
	tmp += 0.5;
	while (--l >= 0)
		tmp /= 10;
	return ((unsigned long int)nb + tmp);
}

char				*post_dot(double f, char *str, int l)
{
	char *tmp;

	tmp = ft_qitoa((unsigned long int)f, l);
	str = ft_strjoin(str, tmp);
	free(tmp);
	return (str);
}

static char			*ft_ftoa(t_printf *a, double f, int n)
{
	char	*str;
	char	*tmp;
	int		l;
	int		sign;
	double	f_2;

	l = n;
	f_2 = (f - (int)f);
	f = rounding(f, l);
	str = ft_itoa((long long)(f));
	f_2 = rounding(f_2, l);
	while (n-- > 0)
		f_2 *= 10;
	tmp = ((n && (a->space_2 || !a->dot)) || a->sharp) ? ft_strjoin(str, ".") : NULL;
	((n && (a->space_2 || !a->dot)) || a->sharp) ? free(str) : 1;
	if (n && (a->space_2 || !a->dot))
		str = post_dot(f_2, tmp, l);
	else if (a->sharp)
		str = tmp;
	return (str);
}

char				*ft_qitoa(unsigned long int n, int l)
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
