/*
** EPITECH PROJECT, 2018
** My World
** File description:
** Envent functions
*/

#include "my_world.h"

int check_key(int func, int key, index *info)
{
	int (*ptr[2])() = {&scrolling, &rotation};

	return ((*ptr[func])(key, info));
}

int key_pressed(sfRenderWindow *window, sfEvent event, index *info)
{
	if (event.key.code >= 71 && event.key.code <= 74)
		return (check_key(0, event.key.code, info));
	else if (event.key.code == 18 || event.key.code == 25)
		return (check_key(1, event.key.code, info));
	return (0);
}

int mouse_wheel(sfRenderWindow *window, sfEvent event, index *info)
{
	if (event.mouseWheel.delta < 0 && info->sclx == 0)
		return (0);
	else {
		info->sclx += event.mouseWheel.delta * 4;
		info->scly += event.mouseWheel.delta * 4;
	}
	info->sclz = info->sclx / 4;
	return (1);
}

int mouse_button(sfRenderWindow *window, sfEvent event, index *info, int action)
{
	int m[3] = {event.mouseButton.x, event.mouseButton.y, 0};
	int ret = 0;

	if (event.mouseButton.button == 0)
		m[2] = 1;
	else if (event.mouseButton.button == 1)
		m[2] = -1;
	if ((ret = check_tool(m, info, action)) != 0)
		return (ret);
	if (check_point(m, info) == 1)
		return (1);
	ret = check_tile(m, info);
	return (ret);
}

int handle_event(sfRenderWindow *window, index *info)
{
	sfEvent e;

	if (sfRenderWindow_waitEvent(window, &e) == sfTrue) {
		if (e.type == sfEvtClosed)
			sfRenderWindow_close(window);
		else if (e.type == sfEvtKeyPressed)
			return (key_pressed(window, e, info));
		if (e.type == sfEvtMouseWheelMoved)
			return (mouse_wheel(window, e, info));
		else if (e.type == sfEvtMouseButtonPressed)
			return (mouse_button(window, e, info, 0));
		if (e.type == sfEvtMouseButtonReleased)
			return (mouse_button(window, e, info, 1));
		else if (e.type == sfEvtMouseMoved)
			return (check_move(e.mouseMove.x, e.mouseMove.y, info));
	}
	return (0);
}
