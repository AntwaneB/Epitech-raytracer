##
## Makefile for fdf in /home/buchse_a/Documents/Piscine-C-lib/my
## 
## Made by Antoine Buchser
## Login   <buchse_a@epitech.net>
## 
## Started on  Mon Oct 21 09:30:31 2013 Antoine Buchser
## Last update Fri Jun  6 10:57:31 2014 Alexandre Page
##

LIB_X		=	./minilibx/
INC_DIR		=	./

CFLAGS		+=	-pthread -Wall -Wextra

RM		=	rm -f
CC		=	cc
NAME		=	rt

SRCS		=	main.c \
			init.c \
			threads.c \
			materials.c \
			limits.c \
			console.c \
			backup.c \
			my_explode.c \
			color.c \
			multispot.c \
			light.c \
			shadow.c \
			checkerboard.c \
			sphere.c \
			plane.c \
			cone.c \
			cylindre.c \
			events.c \
			events_light.c \
			events_dump.c \
			parsing.c \
			parsing_special.c \
			parsing_obj.c \
			rotations.c \
			my_math.c \
			misc.c \
			get_next_line.c \
			mlx_put_pixel_in_image.c \
			reflexion.c \
			perlin.c \
			perlin_init.c \
			pos_operations.c \
			transparency.c \
			antialiasing.c \
			inverse.c \
			legend.c \
			fill_pos.c \
			my_str_to_wordtab.c

OBJS		=	$(SRCS:.c=.o)

all: ./minilibx/libmlx.a $(NAME)

./minilibx/libmlx.a:
	make -C $(LIB_X)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -I$(INC_DIR) -lmlx_$(HOSTTYPE) -L$(LIB_X) -L/usr/lib64 -L/usr/lib64/X11 -lXext -lX11 -lm -pthread

clean:
	make clean -C $(LIB_X)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
