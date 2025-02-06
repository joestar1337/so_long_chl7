#include "./mlx/mlx.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "get_next_line.h"
#include "fcntl.h"
# include <X11/keysym.h>
# include <X11/X.h>

typedef struct s_data
{
    // mlx
    void *ptr;
    void *win;
    // tsawaer
    void *player;
    void *ground;
    void *wall;
    void *coin;
    /// map
    char **map;
    int row;
    int col;
}t_data;


void ft_down(t_data *data)
{
    int p_x;
    int p_y;
    int x;
    int y;
    char **map = data->map;

    p_x = 0;
    p_y = 0;

    while (map[p_y])
    {
        p_x = 0;
        while (map[p_y][p_x])
        {
            if (map[p_y][p_x] == 'P')
            {
                x = p_x;
                y = p_y;
            }
            p_x++;
        }
        p_y++;
    }
    if (map[y + 1][x] == '1')
        return;
    else if (map[y + 1][x] == '0')
    {
        mlx_put_image_to_window(data->ptr, data->win, data->player, x * 64, (y + 1) * 64);
        mlx_put_image_to_window(data->ptr, data->win, data->ground, x * 64, y * 64);
        map[y + 1][x] = 'P';
        map[y][x] = '0';
    }
}



void ft_up(t_data *data)
{
    int p_x;
    int p_y;
    int x;
    int y;
    char **map = data->map;

    p_x = 0;
    p_y = 0;

    while (map[p_y])
    {
        p_x = 0;
        while (map[p_y][p_x])
        {
            if (map[p_y][p_x] == 'P')
            {
                x = p_x;
                y = p_y;
            }
            p_x++;
        }
        p_y++;
    }
    if (map[y - 1][x] == '1')
        return;
    else if (map[y - 1][x] == '0')
    {
        mlx_put_image_to_window(data->ptr, data->win, data->player, x * 64, (y - 1) * 64);
        mlx_put_image_to_window(data->ptr, data->win, data->ground, x * 64, y * 64);
        map[y - 1][x] = 'P';
        map[y][x] = '0';
    }
}

void ft_left(t_data *data)
{
    int p_x;
    int p_y;
    int x;
    int y;
    char **map = data->map;

    p_x = 0;
    p_y = 0;

    while (map[p_y])
    {
        p_x = 0;
        while (map[p_y][p_x])
        {
            if (map[p_y][p_x] == 'P')
            {
                x = p_x;
                y = p_y;
            }
            p_x++;
        }
        p_y++;
    }
    if (map[y][x + 1] == '1')
        return;
    else if (map[y][x + 1] == '0')
    {
        mlx_put_image_to_window(data->ptr, data->win, data->player, (x + 1) * 64, y * 64);
        mlx_put_image_to_window(data->ptr, data->win, data->ground, x * 64, y * 64);
        map[y][x + 1] = 'P';
        map[y][x] = '0';
    }
}

void ft_right(t_data *data)
{
    int p_x;
    int p_y;
    int x;
    int y;
    char **map = data->map;

    p_x = 0;
    p_y = 0;

    while (map[p_y])
    {
        p_x = 0;
        while (map[p_y][p_x])
        {
            if (map[p_y][p_x] == 'P')
            {
                x = p_x;
                y = p_y;
            }
            p_x++;
        }
        p_y++;
    }
    if (map[y][x + 1] == '1')
        return;
    else if (map[y][x - 1] == '0')
    {
        mlx_put_image_to_window(data->ptr, data->win, data->player, (x - 1) * 64, y * 64);
        mlx_put_image_to_window(data->ptr, data->win, data->ground, x * 64, y * 64);
        map[y][x - 1] = 'P';
        map[y][x] = '0';
    }
}



int key_hand(int key, t_data *data)
{
    if (key == XK_Up)
        ft_up(data);
    if (key == XK_Down)
        ft_down(data);
    if (key == XK_Left)
        ft_right(data);
    if (key == XK_Right)
        ft_left(data);
}


char	**ft_split(char const *s, char c);

int main(int c, char **v)
{
    if (!v[1])
        return (1);
    int fd = open(v[1], 0);
    if (fd == -1)
        return (3);
    char *map = NULL;
    char *tmp;
    char **map2d;
    while (1)
    {
        tmp = get_next_line(fd);
        if (!tmp)
            break ;
        map = ft_join(map, tmp);
    }

    map2d = ft_split(map, '\n');
    int h = 64;
    int w = 64;
    int x = 0;
    int y = 0;
    int row = 0;
    while (map2d[row])
        row++;

    void *ptr = mlx_init();
    void *win = mlx_new_window(ptr, strlen(map2d[0]) * 64, row * 64, "taha zaml");
    void *ground = mlx_xpm_file_to_image(ptr, "tmounir.xpm", &w, &h);
    void *wall = mlx_xpm_file_to_image(ptr, "tamounir.xpm", &w, &h);
    void *coin = mlx_xpm_file_to_image(ptr, "amlo.xpm", &w, &h);
    void *player = mlx_xpm_file_to_image(ptr, "player.xpm", &w, &h);

    while (y < row)
    {
        x = 0;
        while (x < (int)strlen(map2d[0]))
        {
            if (map2d[y][x] == '1')
                mlx_put_image_to_window(ptr, win, wall, x * 64, y * 64);
            if (map2d[y][x] == '0')
                mlx_put_image_to_window(ptr, win, ground, x * 64, y * 64);
            if (map2d[y][x] == 'P')
                mlx_put_image_to_window(ptr, win, player, x * 64, y * 64);
            if (map2d[y][x] == 'C')
                mlx_put_image_to_window(ptr, win, coin, x * 64, y * 64);
            x++;
        }
        y++;
    }

    t_data data;
    // inialize struct 
    data.coin = coin;
    data.player = player;
    data.ground = ground;
    data.wall = wall;
    data.col = strlen(map2d[0]);
    data.row = row;
    data.map = map2d;
    data.ptr = ptr;
    data.win = win;


    // lesten for keys
    mlx_key_hook(win, key_hand, &data);
    mlx_loop(ptr);
}