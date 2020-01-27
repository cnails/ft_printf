/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:18:53 by cnails            #+#    #+#             */
/*   Updated: 2020/01/27 19:05:31 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		col_space(t_printf *a, char *str, size_t len)
{
	char *tmp;
	char *p;

	a->space *= (a->space < 0) ? -1 : 1;
	if (a->dot == 2 && !a->align && !a->sharp)
	{
		p = ft_strset('0', a->space - len);
		a->dot = 0;
	}
	else
		p = ft_strset(' ', a->space - len);
	tmp = ft_strjoin(a->buf, p);
	free(a->buf);
	free(p);
	a->buf = tmp;
	a->len += a->space - len;
}

void		collect(t_printf *a, char *str, size_t len)
{
	char *tmp;
	char *new;

	if (!a->buf)
		a->buf = ft_strnew(1);
	if (a->space > len && (!a->align || a->dot) && a->space > 0)
		col_space(a, str, len);
	tmp = ft_strsub(str, 0, len);
	new = ft_strjoin(a->buf, tmp);
	free(tmp);
	tmp = new;
	free(a->buf);
	a->buf = tmp;
	a->len += len;
	if (a->space < 0 && -a->space > len)
		col_space(a, str, len);
	a->dot = (a->one_s ? a->dot : 0);
	a->sharp = 0;
	a->space = 0;
	a->h = 0;
	a->l = 0;
	// a->space_2 = 0;
	// free(str);
}

void		a_init(const char *str, t_printf *a)
{
	a->fd = 1;
	a->space = 0;
	a->str = (char *)str;
}

int			ft_printf(const char *str, ...)
{
	t_printf	a;

	ft_bzero(&a, sizeof(a));
	va_start(a.va, str);
	a_init(str, &a);
	while (*a.str)
	{
		if (*a.str == '%')
		{
			a.str++;
			while ((*a.str) == ' ')
				a.str++;
			if (!(*a.str))
				break ;
			col_par(&a);
		}
		else
			collect(&a, a.str, 1);
		a.str++;
	}
	write(1, a.buf, a.len);
	free(a.buf);
	va_end(a.va);
	return (a.len);
}

/////////////////////////////////

static double rounding(double nb, int l)
{
	int i;
	double tmp;

	tmp = nb - (unsigned long int)nb;
	i = -1;
	while(++i != l)
		tmp *= 10;
	tmp += 0.5;
	while (--l >= 0)
		tmp /= 10;
	return ((unsigned long int)nb + tmp);
}

void	col_f(t_printf *a, double d)
{
	char	*str;
	char	*tmp;

	if (d < 0)
		tmp = ft_strdup("-");
	else
		tmp = (a->sign) ? ft_strdup("+") : ft_strdup("");
	str = ft_ftoa(a, d < 0 ? d * -1 : d, (!a->dot ? 6 : a->space_2));
	collect(a, ft_strjoin(tmp, str), ft_strlen(str) + ((d < 0 || a->sign) ? 1 : 0));

	// int			i;
	// int			f;
	// long long	l;
	// long long	tmp;
	// char		sign;

	// tmp = ret_nb(a, nb);
	// l = tmp;
	// i = 1;
	// sign = '-';
	// while ((tmp /= 10))
	// 	i++;
	// if (a->space && !a->space_2 && a->dot == 1)
	// 	i = 0;
	// if (a->dot == 2 && !a->space_2 && a->space && (l < 0 || a->sign))
	// 	a->space_2 = a->space - 1;
	// if (a->sign)
	// 	sign = l >= 0 ? '+' : '-';
	// if (a->one_s == 1 && !a->sign && l >= 0 && (a->space <= i || a->dot == 2))
	// 	collect_space(a);
	// if (a->dot && !a->space_2 && !a->space)
	// 	a->sign ? collect(a, "+", 1) : collect(a, "", 0);
	// else if (a->dot && l < 0 && a->space_2 >= i)
	// 	collect(a, ft_strjoin("-",ft_strjoin(ft_strset('0', a->space_2 - i), ft_itoa(-l))), a->space_2 + 1);
	// else if (a->dot && a->space_2 >= i && sign == '+')
	// 	collect(a, ft_strjoin("+",ft_strjoin(ft_strset('0', a->space_2 - i), ft_itoa(l))), a->space_2 + 1);
	// else if (a->dot && a->space_2 > i)
	// 	collect(a, ft_strjoin(ft_strset('0', a->space_2 - i), ft_itoa(l)), a->space_2);
	// else if (a->sign && l >= 0 && sign != '-')
	// 	collect(a, ft_strjoin("+", ft_itoa(l)), i + 1);
	// else
	// 	collect(a, ft_itoa(l), i + (l < 0 ? 1 : 0));
}

static int		len(int n)
{
	int i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

void	col_lf(t_printf *a, long double d)
{
	char	*str;
	char	*tmp;
	
	// printf("d = %Lf\n", d);
	if (d < 0)
		tmp = ft_strdup("-");
	else
		tmp = ft_strdup("");
	str = ft_ftoa(a, d < 0 ? d * -1 : d, (!a->dot ? 6 : a->space_2));
	collect(a, ft_strjoin(tmp, str), ft_strlen(str) + (d < 0 ? 1 : 0));
}

static char		*ft_qitoa(unsigned long int n, int l)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * (l + 1))))
		return (NULL);
	str[l--] = '\0';
	while (l != -1)
	{
		str[l--] = n % 10 + '0';
		n /= 10;
	}

	return (str);
}

static char		*post_dot(double f, char *str, int l)
{
	char *tmp;

	tmp = ft_qitoa((unsigned long int)f, l);
	str = ft_strjoin(str, tmp);
	free(tmp);
	return (str);
}

static char			*ft_ftoa(t_printf *a, double f, int n)
{
	char	*str;
	char	*tmp;
	int		l;
	int 	sign;
	double	f_2;

	
	l = n;
	f_2 = (f - (int)f);
	f = rounding(f, l);
	str = ft_itoa((int)(f));

	f_2 = rounding(f_2, l);

	while (n-- > 0)
		f_2 *= 10;
	if (n && (a->space_2 || !a->dot))
	{
		tmp = ft_strjoin(str, ".");
		free(str);
		str = post_dot(f_2, tmp, l);
	}
	else if (a->sharp)
	{
		tmp = ft_strjoin(str, ".");
		free(str);
		str = tmp;
	}
	return (str);
}

/////////////////////////////////

int 		main()
{
	char str[] = "0";
	// printf("%d\n", ft_strcmp(str, "a"));
	printf("%.16f",  0.999999999999999900);
	ft_printf("%#.0f", -7.4);
//	ft_printf("%f", 1.0);
//	printf("\nthis %u number", -267);
	// printf("%d\n", -267);
	// printf("%ld\n", "s");
	// printf("{%+7u}\n", 0);
}