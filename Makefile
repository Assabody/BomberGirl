##
## ETNA PROJECT, 2018
## Bomberman
## File description:
##      Makefile
##

SRC		=	sources/events.c \
			sources/main.c

GCC		=	gcc

CFLAGS		=	-Wall -Wextra -g

SDL		=   -L./lib -lSDL2 -lSDL2_image

RM		=	rm -rf

MV		=	mv

NAME		=	bomberman

OBJ		=	$(SRC:%.c=%.o)

$(NAME)		:	$(OBJ)
			$(GCC) $(CFLAGS) $(SDL) $(SRC) -o $(NAME)

all		:	$(NAME)

clean		:
			$(RM) $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		: 	all clean fclean re
