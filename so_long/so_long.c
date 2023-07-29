/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:45:15 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/07/29 17:03:35 by jiwkim2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		ft_strrlen(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (str[i] != '.')
	{
		i--;
		j++;
	}
	j--;
	return(j);
}

void check_arg(int argc, char *argv)
{
    char *c;

    if (argc != 2)
    	ft_error();
	c = ft_strchr(argv, '.');
	if (ft_strrlen(c) > 3)
		ft_error();
	if (c && (ft_strncmp(c, ".ber", 4) != 0))
		ft_error();
}

void set_t_game(t_game *game)
{
 	game->empty = 0;
	game->wall = 0;
	game->collectible = 0;
	game->exit = 0;
	game->position = 0;
	game->map_x = 0;
	game->map_y = 0;
	game->move_count = 0;
	game->flag = 0;
}

int	line_count_sub(t_game *game, int line_count, char *line)
{
	game->map_x = ft_strlen(line);
	line_count = ft_strlen(line);
	return (line_count);
}

void line_count_wrong_x(char *line, char *all_lines)
{
	free(line);
	free(all_lines);
	exit(1);
}

void	temp_sub(char *temp)
{
	free(temp);
	exit (1);
}

char 	*get_gnl_map_sub(t_game *game, char *line, char *all_lines, int fd)
{
	char *temp;
	int line_count;

	line_count = 0;
	while (line)
	{
		line = get_next_line(fd);
		game->map_y++;
		if (line_count == 0)
			line_count = line_count_sub(game, line_count, line);
		else if (game->map_x != line_count)	
			line_count_wrong_x(line, all_lines);
		if (line == NULL || line[0] == '\n')
		{
			free(line);
 			break ;
		}
		temp = ft_strjoin(all_lines, line);
		free(all_lines);
		free(line);
		if (!temp)
			temp_sub(temp);
		all_lines = temp;
	}
	return (all_lines);
}

char **get_gnl_map(char *c, t_game *game, char *line)
{
	char	*all_lines;
	int		fd;
	char 	**aa;

	all_lines = ft_strdup("");
	if (!all_lines)
		exit(1);
	fd = open(c, O_RDONLY);
	if (fd < 0)
	{
		free(all_lines);
		exit(1);
	}
	all_lines = get_gnl_map_sub(game, line, all_lines, fd);
	close(fd);
	aa = ft_split(all_lines, '\n');
	free(all_lines);
	if (!aa)
		exit(1);
	return (aa);
}

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i);
}

void	check_rectangular(t_game **game)
{
	int	y;
	int	x;
	int	height;
	int	backup;

	y = 0;
	backup = 0;
	height = get_height((*game)->map);
	while (y != height)
	{
		x = 0;
		while ((*game)->map[y][x] != '\0')
			x++;
		y++;
		if (backup != 0)
		{
			if (backup != x)
				ft_error();
		}
		else
			backup = x;
	}
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

void	check_wall(t_game **game)
{
	int		i;

	if (!(check_line((*game)->map[0])))
		ft_error();
	i = get_height((*game)->map);
	if (!(check_line((*game)->map[i - 1])))
		ft_error();
	i--;
	while (i)
	{
		if ((*game)->map[i][0] != '1')
			ft_error();
		if ((*game)->map[i][ft_strlen((*game)->map[i]) -1 ] != '1')
			ft_error();
		i--;
	}
}

void check_c_p_e_sub(t_game **game, int i, int j)
{
	(*game)->exit_y = i;
	(*game)->exit_x = j;
	(*game)->exit++;
}

void	check_c_p_e_ones(t_game **game)
{
	int i;
	int j;

	(*game)->exit = 0;
	(*game)->collectible = 0;
	(*game)->position = 0;
	i = get_height((*game)->map) - 1;
	while (i)
	{
		j = 0;
		while ((*game)->map[i][j] != '\0')
		{
			if ((*game)->map[i][j] == 'E')
				check_c_p_e_sub(game, i ,j);
			else if ((*game)->map[i][j] == 'P')
				(*game)->position++;
			else if ((*game)->map[i][j] == 'C')
				(*game)->collectible++;
			j++;
		}
		i--;
	}
	if ((*game)->exit != 1 || (*game)->position != 1 || (*game)->collectible < 1)
		ft_error();
}

void	check_map(t_game *game)
{
	check_rectangular(&game);
	check_wall(&game);
	check_c_p_e_ones(&game);
}

void			game_init(t_game *game)
{
	int xx;
	int yy;
	int height;
	int backup;
	
	yy = 0;
	backup = 0;
	height = get_height((game)->map);
	while (yy != height)
	{
		xx = 0;
		while ((game)->map[yy][xx] != 'P')
		{
			if ((game)->map[yy][xx] == '\0')
				break ;
			xx++ ;
		}
		if ((game)->map[yy][xx] == 'P')
			break;
		yy++;
	}
	game->x = xx;
	game->y = yy;
}

int	check_move_x(int y, int x, char **map)
{
	if (map[y][x] != '1')
		return (1);
	return (0);
}

int	check_move_y(int x, int y, char **map)
{
	if (map[y][x] != '1')
	{
		return (1);
	}
	return (0);
}

void dfs(t_game *game, int x, int y, char **map) 
{
    if (map[y][x] == 'E' || map[y][x] == 'C')
        game->e_plus_c++;
        map[y][x] = '1';
        if (check_move_y(x, y - 1, map) == 1)
		{
            dfs(game, x, y - 1, map);
        }
        if (check_move_y(x, y + 1, map) == 1)
		{
            dfs(game, x, y + 1, map);
        }
        if (check_move_x(y, x - 1, map) == 1)
		{
            dfs(game, x - 1, y, map);
        }
        if (check_move_x(y, x + 1, map) == 1) 
		{
            dfs(game, x + 1, y, map);    
        }
}

char	*ft_strcpy(char *dest, char *src)
{
	int	a;

	a = 0;
	while (src[a] != '\0')
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = '\0';
	return (dest);
}

char **check_dfs_sub(t_game *game) 
{
    char **map_dfs;
    int i;

    map_dfs = (char **)malloc(sizeof(char *) * (game->map_y));
    if (!map_dfs)
        exit(1);
    i = 0;
    while (i < game->map_y -1 ) 
	{
        map_dfs[i] = (char *)malloc(sizeof(char) * (game->map_x + 1));
        if (!map_dfs[i]) 
		{
            while (i > 0) 
			{
                i--;
                free(map_dfs[i]);
            }
            free(map_dfs);
            exit(1);
        }
        ft_strcpy(map_dfs[i], game->map[i]);
        i++;
    }
    map_dfs[i] = 0;
    return (map_dfs);
}


void check_dfs(t_game *game) 
{
	int	i;
	char **map_dfs;
	
	map_dfs = check_dfs_sub(game);
    dfs(game, game->x, game->y, map_dfs);
    i = 0;
    while (map_dfs[i]) 
	{
        free(map_dfs[i]);
        i++;
    }
    free(map_dfs);
	if (game->e_plus_c != game->exit + game->collectible)
        ft_error();
}




void move_write(unsigned int move)
{
	char	i;

	if (move / 10 > 0)
		move_write(move / 10);
	i = move % 10 + '0';
	write(1, &i , 1);
}

void	move_func(t_game *game)
{
	write(1, "move_count : ", 13);
	move_write(++game->move_count);
	write(1, "\n", 1);
	
}

void	put_img(t_game *game, int x, int y, char *file)
{
	int		img_width;
	int		img_height;
	void	*img;

	img = mlx_xpm_file_to_image(game->mlx, file, &img_width, &img_height);
	if (!img)
		return ;
	mlx_put_image_to_window(game->mlx, game->mlx_win, img, y * 64, x * 64);
	mlx_destroy_image(game->mlx, img);
}

void	categorize_case(t_game *game, int x, int y)
{
	if (game->map[x][y] == '0')
		put_img(game, x, y, "./images/back_ground.xpm");
	else if (game->map[x][y] == '1')
	{
		put_img(game, x, y, "./images/back_ground.xpm");
		put_img(game, x, y, "./images/tree.xpm");
	}
	else if (game->map[x][y] == 'E')
	{
		put_img(game, x, y, "./images/back_ground.xpm");
		if (game->c_check == game->collectible)
			put_img(game, x, y, "./images/exit_fin.xpm");
		else
			put_img(game, x, y, "./images/exit.xpm");
	}
	else if (game->map[x][y] == 'C')
	{
		put_img(game, x, y, "./images/back_ground.xpm");
		put_img(game, x, y, "./images/eat.xpm");
	}
	else if (game->map[x][y] == 'P')
	{
		put_img(game, x, y, "./images/back_ground.xpm");
		put_img(game, x, y, "./images/player.xpm");
	}
}

void	show_map(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	mlx_clear_window(game->mlx, game->mlx_win);
	while (++i < game->map_y - 1)
	{
		j = -1;
		while (++j < game->map_x - 1)
		{
			categorize_case(game, i, j);
		}
	}
	if (game->map[game->y][game->x] == game->map[game->exit_y][game->exit_x] \
		&& (game->c_check == game->collectible))
	{	
		exit(0);
	}
}

void	move_player_flag(t_game *game, int xx, int yy)
{
	if (game->map[yy][xx] == '1')
		return ;
	if(game->map[yy][xx] == 'C')
		game->c_check++;
		game->map[yy][xx] = 'P';
		game->map[game->y][game->x] = 'E';
		game->y = yy;
		game->x = xx;
		game->flag = 0;
}

void	move_player_zero(t_game *game, int xx, int yy)
{
	game->map[yy][xx] = 'P';
	game->map[game->y][game->x] = '0';
	game->y = yy;
	game->x = xx;
}

void	move_player_c(t_game *game, int xx, int yy)
{
	game->c_check++;
		game->map[yy][xx] = 'P';
		game->map[game->y][game->x] = '0';
		game->y = yy;
		game->x = xx;
}

void	move_player(t_game *game, int xx, int yy)
{
	if (game->flag == 1)
		move_player_flag(game, xx, yy);
	 if (game->map[yy][xx] == '0')
		move_player_zero(game, xx, yy);
	else if (game->map[yy][xx] == '1')
		return ;
	else if (game->map[yy][xx] == 'C')
		move_player_c(game, xx, yy);
	else if (game->map[yy][xx] == 'E')
	{
		if (game->collectible != game->c_check)
			game->flag = 1;
		game->map[yy][xx] = 'P';
		game->map[game->y][game->x] = '0';
		game->y = yy;
		game->x = xx;
	}
	move_func(game);
	show_map(game);
}

int				key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		move_player(game, game->x, game->y - 1);
	else if (keycode == KEY_S)
		move_player(game, game->x, game->y + 1);
	else if (keycode == KEY_A)
		move_player(game, game->x - 1, game->y);
	else if (keycode == KEY_D)
		move_player(game, game->x + 1, game->y);
	else if (keycode == KEY_ESC)
		exit(0);
	return (0);
}


int main(int argc, char **argv)
{
    t_game  game;
	char	*line;

	line = "";
    check_arg(argc, argv[1]);
	set_t_game(&game);
	game.map = get_gnl_map(argv[1], &game, line);
	check_map(&game);
	game_init(&game);
	check_dfs(&game);
	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, (game.map_x -1) * 64, (game.map_y -1 )* 64, argv[0]);
	show_map(&game);
	mlx_hook(game.mlx_win, X_EVENT_KEY_RELEASE, 0, &key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}