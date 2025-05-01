# Project Name
NAME        = minishell

# Compiler and Flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
INCLUDES    = -Iinc -Iinc/libft

# Library Paths
LIBFT       = inc/libft/libft.a

# Directories
SRC_DIR     = src
OBJ_DIR     = obj

# Source and Object Files
SRCS        = $(shell find $(SRC_DIR) -name "*.c")
OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Create object directories (mirroring the src structure)
DIRS        = $(sort $(dir $(OBJS)))

# Default target
all: $(NAME)

# Link the final executable
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# Compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(DIRS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create necessary object directories
$(DIRS):
	mkdir -p $@

# Build the libft library
$(LIBFT):
	$(MAKE) -C inc/libft

# Clean object files
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C inc/libft clean

# Remove objects and executable
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C inc/libft fclean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re