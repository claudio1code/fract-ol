NAME = fractol

CC = gcc
CFLAGS = -Wall -Werror -Wextra -O3 -Wno-unused-result -march=native -ffast-math

SRCS_DIR = srcs/
OBJS_DIR = objs/
INCS_DIR = includes/
LIBFT_DIR = libft/
MLX_DIR = minilibx-linux/

SRCS_LIST = 	mouse_key.c \
				fractol.c \
				parsing_input.c \
				julia_and_mandelbrot.c \
				image.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(SRCS_LIST:.c=.o))

LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a

INCLUDES = -I $(INCS_DIR) -I $(LIBFT_DIR)/includes -I $(MLX_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lpthread

RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
CYAN = \033[0;96m
DEF_COLOR = \033[0;39m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@printf "$(YELLOW)Linking $(NAME)... $(DEF_COLOR)"
	@sh -c '(while kill -0 $$PPID 2>/dev/null; do \
		echo -n "\b|"; sleep 0.05; \
		echo -n "\b/"; sleep 0.05; \
		echo -n "\b-"; sleep 0.05; \
		echo -n "\b\\"; sleep 0.05; \
	done) & trap "kill $$!" EXIT; \
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)'
	@printf "\b$(GREEN)OK!$(DEF_COLOR)\n"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@printf "$(CYAN)Compiling $<... $(DEF_COLOR)"
	@sh -c '(while kill -0 $$PPID 2>/dev/null; do \
		echo -n "\b|"; sleep 0.05; \
		echo -n "\b/"; sleep 0.05; \
		echo -n "\b-"; sleep 0.05; \
		echo -n "\b\\"; sleep 0.05; \
	done) & trap "kill $$!" EXIT; \
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@'
	@printf "\b$(GREEN)OK!$(DEF_COLOR)\n"

$(LIBFT):
	@printf "$(CYAN)Compiling Libft... $(DEF_COLOR)"
	@sh -c '(while kill -0 $$PPID 2>/dev/null; do \
		echo -n "\b|"; sleep 0.05; \
		echo -n "\b/"; sleep 0.05; \
		echo -n "\b-"; sleep 0.05; \
		echo -n "\b\\"; sleep 0.05; \
	done) & trap "kill $$!" EXIT; \
	make -sC $(LIBFT_DIR) > /dev/null'
	@printf "\b$(GREEN)OK!$(DEF_COLOR)\n"

$(MLX_LIB):
	@printf "$(CYAN)Compiling MinilibX... $(DEF_COLOR)"
	@sh -c '(while kill -0 $$PPID 2>/dev/null; do \
		echo -n "\b|"; sleep 0.05; \
		echo -n "\b/"; sleep 0.05; \
		echo -n "\b-"; sleep 0.05; \
		echo -n "\b\\"; sleep 0.05; \
	done) & trap "kill $$!" EXIT; \
	make -sC $(MLX_DIR) > /dev/null 2>&1'
	@printf "\b$(GREEN)OK!$(DEF_COLOR)\n"

clean:
	@printf "$(RED)Cleaning objects... $(DEF_COLOR)"
	@sh -c '(while kill -0 $$PPID 2>/dev/null; do \
		echo -n "\b|"; sleep 0.05; \
		echo -n "\b/"; sleep 0.05; \
		echo -n "\b-"; sleep 0.05; \
		echo -n "\b\\"; sleep 0.05; \
	done) & trap "kill $$!" EXIT; \
	rm -rf $(OBJS_DIR) && make -sC $(LIBFT_DIR) clean > /dev/null && make -sC $(MLX_DIR) clean > /dev/null'
	@printf "\b$(GREEN)OK!$(DEF_COLOR)\n"

fclean: clean
	@printf "$(RED)Cleaning executable... $(DEF_COLOR)"
	@sh -c '(while kill -0 $$PPID 2>/dev/null; do \
		echo -n "\b|"; sleep 0.05; \
		echo -n "\b/"; sleep 0.05; \
		echo -n "\b-"; sleep 0.05; \
		echo -n "\b\\"; sleep 0.05; \
	done) & trap "kill $$!" EXIT; \
	rm -f $(NAME) && make -sC $(LIBFT_DIR) fclean'
	@printf "\b$(GREEN)OK!$(DEF_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re
