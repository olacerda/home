/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_overhead.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:06:29 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/21 20:29:12 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <sys/time.h>

long current_time_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "Teste");

    int w_small = 1, h_small = 1;
    int w_block = 64, h_block = 64;
    int w_large = 640, h_large = 640;

    void *img_small = mlx_new_image(mlx, w_small, h_small);
    void *img_block = mlx_new_image(mlx, w_block, h_block);
    void *img_large = mlx_new_image(mlx, w_large, h_large);

    long t0, t1;
    int i;

    // Overhead estimado: imagem mínima 1x1
    t0 = current_time_ms();
    for (i = 0; i < 1000; i++)
        mlx_put_image_to_window(mlx, win, img_small, 0, 0);
    t1 = current_time_ms();
    printf("Overhead (1x1) médio: %f ms\n", (t1 - t0) / 1000.0);

    // Tempo imagem 64x64
    t0 = current_time_ms();
    for (i = 0; i < 1000; i++)
        mlx_put_image_to_window(mlx, win, img_block, 0, 0);
    t1 = current_time_ms();
    printf("Tempo 64x64 médio: %f ms\n", (t1 - t0) / 1000.0);


	// Atualização de 12 blocos 64x64
	int positions[12][2] = {
		{0, 0}, {64, 0}, {128, 0}, {192, 0},
		{0, 64}, {64, 64}, {128, 64}, {192, 64},
		{0, 128}, {64, 128}, {128, 128}, {192, 128}
	};

	t0 = current_time_ms();
	for (i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 12; j++)
			mlx_put_image_to_window(mlx, win, img_block, positions[j][0], positions[j][1]);
	}
	t1 = current_time_ms();
	printf("Tempo 12 blocos 64x64 médio: %f ms\n", (t1 - t0) / 1000.0);

    // Tempo imagem 640x640
    t0 = current_time_ms();
    for (i = 0; i < 1000; i++)
        mlx_put_image_to_window(mlx, win, img_large, 0, 0);
    t1 = current_time_ms();
    printf("Tempo 640x640 médio: %f ms\n", (t1 - t0) / 1000.0);

    mlx_loop(mlx);
    return 0;
}