/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmetallo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:25:21 by dmetallo          #+#    #+#             */
/*   Updated: 2019/11/04 14:25:23 by dmetallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*post_dot(double f, char *str)
{
	char *tmp;

	tmp = ft_itoa((int)f);
	str = ft_strjoin(str, tmp);
	free(tmp);
	return (str);
}

char		*ft_dtoa(double f, int n)
{
	char *str;
	char *tmp;

	n = (n < 0) ? 0 : n;
	str = ft_itoa((int)f);
	f -= (int)f;
	while (--n > 0 && f < 10000000)
		f *= 10;
	if ((int)f)
	{
		tmp = ft_strjoin(str, ".");
		free(str);
		str = post_dot(f, tmp);
	}
	f -= (int)f;
	while (--n > 0)
		f *= 10;
	str = post_dot(f, str);
	return (str);
}