NAME		:= hello_world
SRC			:= main.c
OBJS		:= $(SRC:.c=.o)

# CC_FLAGS	:= -Wall -Wextra -Werror
MLX_FLAGS	:= -lmlx -lXext -lX11 -lm

%.o:		%.c
			$(CC) -c $< $(CC_FLAGS) $(MLX_FLAGS) -o $@

$(NAME):	$(OBJS)
			$(CC) $< $(CC_FLAGS) $(MLX_FLAGS) -o $@
