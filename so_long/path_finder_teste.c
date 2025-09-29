/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder_teste.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 06:16:34 by olacerda          #+#    #+#             */
/*   Updated: 2025/09/29 06:21:34 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

/*
 * Este código é apenas um pathfinder simples (A*),
 * para grid de mapa estilo so_long.
 * Paredes = '1'
 * Caminho livre = '0'
 * Player = 'P'
 * Enemy = 'E'
 *
 * Ele encontra o caminho mais curto de E até P
 * e imprime as coordenadas do caminho.
 *
 * Não há integração com o jogo, é só a lógica do path.
 */

typedef struct s_node
{
    int x, y;
    int g;           // custo desde o início
    int h;           // heurística até o destino
    int f;           // g + h
    struct s_node *parent;
}   t_node;

typedef struct s_list
{
    t_node *node;
    struct s_list *next;
}   t_list;

int g_rows, g_cols;

int is_valid(char **map, int x, int y)
{
    return (x >= 0 && x < g_rows && y >= 0 && y < g_cols && map[x][y] != '1');
}

int heuristic(int x1, int y1, int x2, int y2)
{
    // distância Manhattan
    return abs(x1 - x2) + abs(y1 - y2);
}

t_node *create_node(int x, int y, int g, int h, t_node *parent)
{
    t_node *n = malloc(sizeof(t_node));
    n->x = x;
    n->y = y;
    n->g = g;
    n->h = h;
    n->f = g + h;
    n->parent = parent;
    return n;
}

int in_list(t_list *list, int x, int y)
{
    while (list)
    {
        if (list->node->x == x && list->node->y == y)
            return 1;
        list = list->next;
    }
    return 0;
}

void push_list(t_list **list, t_node *node)
{
    t_list *new = malloc(sizeof(t_list));
    new->node = node;
    new->next = *list;
    *list = new;
}

t_node *pop_lowest(t_list **list)
{
    t_list *prev = NULL, *cur = *list;
    t_list *best_prev = NULL, *best = cur;
    while (cur)
    {
        if (cur->node->f < best->node->f)
        {
            best = cur;
            best_prev = prev;
        }
        prev = cur;
        cur = cur->next;
    }
    if (best_prev)
        best_prev->next = best->next;
    else
        *list = best->next;
    t_node *res = best->node;
    free(best);
    return res;
}

void free_list(t_list *list)
{
    while (list)
    {
        t_list *tmp = list;
        list = list->next;
        free(tmp->node);
        free(tmp);
    }
}

void reconstruct_path(t_node *end)
{
    if (!end) return;
    int length = 0;
    t_node *cur = end;
    while (cur)
    {
        length++;
        cur = cur->parent;
    }
    int (*path)[2] = malloc(sizeof(int[2]) * length);
    cur = end;
    for (int i = length - 1; i >= 0; i--)
    {
        path[i][0] = cur->x;
        path[i][1] = cur->y;
        cur = cur->parent;
    }
    printf("Caminho encontrado (%d passos):\n", length);
    for (int i = 0; i < length; i++)
        printf("(%d,%d)\n", path[i][0], path[i][1]);
    free(path);
}

void astar(char **map, int sx, int sy, int ex, int ey)
{
    t_list *open = NULL;
    t_list *closed = NULL;

    push_list(&open, create_node(sx, sy, 0, heuristic(sx, sy, ex, ey), NULL));

    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    while (open)
    {
        t_node *cur = pop_lowest(&open);

        if (cur->x == ex && cur->y == ey)
        {
            reconstruct_path(cur);
            free_list(open);
            free_list(closed);
            return;
        }
        push_list(&closed, cur);

        for (int i = 0; i < 4; i++)
        {
            int nx = cur->x + dirs[i][0];
            int ny = cur->y + dirs[i][1];
            if (!is_valid(map, nx, ny))
                continue;
            if (in_list(closed, nx, ny))
                continue;
            int g = cur->g + 1;
            int h = heuristic(nx, ny, ex, ey);
            t_node *neighbor = create_node(nx, ny, g, h, cur);
            if (!in_list(open, nx, ny))
                push_list(&open, neighbor);
            else
                free(neighbor);
        }
    }
    printf("Nenhum caminho encontrado.\n");
    free_list(open);
    free_list(closed);
}

int main(void)
{
    // mapa de teste
    char *map[] = 
	{
	//   0123456789
        "1111111111", // 0
        "1000000001", // 1
        "100100E001", // 2
        "1001111111", // 3
        "1000000001", // 4
        "1111110001", // 5
        "1P00010001", // 6
        "1000010001", // 7
        "1000000001", // 8
        "1111111111"  // 9
    };
    g_rows = 10;
    g_cols = 10;

    int sx, sy, ex, ey;
    for (int i = 0; i < g_rows; i++)
    {
        for (int j = 0; j < g_cols; j++)
        {
            if (map[i][j] == 'E')
            {
                sx = i; sy = j;
            }
            if (map[i][j] == 'P')
            {
                ex = i; ey = j;
            }
        }
    }
    astar(map, sx, sy, ex, ey);
    return 0;
}