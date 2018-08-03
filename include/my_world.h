/*
** EPITECH PROJECT, 2018
** My World
** File description:
** header file of the My World project
*/

#ifndef MY_WORLD
#define MY_WORLD

#include <SFML/Graphics.h>
#include <SFML/Audio.h>

#define SCAL_X 64
#define SCAL_Y 64
#define SCAL_Z SCAL_X / 4
#define WIN_W 1100
#define WIN_H 800
#define WINH_4 WIN_H / 4
#define WINW_2 WIN_W / 2
#define D 5
#define H 15

typedef struct
{
	int sclx;
	int scly;
	int sclz;
	double cos;
	double sin;
	int b[3];
	int scrollx;
	int scrolly;
	int h;
	int w;
	int **m3;
	int **obj;
	sfSprite **sprite;
	sfMusic *music;
}index;

int world(sfRenderWindow *window);
sfVector2f *get_square(int i, int j, index *info);
int load_map(index *info);
int save_map(index *info);
int reset_map(index *info);
int display(sfRenderWindow *window, index info);
int handle_event(sfRenderWindow *window, index *info);
sfVector2f get_point(int x, int y, index info);
sfVertexArray *get_base(int nb, int max, sfVector2f **m, index info);
sfVertexArray *create_line(sfVector2f *p1, sfVector2f *p2);
sfVertexArray *create_t(sfVector2f *p, sfVector2f *p2, sfVector2f *p3, int s);
sfVector2f iso_pnt(int x, int y, int z, index info);
sfVector2f  **create_2d_map(index a);
int check_tile(int m[3], index *info);
int check_b(int m[3], int i, int j, index *info);
int check_b2(int m[3], int i, int j, index *info);
int check_point(int m[3], index *info);
int rotation(int key, index *info);
int scrolling(int key, index *info);
int get_shadow(int **m, int i, int j);
int **get_map(char *buf, index info);
int **get_obj(char *buf, index info);
char *get_buf(int size);
int check_tool(int m[3], index *info, int action);
int check_move(int x, int y, index *info);
void display_tool(sfRenderWindow *win, index a);

#endif
