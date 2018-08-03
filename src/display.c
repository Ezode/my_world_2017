/*
** EPITECH PROJECT, 2018
** My World
** File description:
** Displaying functions
*/

#include "my_world.h"

void draw_base(sfRenderWindow *window, sfVector2f **m, index info)
{
	sfVertexArray *vertex = NULL;
	int x = (info.w - 1) * info.sclx;
	int y = (info.h - 1) * info.scly;
	sfVector2f p1 = get_point(0, 0, info);
	sfVector2f p2 = get_point(x, 0, info);
	sfVector2f p3 = get_point(0, y, info);

	vertex = get_base(1, info.w, m, info);
	sfRenderWindow_drawVertexArray(window, vertex, NULL);
	vertex = get_base(2, info.h, m, info);
	sfRenderWindow_drawVertexArray(window, vertex, NULL);
	vertex = create_line(&m[0][0], &p1);
	sfRenderWindow_drawVertexArray(window, vertex, NULL);
	vertex = create_line(&m[info.h - 1][0], &p3);
	sfRenderWindow_drawVertexArray(window, vertex, NULL);
	vertex = create_line(&m[0][info.w - 1], &p2);
	sfRenderWindow_drawVertexArray(window, vertex, NULL);
	vertex = create_line(&p2, &p1);
	sfRenderWindow_drawVertexArray(window, vertex, NULL);
	vertex = create_line(&p3, &p1);
	sfRenderWindow_drawVertexArray(window, vertex, NULL);
}

void draw_tile(sfRenderWindow *w, sfVector2f **m, index a, int e[3])
{
	sfVertexArray *vertex = NULL;

	if (e[1] > 0 && e[0] > 0) {
		vertex = create_t(&m[e[1]-1][e[0]-1], &m[e[1]][e[0]-1], \
			&m[e[1]][e[0]], e[2]);
		sfRenderWindow_drawVertexArray(w, vertex, NULL);
		vertex = create_t(&m[e[1]-1][e[0]-1], &m[e[1]-1][e[0]], \
			&m[e[1]][e[0]], e[2]);
		sfRenderWindow_drawVertexArray(w, vertex, NULL);
	}
	if (e[0] > 0) {
		vertex = create_line(&m[e[1]][e[0]], &m[e[1]][e[0] - 1]);
		sfRenderWindow_drawVertexArray(w, vertex, NULL);
	}
	if (e[1] > 0) {
		vertex = create_line(&m[e[1]][e[0]], &m[e[1] - 1][e[0]]);
		sfRenderWindow_drawVertexArray(w, vertex, NULL);
	}
}

void draw_obj(sfRenderWindow *win, index a, int i, int j)
{
	sfVector2f pos = {0};
	double s = a.sclx / 64.0;
	sfVector2f scale = {s, s};
	sfVector2f p1 = {0};
	sfVector2f p2 = {0};

	if (j > 0 && j < a.h && i > 0 && i < a.w && a.obj[j][i] != 0) {
		p1 = iso_pnt(i * a.sclx, j * a.scly, a.m3[j][i] * a.sclz, a);
		p2 = iso_pnt((i-1) * a.sclx, (j-1) * \
			a.scly, a.m3[j-1][i-1] * a.sclz, a);
		pos.x = p1.x + WINW_2 + a.scrollx - \
			a.sclx / 2 + a.sclx / 6;
		pos.y = p2.y - (p2.y - p1.y) / 2 + WIN_H - \
			WINH_4 + a.scrolly - a.sclx / 1.2;
		sfSprite_setScale(a.sprite[0], scale);
		sfSprite_setPosition(a.sprite[0], pos);
		sfRenderWindow_drawSprite(win, a.sprite[0], 0);
	}
}

int draw_map(sfRenderWindow *win, sfVector2f **m2, index a)
{
	int e[3] = {0};

	for (e[1] = a.h - 1; e[1] != -1; e[1]--) {
		for (e[0] = a.w - 1; e[0] != -1; e[0]--) {
			e[2] = get_shadow(a.m3, e[0], e[1]);
			draw_tile(win, m2, a, e);
			draw_obj(win, a, e[0], e[1]);
		}
	}
	draw_base(win, m2, a);
	return (0);
}

int display(sfRenderWindow *window, index info)
{
	sfVector2f **map2d = NULL;
	sfColor color = {34, 47, 56};

	sfRenderWindow_clear(window, color);
	map2d = create_2d_map(info);
	if (map2d == NULL)
		return (1);
	draw_map(window, map2d, info);
	display_tool(window, info);
	sfRenderWindow_display(window);
	return (0);
}
