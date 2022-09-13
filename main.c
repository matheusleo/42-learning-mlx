/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 20:58:30 by mleonard          #+#    #+#             */
/*   Updated: 2022/09/12 23:27:20 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "colors.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int		offset;
	char	*dst;

	offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}

void	create_square(t_data *img, int size_goal, int color)
{
	static int	offset = 5;
	int			cur_len;
	int			cur_color;

	// write upper side
	cur_len = -1;
	while (++cur_len < size_goal)
		my_mlx_pixel_put(img, offset + cur_len, offset, color);
	// write left side
	cur_len = -1;
	while (++cur_len < size_goal)
		my_mlx_pixel_put(img, offset, offset + cur_len, color);
	// write down side
	cur_len = -1;
	while (++cur_len < size_goal)
		my_mlx_pixel_put(img, offset + cur_len, offset + size_goal, color);
	// write right side
	cur_len = -1;
	while (++cur_len < size_goal)
		my_mlx_pixel_put(img, offset + size_goal, offset + cur_len, color);

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

/*
	(x-xo)² + (y-yo)² = r²
	(cur_x - offset)² + (cur_y - offset)² = r²
 */
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

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 960, 640, "Hello world!");
	img.img = mlx_new_image(mlx, 960, 540);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
					&img.line_length, &img.endian);
	create_square(&img, 500, WHITE);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
