CC=cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC_DIR = src
OBJ_DIR = obj
SRCS = src/main.c \
src/monitor.c \
src/philo.c \
src/utils/cleanup.c \
src/utils/ft_atoi.c \
src/utils/philo_action.c \
src/utils/time.c

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

NAME = philo

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/utils

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test