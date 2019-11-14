/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmetallo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:28:29 by dmetallo          #+#    #+#             */
/*   Updated: 2019/11/07 18:28:30 by dmetallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strset(char c, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = ft_strnew(n);
	while (i < n)
		str[i] = c;
	return (str);
}