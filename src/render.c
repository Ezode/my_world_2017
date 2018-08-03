/*
** EPITECH PROJECT, 2018
** My World
** File description:
** Render functions
*/

#include "my_world.h"

sfVertexArray *create_line(sfVector2f *p1, sfVector2f *p2)
{
	sfVertexArray *vertex_array = sfVertexArray_create();
	sfVertex vertex1 = {.position = p1[0], .color = sfWhite};
	sfVertex vertex2 = {.position = p2[0], .color = sfWhite};

	sfVertexArray_append(vertex_array, vertex1);
	sfVertexArray_append(vertex_array, vertex2);
	sfVertexArray_setPrimitiveType(vertex_array, sfLinesStrip);
	return (vertex_array);
}

sfVertexArray *create_t(sfVector2f *p, sfVector2f *p2, sfVector2f *p3, int s)
{
	sfColor c[3] = {{120, 163, 55, 255}, {153, 188, 96, 255},
			{177, 215, 119, 255}};
	sfVertexArray *vertex_array = sfVertexArray_create();
	sfVertex vertex1 = {.position = p[0], .color = c[s]};
	sfVertex vertex2 = {.position = p2[0], .color = c[s]};
	sfVertex vertex3 = {.position = p3[0], .color = c[s]};

	sfVertexArray_append(vertex_array, vertex1);
	sfVertexArray_append(vertex_array, vertex2);
	sfVertexArray_append(vertex_array, vertex3);
	sfVertexArray_setPrimitiveType(vertex_array, sfTrianglesStrip);
	return (vertex_array);
}

sfVertex get_vertex(int c[3], int nb, sfVector2f **m, index a)
{
	sfVertex v;
	sfColor color[2] = {{141, 126, 71, 255}, {101, 83, 45, 255}};
	sfVector2f point = {0};

	if (c[1] == 0) {
		if (nb == 1)
			v.position = m[0][c[0]];
		else
			v.position = m[c[0]][0];
		v.color = color[nb - 1];
	}
	else if (c[1] == 1) {
		if (nb == 1)
			point = get_point(c[2], 0, a);
		else
			point = get_point(0, c[2], a);
		v.position = point;
		v.color = color[nb - 1];
	}
	return (v);
}

sfVertexArray *get_base(int nb, int max, sfVector2f **m, index info)
{
	sfVertex v;
	sfVertexArray *vertex = sfVertexArray_create();

	for (int c[3] = {0, 0}; c[0] != max; c[0] = c[0]) {
		if (c[1] == 0) {
			v = get_vertex(c, nb, m, info);
			c[1] = 1;
		}
		else if (c[1] == 1) {
			c[2] = c[0] * info.sclx;
			v = get_vertex(c, nb, m, info);
			c[1] = 0;
			c[0]++;
		}
		sfVertexArray_append(vertex, v);
	}
	sfVertexArray_setPrimitiveType(vertex, sfTrianglesStrip);
	return (vertex);
}

void display_tool(sfRenderWindow *win, index a)
{
	int i = 1;
	sfVector2f pos = {10, 10};

	while (i != 4) {
		sfSprite_setPosition(a.sprite[i], pos);
		sfRenderWindow_drawSprite(win, a.sprite[i], 0);
		pos.x += 90;
		i++;
	}
}
