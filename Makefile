NAME = cub3D

CC = cc    
GREEN = \033[0;32m

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g 
#MLX_FLAGS = -lglfw -framework Cocoa -framework OpenGL -framework IOKit
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit

# Library directories and files
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE = -I${LIBFT_DIR}

MLX42_DIR = ./MLX42/build
MLX42 = $(MLX42_DIR)/libmlx42.a

# Include directories
INCLUDES = -I/opt/X11/include -Iinclude -Ilibft -IMLX42/include

# Source files and object files
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

# Rule to build everything
all: makelibft $(NAME)

# Build the executable
$(NAME): ${MLX42} ${LIBFT} ${OBJECTS} 
	@echo "${GREEN}Creating The Executable✅: ${NAME}" 
	@$(CC) ${OBJECTS} $(LIBFT_INCLUDE) -o ${NAME}
	
# Pattern rule for compiling object files
$(OBJECTS): %.o: %.c 
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "Compiling: $(notdir $<)\n"


# Rule for building libft
makelibft:
	@make -C ${LIBFT_DIR}

# Rule for building MLX42
$(MLX42):
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		cd MLX42 && cmake -B build; \
	fi
	@make -C $(MLX42_DIR) || { echo "Error: MLX42 build failed!"; exit 1; }

# Clean up object files
clean:
	@rm -f ${OBJECTS}
	@make clean -C ${LIBFT_DIR}
	rm -rf $(MLX42_DIR)

# Full clean
fclean: clean
	@rm -f $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re makelibft
