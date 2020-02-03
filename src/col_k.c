/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_k.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmetallo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 19:53:27 by dmetallo          #+#    #+#             */
/*   Updated: 2020/01/30 19:53:29 by dmetallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		time_sub(int *t, int num, unsigned long long *d)
{
	(*t)++;
	*d -= num;
}

static void		push(t_printf *a, int y, int m, int d)
{
	char	*str;
	char	*p;
	char	*tmp;

	tmp = ft_itoa(y);
	str = ft_strsub(tmp, 0, 4);
	free(tmp);
	p = ft_strjoin(str, "-");
	free(str);
	tmp = ft_itoa(m);
	str = ft_strjoin(p, tmp);
	free(tmp);
	free(p);
	p = ft_strjoin(str, "-");
	free(str);
	tmp = ft_itoa(d);
	str = ft_strjoin(p, tmp);
	free(tmp);
	free(p);
	collect(a, str, ft_strlen(str));
	free(str);
}

void			col_k(t_printf *a, unsigned long long k)
{
	int		year;
	int		month;
	int		day;

	year = 1970;
	month = 1;
	day = 1;
	while (k > 31556926)
		time_sub(&year, 31556926, &k);
	while (k > 2629743)
		time_sub(&month, 2629743, &k);
	while (k > 86400)
		time_sub(&day, 86400, &k);
	push(a, year, month, day);
	a->str++;
}
