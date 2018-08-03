/*
** EPITECH PROJECT, 2018
** My World
** File description:
** Map creation functions
*/

#include <stdlib.h>
#include <stdio.h>
#include "my_world.h"

char *get_buf(int size)
{
	FILE *map = fopen("map", "r");
	char *buf = NULL;

	buf = malloc(sizeof(char) * (size + 1));
	if (buf == NULL)
		return (NULL);
	fread(buf, size, 1, map);
	buf[size] = '\0';
	fclose(map);
	return (buf);
}

int **get_obj(char *buf, index info)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int **obj;

	obj = malloc(sizeof(int*) * info.h);
	if (obj == NULL)
		return (NULL);
	for (i = 0; i != info.h; i++) {
		obj[i] = malloc(sizeof(int) * info.w);
		if (obj[i] == NULL)
			return (NULL);
	}
	for (j = 0, k = 1; j != info.h; j++, k++) {
		for (i = 0; i != info.w; i++, k += 3)
			obj[j][i] = buf[k] - 48;
	}
	return (obj);
}

int **get_map(char *buf, index info)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int **map;

	map = malloc(sizeof(int*) * info.h);
	if (map == NULL)
		return (NULL);
	for (i = 0; i != info.h; i++) {
		map[i] = malloc(sizeof(int) * info.w);
		if (map[i] == NULL)
			return (NULL);
	}
	for (j = 0; j != info.h; j++, k++) {
		for (i = 0; i != info.w; i++, k += 3)
			map[j][i] = buf[k] - 48;
	}
	return (map);
}
