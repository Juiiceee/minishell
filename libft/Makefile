NAME = libft.a

SRC = ft_bzero.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_memcpy.c \
		ft_memcmp.c \
		ft_memchr.c \
		ft_memset.c \
		ft_memmove.c \
		ft_strlen.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_itoa.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c 

SRCB = 	ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c

OBJ = $(SRC:.c=.o)

OBJB = $(SRCB:.c=.o)

FLAGS = -Wall -Wextra -Werror  

ARC = ar rc

LIBRAN = ranlib

CC = cc

INCLUDE = ./

.c.o:
		$(CC) $(FLAGS) -c $< -o ${<:.c=.o} -I $(INCLUDE)

$(NAME): ${OBJ}
		$(ARC) $(NAME) $(OBJ)
		$(LIBRAN) $(NAME)

all: $(NAME) $(bonus)

clean:
	rm -f $(OBJ) $(OBJB)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: ${OBJB}
	$(ARC) $(NAME) $(OBJB)
	$(LIBRAN) $(NAME)

so:
	$(CC) -nostartfiles -fPIC $(FLAGS) $(SRC)
	gcc -nostartfiles -shared -o libft.so $(OBJ)

.PHONY : all clean fclean re so bonus
