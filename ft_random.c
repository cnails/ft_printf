/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 21:36:49 by cnails            #+#    #+#             */
/*   Updated: 2019/12/05 22:08:47 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_random()
{
	char *a;
	long int b;
	unsigned char i;
	a = (char *)malloc(sizeof(char) * 1);
	a = "r";
	
	b = (long int)a;
	while (b / 10 > 10)
		b -= 1000;
	i = (unsigned char)b;
	// ft_strdel(&a);
	if (i / 100)
	{
		i = i % 10 ? i : i % 7;
		return ((i % 10) * (i % 10));
	}
	return (i);
}

int		main()
{
	printf("%d\n", ft_random());
}
