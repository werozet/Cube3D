NAME		:= cub3D
INCDIR		:= include
SRCDIR		:= src
LIBFTDIR	:= libft
LIBFT		:= $(LIBFTDIR)/libft.a
LIBFT_INC	:= -I $(LIBFTDIR)/includes

SRC			:= \
	cleanup.c \
	config_identifiers.c \
	config_parse_helpers.c \
	config_parse.c \
	image.c \
	input_helpers.c \
	input.c \
	main_helpers.c \
	main.c \
	map_parse_helpers.c \
	map_parse_read_rows.c \
	map_parse_row.c \
	map_parse.c \
	map_validate.c \
	raycast_helpers.c \
	raycast_init_ray.c \
	raycast.c \
	render.c \
	utils_color.c \
	utils_math.c \

SRC			:= $(addprefix $(SRCDIR)/,$(SRC))

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -I $(INCDIR) $(LIBFT_INC)

MLXDIR		:= minilibx-linux
MLX_REPO	:= https://github.com/42Paris/minilibx-linux.git
MLXINC		:= -I $(MLXDIR)
MLXFLAGS	:= -L$(MLXDIR) -lmlx_Linux -lXext -lX11 -lm -lz
MLXDEP		:= $(MLXDIR)/libmlx_Linux.a

CFLAGS		+= $(MLXINC)

OBJ			:= $(SRC:.c=.o)

.PHONY: all clean fclean re bonus mlx fetch-mlx update-mlx

all: $(NAME)

$(NAME): $(LIBFT) $(MLXDEP) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(MLXDIR):
	git clone --depth 1 $(MLX_REPO) $(MLXDIR)

$(MLXDEP): | $(MLXDIR)
	$(MAKE) -C $(MLXDIR)

mlx: $(MLXDEP)
fetch-mlx: $(MLXDIR)
update-mlx:
	@if [ -d "$(MLXDIR)" ]; then \
		git -C $(MLXDIR) pull --ff-only; \
	else \
		git clone --depth 1 $(MLX_REPO) $(MLXDIR); \
	fi

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	@if [ -d "$(MLXDIR)" ]; then $(MAKE) -C $(MLXDIR) clean; fi
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	rm -f $(NAME)

re: fclean all

bonus: all
