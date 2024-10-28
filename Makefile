

NAME = cub3D

CC = cc    
CFLAGS = -Wall -Wextra -Werror -g 
MLX_FLAGS = -L/opt/X11/lib -lX11 -lXext -lglfw -lm # Linux-specific flags

# Library directories and files
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE = -I$(LIBFT_DIR)

MLX42_DIR = ./MLX42/build
MLX42 = $(MLX42_DIR)/libmlx42.a

# Include directories
INCLUDES = -I/opt/X11/include -Iinclude -Ilibft -IMLX42/include

# Source files and object files
SOURCES = $(wildcard src/*.c)
OBJS_DIR = objs/
OBJECTS = $(SOURCES:src/%.c=objs/%.o)

# Rule to build everything
all: makelibft makemlx $(NAME)

# Build the executable
$(NAME): ${OBJECTS} $(LIBFT) $(MLX42)
	@echo "\033[0;32mCreating The Executable✅: ${NAME}\033[0m"
	@$(CC) $(OBJECTS) $(LIBFT) $(MLX42) $(INCLUDES) $(MLX_FLAGS) -o $(NAME)
	
# Compile object files
objs/%.o: src/%.c
	@mkdir -p objs
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiling: $(notdir $<)"

# Rule for building libft
makelibft:
	@make -C $(LIBFT_DIR)

# Rule for building MLX42
makemlx:
	@if [ ! -f "$(MLX42)" ]; then \
		cd MLX42 && cmake -B build && cmake --build build; \
	fi

# Clean up object files
clean:
	@rm -rf ${OBJS_DIR}
	@rm -f ${OBJECTS}
	@make clean -C ${LIBFT_DIR}
	@echo "Cleaning MLX42..."
	@rm -rf $(MLX42_DIR) ${OBJECTS}

# Full clean
fclean: clean
	@rm -f $(NAME)
	@echo "Executable and objects removed."

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re makelibft makemlx

# NAME = cub3D

# CC = cc    
# CFLAGS = -Wall -Wextra -Werror -g 
# MLX_FLAGS = -L/opt/X11/lib -lX11 -lXext -lglfw -lm # Linux-specific flags

# # Library directories and files
# LIBFT_DIR = ./libft
# LIBFT = $(LIBFT_DIR)/libft.a
# LIBFT_INCLUDE = -I$(LIBFT_DIR)

# MLX42_DIR = ./MLX42/build
# MLX42 = $(MLX42_DIR)/libmlx42.a

# # Include directories
# INCLUDES = -I/opt/X11/include -Iinclude -Ilibft -IMLX42/include

# # Source files and object files
# SOURCES = $(wildcard src/*.c)
# OBJECTS = $(SOURCES:src/%.c=objs/%.o)

# # Rule to build everything
# all: makelibft makemlx $(NAME)

# # Build the executable
# $(NAME): ${OBJECTS} $(LIBFT) $(MLX42)
# 	@echo "\033[0;32mCreating The Executable✅: ${NAME}\033[0m"
# 	@$(CC) ${OBJECTS} $(LIBFT) $(MLX42) $(INCLUDES) $(MLX_FLAGS) -o ${NAME}
	
# # Compile object files
# objs/%.o: src/%.c
# 	@mkdir -p objs
# 	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
# 	@echo "Compiling: $(notdir $<)"

# # Rule for building libft
# makelibft:
# 	@make -C $(LIBFT_DIR)

# # Rule for building MLX42
# makemlx:
# 	@if [ ! -f "$(MLX42)" ]; then \
# 		cd MLX42 && cmake -B build && cmake --build build; \
# 	fi

# # Clean up object files
# clean:
# 	@rm -f ${OBJECTS}
# 	@make clean -C ${LIBFT_DIR}
# 	@echo "Cleaning MLX42..."
# 	@rm -rf $(MLX42_DIR)

# # Full clean
# fclean: clean
# 	@rm -f $(NAME)
# 	@echo "Executable and objects removed."

# # Rebuild everything
# re: fclean all

# .PHONY: all clean fclean re makelibft makemlx



