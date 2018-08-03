/*
** EPITECH PROJECT, 2018
** My World
** File description:
** Main function of the My World project
*/

#include "my_world.h"

int my_strcmp(const char *s1, const char *s2)
{
	int i = 0;

	while (s1[i] == s2[i]) {
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	if (s1[i] > s2[i])
		return (1);
	else if (s1[i] < s2[i])
		return (-1);
	return (0);
}

int check_line(char *line, char *name)
{
	int i = 0;

	while (line[i] != '=') {
		if (line[i] == '\0')
			return (0);
		if (line[i] != name[i])
			return (0);
		i++;
	}
	if (my_strcmp(&line[i + 1], ":0.0") != 0)
		return (0);
	return (1);
}

int check_env(char **env)
{
	int i = 0;

	while (env[i] != NULL) {
		if (check_line(env[i], "DISPLAY") == 1)
			return (0);
		i++;
	}
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	sfRenderWindow *window = NULL;
	sfVideoMode mode = {WIN_W, WIN_H, 32};

	if (check_env(envp) != 0)
		return (84);
	window = sfRenderWindow_create(mode, "My World", sfClose, NULL);
	if (window == NULL)
		return (84);
	sfRenderWindow_setFramerateLimit(window, 60);
	if (world(window) != 0)
		return (84);
	return (0);
}
