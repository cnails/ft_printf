/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmetallo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:10:19 by dmetallo          #+#    #+#             */
/*   Updated: 2020/01/30 18:10:21 by dmetallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static size_t	len(unsigned int nb)
{
	size_t i;

	i = 1;
	while ((nb /= 2) >= 1)
		i++;
	return (i);
}

void			col_b(t_printf *a, void *nb)
{
	unsigned int	nbr;
	char			*str;
	size_t			i;

	nbr = (unsigned int)nb;
	i = len(nbr);
	str = (char*)malloc(sizeof(char) * (i + 1));
	str[i--] = '\0';
	while (nbr)
	{
		str[i--] = nbr % 2 + '0';
		nbr /= 2;
	}
	collect(a, str, ft_strlen(str));
	free(str);
	a->str++;
}
