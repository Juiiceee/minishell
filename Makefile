NAME            := pipex
OBJ_DIR         := obj
SRCS            := error.c ft_split.c main.c process.c utils.c utilsprocess.c
OBJS            := $(SRCS:%.c=$(OBJ_DIR)/%.o)
CC              := cc
CFLAGS          := -Wall -Wextra -Werror -g3 -MMD -MP
RM              := rm -rf
DIR_DUP         = mkdir -p $(@D)

all             : $(NAME)

norm    :
   $(NORM)

$(NAME) :       $(OBJS)
   $(CC) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
   $(DIR_DUP)
   $(CC) -c $< $(CFLAGS) -o $@

clean   :
   $(RM) $(OBJ_DIR)

fclean  :       clean
   $(RM) $(NAME)

re      :       fclean all

.PHONY: all clean fclean re

-include $(DEP)