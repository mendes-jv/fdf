# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 14:09:11 by jovicto2          #+#    #+#              #
#    Updated: 2023/09/26 08:51:38 by jovicto2         ###   ########.org.br    #
#                                                                              #
# **************************************************************************** #

# Variables

NAME			:= fdf

SOURCES_DIR		:= sources/
OBJECTS_DIR		:= objects/
HEADERS_DIR		:= includes/
LIBRARIES_DIR	:= libraries/
BUILD_DIR		:= build/
MLX_DIR			:= $(addprefix $(LIBRARIES_DIR), mlx42/)
LIBFT_DIR		:= $(addprefix $(LIBRARIES_DIR), libft/)
MLX_FILE		:= libmlx42.a
LIBFT_FILE 		:= libft.a

MAKE			:= make
CMAKE			:= cmake
MAKE_LIBS		:= $(MAKE) -C
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -g3
FSANITIZE		:= -fsanitize=address
MKDIR			:= mkdir -p
RM				:= rm -rf
MLX_FLAGS		:= -ldl -lglfw -pthread -lm

# Sources

SOURCE_FILES	:= fdf map_handle error_handle

SOURCES			:= $(addprefix $(SOURCES_DIR), $(addsuffix .c, $(SOURCE_FILES)))
OBJECTS			:= $(addprefix $(OBJECTS_DIR), $(addsuffix .o, $(SOURCE_FILES)))
LIBFT			:= $(addprefix $(LIBFT_DIR), $(LIBFT_FILE))
MLX_BUILD		:= $(addprefix $(MLX_DIR), $(BUILD_DIR))
MLX				:= $(addprefix $(MLX_BUILD), $(MLX_FILE))

LIBFT_HEADER	:= $(addprefix $(LIBFT_DIR), includes/libft.h)
MLX_HEADER		:= $(addprefix $(MLX_DIR), include/)
HEADERS			:= -I $(HEADERS_DIR) -I $(MLX_HEADER)

# Rules

.PHONY: all clean fclean re

all: libraries $(NAME)

libraries: $(MLX) $(LIBFT)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(FSANITIZE) $(OBJECTS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME) $(HEADERS)

$(LIBFT):
	@$(MAKE_LIBS) $(LIBFT_DIR)

$(MLX):
	@$(CMAKE) $(MLX_DIR) -B $(MLX_BUILD) && $(MAKE_LIBS) $(MLX_BUILD) -j4

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
