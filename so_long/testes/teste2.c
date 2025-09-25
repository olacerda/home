/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 00:50:41 by olacerda          #+#    #+#             */
/*   Updated: 2025/09/18 05:50:43 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "teste.h"

void	teste(void *teste)
{
	int	size;

	size = sizeof(*teste);
	printf("Size in function: %d\n", size);
}

void	sheet_to_image_convertor(t_sheet *src, t_image *dst, int sprite_line, int sprite_column)
{
	int	bytes_per_line;
	int	img_line;
	int src_idx;
	int	dst_idx;
	int	count;
	
	bytes_per_line = ((src->bpp * dst->wide) / 8);  // PORQUE ISSO EMBAIXO NAO FUNCIONA  !!!!!!????
	src_idx = ((((sprite_line - 1) - ((sprite_line / (src->wide / dst->wide)) * (src->wide / dst->wide))) * dst->sizeline) + ((sprite_line / (src->wide / dst->wide)) * (src->sizeline * dst->tall)));
	img_line = 0;
	count = 0;
	dst_idx = 0;
	printf("\nsrc_index: %d\nsrc_sizeline: %d\nsrc_tall: %d\ndst_sizeline %d\ndst_tall: %d\ndst_wide: %d\nsrc_bpp: %d\n\n", src_idx, src->sizeline, src->tall, dst->sizeline, dst->tall, dst->wide, src->bpp);
	if (src_idx > ((src->sizeline * src->tall) - (dst->sizeline * dst->tall)))
		return ;
	while (img_line < dst->tall)
	{
		count = 0;
		while(count < bytes_per_line)
		{
			dst->img[dst_idx++] = src->img[src_idx++];
			count++;
		}
		img_line++;
		src_idx = (src_idx + src->sizeline - count);
		// (img_line * src->sizeline) + (dst->sizeline * (sprite_line - 1));
	}
}

void sheet_to_image_convertor(t_sheet *src, t_image *dst, int sprite_number)
{
    int sprite_w = 64;
    int sprite_h = 64;
    int bytes_per_pixel = src->bpp / 8;
    int sprites_per_row = src->wide / sprite_w;
    int src_start_y = ((sprite_number - 1) / sprites_per_row) * sprite_h;
    int src_start_x = ((sprite_number - 1) % sprites_per_row) * sprite_w;

    if (!src || !dst || !src->img || !dst->img)
        return;

    int y = 0;
    while (y < sprite_h)
    {
        int x = 0;
        while (x < sprite_w)
        {
            int src_idx = ((src_start_y + y) * src->sizeline) + (src_start_x + x) * bytes_per_pixel;
            int dst_idx = (y * dst->sizeline) + x * bytes_per_pixel;

            int b = 0;
            while (b < bytes_per_pixel)
            {
                dst->img[dst_idx + b] = src->img[src_idx + b];
                b++;
            }
            x++;
        }
        y++;
    }
}

int	main(void)
{
	struct s_primeira {int a, b, c; char *d;} primeira = {1, 2, 3, NULL};
	struct s_segunda {int a, b; char *d; char e, f, g, h; long i, j;} segunda = {1, 2, NULL, 'a', 'b', 'c', 'd', 4, 19};
	int	size1 = sizeof (primeira);
	int	size2 = sizeof (segunda);

	printf("Primeira: %d\nSgunda: %d\n", size1, size2);
	teste(&primeira);
	teste(&segunda);
}