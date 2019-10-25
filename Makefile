NAME = printf

all: $NAME

$NAME:
	gcc *.c -L libft -lft 

clean:
	rm a.out
