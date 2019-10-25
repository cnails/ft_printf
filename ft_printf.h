/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:24:10 by cnails            #+#    #+#             */
/*   Updated: 2019/10/25 11:16:06 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <stdarg.h>

typedef	struct	s_printf
{
	int			len;
	int			fd;
	char		ch;
	char		*buf;
	char		*str;
	va_list		va;
}				t_printf;

#endif
