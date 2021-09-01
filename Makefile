NAME		=	so_long

LIB			=	-L./libs/libft -lft -L/libs/mlx -lm -lbsd -lX11 -lXext ./libs/mlx/libmlx.a

INC			=	-I./includes -I./libs/mlx

PARSING		=	

RENDERING	=	

GNL			=	GNL/get_next_line.c \
				GNL/get_next_line_utils.c \

UTILS		=	utils/clear.c \
				utils/save.c \
				utils/screen.c \

ERRORS		=	errors/ft_error.c \

INPUTS		=	inputs/inputs.c \

INITS		=	inits/allocs.c \
				inits/inits.c \

SRC_PATH	=	./srcs/

SRC			=	errors/ft_error errors/ft_puterr main.c

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))

FLAGSD		=	-Wall -Wextra -Werror -fsanitize=address -g3

FLAGS		=	-Wall -Wextra -Werror

OBJS		=	$(SRCS:.c=.o)

CC			=	@clang

RM			=	@rm -f

all:	$(NAME)
$(NAME):$(OBJS)
		@make -C libs/libft
		@make -C libs/mlx
		$(CC) $(FLAGSD) $(INC) -o $(NAME) $(OBJS) $(LIB)
		@echo "$(NAME) created"

%.o: %.c
	$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:
		@make $@ -C libs/libft
		@make $@ -C libs/mlx
		$(RM) $(OBJS)
		@echo "$(OBJS) deleted"

fclean: clean
		@make $@ -C libs/libft
		$(RM) $(NAME)
		@echo "$(NAME) deleted"

re:		fclean all

.PHONY: all clean fclean re
