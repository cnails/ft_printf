/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_col_par.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:27:35 by cnails            #+#    #+#             */
/*   Updated: 2020/01/19 20:59:12 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	col_d(t_printf *a, int nb)
{
	int i;
	int f;
	int tmp;
	char sign;

	tmp = nb;
	i = 1;
	if ((f = (tmp < 0) ? 1 : 0))
		tmp *= -1;
	while ((tmp /= 10))
		i++;
	sign = (a->sign ? (nb > 0 ? '+' : '-') : '-');
	if (sign == '+')
		collect(a, ft_strjoin(&sign, ft_itoa(nb)), i + f + 1);
	else
		collect(a, ft_itoa(nb), i + f);
}

void	col_u(t_printf *a, void *nb, char c)
{
	unsigned long long i;
	unsigned long long f;
	unsigned long long l;
	unsigned long long tmp;
	char sign;

	if (a->l == 1)
		tmp = (unsigned long)nb;
	else if (a->l == 2)
		tmp = (unsigned long long)nb;
	else if (a->h == 1)
		tmp = (unsigned short)nb;
	else if (a->h == 2)
		tmp = (unsigned char)nb;
	else
		tmp = (unsigned int)nb;
	l = (unsigned long long)tmp;
	i = 1;
	while ((tmp /= 10))
		i++;
	if (a->space && !a->space_2 && a->dot == 1)
		i = 0;
	if (a->dot && !a->space)
	{
		a->dot = 2;
		a->space = a->space_2;
	}
	sign = (a->sign ? (l > 0 ? '+' : '-') : '-'); // stop, it is illegal
	if (a->dot == 2 && !a->space_2 && !a->space)
		collect(a, "", 0);
	else if (a->dot && a->space && a->space_2 > i)
		collect(a, ft_strjoin(ft_strset('0', a->space_2 - i), ft_itoa(l)), a->space_2);
	else if (sign == '+')
		collect(a, ft_strjoin(&sign, ft_itoa(l)), i + 1);
	else
		collect(a, ft_itoa(l), i);
	a->l = 0;
	a->h = 0; // вынести обнуление всех переменных в одну функцию
}

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
	char	*p;

	if (a->dot == 1)
		a->dot = 2;
	tmp = ft_itoa_base(c, 8, 'a');
	if (a->space_2 > ft_strlen(tmp))
	{
		if (a->dot == 2)
			collect(a, ft_strjoin(ft_strset('0', a->space_2 - ft_strlen(tmp)), tmp), a->space_2);
		else
			collect(a, ft_strjoin(ft_strset(' ', a->space_2 - ft_strlen(tmp)), tmp), a->space_2);
	}
	else
	{
		if (a->space_2)
			a->space = a->space_2;
		collect(a, tmp, ft_strlen(tmp));
	}
}

void	col_f(t_printf *a, long double ld)
{
	char	*str;

	str = ft_dtoa(ld, a->nbr + 7);
	collect(a, str, ft_strlen(str));
	a->nbr = -1;
}

void	ft_printbits(unsigned long int octet)
{
	unsigned long int div;

	div = 2147483648 * 64;
	while (div != 1)
	{
		if (octet / div == 1)
			write(1, "1", 1);
		else
			write(1, "0", 1);
		octet = octet % div;
		div = div / 2;
	}
	if (octet == 1)
		write(1, "1", 1);
	else
		write(1, "0", 1);
}

void	col_p(t_printf *a, void *str, char c)
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
		s = ft_strjoin("0x", s);
	}
	if (a->dot)
	{
		if (a->space)
		{
			u = a->space;
			a->space = 0;
		}
		collect(a, "0x", 2);
		a->space = u - 2;
		col_space(a, str, ft_strlen(s));
		collect(a, ft_strjoin("", s), ft_strlen(s));
	}
	else
		collect(a, ft_strjoin("0x", s), ft_strlen(s) + 2);
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
			collect(a, ft_strjoin("0x", ft_strjoin(ft_strset('0', a->space_2 - ft_strlen(s)), s)), a->space_2 + 2);
		else
			collect(a, ft_strjoin("0x", s), ft_strlen(s) + 2);
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
	// if (s)
	// 	free(s);
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
	if (*a->str == '+' || *a->str == '-' || *a->str == '\'')
		col_plus_min_sl(a);
	if (*a->str == '.' || *a->str == '0' || *a->str == '#')
		col_dot(a);
	if (*a->str >= '0' && *a->str <= '9')
		dot_space(a);
	if (*a->str == 'h' || *a->str == 'l')
		col_hl(a);
	if (*a->str == 'd' || *a->str == 'i' || *a->str == 'D' || *a->str == 'I')
		col_d(a, va_arg(a->va, int));
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
	// if (*a->str == '\'' && *a->str + 1 == 'd')
	// {
		// printf("1\n");
		// col_f(a, va_arg(a->va, int));
	// }
}
