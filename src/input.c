/*
** EPITECH PROJECT, 2018
** My World
** File description:
** Input functions
*/

#include "my_world.h"

int get_shadow(int **m, int i, int j)
{
	int p1 = 0;
	int p2 = 0;
	int p3 = 0;
	int p4 = 0;

	if (j > 0 && i > 0) {
		p1 = m[j][i];
		p2 = m[j - 1][i];
		p3 = m[j][i - 1];
		p4 = m[j - 1][i - 1];
		if (p1 == p2 && p2 == p3 && p3 == p4)
			return (1);
		else if ((p1 < p2 || p3 < p2 || p4 < p2) || \
			(p1 < p4 && p2 == p3))
			return (0);
		else
			return (2);
	}
	return (1);
}

void up_tile(index *a, int b, int i, int j)
{
	a->m3[j][i] += b;
	a->m3[j - 1][i - 1] += b;
	a->m3[j][i - 1] += b;
	a->m3[j - 1][i] += b;
}

int check_b2(int m[3], int i, int j, index *a)
{
	sfVector2f *p = get_square(i, j, a);

	if (p == NULL)
		return (-1);
	if (m[1] > p[0].y + 5 && m[1] < p[1].y - 5 && \
	m[0] > p[2].x + 5 && m[0] < p[3].x - 5) {
		if (m[2] == -1 && (a->m3[j][i] == -D || \
			a->m3[j - 1][i - 1] == -D || \
			a->m3[j][i - 1] == -D || \
			a->m3[j - 1][i] == -D))
			return (0);
		else if (m[2] == 1 && (a->m3[j][i] == H || a->m3[j - 1][i - 1] \
			== H || a->m3[j][i - 1] == H || a->m3[j - 1][i] == H))
			return (0);
		else
			up_tile(a, m[2], i, j);
		return (1);
	}
	return (0);
}

int check_b(int m[3], int i, int j, index *a)
{
	sfVector2f p = {0};

	p = iso_pnt(i * a->sclx, j * a->scly, a->m3[j][i] * a->sclz, *a);
	p.y += WIN_H - WINH_4 + a->scrolly;
	p.x += WINW_2 + a->scrollx;
	if (p.x - 5 < m[0] && p.x + 5 > m[0] && \
	p.y - 5 < m[1] && p.y + 5 > m[1]) {
		if (m[2] == -1 && a->m3[j][i] > -D)
			a->m3[j][i] += m[2];
		else if (m[2] == 1 && a->m3[j][i] < H)
			a->m3[j][i] += m[2];
		else
			return (0);
		return (1);
	}
	return (2);
}

int check_tile(int m[3], index *a)
{
	int i  = 0;
	int j = 0;
	int ret = 0;

	for (j = a->h - 1; j != 0 && ret == 0; j--) {
		for (i = a->w - 1; i != 0 && ret == 0; i--) {
			ret = check_b2(m, i, j, a);
		}
	}
	return (ret);
}
