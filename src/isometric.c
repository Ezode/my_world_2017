/*
** EPITECH PROJECT, 2018
** My World
** File description:
** Isometric functions
*/

#include <stdlib.h>
#include <math.h>
#include "my_world.h"

sfVector2f iso_pnt(int x, int y, int z, index info)
{
	sfVector2f point2d = {0};

	point2d.x = cos(info.cos) * x - cos(info.cos) * y;
	point2d.y = sin(info.sin) * y + sin(info.sin) * x - z;
	return (point2d);
}

sfVector2f  **create_2d_map(index a)
{
	sfVector2f **m2 = NULL;

	m2 = malloc(sizeof(sfVector2f*) * a.h);
	if (m2 == NULL)
		return (NULL);
	for (int i = 0; i != a.h; i++) {
		m2[i] = malloc(sizeof(sfVector2f) * a.w);
		if (m2[i] == NULL)
			return (NULL);
	}
	for (int j = 0; j != a.h; j++) {
		for (int i = 0; i != a.w; i++) {
			m2[j][i] = iso_pnt(i * a.sclx, j * \
					a.scly, a.m3[j][i] * a.sclz, a);
			m2[j][i].y += WIN_H - WINH_4 + a.scrolly;
			m2[j][i].x += WINW_2 + a.scrollx;
		}
	}
	return (m2);
}

sfVector2f get_point(int x, int y, index info)
{
	sfVector2f point = {0};

	point = iso_pnt(x, y, 0, info);
	point.y += WIN_H - WINH_4 + D * info.sclz + info.scrolly;
	point.x += WINW_2 + info.scrollx;
	return (point);
}

int check_point(int m[3], index *a)
{
	int ret = 2;

	for (int j = 0; j != a->h && ret == 2; j++) {
		for (int i = 0; i != a->w && ret == 2; i++) {
			ret = check_b(m, i, j, a);
		}
	}
	return (ret);
}

sfVector2f *get_square(int i, int j, index *a)
{
	sfVector2f *p = malloc(sizeof(sfVector2f) * 4);

	if (p == NULL)
		return (NULL);
	p[0] = iso_pnt(i * a->sclx, j * a->scly, a->m3[j][i] * a->sclz, *a);
	p[0].y += WIN_H - WINH_4 + a->scrolly;
	p[0].x += WINW_2 + a->scrollx;
	p[1] = iso_pnt((i-1)*a->sclx, (j-1)*a->scly, \
		a->m3[j-1][i-1] * a->sclz, *a);
	p[1].y += WIN_H - WINH_4 + a->scrolly;
	p[1].x += WINW_2 + a->scrollx;
	p[2] = iso_pnt((i-1)*a->sclx, (j)*a->scly, a->m3[j][i-1] * a->sclz, *a);
	p[2].y += WIN_H - WINH_4 + a->scrolly;
	p[2].x += WINW_2 + a->scrollx;
	p[3] = iso_pnt((i)*a->sclx, (j-1)*a->scly, a->m3[j-1][i] * a->sclz, *a);
	p[3].y += WIN_H - WINH_4 + a->scrolly;
	p[3].x += WINW_2 + a->scrollx;
	return (p);
}
