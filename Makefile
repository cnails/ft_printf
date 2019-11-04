NAME = printf

all: $NAME

$NAME:
	gcc -g *.c -L libft -lft 

clean:
	rm a.out
