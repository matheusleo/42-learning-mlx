/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 20:58:30 by mleonard          #+#    #+#             */
/*   Updated: 2022/09/05 23:24:03 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

int main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	
	mlx_win = mlx_new_window(mlx, 960, 540, "Hello world!");
	mlx_loop(mlx);
}
