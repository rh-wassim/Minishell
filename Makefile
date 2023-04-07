NAME		=	minishell

HEADER		=	./includes/minishell.h

LIBFT 		:=	./libft/libft.a

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra

SRCS		=	srcs/main.c \
				srcs/prompt.c \
				srcs/lexer_utils.c \
				srcs/lexer.c \

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				make -C libft/
#				$(CC) $(LIBFT) $(CFLAGS) $(HEADER) $(OBJS) -o $(NAME)
				$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
clean		:
				rm -rf $(OBJS)
				make clean -C libft/

fclean		:	clean
				rm -rf $(NAME)
				make fclean -C libft/

re			:	fclean all
