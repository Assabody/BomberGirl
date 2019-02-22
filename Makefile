##
## ETNA PROJECT, 2018
## Bomberman
## File description:
##      Makefile
##

SRC		=	sources/moves.c \
			sources/drawing.c \
			sources/events.c \
			sources/player.c \
			sources/bombe.c \
			sources/renderTexture.c \
			sources/main.c \
			sources/game.c \
			sources/menu.c \
			network/client.c \
			network/message.c

GCC		=	gcc

CFLAGS		=	-Wall -Wextra -g

SDL		=   -L./lib -lSDL2 -lSDL2_image -lSDL_ttf

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
