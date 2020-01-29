/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_o.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:27:35 by cnails            #+#    #+#             */
/*   Updated: 2020/01/29 16:49:59 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	col_o_one_more(t_printf *a, char *str)
{
	char *tmp;
	char *tmp_join;

	tmp = ft_strset('0', a->space_2 - ft_strlen(str));
	tmp_join = ft_strjoin(tmp, str);
	if (a->space && a->space_2)
		a->dot = 1;
	collect(a, tmp_join, a->space_2);
	free(tmp);
	free(tmp_join);
}

void	col_o_norm(t_printf *a)
{
	a->dot = 1;
	collect(a, "", 0);
}

void	col_o_dop(t_printf *a, char *tmp)
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

void	col_o(t_printf *a, long long int c)
{
	char	*tmp;
	char	*tes;

	tmp = ft_itoa_base(c, 8, 'a');
	if (a->sharp && ft_strcmp(tmp, "0")\
		&& (a->dot != 2 || a->space_2 < ft_strlen(tmp)))
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
	else if (a->space_2 > ft_strlen(tmp))
		col_o_one_more(a, tmp);
	else
		col_o_dop(a, tmp);
	free(tmp);
}
