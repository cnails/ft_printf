/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_col_par.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:27:35 by cnails            #+#    #+#             */
/*   Updated: 2019/12/05 15:08:12 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_numlen(int nb)
{
	int i;

	i = 1;
	while (nb /= 10)
		i++;
	return (i);
}

void	col_d(t_printf *a, int nb)
{
	int f;
	int tmp;
	char sign;

	tmp = nb;
	if ((f = (tmp < 0) ? 1 : 0))
		tmp *= -1;
	sign = (a->sign ? (nb > 0 ? '+' : '-') : '-'); // stop, it is illegal
	if (sign == '+')
		collect(a, ft_strjoin(&sign, ft_itoa(nb)), ft_numlen(tmp) + f + 1);
	else
		collect(a, ft_itoa(nb), ft_numlen(tmp) + f);
}

void	col_ld(t_printf *a, long int nb, char c)
{
	long long int i;
	long long int f;
	long int tmp;
	char sign;

	// ft_printbits(nb);
	// ft_putchar('\n');
	// printf("%d\n", (nb >> 33));
	// ft_printbits(1 << 31);
	// ft_putchar('\n');
	// if (1 << 31 & nb)
		// printf("yes\n");
	tmp = (long int)nb;
	// printf("d = %0ld\n", tmp);
	// printf("%ld\n", (1 | (nb >> 33)));
	// if ((tmp < 0) && ((1 | (nb >> 33)) > 0))
		// printf("ttest\n");
	
	// if ((((tmp < 0) ^ (1 | (nb >> 33))) > 0))
	// 	printf("DIF\n");
	// if ((((tmp > 0) ^ (1 | (nb << 33))) <= 0))
		// printf("DIF\n");
	// if ((tmp > 0) && ((1 | (nb >> 33)) < 0))
	// 	printf("ttest\n");
	// tmp = nb;
	if (c == 'u')
		nb = (nb ^ (nb >> 33)) - (nb >> 33);
	else
		a->str++;
	i = 1;
	if ((f = (tmp < 0) ? 1 : 0))
		tmp *= -1;
	while ((tmp /= 10))
		i++;
	sign = (a->sign ? (nb > 0 ? '+' : '-') : '-'); // stop, it is illegal
	if (sign == '+')
		collect(a, ft_strjoin(&sign, ft_itoa(nb)), i + f + 1);
	else
		collect(a, ft_itoa(nb), i + f);
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

	if (*a->str == 'o')
	{
		if (a->dot == 1)
			a->dot = 2;
		tmp = ft_itoa_base(c, 8, 'a');
		if ((a->space > a->space_2 && a->space_2) || (a->align))
		{
			if (a->align)
				a->space = (a->space ^ (a->space >> 31)) - (a->space >> 31);
			p = ft_strnew(1);
			new = a->space;
			// printf("space = %d\n", a->space);
			// printf("space_2 = %d\n", a->space_2);
			// printf("d = %d\n", (int)(a->space_2 - ft_strlen(tmp)));
			if ((int)(a->space_2 - ft_strlen(tmp)) > 0)
				p = ft_strset('0', a->space_2 - ft_strlen(tmp));
			// printf("str = %s\n", tmp);
			p = ft_strjoin(p, tmp);
			int l;
			l = a->space - ft_strlen(p);
			l = l < 0 ? 0 : l;
			int u;
			u = a->space > ft_strlen(tmp) ? a->space : ft_strlen(tmp);
			u = a->space_2 > u ? a->space_2 : u;
			if (!a->align)
				collect(a, ft_strjoin(ft_strset(' ', l), p), u);
			else
				collect(a, ft_strjoin(p, ft_strset(' ', l)), u);
		}
		else
		{
			// printf("space = %d\n", a->space);
			// printf("space_2 = %d\n", a->space_2);
			if (a->space_2)
				a->space = a->space_2;
			collect(a, tmp, ft_strlen(tmp));
		}
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

void	col_x(t_printf *a, void *str, char c)
{
	char	*s;
	int		u;

	// s = ft_itoa_base((4294967295 + (unsigned long long int)str), 16, c == 'X' ? 'A' : 'a');
	// printf("TEST = %s\n", s);
	s = ft_itoa_base((unsigned int)str, 16, c == 'X' ? 'A' : 'a');
	// printf("TEST = %s\n", s);
	// ft_printbits((unsigned int)str);
	// ft_putchar('\n');
	// ft_printbits(~(long long unsigned int)str);
	// ft_putchar('\n');
	if (c == 'p')
	{
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
	else
	{
		// a->dot = (a->dot == 1 && (!a->space || a->space_2)) || a->dot == 2 ? 2 : 1;
		// a->space = a->space_2 && !a->space ? a->space_2 : a->space;
		if (a->space_2 && !a->space)
		{
			a->dot = (a->dot == 1 && (!a->space || a->space_2)) || a->dot == 2 ? 2 : 1;
			// printf("1\n");
			a->space = a->space_2;
			a->space_2 = 0;
		}
		// if (a->space > a->space_2)
		// 	a->space -= a->space_2;
		// printf("space = %d\n", a->space);
		// printf("space_2 = %d\n", a->space_2);
		// if (a->space_2 > a->space && a->space > 0)
		// {
		// 	a->space = a->space_2;
		// 	a->space_2 = 0;
		// }
		if (a->space_2 && a->space != 0 && a->space != a->space_2 && a->space_2 > ft_strlen(s))
			collect(a, ft_strjoin(ft_strset('0', a->space_2 - ft_strlen(s)), s), a->space_2);
		else
			collect(a, s, ft_strlen(s));
	}
	free(s);
}

void	dot_space(t_printf *a)
{
	char	*str;
	int		n;

	a->str = (*a->str == '.') ? a->str + 1 : a->str;
	str = a->str;
	// printf("str = %c\n", *a->str);
	while (*(a->str) >= '0' && *(a->str) <= '9' && *(a->str + 1))
		a->str++;
	// printf("str = %c\n", *a->str);
	n = ft_atoi(str);
	// printf("%d\n", n);
	n *= (a->align) ? -1 : 1;
	if (a->dot != 0 && a->dot != 2)
		a->space_2 = n > 0 ? n : -n;
	else
		a->space = n;
	// if (!(*a->str + 1))
		// collect(a, "", n);
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
	if (*a->str == '.')
		a->dot = 1;
	else
		a->dot = 2;
	a->str++;
	if (*a->str == '-')
	{
		a->dot = 0;
		col_plus_min_sl(a);
	}
	if (*a->str >= '0' && *a->str <= '9')
		dot_space(a);
}

void	col_par(t_printf *a)
{
//	if ((*a->str >= '0' && *a->str <= '9') || *a->str == '-' || *a->str == '.')
	if (*a->str == '+' || *a->str == '-' || *a->str == '\'')
		col_plus_min_sl(a);
	// printf("c = %c\n", *a->str);
	if (*a->str == '.' || *a->str == '0')
	{
		// printf("lol\n");
		col_dot(a);
	}
	// printf("c = %c\n", *a->str);
	if (*a->str >= '0' && *a->str <= '9')// && !(a->align))
		dot_space(a);
	// printf("c = %c\n", *a->str);
	if (*a->str == 'd' || *a->str == 'i' || *a->str == 'D' || *a->str == 'I')
		col_d(a, va_arg(a->va, int));
	else if (*a->str == 'l' && *(a->str + 1) == 'd')
		col_ld(a, va_arg(a->va, long long int), 'l');
	else if (*a->str == 's' || *a->str == 'S')
		col_s(a, va_arg(a->va, char *));
	else if (*a->str == 'u')
		col_ld(a, va_arg(a->va, long int), 'u');
	else if (*a->str == 'c' || *a->str == 'C')
		col_c(a, va_arg(a->va, int));
	else if (*a->str == 'o')
		col_o(a, va_arg(a->va, long long int));
	else if (*a->str == '%')
		col_c(a, '%');
	else if (*a->str == 'f')
		col_f(a, va_arg(a->va, double));
	else if (*a->str == 'x' || *a->str == 'p' || *a->str == 'X')
		col_x(a, va_arg(a->va, void *), *a->str);
	else
		collect(a, a->str, 1);
	// if (*a->str == '\'' && *a->str + 1 == 'd')
	// {
		// printf("1\n");
		// col_f(a, va_arg(a->va, int));
	// }
}

