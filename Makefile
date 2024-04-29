NAME = pipex
BNAME = checker
CC = cc

SRC = 	parse.c \
		main.c  \
		exec.c  \

BSRC = 	

OBJ = $(SRC:.c=.o)
BOBJ = $(BSRC:.c=.o)

all: $(NAME) 

$(NAME):$(OBJ)
	@make -C libft
	@make -C ft_printf
	$(CC) $(SRC) -Wall -Wextra -Werror -ggdb3 ./ft_printf/libftprintf.a ./libft/libft.a -o $(NAME)

$(BNAME):$(BOBJ)
	@make -C libft
	@make -C ft_printf
	$(CC) $(BSRC) -Wall -Wextra -Werror -g ./ft_printf/libftprintf.a ./libft/libft.a -o $(BNAME)

bonus : $(BNAME)

clean:
	rm -rf $(OBJ) $(BOBJ)
	@make clean -C libft
	@make clean -C ft_printf
fclean: clean
	rm -rf $(NAME) $(BNAME)
	@make fclean -C libft
	@make fclean -C ft_printf
re: fclean all
.SECONDARY: $(OBJ) $(BOBJ)