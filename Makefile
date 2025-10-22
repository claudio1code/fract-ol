NAME = fractol

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

SRCS_DIR = srcs/
OBJS_DIR = objs/
INCS_DIR = includes/
LIBFT_DIR = libft/
MLX_DIR = minilibx-linux/

SRCS_LIST = 	mouse_key.c \
				fractol.c \
				parsing_input.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(SRCS_LIST:.c=.o))

LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a

INCLUDES = -I $(INCS_DIR) -I $(LIBFT_DIR)/includes -I $(MLX_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

GREEN = \033[0;92m
YELLOW = \033[0;93m
CYAN = \033[0;96m
DEF_COLOR = \033[0;39m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@echo -n "$(YELLOW)A linkar $(NAME)... $(DEF_COLOR)"
	@sh -c 'i=0; while [ $$i -lt 10 ]; do \
		echo -n "\b|"; sleep 0.05; \
		echo -n "\b/"; sleep 0.05; \
		echo -n "\b-"; sleep 0.05; \
		echo -n "\b\\"; sleep 0.05; \
		i=$$(($$i+1)); \
	done'
	@echo "\b\b$(GREEN)OK!$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@echo -n "$(CYAN)A compilar $<... $(DEF_COLOR)"
	@sh -c 'i=0; while [ $$i -lt 10 ]; do \
		echo -n "\b|"; sleep 0.05; \
		echo -n "\b/"; sleep 0.05; \
		echo -n "\b-"; sleep 0.05; \
		echo -n "\b\\"; sleep 0.05; \
		i=$$(($$i+1)); \
	done'
	@echo "\b\b$(GREEN)OK!$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(MLX_LIB):
	@make -sC $(MLX_DIR)
clean:
	@rm -rf $(OBJS_DIR)
	@make -sC $(LIBFT_DIR) clean
	@make -sC $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
