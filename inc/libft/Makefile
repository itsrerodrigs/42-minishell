# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 18:39:36 by marielidias       #+#    #+#              #
#    Updated: 2025/06/09 18:53:21 by renrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I../includes
AR = ar rcs
RM = rm -f

SRCS = ft_atoi.c     ft_atol.c      ft_bzero.c      ft_calloc.c   \
       ft_isalnum.c  ft_isalpha.c   ft_isascii.c    ft_isdigit.c  \
       ft_isprint.c  ft_isspace.c   ft_itoa.c       ft_lstadd_back.c \
       ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
       ft_lstlast.c  ft_lstmap.c    ft_lst_remove_node.c ft_lstsize.c \
       ft_memchr.c   ft_memcmp.c    ft_memcpy.c     ft_memmove.c \
       ft_memset.c   ft_putchar.c    ft_putchar_fd.c ft_putendl_fd.c \
       ft_putnbr.c    ft_putnbr_fd.c  ft_putnbr_hex.c ft_putnbr_u.c \
       ft_putptr.c    ft_putstr.c     ft_putstr_fd.c  ft_printf.c \
       ft_split.c     ft_strchr.c     ft_strdup.c     ft_striteri.c \
       ft_strjoin.c   ft_strlcat.c    ft_strlcpy.c    ft_strlen.c \
       ft_strmapi.c   ft_strnstr.c    ft_strncmp.c    ft_strrchr.c \
       ft_strtrim.c   ft_substr.c     ft_tolower.c    ft_toupper.c \
       get_next_line.c ft_strcmp.c    ft_strndup.c      ft_atoi_n.c

OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
