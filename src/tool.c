/*
** EPITECH PROJECT, 2018
** My World
** File description:
** Tool functions
*/

#include "my_world.h"

int scrolling(int key, index *info)
{
	if (key == 71)
		info->scrollx += 20;
	else if (key == 72)
		info->scrollx -= 20;
	if (key == 73)
		info->scrolly += 20;
	else if (key == 74)
		info->scrolly -= 20;
	return (1);
}

int rotation(int key, index *info)
{
	if (key == 25 && info->sin < 35.2) {
		info->sin += 0.01;
		return (1);
	}
	else if (key == 18 && info->sin > 34.6) {
		info->sin -= 0.01;
		return (1);
	}
	return (0);
}

int check_tool(int m[3], index *info, int action)
{
	int i = 1;
	sfColor c[2] = {{255, 255, 255, 255}, {255, 10, 255, 255}};
	int (*ptr[3])() = {&reset_map, &load_map, &save_map};

	while (i != 4) {
		if (m[0] > i * 10 + (i - 1) * 80 && m[0] < i * 10 + i * 80 && \
		    m[1] > 10 && m[1] < 90) {
			sfSprite_setColor(info->sprite[i], c[action]);
			return ((*ptr[i - 1])(info));
		}
		i++;
	}
	return (0);
}

int set_color(index *info, int i)
{
	sfColor c2 = {255, 10, 255, 255};

	if (info->b[i - 1] == 0) {
		sfSprite_setColor(info->sprite[i], c2);
		info->b[i - 1] = 1;
		return (1);
	}
	return (0);
}

int check_move(int x, int y, index *info)
{
	int i = 0;
	int ret = 0;
	sfColor c1 = {255, 255, 255, 255};

	for (i = 1; i != 4; i++) {
		if (x > i * 10 + (i - 1) * 80 && x < i * 10 + i * 80 && \
		    y > 10 && y < 90) {
			ret = set_color(info, i);
		}
		else if (info->b[i - 1] == 1) {
			sfSprite_setColor(info->sprite[i], c1);
			info->b[i - 1] = 0;
			ret = 1;
		}
	}
	return (ret);
}
