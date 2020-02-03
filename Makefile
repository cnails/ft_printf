# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cnails <cnails@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/30 12:33:56 by cnails            #+#    #+#              #
#    Updated: 2020/01/30 12:38:35 by cnails           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

INC_DIR		= ./includes 
SRC_DIR		= ./src

HEADERS		= ft_printf.h
SRC     	= \
			  col_b.c \
			  col_d.c \
			  col_f.c \
			  col_k.c \
			  col_lf.c \
			  col_o.c \
			  col_s_c_p.c \
			  col_u.c \
			  col_x.c \
			  \
			  ft_col_par.c \
			  ft_dop_dop_func.c	\
			  ft_dop_func.c \
			  ft_printf.c \

OBJS = $(SRC:.c=.o)

LIBFT = ./libft

WFL = -Wall -Wextra -Werror

IFL = -I$(INC_DIR)

SRCS = $(addprefix $(SRC_DIR))

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)/
	cp $(LIBFT)/libft.a ./$(NAME)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o: $(SRC_DIR)/%.c
	gcc $(WFL) $(IFL) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT)/ clean
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT)/ fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
