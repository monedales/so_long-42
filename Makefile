# Program name
NAME = so_long
# BONUS_NAME = 

# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
YELLOW = \033[0;33m
LILAC = \033[0;95m
# 24-bit "truecolor" lilac (pastel). Terminal must support 24-bit color to show this.
LILAC_TRUE = \033[38;2;200;162;200m
RESET = \033[0m

# Directories
SRC_DIR = src
SRC_BONUS_DIR = src_bonus

INCLUDE_DIR = include

LIBFT_DIR = libs/libft
MLX_DIR = libs/minilibix-linux

OBJ_DIR = obj
OBJ_BONUS_DIR = obj_bonus

#flag pro mac -Wno-deprecated-non-prototype -std=c17
# Compiler and base flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDE_DIR) -I $(MLX_DIR)
AR = ar rcs
RM = rm -rf

# Detect system (macOS or Linux)
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	# macOS config - Using XQuartz (X11)
	X11_PATH = /opt/X11
	CFLAGS += -I $(X11_PATH)/include -Wno-deprecated-non-prototype
	LDFLAGS := -L $(LIBFT_DIR) -L $(MLX_DIR) -L $(X11_PATH)/lib
	LDLIBS  := -lft -lmlx -lXext -lX11 -lm -lz
else ifeq ($(UNAME_S), Linux)
	# Linux config
	LDFLAGS := -L $(LIBFT_DIR) -L $(MLX_DIR)
	LDLIBS  := -lft -lmlx -lXext -lX11 -lm -lz
else
	$(error Unsupported operating system: $(UNAME_S))
endif

# Source files
SRC := so_long.c map_parser.c map_validator.c map_count.c pathfinding.c \
	error_handler.c game_init.c texture_loader.c render.c render_tiles.c \
	render_utils.c events.c events_animation.c free_utils.c free_textures.c \
	file_utils.c camera.c scenes.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Bonus source files - only checker-specific files
SRC_BONUS = \

# Shared files needed for checker (reuse from src/)
SRC_SHARED = \
	
OBJS_BONUS = $(addprefix $(OBJ_BONUS_DIR)/, $(SRC_BONUS:.c=.o))
OBJS_SHARED = $(addprefix $(OBJ_BONUS_DIR)/, $(SRC_SHARED:.c=.o))

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a

# Default rule
all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@$(MAKE) banner

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR) --silent

# Bonus target
# bonus: $(BONUS_NAME)

# $(BONUS_NAME): $(OBJS_BONUS) $(OBJS_SHARED) $(LIBFT)
# 	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(OBJS_SHARED) $(LIBFT) -o $(BONUS_NAME)
# 	@$(MAKE) bonus-banner

# $(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
# 	@mkdir -p $(OBJ_BONUS_DIR)
# 	@$(CC) $(CFLAGS) -c $< -o $@

# $(OBJ_BONUS_DIR)/%.o: $(SRC_DIR)/%.c
# 	@mkdir -p $(OBJ_BONUS_DIR)
# 	@$(CC) $(CFLAGS) -c $< -o $@


# Banner rules
banner:
	@echo ""
	@printf '%b\n' "$(LILAC_TRUE) ███████╗ ██████╗     ██╗      ██████╗ ███╗   ██╗ ██████╗ $(RESET)"
	@printf '%b\n' "$(LILAC_TRUE) ██╔════╝██╔═══██╗    ██║     ██╔═══██╗████╗  ██║██╔════╝ $(RESET)"
	@printf '%b\n' "$(LILAC_TRUE) ███████╗██║   ██║    ██║     ██║   ██║██╔██╗ ██║██║  ███╗$(RESET)"
	@printf '%b\n' "$(LILAC_TRUE) ╚════██║██║   ██║    ██║     ██║   ██║██║╚██╗██║██║   ██║$(RESET)"
	@printf '%b\n' "$(LILAC_TRUE) ███████║╚██████╔╝    ███████╗╚██████╔╝██║ ╚████║╚██████╔╝$(RESET)"
	@printf '%b\n' "$(LILAC_TRUE) ╚══════╝ ╚═════╝     ╚══════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ $(RESET)"
	@echo ""
	@echo "           🐱 Louis    vs    Ozzy 🐱"
	@echo "            /\\_/\\ ← →  ← → /\\_/\\" 
	@echo "           ( o.o )          ( -.- )"
	@echo "            > ^ <           > ^ <"
	@echo ""
	@echo "$(GREEN)Compiled successfully! Ready to explore the map!$(RESET)"
	@echo ""

# bonus-banner:
# 	@echo ""


.PHONY: all clean fclean re normi banner bonus-banner bonus

# Quick visual test for colors
test_colors:
	@printf '%b\n' "$(LILAC)LILAC (ANSI bright magenta)$(RESET)"
	@printf '%b\n' "$(LILAC_TRUE)LILAC_TRUE (24-bit truecolor)$(RESET)"

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) clean --silent
	@$(RM) $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@echo "$(RED) $(NAME) objects removed$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo "$(RED) $(NAME) deleted$(RESET)"

re: fclean all
	@echo "$(LILAC_TRUE)🔄 $(NAME) rebuild$(RESET)"

normi:
	@norminette -R CheckForbiddenSourceHeader $(addprefix $(SRC_DIR)/, $(SRC)) $(INCLUDE_DIR)/*.h
# Valgrind testing
valgrind: $(NAME)
	@echo "$(YELLOW)Running valgrind with MLX suppressions...$(RESET)"
	@valgrind --leak-check=full --suppressions=valgrind.supp --show-leak-kinds=definite,indirect ./$(NAME) maps/medium.ber

valgrind-full: $(NAME)
	@echo "$(YELLOW)Running valgrind showing all leaks...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) maps/medium.ber
