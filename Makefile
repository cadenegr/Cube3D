# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 14:55:14 by cadenegr          #+#    #+#              #
#    Updated: 2024/10/09 13:59:06 by cadenegr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCDIRS =	src src/main src/parse_map src/line src/keypress src/3d
OBJDIR = obj
LIBFTDIR = libft
MINILIBXDIR = minilibx-linux

SRC_FILES = src/main/main.c \
            src/main/init.c \
            src/parse_map/elements_map.c \
            src/parse_map/map.c \
            src/parse_map/textures.c \
            src/parse_map/validate_map.c \
            src/line/line.c \
            src/line/fov.c \
            src/keypress/keypress.c \
            src/keypress/util_keypress.c \
            src/3d/3d.c \
            src/3d/3d_tex.c
OBJ_FILES = $(SRC_FILES:%.c=$(OBJDIR)/%.o)

LIBFT = $(LIBFTDIR)/libft.a
MINILIBX = $(MINILIBXDIR)/libmlx.a
INCLUDES = -I./include -I$(LIBFTDIR) -I$(MINILIBXDIR)

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L$(LIBFTDIR) -lft -L$(MINILIBXDIR) -lmlx -L/usr/X11R6/lib -lXext -lX11 -lm
RM = rm -rf

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJDIR) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME) $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	make -C $(LIBFTDIR)

$(MINILIBX):
	make -C $(MINILIBXDIR)

clean:
	$(RM) $(OBJDIR)
	make -C $(LIBFTDIR) clean
	make -C $(MINILIBXDIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFTDIR) fclean
	make -C $(MINILIBXDIR) clean

re: fclean all
