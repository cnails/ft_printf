/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmetallo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:40:30 by dmetallo          #+#    #+#             */
/*   Updated: 2020/01/30 16:40:37 by dmetallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void				dop_f(t_printf *a, char *str, char *sign)
{
	int		space;

	space = a->space;
	a->space = 0;
	collect(a, sign, 1);
	a->space = space + (a->align ? 1 : -1);
	a->dot = 2;
	collect(a, str, ft_strlen(str));
	free(str);
	free(sign);
}

void				else_f(t_printf *a, char *str, char *sign, double d)
{
	char *tmp;

	tmp = ft_strjoin(sign, str);
	if (a->dot == 3)
		a->dot = 2;
	collect(a, tmp, ft_strlen(str) + ((d < 0 || a->sign) ?\
		1 : 0));
	free(tmp);
	free(sign);
	free(str);
}

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
	str = ft_ftoa(a, (d < 0 ? d * -1 : d), (!a->dot ? 6 : a->space_2));
	if (d < 0)
		tmp = ft_strdup("-");
	else
		tmp = (a->sign) ? ft_strdup("+") : ft_strdup("");
	if ((d < 0 || a->sign) && a->dot == 3)
		dop_f(a, str, tmp);
	else
		else_f(a, str, tmp, d);
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
