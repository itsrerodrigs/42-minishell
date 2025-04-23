# Project Name
NAME        = minishell

# Compiler and Flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
INCLUDES    = -Iinc -Iinc/libft

# Library Paths
LIBFT       = inc/libft/libft.a

# Source and Object Directories
SRC_DIR     = src
OBJ_DIR     = obj

# Source Files
SRCS        =	$(addprefix $(SRC_DIR)/, builtin.c execution.c input_handling.c main.c memory.c tokenization.c signals_utils.c  utils.c )
			  
			  
# Object Files
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default Target
all: $(NAME)

# Rule to build the final executable
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to create the object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Rule to build the libft library
$(LIBFT):
	@$(MAKE) -C inc/libft

# Clean up object files
clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C inc/libft clean

# Clean up everything (objects and executable)
fclean: clean
	rm -f $(NAME)
	@make -C inc/libft fclean

# Rebuild the project
re: fclean all

# Phony targets to avoid conflicts with files of the same name
.PHONY: all clean fclean re