/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:20:09 by cnails            #+#    #+#             */
/*   Updated: 2019/11/14 15:37:45 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_itoa_base(int nbr, int base)
{
	char	*str;
	int		i;
	int		sign;
	int		n;

	sign = (nbr < 0 && base == 10) ? 1 : 0;
	n = (nbr < 0) ? -nbr : nbr;
	while ((n /= base) >= 1)
		i++;
	i += 1;
	n = (nbr < 0) ? -nbr : nbr;
	if (!(str = (char *)ft_memalloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (i--)
	{
		str[i + sign] = (n % base < 10) ? n % base + '0' : n % base + 'A' - 10;
		n /= base;
	}
	(sign) ? str[0] = '-' : 0;
	return (str);
}
