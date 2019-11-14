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
	char *p;

	if (!a->buf)
		a->buf = ft_strnew(1);
	if (a->space > len)
	{
		p = ft_strset(' ', a->space - len);
		tmp = ft_strjoin(a->buf, p);
		free(a->buf);
		a->buf = tmp;
		a->len += a->space - len;
		a->space = 0;
	}
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
	a.nbr = -1;
	a.space = 0;
	a.str = (char *)str;
	va_start(a.va, str);
	while (*a.str)
	{
		if (*a.str == '%')
		{
			a.str++;
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

//	printf("%s", ft_strsub(t,0,s-t));
//	ft_printf("%.20f", 12345678901234567.123456789012345678901234567890);
//	printf("\n%     D", 11);
//	printf("\n%C", (-0 == 0) ? 'y' : 'n');
//	printf("%d\n",  (int)(0.12345));
//	printf("%.10Lf\n", (long double)12345678901234567890123.12345678901234567890);
//	printf( "%0*x", 8, 15 );
//	printf("\n**%2d",12345678);
//	printf("\n%3d %s", 12, "123");
	printf("\n%.2f %s   %10d.\n", 1234567890.1234567890, "qwerty",10);
	ft_printf("\n%.2f %s   %10d.", 1234567890.1234567890, "qwerty",10);
//	printf("\n%.s","qwertyuiop1234567");

}
