# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/28 10:48:33 by mdavid            #+#    #+#              #
#    Updated: 2020/06/24 15:15:51 by mdavid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = srcs/
OBJ_DIR = objs/

vpath %.c srcs/list
vpath %.c srcs/string
vpath %.c srcs/memory
vpath %.c srcs/table
vpath %.c srcs/printing
vpath %.c srcs/others
vpath %.o $(OBJ_DIR)
vpath %.h include

INC_DIR= include/
INCLUDE = libft.h

LIB_FILES =	ft_memset	\
			ft_bzero	\
			ft_memcpy	\
			ft_memccpy	\
			ft_memmove	\
			ft_memchr	\
			ft_memcmp	\
			ft_strlen	\
			ft_strdup	\
			ft_strcpy	\
			ft_strncpy	\
			ft_strcat	\
			ft_strncat	\
			ft_strlcat	\
			ft_strchr	\
			ft_strrchr	\
			ft_strstr	\
			ft_strnstr	\
			ft_strcmp	\
			ft_strncmp	\
			ft_atoi	\
			ft_isalpha	\
			ft_isdigit	\
			ft_isalnum	\
			ft_isascii	\
			ft_isprint	\
			ft_toupper	\
			ft_tolower	\
			ft_memalloc	\
			ft_memdel	\
			ft_strnew	\
			ft_strdel	\
			ft_strclr	\
			ft_striter	\
			ft_striteri	\
			ft_strmap	\
			ft_strmapi	\
			ft_strequ	\
			ft_strnequ	\
			ft_strsub	\
			ft_strjoin	\
			ft_strtrim	\
			ft_strsplit	\
			ft_itoa	\
			ft_putchar	\
			ft_putstr	\
			ft_putendl	\
			ft_putnbr	\
			ft_putchar_fd	\
			ft_putstr_fd	\
			ft_putendl_fd	\
			ft_putnbr_fd	\
			ft_lstnew	\
			ft_lstdelone	\
			ft_lstdel	\
			ft_lstadd	\
			ft_lstiter	\
			ft_lstmap	\
			ft_isupper	\
			ft_islower	\
			ft_power	\
			ft_eraser	\
			ft_strjoin_1n	\
			ft_strdup_1n	\
			ft_strjoin_1sp	\
			ft_strdup_1sp	\
			ft_strdup_p	\
			ft_strtrunc_x	\
			ft_strdupfree

LIB_SRCS = $(addsuffix .c, $(LIB_FILES))
LIB_OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(LIB_FILES)))

# ---------- COLORS ---------- #
NOC = \033[0m
BOLD = \033[1m
UNDERLINE = \033[4m
BLACK = \033[1;30m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
VIOLET = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m

#---------- RULES ---------- #
all : $(NAME)

$(NAME) : $(LIB_OBJS)
	@echo "$(CYAN)[ar rcs)]$(NOC)$(VIOLET)Constructing librairy$(NOC)"
	@ar rcs $(NAME) $^
	@echo "$(CYAN)[ar rcs)]$(NOC) --> $(GREEN)Librairy created$(NOC)"

$(LIB_OBJS): $(INCLUDE) | $(OBJ_DIR)

$(OBJ_DIR)%.o : %.c
	@echo "  $(CYAN)[$(CC)] - [$(CFLAGS)]$(NOC) $(YELLOW)$(BOLD)in progress ...:$(NOC) $< \033[1;31m->\033[0m $@"
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR): 
	@mkdir -p $@

show:
	@echo "$(YELLOW)LIB_FILES:$(NOC)\n $(LIB_FILES)"
	@echo "$(YELLOW)LIB_SRCS:$(NOC)\n $(LIB_SRCS)"
	@echo "$(YELLOW)LIB_OBJS:$(NOC)\n $(LIB_OBJS)"

norme :
	 @norminette -R CheckForbiddenSourceHeader $(SRCS) $(INCLUDE)
	 
clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all show norme clean fclean re