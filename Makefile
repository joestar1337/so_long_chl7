SRC = main.c get_next_line.c get_next_line_utils.c ft_split.c
OBJ = $(SRC:.c=.o)
NAME = so_long
CC = cc
CFLAGS = -W
LDFLAGS = -lXext -lX11 -lm -lz

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) ./mlx/libmlx_Linux.a -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all