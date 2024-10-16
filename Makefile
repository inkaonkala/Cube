NAME = cub3D
#NAME_BONUS = cub3D_bonus

CC = cc    
GREEN = \033[0;32m

FLAGS = -Wall -Wextra -Werror -I./libft -g 
MLX_FLAGS = -lglfw -framework Cocoa -framework OpenGL -framework IOKit

LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a
LIBFT_INCLUDE = -I ${LIBFT_DIR}

MLX42_DIR = ./MLX42/build
MLX42 = ./MLX42/build/libmlx42.a
#LD_FLAGS = -L/Users/${USER}/.brew/opt/glfw/lib/

#for yunchia's mac
LD_FLAGS = -L/usr/local/opt/glfw/lib/

INCLUDES = -I/opt/X11/include -Imlx

SOURCES  = 	./src/main.c\
		   
#SOURCES_BONUS  = 	


OBJECTS = ${SOURCES:.c=.o}
#BONUS_OBJECTS = ${SOURCES_BONUS:.c=.o}


all: makelibft ${NAME} ${NAME_BONUS}


%.o: %.c 
	${CC} ${FLAGS} ${INCLUDES} -c $< -o $@

makelibft:
	make -C ${LIBFT_DIR}

${NAME}: ${LIBFT} ${MLX42} ${OBJECTS}
	@(echo "${GREEN}Creating The Executable✅: ${NAME}" && ${CC} ${CFLAGS} ${OBJECTS} ${LIBFT_INCLUDE} $(MLX42) $(MLX_FLAGS) ${LD_FLAGS} -L${LIBFT_DIR} ${INCLUDES} -lft -o ${NAME})

#${NAME_BONUS}: ${LIBFT} ${MLX42} ${BONUS_OBJECTS}
#	@(echo "${GREEN}Creating The Executable✅: ${NAME_BONUS}" && ${CC} ${CFLAGS} ${BONUS_OBJECTS} ${LIBFT_INCLUDE} $(MLX42) $(MLX_FLAGS) ${LD_FLAGS} -L${LIBFT_DIR} ${INCLUDES} -lft -o ${NAME_BONUS})

${LIBFT}:
	make -C ./libft

${MLX42}:
	cd MLX42 &&    cmake -B build && cmake --build build -j4

clean:
	rm -f ${OBJECTS} ${BONUS_OBJECTS}
	@make clean -C ${LIBFT_DIR}
	rm -rf MLX42/build

fclean: clean

re: fclean all