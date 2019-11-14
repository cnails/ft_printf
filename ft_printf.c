/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:18:53 by cnails            #+#    #+#             */
/*   Updated: 2019/11/14 12:06:22 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	collect(t_printf *a, char *str, size_t len)
{
	char *tmp;
	
	if (!a->buf)
		a->buf = ft_strnew(1);
	tmp = ft_strsub(str, 0, len);
	tmp = ft_strjoin(a->buf, tmp);
	free(a->buf);
	a->buf = tmp;
	a->len += len;
}

int		ft_printf(const char *str, ...)
{
	t_printf	a;
	
	ft_bzero(&a, sizeof(a));
	a.fd = 1;
	a.str = (char *)str;
	va_start(a.va, str);
	while (*a.str)
	{
		if (*a.str++ == '%')
		{
			if ((*a.str) == ' ')
				collect(&a, a.str, 1);
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
//	ft_putnbr(a.len);
	va_end(a.va);
	return (0);
}


int main()
{
	char *s;
//	ft_printf("%     D", 11);
//	printf("\n%     D", 11);
//	printf("\n%C", (-0 == 0) ? 'y' : 'n');
	int c = 1600000;
	while ((c = ft_for(5, 1, 10)))
		printf("%d\n", c);
	// printf("%llu\n", (unsigned long long)12345678901234567890.123456789012345678901234567890);
//	printf("%s", ft_dtoa(231.1234567890123456789, 3));
	// printf("\n%.20f", 12345678901234567890.123456789012345678901234567890);
	return (0);
}
