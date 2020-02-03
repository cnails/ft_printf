/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_o.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmetallo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:41:19 by dmetallo          #+#    #+#             */
/*   Updated: 2020/01/30 16:41:22 by dmetallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		col_o_norm(t_printf *a)
{
	a->dot = 1;
	collect(a, "", 0);
}

void		col_o_dop(t_printf *a, char *tmp)
{
	if (a->space && a->space_2 && a->dot)
	{
		a->dot = 1;
		a->space_2 = a->space;
	}
	if (a->space_2)
		a->space = a->space_2;
	collect(a, tmp, ft_strlen(tmp));
}

long long	ret_onb(t_printf *a, void *nb)
{
	if (a->l == 1)
		return ((unsigned long)nb);
	else if (a->l == 2)
		return ((unsigned long long)nb);
	else if (a->h == 1)
		return ((unsigned short)nb);
	else if (a->h == 2)
		return ((unsigned char)nb);
	else
		return ((unsigned int)nb);
}

char		*ft_uitoa_base(unsigned long long int nbr, int base, char a)
{
	char					*str;
	int						i;
	unsigned long long int	n;

	i = 0;
	n = nbr;
	while ((n /= base) >= 1)
		i++;
	i += 1;
	n = nbr;
	if (!(str = (char *)ft_memalloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (i--)
	{
		str[i] = (n % base < 10) ? n % base + '0' : n % base + a - 10;
		n /= base;
	}
	return (str);
}

void		col_o(t_printf *a, void *c)
{
	char		*tmp;
	char		*tes;

	tmp = ft_uitoa_base(ret_onb(a, c), 8, 'a');
	if (a->sharp && ft_strcmp(tmp, "0")\
		&& (a->dot != 2 || a->space_2 < (int)ft_strlen(tmp)))
	{
		tes = tmp;
		tmp = ft_strjoin("0", tes);
		free(tes);
	}
	if (a->dot == 2 && a->sharp && !a->space_2)
		a->space_2 = a->space;
	if (((a->dot == 2 && !a->space) || (!a->space_2 &&\
		a->dot == 1)) && !a->space_2 && !a->sharp)
		col_o_norm(a);
	else if (a->space_2 > (int)ft_strlen(tmp))
		col_o_one_more(a, tmp);
	else
		col_o_dop(a, tmp);
	free(tmp);
}
