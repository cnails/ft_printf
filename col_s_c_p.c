/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_s_c_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:27:35 by cnails            #+#    #+#             */
/*   Updated: 2020/01/29 19:59:06 by cnails           ###   ########.fr       */
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
	if ((int)ft_strlen(str) > a->s && a->dot == 1)
		u = a->s;
	else
		u = ft_strlen(str);
	collect(a, str, u);
}

////////////////////////////////////////////////////////////////////////////////////

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;

	i = 0;
	if (s1 && s2)
	{
		if (!(str = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1)
							+ ft_strlen((char *)s2) + 1))))
			return (NULL);
		while (*s1)
			str[i++] = *s1++;
		while (*s2)
			str[i++] = *s2++;
		if (*s2 == '\x00')
			str[i++] = '\x00';
		str[i++] = '\0';
		return (str);
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	if (s[i] == '\x00')
		i++;
	return (i);
}


char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if ((len + 1) < len || !s)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}

//////////////////////////////////////////////////////////////////////////////////

void	col_c(t_printf *a, char c)
{
	char *p;
	char *new;

	p = NULL;
	if (c == '\x00' && a->align)
	{
		write(1, "\x00", 1);
		a->space++;
		collect(a, "", 0);
	}
	else
		collect(a, &c, 1);
}

void	col_p(t_printf *a, void *str, char c)
{
	char	*s;
	char	*tmp;
	int		u;

	u = 0;
	if (a->dot && !a->space_2 && !)
	s = ret_s(a, str, c);
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
	{
		tmp = ft_strjoin("0x", s);
		collect(a, tmp, ft_strlen(s) + 2);
		free(tmp);
	}
	free(s);
}
