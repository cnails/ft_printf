#NAME = printf

#all: $NAME

#$NAME:
#	gcc -g *.c -L libft -lft 

#clean:
#	rm a.out

C = clang

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror -O2

LIBFT = libft

DIR_S = sources

DIR_O = temporary

HEADER = include

SOURCES = *.c


SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

# OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(NAME)
	gcc -c *.c 
	@ar rc $(NAME) *.o
	@ranlib $(NAME)

# $(DIR_O)/%.o: $(DIR_S)/%.c
	# @mkdir -p temporary
	# @$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

norme:
	norminette ./libft/
	@echo
	norminette ./$(HEADER)/
	@echo
	norminette ./$(DIR_S)/

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)
	@make clean -C $(LIBFT)

fclean: clean
	rm -rf *.o
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all
