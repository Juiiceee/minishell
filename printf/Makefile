NAME = libftprinterr.a

OBJ_DIR			:= ../obj

SRC = ft_printerr.c \
		ft_printerr_utils.c \
		print_char.c \
		print_lhex.c \
		print_uhex.c \
		print_nbr.c \
		print_unbr.c \
		print_pointer.c \
		print_str.c 

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

FLAGS = -Wall -Wextra -Werror  

ARC = ar rcs

LIBRAN = ranlib

CC = cc

INCLUDE = ft_printerr.h

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

$(NAME): $(OBJ)
		$(ARC) $(NAME) $(OBJ)
		$(LIBRAN) $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
