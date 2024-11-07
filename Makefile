

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


################################### for mac

# NAME = cub3D

# CC = cc    
# CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
# #MLX_FLAGS = -L/opt/X11/lib -lX11 -lXext -lglfw -lm # Linux-specific flags

# #MLX_FLAGS = -L/usr/local/opt/libx11/lib -L/usr/local/opt/libxext/lib -lX11 -lXext
# MLX_FLAGS = -L/usr/local/opt/glfw/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit

# # Library directories and files
# LIBFT_DIR = ./libft
# LIBFT = $(LIBFT_DIR)/libft.a
# LIBFT_INCLUDE = -I$(LIBFT_DIR)

# MLX42_DIR = ./MLX42/build
# MLX42 = $(MLX42_DIR)/libmlx42.a
# #MLX42 = ./libmlx42.a

# # 链接选项，指向 libx11 和 libxext 的库


# # 包含选项，指向 libx11 和 libxext 的头文件
# INCLUDES = -I/usr/local/opt/libx11/include -I/usr/local/opt/libxext/include


# # Include directories
# #INCLUDES = -I/opt/X11/include -Iinclude -Ilibft -IMLX42/include


# # Source files and object files
# SOURCES = $(wildcard src/*.c)
# OBJS_DIR = objs/
# OBJECTS = $(SOURCES:src/%.c=objs/%.o)

# # Rule to build everything
# all: makelibft makemlx $(NAME)

# # Build the executable
# $(NAME): ${OBJECTS} $(LIBFT) $(MLX42)
# 	@echo "\033[0;32mCreating The Executable✅: ${NAME}\033[0m"
# 	@$(CC) $(OBJECTS) $(LIBFT) $(MLX42) $(INCLUDES) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)
	
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
# 	@rm -rf ${OBJS_DIR}
# 	@rm -f ${OBJECTS}
# 	@make clean -C ${LIBFT_DIR}
# 	@echo "Cleaning MLX42..."
# 	@rm -rf $(MLX42_DIR) ${OBJECTS}

# # Full clean
# fclean: clean
# 	@rm -f $(NAME)
# 	@echo "Executable and objects removed."

# # Rebuild everything
# re: fclean all

# .PHONY: all clean fclean re makelibft makemlx