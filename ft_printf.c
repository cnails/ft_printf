/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:18:53 by cnails            #+#    #+#             */
/*   Updated: 2020/01/20 17:59:38 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	col_space(t_printf *a, char *str, size_t len)

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
	a->space = 0;
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
	a->space = 0;
	a->dot = 0;
	a->sharp = 0;
}

int			ft_printf(const char *str, ...)
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
	free(a.buf);
//	ft_putnbr(a.len);
	va_end(a.va);
	return (a.len);
}

// int 		main()
// {
// 	char str[] = "0";

// 	// printf("%d\n", ft_strcmp(str, "a"));
// 	ft_printf("%.5d", 2);
// //	printf("\nthis %u number", -267);
// 	ft_printf("%#5.0o", 0);
// 	// printf("{%+7u}\n", 0);
// }
