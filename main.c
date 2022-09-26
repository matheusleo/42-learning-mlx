/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 20:58:30 by mleonard          #+#    #+#             */
/*   Updated: 2022/09/26 19:18:36 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "colors.h"
#include "keys.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}			t_vars;

typedef struct s_square
{
	int	x_pos;
	int	y_pos;
}			t_square;


typedef struct s_docs
{
	t_data		*data;
	t_vars		*vars;
	t_square	*square;
}			t_docs;


// GETTING STARTED
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int		offset;
	char	*dst;

	offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}

void	create_square(t_data *img, int size_goal, int color, int offset_x, int offset_y)
{
	int			cur_len;
	int			cur_color;

	// write upper side
	cur_len = -1;
	while (++cur_len < size_goal)
		my_mlx_pixel_put(img, offset_x + cur_len, offset_y, color);
	// write left side
	cur_len = -1;
	while (++cur_len < size_goal)
		my_mlx_pixel_put(img, offset_x, offset_y + cur_len, color);
	// write down side
	cur_len = -1;
	while (++cur_len < size_goal)
		my_mlx_pixel_put(img, offset_x + cur_len, offset_y + size_goal, color);
	// write right side
	cur_len = -1;
	while (++cur_len < size_goal)
		my_mlx_pixel_put(img, offset_x + size_goal, offset_y + cur_len, color);

}

void	create_circle_version_1(t_data *img, int radius, int color)
{
	static int	offset = 250;
	int			cur_x;
	int			cur_y;

	cur_x = 0;
	cur_y = 0;
	// prints third sector
	while (--cur_x >= radius * -1 && --cur_y >= radius * -1)
		my_mlx_pixel_put(img, offset + cur_x, offset + cur_y, RED);
	// prints second sector
	while (++cur_x <= 0 && --cur_y >= radius * -2)
		my_mlx_pixel_put(img, offset + cur_x, offset + cur_y, GREEN);
	// print first sector
	while (++cur_x <= radius && ++cur_y <= 0)
		my_mlx_pixel_put(img, offset + cur_x, offset + cur_y, BLUE);
	// print fourth sector
	while (--cur_x >= 0 && ++cur_y <= radius)
		my_mlx_pixel_put(img, offset + cur_x, offset + cur_y, WHITE);
}

void	create_circle_version_2(t_data *img, int radius, int color)
{
	int	offset;
	int	cur_x;
	int	cur_y;
	int	cur_radius_sq;

	offset = 250;
	cur_x = 0;
	cur_y = 0;
	cur_radius_sq = cur_x * cur_x + cur_y + cur_y;
	while (cur_radius_sq <= radius * radius)
	{
		my_mlx_pixel_put(img, cur_x + offset, cur_y + offset, color);
		cur_x++;
		cur_y++;
		cur_radius_sq = cur_x * cur_x + cur_y + cur_y;
	}
}

// EVENTS
int	close_win(t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	mouse_entered(int x, int y, t_vars *vars)
{
	printf("Hello!\n");
}

int	mouse_left(int x, int y, t_vars *vars)
{
	printf("Bye!\n");
}

int	mouse_moved(int x, int y, t_vars *vars)
{
	printf("Moving!\n");
}

int cross_click(t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}


int	key_press(int keycode, t_vars *vars)
{
	printf("%d\n", keycode);
	// close on ESC
	if (keycode == 0xff1b)
		close_win(vars);
}

// HOOKS
int	key_hook(int keycode, t_vars vars)
{
	printf("Hello from key_hook function!\n");
}

int	mouse_hook(int keycode, t_vars *vars)
{
	printf("Hello from mouse_hook function\n");
}

int	mouse_move_hook(int x, int y, t_vars *vars)
{
	printf("Hello from mouse_move_hook function\n");
	printf("pos_x %d\n", x);
	printf("pos_y %d\n", y);
}

// LOOPS
int move_square(int keycode, t_docs *docs)
{
	t_square	*square;
	t_vars		*vars;
	t_data		*data;

	printf("move_square\nkeycode %d\n", keycode);
	square = docs->square;
	vars = docs->vars;
	data = docs->data;
	if (keycode == W_CODE && square->y_pos > 0)
		square->y_pos--;
	if (keycode == S_CODE && square->y_pos < 640)
		square->y_pos++;
	if (keycode == A_CODE && square->x_pos > 0)
		square->x_pos--;
	if (keycode == D_CODE && square->x_pos < 960)
		square->x_pos++;
	create_square(&(data->img), 50, 16711680, square->x_pos, square->y_pos);
}

int	render_next_frame(t_docs *docs)
{
	t_data		*data;
	t_vars		*vars;
	t_square	*square;

	data = docs->data;
	vars = docs->vars;
	square = docs->square;
	mlx_put_image_to_window(vars->mlx, vars->win, data->img, 0, 0);
}

int	main(void)
{
	t_vars		vars;
	t_data		img;
	t_square	square;
	t_docs		docs;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 960, 640, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 960, 640);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
					&img.line_length, &img.endian);
	square.x_pos = 50;
	square.y_pos = 25;
	docs.data = &img;
	docs.vars = &vars;
	docs.square = &square;
	create_square(&img, 50, 16711680, square.x_pos, square.y_pos);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, move_square, &docs);
	mlx_loop_hook(vars.mlx, render_next_frame, &docs);
	mlx_loop(vars.mlx);
}
