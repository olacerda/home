/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:31:21 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/01 13:02:32 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "so_long.h"

int	main(void)
{
	void	*mlx = mlx_init();
	void	*window = mlx_new_window(mlx, 600, 600, "TESTE");
	void	*image = mlx_new_image(mlx, WIDE, TALL);
	int bpp = 0;
	int endian = 0;
	int wide = 0;
	char	*buffer = mlx_get_data_addr(image, &bpp, &wide, &endian);
	int	line = 0;
	int	column = 0;
	int	index = 0;
	while (line < 64)
	{
		column = 0;
		while (column < 64)
		{
			((int *)buffer)[index] = 85542;
			index++;
			column++;
		}
		line++;
	}
	mlx_put_image_to_window(mlx, window, image, 0, 0);
	mlx_loop(mlx);	
}