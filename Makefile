##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile for the My World project
##

SRC	=	src/main.c		\
		src/world.c		\
		src/display.c		\
		src/isometric.c		\
		src/render.c		\
		src/event.c		\
		src/map.c		\
		src/map_creation.c	\
		src/input.c		\
		src/tool.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_world

CFLAGS = -I ./include -l c_graph_prog -Wall -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
