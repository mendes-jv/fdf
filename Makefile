# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 14:09:11 by jovicto2          #+#    #+#              #
#    Updated: 2023/09/13 14:09:13 by jovicto2         ###   ########.org.br    #
#                                                                              #
# **************************************************************************** #

# Variables

NAME			:= fdf

SOURCES_DIR		:= sources/
OBJECTS_DIR		:= objects/
HEADERS_DIR		:= includes/
LIBRARIES_DIR	:= libraries/
MLX_DIR			:= $(addprefix $(LIBRARIES_DIR), mlx42/)
LIBFT_DIR		:= $(addprefix $(LIBRARIES_DIR), libft/)

MAKE			:= make
CMAKE			:= cmake
MAKE_LIBS		:= $(MAKE) -C
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -g3
FSANITIZE		:= -fsanitize=address
MKDIR			:= mkdir -p
RM				:= rm -rf

# Sources

SOURCE_FILES	:= fdf

SOURCES			:= $(addprefix $(SOURCES_DIR), $(addsuffix .c, $(SOURCE_FILES)))
OBJECTS			:= $(addprefix $(OBJECTS_DIR), $(addsuffix .o, $(SOURCE_FILES)))
LIBFT			:= $(addprefix $(LIBFT_DIR), libft.a)
MLX_BUILD		:= $(addprefix $(MLX_DIR), build/)
MLX				:= $(addprefix $(MLX_BUILD), libmlx42.a) -ldl -lglfw -pthread -lm

LIBFT_HEADER	:= $(addprefix $(LIBFT_DIR), includes/libft.h)
MLX_HEADER		:= $(addprefix $(MLX_DIR), include/)
HEADERS			:= -I $(HEADERS_DIR) -I $(MLX_HEADER)

# Libraries checkers

MLX_EXISTS		:= $(shell [ -e $(MLX) ] && echo 1 || echo 0)
LIBFT_EXISTS	:= $(shell [ -e $(LIBFT) ] && echo 1 || echo 0)

# Rules

.PHONY: all clean fclean re

all: libraries $(NAME)

libraries: $(MLX) $(LIBFT)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(FSANITIZE) $(OBJECTS) $(LIBFT) $(MLX) -o $(NAME) $(HEADERS)

$(LIBFT):
ifeq ($(LIBFT_EXISTS),0)
	@$(MAKE_LIBS) $(LIBFT_DIR)
endif

$(MLX):
ifeq ($(MLX_EXISTS),0)
	@$(CMAKE) $(MLX_DIR) -B $(MLX_BUILD) && $(MAKE_LIBS) $(MLX_BUILD) -j4
 endif

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c
	@$(MKDIR) $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean: cleanlibs
	@$(RM) $(OBJECTS_DIR)

cleanlibs: cleanmlx cleanlibft

cleanlibft:
	@$(MAKE_LIBS) $(LIBFT_DIR) fclean

cleanmlx:
	@$(RM) $(MLX_BUILD)

fclean: clean
	@$(RM) $(NAME)

re: fclean
	@$(MAKE)

run: all
	@./$(NAME)
