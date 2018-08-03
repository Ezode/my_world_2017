/*
** EPITECH PROJECT, 2018
** My World
** File description:
** Map functions
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "my_world.h"

int get_map_size(index *info)
{
	FILE *map = fopen("map", "r");
	char buf[1];
	int i = 0;

	if (map == NULL) {
		write(1, "Cannot open the map\n", 20);
		return (1);
	}
	while (fread(buf, 1, 1, map) == 1) {
		if (buf[0] == '\n')
			info->h++;
		i++;
	}
	info->w = (i / info->h) / 3;
	fclose(map);
	return (0);
}

int reset_map(index *info)
{
	int i = 0;
	int j = 0;

	for (j = 0; j != info->h; j++) {
		for (i = 0; i != info->w; i++) {
			info->m3[j][i] = 0;
		}
	}
	return (1);
}

int save_map(index *info)
{
	int i = 0;
	int j = 0;
	char buf[3];
	int fd = open("map", O_WRONLY);

	if (fd == -1) {
		write(1, "Error saving the map\n", 21);
		return (-1);
	}
	for (j = 0; j != info->h; j++) {
		for (i = 0; i != info->w; i++) {
			buf[0] = info->m3[j][i] + 48;
			buf[1] = info->obj[j][i] + 48;
			buf[2] = '.';
			write(fd, buf, 3);
		}
		write(fd, "\n", 1);
	}
	return (1);
}

void free_map(index *info)
{
	int i = 0;

	while (i != info->h) {
		free(info->m3[i]);
		i++;
	}
	free(info->m3);
	info->h = 0;
	info->w = 0;
}

int load_map(index *info)
{
	char *buf = NULL;

	if (info->m3 != NULL)
		free_map(info);
	if (get_map_size(info) != 0)
		return (-1);
	buf = get_buf(((info->w + 1) * 3) * info->h);
	if (buf == NULL)
		return (-1);
	info->m3 = get_map(buf, *info);
	info->obj = get_obj(buf, *info);
	if (info->m3 == NULL || info->obj == NULL)
		return (-1);
	free(buf);
	return (1);
}
