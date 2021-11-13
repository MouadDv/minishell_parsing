# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chicky <chicky@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 00:43:14 by milmi             #+#    #+#              #
#    Updated: 2021/11/12 17:12:06 by chicky           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft.a
SRCS = main.c env_strct.c scan.c print_strct.c parser.c rmquotes.c parser_utils.c parser_utils2.c parser_utils3.c data_proccessing.c data_proccessing_utils.c free.c execution.c implim_cd.c implim_pwd.c implim_export.c implim_unset.c implim_env.c implim_echo.c implim_exit.c call_exec.c pipes.c exec_redir.c pipes_norm.c exec_redir_norm.c exec_redir_norm2.c implim_export_utils.c impim_export_utils2.c call_exec_utils.c
FLAGS= -g -lreadline -L /Users/milmi/.brew/opt/readline/lib -I /Users/milmi/.brew/opt/readline/include -Wall -Wextra -Werror -fsanitize=address
HOMEENVFLAGS= -g -lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include -Wall -Wextra -Werror -fsanitize=address
VALGRIND= -lreadline -L /Users/milmi/.brew/opt/readline/lib -I /Users/milmi/.brew/opt/readline/include -Wall -Wextra -Werror
LINUXFLAGS= libreadline.a
rm = rm -f
CC = gcc

all : $(NAME)

$(NAME) : $(LIBFT)  $(LINUXFLAGS)
	$(CC) $(LINUXFLAGS) $(LIBFT) $(SRCS) $(LIBFT) -lreadline -o $(NAME)

$(LINUXFLAGS):
	make -C readline
	cp readline/libreadline.a .

$(LIBFT):
	make -C libft
	cp libft/libft.a .

valgrind: fclean $(LIBFT)
	$(CC) $(VALGRIND) $(LIBFT) $(SRCS) $(LIBFT) -o $(NAME)
	valgrind --leak-check=full ./minishell
clean :
	
fclean : clean
	@$(rm) $(NAME)
	make -C libft fclean
	$(rm) libft.a

re: fclean all

.PHONY: all bonus both clean fclean re
