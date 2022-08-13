NAME		=	philosophers

HEADER		=	philo.h

SRC			=	init.c life_and_death.c ft_atoi.c time.c

OBJ			=	$(SRC:.c=.o)

FLAGS		=	-Wall -Wextra -Werror

%.o: %.c	$(HEADER)
			gcc $(FLAGS) -o $@ -c $< -I $(HEADER) -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ) $(HEADER)
			gcc $(FLAGS) $(OBJ) -o $(NAME)

clean:
		rm -f *.o
		@echo "All cleaned"
		@say	"All cleaned"

fclean:	clean
		rm -f $(NAME)
			
re:		fclean all

.PHONY:	all clean fclean re
		@say		"PHONY like a Pony"