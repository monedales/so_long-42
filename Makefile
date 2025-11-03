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

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDE_DIR)
LDFLAGS := -L $(LIBFT_DIR#include <stdio.h>) -L $(MLX_DIR)
LDLIBS  := -lft -lmlx -lXext -lX11 -lm -lz
AR = ar rcs
RM = rm -rf

# Source files
SRC := mlx_test.c \


# Detect empty SRC to avoid linking when no sources are present
ifeq ($(strip $(SRC)),)
SRC_EMPTY := 1
else
SRC_EMPTY := 0
endif


OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Bonus source files - only checker-specific files
SRC_BONUS = \

# Shared files needed for checker (reuse from src/)
SRC_SHARED = \
	
OBJS_BONUS = $(addprefix $(OBJ_BONUS_DIR)/, $(SRC_BONUS:.c=.o))
OBJS_SHARED = $(addprefix $(OBJ_BONUS_DIR)/, $(SRC_SHARED:.c=.o))

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a

ifeq ($(strip $(SRC)),)
all: $(LIBFT)
	@printf '%b\n' "$(YELLOW)No source files in $(SRC_DIR) (SRC is empty). Add .c files to SRC in Makefile to build $(NAME).$(RESET)"
else
all: $(NAME)
endif

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@$(MAKE) banner

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

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
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@echo "$(RED) $(NAME) objects removed$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo "$(RED) $(NAME) deleted$(RESET)"

re: fclean all
	@echo "$(LILAC_TRUE)🔄 $(NAME) rebuild$(RESET)"

normi:
	@norminette -R CheckForbiddenSourceHeader $(addprefix $(SRC_DIR)/, $(SRC)) $(INCLUDE_DIR)/*.h