/*
** EPITECH PROJECT, 2018
** My World
** File description:
** create a terraformer program
*/

#include <stdlib.h>
#include "my_world.h"

int music(index *info, int action)
{
	if (action == 1) {
		info->music = sfMusic_createFromFile("sound/music.ogg");
		if (info->music == NULL)
			return (1);
		sfMusic_play(info->music);
		sfMusic_setLoop(info->music, sfTrue);
	}
	else {
		sfMusic_stop(info->music);
		sfMusic_destroy(info->music);
	}
	return (0);
}

void destroy_sprite(index *info)
{
	int i = 0;

	while (i != 4) {
		sfSprite_destroy(info->sprite[i]);
		i++;
	}
}

int load_sprite(index *info)
{
	sfTexture *texture = NULL;

	if ((info->sprite = malloc(sizeof(sfSprite*) * 4)) == NULL)
		return (1);
	info->sprite[0] = sfSprite_create();
	texture = sfTexture_createFromFile("sprite/tree.png", NULL);
	sfSprite_setTexture(info->sprite[0], texture, 0);
	info->sprite[1] = sfSprite_create();
	texture = sfTexture_createFromFile("sprite/b_reset.png", NULL);
	sfSprite_setTexture(info->sprite[1], texture, 0);
	info->sprite[2] = sfSprite_create();
	texture = sfTexture_createFromFile("sprite/b_load.png", NULL);
	sfSprite_setTexture(info->sprite[2], texture, 0);
	info->sprite[3] = sfSprite_create();
	texture = sfTexture_createFromFile("sprite/b_save.png", NULL);
	sfSprite_setTexture(info->sprite[3], texture, 0);
	return (0);
}

int launch_anim(sfRenderWindow *win, index *info)
{
	sfEvent e;
	sfClock *clock = sfClock_create();
	sfTime time;

	while (info->sclx != SCAL_X) {
		if (sfRenderWindow_pollEvent(win, &e) == sfTrue && \
		    e.type == sfEvtClosed) {
			sfRenderWindow_close(win);
			return (0);
		}
		time = sfClock_getElapsedTime(clock);
		if (time.microseconds >= 25000) {
			info->sclx++;
			info->scly++;
			info->sclz = info->sclx / 4;
			sfClock_restart(clock);
			display(win, *info);
		}
	}
	return (0);
}

int world(sfRenderWindow *window)
{
	index info = {0, 0, 0, 45, 34.8, {0}};

	if (load_sprite(&info) != 0)
		return (-1);
	if (load_map(&info) == -1)
		return (-1);
	if (music(&info, 1) != 0)
		return (-1);
	if (launch_anim(window, &info) != 0)
		return (-1);
	for (int tmp = 0; sfRenderWindow_isOpen(window); tmp = 0) {
		if ((tmp = handle_event(window, &info)) == -1)
			return (-1);
		else if (tmp == 1)
			tmp = display(window, info);
	}
	music(&info, 2);
	destroy_sprite(&info);
	return (0);
}
