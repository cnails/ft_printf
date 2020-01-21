/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_col_par.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:27:35 by cnails            #+#    #+#             */
/*   Updated: 2020/01/21 18:39:07 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	col_s(t_printf *a, char *str)
{
	int u;

	if (*a->str >= 0 && *a->str <= 9)
		dot_space(a);
	if (a->space && a->dot == 1 && !a->space_2)
	{
		collect(a, "", 0);
		return ;
	}
	if ((a->space_2 && a->dot == 1) || (a->space && a->dot == 1 && !a->space_2))
	{
		a->s = a->space_2 ? a->space_2 : a->space;
		if (a->space && a->dot == 1 && !a->space_2)
			a->space = 0;
		a->space_2 = 0;
	}
	if (str == NULL)
		str = "(null)";
	if (ft_strlen(str) > a->s && a->dot == 1)
		u = a->s;
	else
		u = ft_strlen(str);
	collect(a, str, u);
}

void	col_c(t_printf *a, char c)
{
	collect(a, &c, 1);
}

void	col_o(t_printf *a, long long int c)
{
	char	*tmp;
	int		new;
	char	*tes;
	char	*p;

	tmp = ft_itoa_base(c, 8, 'a');
	if (a->sharp && ft_strcmp(tmp, "0") && (a->dot != 2 || a->space_2 < ft_strlen(tmp)))
	{
		tes = tmp;
		tmp = ft_strjoin("0", tes);
		free(tes);
	}
	if (a->dot == 2 && a->sharp && !a->space_2)
		a->space_2 = a->space;
	if (((a->dot == 2 && !a->space) || (!a->space_2 && a->dot == 1)) && !a->space_2 && !a->sharp)
	{
		a->dot = 1;
		collect(a, "", 0);
	}
	else if (a->space_2 > ft_strlen(tmp))
	{
		if (a->space && a->space_2)
			a->dot = 1;
		collect(a, ft_strjoin(ft_strset('0', a->space_2 - ft_strlen(tmp)), tmp), a->space_2);
	}
	else
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
	free(tmp);
}

void	col_f(t_printf *a, long double ld)
{
	char	*str;

	str = ft_dtoa(ld, a->nbr + 7);
	collect(a, str, ft_strlen(str));
	a->nbr = -1;
}

void	col_p(t_printf *a, void *str, char c)
{
	char	*s;
	int		u;
	char	*tmp;

	if (a->h == 1)
		s = ft_itoa_base((unsigned short)str, 16, c == 'X' ? 'A' : 'a');
	else if (a->h == 2)
		s = ft_itoa_base((unsigned char)str, 16, c == 'X' ? 'A' : 'a');
	else if (a->l == 2)
		s = ft_itoa_base((unsigned long long)str, 16, c == 'X' ? 'A' : 'a');
	else
		s = ft_itoa_base((long int)str, 16, c == 'X' ? 'A' : 'a');
	if (a->dot)
	{
		if (a->space)
		{
			u = a->space;
			a->space = 0;
		}
		collect(a, "0x", 2);
		a->space = u - 2;
		collect(a, s, ft_strlen(s));
	}
	else
		collect(a, ft_strjoin("0x", s), ft_strlen(s) + 2);
	free(s);
}

void	col_x(t_printf *a, void *str, char c)
{
	char	*s;
	int		u;

	if (a->h == 1)
		s = ft_itoa_base((unsigned short)str, 16, c == 'X' ? 'A' : 'a');
	else if (a->h == 2)
		s = ft_itoa_base((unsigned char)str, 16, c == 'X' ? 'A' : 'a');
	else if (a->l == 2)
		s = ft_itoa_base((unsigned long long)str, 16, c == 'X' ? 'A' : 'a');
	else
		s = ft_itoa_base((long int)str, 16, c == 'X' ? 'A' : 'a');
	if (a->sharp == 1 && str != 0)
	{
		if (a->sharp && a->space > 2 && a->dot == 2 && a->sharp)
			a->space_2 = a->space - 2;
		if (a->space_2 > ft_strlen(s))
			collect(a, ft_strjoin(c == 'x' ? "0x" : "0X", ft_strjoin(ft_strset('0', a->space_2 - ft_strlen(s)), s)), a->space_2 + 2);
		else
			collect(a, ft_strjoin(c == 'x' ? "0x" : "0X", s), ft_strlen(s) + 2);
	}
	else
	{
		if (!ft_strcmp(s, "0") && (a->space_2 || a->dot == 1))
		{
			s = "";
			if (a->sharp && a->dot == 1 && a->space && !a->space_2)
				a->dot = 0;
		}
		if (a->space && !a->space_2 && a->sharp)
			a->space_2 = a->space;
		if (a->space_2 > ft_strlen(s) && a->dot)
			collect(a, ft_strjoin(ft_strset('0', a->space_2 - ft_strlen(s)), s), a->space_2);
		else
			collect(a, s, ft_strlen(s));
	}
	a->h = 0;
	a->l = 0;
}

void	dot_space(t_printf *a)
{
	char	*str;
	int		n;

	a->str = (*a->str == '.') ? a->str + 1 : a->str;
	str = a->str;
	while (*(a->str) >= '0' && *(a->str) <= '9' && *(a->str + 1))
		a->str++;
	n = ft_atoi(str);
	n *= (a->align) ? -1 : 1;
	if (a->dot != 0 && a->dot != 2)
		a->space_2 = n > 0 ? n : -n;
	else
		a->space = n;
	if (*a->str == '.')
		col_dot(a);
}

void	col_plus_min_sl(t_printf *a)
{
	if (*a->str == '-')
		a->align = 1;
	if (*a->str == '+')
		a->sign = 1;
	a->str++;
	if (*a->str == '-' || *a->str == '+' || *a->str == '\'')
		col_plus_min_sl(a);
}

void	col_dot(t_printf *a)
{
	if (*a->str == '#')
	{
		a->sharp = 1;
		a->str++;
	}
	if (*a->str == '.')
	{
		a->dot = 1;
		a->str++;
	}
	else if (*a->str == '0')
	{
		a->dot = 2;
		a->str++;
	}
	if (*a->str == '-')
	{
		a->dot = 0;
		col_plus_min_sl(a);
	}
	if (*a->str == '+')
		col_plus_min_sl(a);
	if (*a->str >= '0' && *a->str <= '9')
		dot_space(a);
}

void	col_hl(t_printf *a)
{
	if (*a->str == 'h')
	{
		if (a->h == 1)
			a->h = 2;
		else
			a->h = 1;
	}
	if (*a->str == 'l')
	{
		if (a->l == 1)
			a->l = 2;
		else
			a->l = 1;
	}
	a->str++;
	if (*a->str == 'h' || *a->str == 'l')
		col_hl(a);
}

void	col_par(t_printf *a)
{
	if (*(a->str - 1) == ' ')
		a->one_s = 1;
	if (*a->str == '+' || *a->str == '-' || *a->str == '\'')
		col_plus_min_sl(a);
	if (*a->str == '.' || *a->str == '0' || *a->str == '#')
		col_dot(a);
	if (*a->str >= '0' && *a->str <= '9')
		dot_space(a);
	if (*a->str == 'h' || *a->str == 'l')
		col_hl(a);
	if (*a->str == 'd' || *a->str == 'i' || *a->str == 'D' || *a->str == 'I')
		col_d(a, va_arg(a->va, void *));
	else if (*a->str == 's' || *a->str == 'S')
		col_s(a, va_arg(a->va, char *));
	else if (*a->str == 'u')
		col_u(a, va_arg(a->va, void *), 'u');
	else if (*a->str == 'c' || *a->str == 'C')
		col_c(a, va_arg(a->va, int));
	else if (*a->str == 'o')
		col_o(a, va_arg(a->va, long long int));
	else if (*a->str == '%')
		col_c(a, '%');
	else if (*a->str == 'f')
		col_f(a, va_arg(a->va, double));
	else if (*a->str == 'x' || *a->str == 'X')
		col_x(a, va_arg(a->va, void *), *a->str);
	else if (*a->str == 'p')
		col_p(a, va_arg(a->va, void *), *a->str);
	else
		collect(a, a->str, 1);
}
