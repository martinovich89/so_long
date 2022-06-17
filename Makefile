NAME		=	test

LIB			=	-L./libs/libft -lft -L./libs/mlx -lm -lX11 -lbsd -lXext -lmlx
INC			=	-I./includes -I./libs/mlx



SRC_PATH	=	./srcs/

SRC			=	malloc_runtime.c

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
	$(CC) $(FLAGSD) $(INC) -o $@ -c $<

clean:
		make $@ -C libs/libft
		make $@ -C libs/mlx
		$(RM) $(OBJS)
		echo "$(OBJS) deleted"

fclean: clean
		make $@ -C libs/libft
		$(RM) ./libs/libft.a ./libs/libmlx.a
		$(RM) $(NAME)
		echo "$(NAME) deleted"

re:		fclean all

debug:
	@echo 'INC:$(INC)'
	@echo 'FLAGS:$(FLAGS)'

.PHONY: all clean fclean re
