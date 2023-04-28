NAME = minishell

LIBFT = libft/libft.a

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -lreadline #-fsanitize=address -g3

C_FILES = echo.c \
			pwd.c \
			unset.c \
			env.c \
			cd.c \
			exit.c \
			ft_export.c \
			# excutebuitins.c \
			#findpath.c \
			# main.c \
			# chdir.c \
			#
			
			

all : $(NAME)

$(NAME) : $(C_FILES) $(LIBFT)
			$(CC) $(CFLAGS) $(C_FILES) $(LIBFT) -o $(NAME)

$(LIBFT) :
		make -C libft
clean :
	$(RM) $(NAME)
	make clean -C libft

fclean : clean
	$(RM) $(NAME) $(NAMEB)
	make fclean -C LIBFT

re: fclean all


git : 
	git add . && git commit -m "mimiz" && git push origin master