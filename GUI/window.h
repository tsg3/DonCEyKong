#ifndef DONCEYKONGUSER_WINDOW_H
#define DONCEYKONGUSER_WINDOW_H

#include "allegro5/allegro.h"

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *timer;
bool redraw;
const float FPS;
ALLEGRO_BITMAP* image;
ALLEGRO_BITMAP* image2;
ALLEGRO_BITMAP* martillo;
ALLEGRO_BITMAP* gasolina;

ALLEGRO_BITMAP* marioX[3];
ALLEGRO_BITMAP* marioY[3];
int nivelPiso;

bool key[4];
float xM, yM;
enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int obtenerPiso(int x);
int initialize();
void finishExecution();
void reading();
void platforms(ALLEGRO_BITMAP  *image);
void barrels(ALLEGRO_BITMAP  *image);
void martillos(ALLEGRO_BITMAP *martillo);
void gasolina_inicial(ALLEGRO_BITMAP* gasolina);
ALLEGRO_BITMAP* createImage(char* carpeta, char* nombreImagen);

#endif //DONCEYKONGUSER_WINDOW_H
