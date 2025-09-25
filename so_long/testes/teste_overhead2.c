/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_overhead_real.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:50:00 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/21 20:50:00 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <sys/time.h>

long current_time_us()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

int main()
{
	int	frame = 60;
	int j = 0;
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 640, 640, "Teste Real");

    int w_block = 64, h_block = 64;
    int w_large = 640, h_large = 640;

    void *img_block = mlx_new_image(mlx, w_block, h_block);
    void *img_large = mlx_new_image(mlx, w_large, h_large);

    long t0, t1;


	// int positions[12][2] = {
	// {0, 0}, {64, 0}, {128, 0}, {192, 0},
	// {0, 64}, {10, 0}, {128, 64}, {192, 64},
	// {0, 128}, {64, 128}, {128, 128}, {192, 128}
    // };

	//Colocando a TUDO pela primeira vez (640x640)
    t0 = current_time_us();
	mlx_put_image_to_window(mlx, win, img_large, 0, 0);
    t1 = current_time_us();
    printf("TUDO Upload---> %f ms\n\n\nFrames: %d\n\n\n\n", (t1 - t0) / 1000.0, frame);

	



	// ATUALIZANDO a TUDO (640x640)
    t0 = current_time_us();
	for (j = 0; j < frame; j++)
	{
		mlx_put_image_to_window(mlx, win, img_large, 0, 0);
		// mlx_do_sync(mlx);
	}
    t1 = current_time_us();
    printf("\nTUDO: %f ms\n", (t1 - t0) / 1000.0);

	// DOIS BLOCOS
    t0 = current_time_us();
    for (j = 0; j < frame; j++)
	{
        mlx_put_image_to_window(mlx, win, img_block, 0, 0);
        mlx_put_image_to_window(mlx, win, img_block, 10, 0);
		mlx_do_sync(mlx);
	}
    t1 = current_time_us();
    printf("DOIS: %f ms\n", (t1 - t0) / 1000.0);

    // Atualizando 1 bloco 64x64
    t0 = current_time_us();
	for (j = 0; j < frame; j++)
	{
		mlx_put_image_to_window(mlx, win, img_block, 0, 0);
		// mlx_do_sync(mlx);
	}
    t1 = current_time_us();
    printf("UM: ---%f ms\n\n\n", (t1 - t0) / 1000.0);





	// ATUALIZANDO a TUDO (640x640)
    t0 = current_time_us();
	for (j = 0; j < frame; j++)
	{
		mlx_put_image_to_window(mlx, win, img_large, 0, 0);
		// mlx_do_sync(mlx);
	}
    t1 = current_time_us();
    printf("\nTUDO: %f ms\n", (t1 - t0) / 1000.0);

	// DOIS BLOCOS
	t0 = current_time_us();
	for (j = 0; j < frame; j++)
	{
		mlx_put_image_to_window(mlx, win, img_block, 0, 0);
		mlx_put_image_to_window(mlx, win, img_block, 10, 0);
		mlx_do_sync(mlx);
	}
	t1 = current_time_us();
	printf("DOIS: %f ms\n", (t1 - t0) / 1000.0);

	// Atualizando 1 bloco 64x64
    t0 = current_time_us();
	for (j = 0; j < frame; j++)
	{
		mlx_put_image_to_window(mlx, win, img_block, 0, 0);
		// mlx_do_sync(mlx);
	}
    t1 = current_time_us();
    printf("UM: ---%f ms\n\n\n", (t1 - t0) / 1000.0);





	// ATUALIZANDO a TUDO (640x640)
    t0 = current_time_us();
	for (j = 0; j < frame; j++)
	{
		mlx_put_image_to_window(mlx, win, img_large, 0, 0);
		// mlx_do_sync(mlx);
	}
    t1 = current_time_us();
    printf("\nTUDO: %f ms\n", (t1 - t0) / 1000.0);

	// DOIS BLOCOS
	t0 = current_time_us();
	for (j = 0; j < frame; j++)
	{
		mlx_put_image_to_window(mlx, win, img_block, 0, 0);
		mlx_put_image_to_window(mlx, win, img_block, 10, 0);
		mlx_do_sync(mlx);
	}
	t1 = current_time_us();
	printf("DOIS: %f ms\n", (t1 - t0) / 1000.0);

    // Atualizando 1 bloco 64x64
    t0 = current_time_us();
	for (j = 0; j < frame; j++)
	{
		mlx_put_image_to_window(mlx, win, img_block, 0, 0);
		// mlx_do_sync(mlx);
	}
    t1 = current_time_us();
    printf("UM: ---%f ms\n\n\n", (t1 - t0) / 1000.0);





	// ATUALIZANDO a TUDO (640x640)
    t0 = current_time_us();
	for (j = 0; j < frame; j++)
	{
		mlx_put_image_to_window(mlx, win, img_large, 0, 0);
		// mlx_do_sync(mlx);
	}
    t1 = current_time_us();
    printf("\nTUDO: %f ms\n", (t1 - t0) / 1000.0);


    // Atualizando 2 blocos 64x64
    t0 = current_time_us();
    for (j = 0; j < frame; j++)
	{
        mlx_put_image_to_window(mlx, win, img_block, 0, 0);
        mlx_put_image_to_window(mlx, win, img_block, 10, 0);
		mlx_do_sync(mlx);
	}
    t1 = current_time_us();
    printf("DOIS: %f ms\n", (t1 - t0) / 1000.0);

	// Atualizando 1 bloco 64x64
    t0 = current_time_us();
	for (j = 0; j < frame; j++)
	{
		mlx_put_image_to_window(mlx, win, img_block, 0, 0);
		// mlx_do_sync(mlx);
	}
    t1 = current_time_us();
    printf("UM: ---%f ms\n\n\n\n", (t1 - t0) / 1000.0);






	// ATUALIZANDO a TUDO (640x640)
    t0 = current_time_us();
	for (j = 0; j < frame; j++)
	{
		mlx_put_image_to_window(mlx, win, img_large, 0, 0);
		// mlx_do_sync(mlx);
	}
    t1 = current_time_us();
    printf("\nTUDO: %f ms\n", (t1 - t0) / 1000.0);

	// DOIS BLOCOS
	t0 = current_time_us();
	for (j = 0; j < frame; j++)
	{
		mlx_put_image_to_window(mlx, win, img_block, 0, 0);
		mlx_put_image_to_window(mlx, win, img_block, 10, 0);
		mlx_do_sync(mlx);
	}
	t1 = current_time_us();
	printf("DOIS: %f ms\n", (t1 - t0) / 1000.0);

	// Atualizando 1 bloco 64x64
    t0 = current_time_us();
	for (j = 0; j < frame; j++)
	{
		mlx_put_image_to_window(mlx, win, img_block, 0, 0);
		// mlx_do_sync(mlx);
	}
    t1 = current_time_us();
    printf("UM: ---%f ms\n\n\n", (t1 - t0) / 1000.0);





	// ATUALIZANDO a TUDO (640x640)
    t0 = current_time_us();
	for (j = 0; j < frame; j++)
	{
		mlx_put_image_to_window(mlx, win, img_large, 0, 0);
		// mlx_do_sync(mlx);
	}
    t1 = current_time_us();
    printf("\nTUDO: %f ms\n", (t1 - t0) / 1000.0);

	// DOIS BLOCOS
	t0 = current_time_us();
	for (j = 0; j < frame; j++)
	{
		mlx_put_image_to_window(mlx, win, img_block, 0, 0);
		mlx_put_image_to_window(mlx, win, img_block, 10, 0);
		mlx_do_sync(mlx);
	}
	t1 = current_time_us();
	printf("DOIS: %f ms\n", (t1 - t0) / 1000.0);

	// Atualizando 1 bloco 64x64
    t0 = current_time_us();
	for (j = 0; j < frame; j++)
	{
		mlx_put_image_to_window(mlx, win, img_block, 0, 0);
		// mlx_do_sync(mlx);
	}
    t1 = current_time_us();
    printf("UM: ---%f ms\n\n\n", (t1 - t0) / 1000.0);





    mlx_loop(mlx);
    return 0;
}