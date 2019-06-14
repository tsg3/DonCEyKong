#ifndef DONCEYKONGUSER_WINDOW_H
#define DONCEYKONGUSER_WINDOW_H

#include "allegro5/allegro.h"
#include "listaBarriles.h"
#include "listaBarrilesVerticales.h"
#include "listaBarrilesMixtos.h"

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *timer;
bool redraw;
const float FPS;
ALLEGRO_BITMAP* image;
ALLEGRO_BITMAP* image2;
ALLEGRO_BITMAP* martillo;
ALLEGRO_BITMAP* gasolina;
ALLEGRO_BITMAP* escalera;

ALLEGRO_BITMAP* marioX[3];
ALLEGRO_BITMAP* marioY[3];
ALLEGRO_BITMAP* marioZ[2];
ALLEGRO_BITMAP* marioM[5];


ALLEGRO_BITMAP* barrilV[4];
DWORD WINAPI barrilThread(void* barril);
void movimientoBarril(BarrilL* barril_actual, float x, float y, float mov);
void actualizarBarriles(BarrilL* barril_actual);
int choque();
DWORD WINAPI muerteChoque();
int colision(float i1x, float i1y, float d1x, float d1y, float i2x, float i2y, float d2x, float d2y);
int random;

ALLEGRO_BITMAP* barrilVertical[2];
DWORD WINAPI barrilVerticalThread(void* BarrilV);
void movimientobarrilVertical(BarrilVertical* barril_actual, float y, float mov);
void actualizarBarrilesVerticales(BarrilVertical* barril_actual);

DWORD WINAPI barrilMixtoThread(void* BarrilM);
void movimientoVerticalBarrilMixto(BarrilMixto* barril_actual, float y, float mov);
int movimientoHorizontalBarrilMixto(BarrilMixto* barril_actual, float x, float mov);
void movimientoBarrilMixto(BarrilMixto* barril_actual, float x, float y, float movX, float movY);
void actualizarBarrilesMixto(BarrilMixto* barril_actual);

ALLEGRO_BITMAP** mario;
float nivelPiso;

bool key[4];
float xM, yM;
enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
float salto;
int subiendo_escalera;
int countKeys();
int saltando;
int vivo;
DWORD WINAPI morir();
float posicionMuerto;
float finalMuerto;
int muertoID;

int dentroLimite();
int hay_escaleras(int arriba);
DWORD WINAPI saltar();
int obtenerPiso(float x, float nivel);
int initialize();
void finishExecution();
void reading();
void escaleras(ALLEGRO_BITMAP  *imagen);
void platforms(ALLEGRO_BITMAP  *imagen);
void barrels(ALLEGRO_BITMAP  *imagen);
void martillos(ALLEGRO_BITMAP *imagen);
void gasolina_inicial(ALLEGRO_BITMAP* imagen);
ALLEGRO_BITMAP* createImage(char* carpeta, char* nombreImagen);

#endif //DONCEYKONGUSER_WINDOW_H
