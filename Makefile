NAME = so_long
CC = cc
MLX_LIB = libs/mlx/
LIBFT_LIB = libs/libft/
FLAGS = -L $(LIBFT_LIB) -lft -L $(MLX_LIB) -L /usr/lib -lmlx -lXext -lX11 -lm
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
RM		= rm -f

SRC = 	srcs/main.c \
		srcs/get_data.c  \
		srcs/draw_map.c \
		srcs/key_hook.c \
		srcs/utils.c \

OBJS = $(SRC:%.c=%.o)

all:	$(NAME)

.c.o:
		$(CC) -I includes/. $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
		make -C $(MLX_LIB)
		make -C $(LIBFT_LIB)
		$(CC) $(CFLAGS) $(OBJS) $(FLAGS) -o $(NAME)

clean:
		$(RM) */*.o
		$(RM) $(OBJS)
		make -C $(MLX_LIB) clean
		make -C $(LIBFT_LIB) clean

fclean:	clean
		$(RM) $(NAME) $(MLX_LIB)/libmlx.a
		make -C $(LIBFT_LIB) fclean

re:		fclean all

.PHONY : all clean fclean re bonus