/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 20:58:30 by mleonard          #+#    #+#             */
/*   Updated: 2022/09/09 10:19:35 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

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

	// write upper side
	cur_len = -1;
	while (++cur_len < size_goal) {
		my_mlx_pixel_put(img, offset + cur_len, offset, 0x00FF0000);
	}
	// write left side
	cur_len = -1;
	while (++cur_len < size_goal) {
		my_mlx_pixel_put(img, offset, offset + cur_len, 0x0000FF00);
	}
	// write down side
	cur_len = -1;
	while (++cur_len < size_goal) {
		my_mlx_pixel_put(img, offset + cur_len, offset + size_goal, 0x000000FF);
	}
	// write right side
	cur_len = -1;
	while (++cur_len < size_goal) {
		my_mlx_pixel_put(img, offset + size_goal, offset + cur_len, 0xFFFFFF);
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
	create_square(&img, 100, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
