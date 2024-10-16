NAME = cub3D
#NAME_BONUS = cub3D_bonus

CC = cc    
GREEN = \033[0;32m
BLUE = \033[0;34m
END = \033[0m

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

SRCS_DIR = src/

SOURCES  = 	main.c \
			init_game.c
		   
#SOURCES_BONUS  = 	


OBJS_DIR = objs/

OBJECTS = $(addprefix ${OBJS_DIR}, ${SOURCES:.c=.o})

# 确保 objs 目录存在
${OBJS_DIR}:
	@mkdir -p ${OBJS_DIR}
	@echo "${GREEN}${OBJS_DIR} directory created${END}"


#	@echo "${GREEN}${OBJS_DIR} directory created${END}"

#OBJECTS = ${addprefix ${OBJS_DIR}, ${SOURCES:.c=.o}}

	

${OBJS_DIR}%.o: ${SRCS_DIR}%.c | ${OBJS_DIR}
	${CC} ${FLAGS} ${INCLUDES} -c $< -o $@


#BONUS_OBJECTS = ${SOURCES_BONUS:.c=.o}
all: makelibft ${NAME}
#all: makelibft ${NAME} ${NAME_BONUS}


makelibft:
	@make -C ${LIBFT_DIR}
	@echo "${GREEN}${LIBFT_DIR} libft created${END}"

${LIBFT}:
	@make -C ./libft
	@echo "${GREEN}${LIBFT} libft created${END}"

${MLX42}:
	cd MLX42 &&    cmake -B build && cmake --build build -j4

${NAME}: ${OBJS_DIR} ${OBJECTS} ${LIBFT} ${MLX42} 
	@(echo "${BLUE}Creating The Executable ✅: ${NAME} ${END}" && ${CC} ${FLAGS} ${OBJECTS} ${LIBFT_INCLUDE} $(MLX42) $(MLX_FLAGS) ${LD_FLAGS} -L${LIBFT_DIR} ${INCLUDES} -lft -o ${NAME})

#${NAME_BONUS}: ${LIBFT} ${MLX42} ${BONUS_OBJECTS}
#	@(echo "${BLUE}Creating The Executable ✅: ${NAME_BONUS} ${END}" && ${CC} ${CFLAGS} ${BONUS_OBJECTS} ${LIBFT_INCLUDE} $(MLX42) $(MLX_FLAGS) ${LD_FLAGS} -L${LIBFT_DIR} ${INCLUDES} -lft -o ${NAME_BONUS})



clean:
	rm -f ${OBJECTS} ${BONUS_OBJECTS}
#	rm -fr ${OBJECTS_BONUS_DIR}
	@make clean -C ${LIBFT_DIR}
	rm -rf MLX42/build
	rm -rf ${OBJS_DIR}
#	rm -f .bonus
fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX42_DIR)
	@echo "${GREEN} ${NAME} removed${END}"

re: fclean all

# sets the default goal to re.
#.DEFAULT_GOAL := re

.PHONY: all makelibft clean fclean re


######################################################


# NAME = cub3D
# #NAME_BONUS = cub3D_bonus

# CC = cc    
# GREEN = \033[0;32m
# END = \033[0m

# FLAGS = -Wall -Wextra -Werror -I./libft -g 
# MLX_FLAGS = -lglfw -framework Cocoa -framework OpenGL -framework IOKit

# LIBFT_DIR = ./libft
# LIBFT = ./libft/libft.a
# LIBFT_INCLUDE = -I ${LIBFT_DIR}

# MLX42_DIR = ./MLX42/build
# MLX42 = ./MLX42/build/libmlx42.a
# #LD_FLAGS = -L/Users/${USER}/.brew/opt/glfw/lib/

# #for yunchia's mac
# LD_FLAGS = -L/usr/local/opt/glfw/lib/

# INCLUDES = -I/opt/X11/include -Imlx

# SOURCES  = 	./src/main.c\
		   
# #SOURCES_BONUS  = 	


# OBJECTS = ${SOURCES:.c=.o}
# #BONUS_OBJECTS = ${SOURCES_BONUS:.c=.o}


# all: makelibft ${NAME}
# #all: makelibft ${NAME} ${NAME_BONUS}

# %.o: %.c 
# 	${CC} ${FLAGS} ${INCLUDES} -c $< -o $@

# makelibft:
# 	make -C ${LIBFT_DIR}

# ${NAME}: ${LIBFT} ${MLX42} ${OBJECTS}
# 	@(echo "${GREEN}Creating The Executable: ${NAME} ✅${END}" && ${CC} ${CFLAGS} ${OBJECTS} ${LIBFT_INCLUDE} $(MLX42) $(MLX_FLAGS) ${LD_FLAGS} -L${LIBFT_DIR} ${INCLUDES} -lft -o ${NAME})

# #${NAME_BONUS}: ${LIBFT} ${MLX42} ${BONUS_OBJECTS}
# #	@(echo "${GREEN}Creating The Executable: ${NAME_BONUS} ✅${END}" && ${CC} ${CFLAGS} ${BONUS_OBJECTS} ${LIBFT_INCLUDE} $(MLX42) $(MLX_FLAGS) ${LD_FLAGS} -L${LIBFT_DIR} ${INCLUDES} -lft -o ${NAME_BONUS})

# ${LIBFT}:
# 	make -C ./libft

# ${MLX42}:
# 	cd MLX42 &&    cmake -B build && cmake --build build -j4

# clean:
# 	rm -f ${OBJECTS} ${BONUS_OBJECTS}
# 	@make clean -C ${LIBFT_DIR}
# 	rm -rf MLX42/build

# fclean: clean
# 	rm -f ${NAME}
# 	rm -rf ${MLX42_DIR}
# 	@echo "${GREEN} ${NAME} removed${END}"

# re: fclean all



# # .PHONY: all makelibft clean fclean re




