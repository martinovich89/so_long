NAME		=	so_long

LIB			=	-L./libs/libft -lft -L./libs/mlx -lm -lX11 -lz -lXext -lmlx
INC			=	-I./includes -I./libs/mlx

PARSING		=	

RENDERING	=	

GNL			=	get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \
				get_next_line/get_next_line_utils2.c

ERRORS		=	errors/ft_error.c 

INPUTS		=	inputs/inputs.c 

SRC_PATH	=	./srcs/

SRC			=	$(GNL) $(ERRORS) $(INPUTS) $(INITS) main.c

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))

FLAGSD		=	-Wall -Wextra -Werror #-fsanitize=address -g3

FLAGS		=	-Wall -Wextra -Werror

OBJS		=	$(SRCS:.c=.o)

CC			=	clang

RM			=	rm -f

all: $(NAME)

$(NAME): $(OBJS)
		make -C libs/libft
		make -C libs/mlx
		cp ./libs/libft/libft.a libs
		cp ./libs/mlx/libmlx.a libs
		$(CC) $(FLAGSD) $(INC) -o $(NAME) $(OBJS) $(LIB)
		echo "$(NAME) created"

%.o: %.c
	$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:
		make $@ -C libs/libft
		make $@ -C libs/mlx
		$(RM) $(OBJS)
		echo "$(OBJS) deleted"

fclean: clean
		make $@ -C libs/libft
		$(RM) $(NAME)
		echo "$(NAME) deleted"

re:		fclean all

debug:
	@echo 'INC:$(INC)'
	@echo 'FLAGS:$(FLAGS)'

.PHONY: all clean fclean re
