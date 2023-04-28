NAME		=	minishell

HEADER		=	./includes/minishell.h

LIBFT 		:=	./libft/libft.a

CC			=	gcc

CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g  -I /Users/wrhilane/Desktop/readline-8.2

SRCS		= srcs/main.c \
			srcs/init.c \
		 	srcs/lexer.c \
			srcs/lexer_check.c \
			srcs/lexer_utils1.c \
			srcs/lexer_utils2.c \
			srcs/lexer_utils3.c \
			srcs/parsing.c \
			srcs/parsing_check.c \
			srcs/utils_general_2.c \
			srcs/utils_general_1.c \
			srcs/utils_general_3.c \
			srcs/redir_utils.c \
			execution/echo.c \
			execution/pwd.c \
			execution/unset.c \
			execution/env.c \
			execution/cd.c \
			execution/exit.c \
			execution/ft_export.c \
			execution/excutebuitins.c \
			execution/findpath.c \
			execution/id_utils.c \

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				make -C libft/
#				$(CC) $(LIBFT) $(CFLAGS) $(HEADER) $(OBJS) -o $(NAME)
				$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline /Users/wrhilane/Desktop/readline-8.2/libreadline.a -lcurses
clean		:
				rm -rf $(OBJS)
				make clean -C libft/

fclean		:	clean
				rm -rf $(NAME)
				make fclean -C libft/

re			:	fclean all
