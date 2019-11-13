/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_for.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:36:57 by cnails            #+#    #+#             */
/*   Updated: 2019/11/13 15:31:31 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	stat_for(int sum, int end)
{
	static int i;
	int final;

	if (i == end)
	{
		final = sum + i;
		i = 0;
		return (final);
	}
	i += sum;
	return (i);
}

int			ft_for(int start, int sum, int end)
{
	int i;

	if (sum < 0)
		return (0);
	i = stat_for(sum, end);
	if (end - i >= start)
		return (i);
	return (0);
}
