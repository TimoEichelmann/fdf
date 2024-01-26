# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/26 18:04:10 by teichelm          #+#    #+#              #
#    Updated: 2024/01/26 18:31:12 by teichelm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
MLX = libmlx.a
LIBRARIES = -lXext -lX11 -lm -Lft
SRC = controls.c draw.c fdf.c helpers.c initialize.c isometry.c mlx.c read.c
OBJ = controls.o draw.o fdf.o helpers.o initialize.o isometry.o mlx.o read.o
LIBFT_OBJS = libft.a

all : $(NAME)
$(NAME) : $(OBJ) $(LIBFT_OBJS) $(MLX)
	cc -Wall -Werror -Wextra -o fdf $(OBJ) $(LIBFT_OBJS) $(MLX) $(LIBRARIES)
$(OBJ) : $(SRC)
	cc -c -Wall -Werror -Wextra $(SRC)
$(LIBFT_OBJS):
	cd ./libft && make
	cd ./libft && mv libft.a "../"
	cd ./libft && make fclean
$(MLX):
	cd ./mlx && make
	cd ./mlx && mv libmlx.a "../"
clean:
	-rm -f $(OBJ) $(LIBFT_OBJS) $(MLX)
	cd libft && make clean
fclean: clean
	-rm -f $(NAME)
	cd libft && make clean
re: fclean all