#include <stdio.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <time.h>

#include "window.h"

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
bool redraw = true;
const float FPS = 60;
ALLEGRO_BITMAP* image = NULL;
ALLEGRO_BITMAP* image2 = NULL;
ALLEGRO_BITMAP* martillo = NULL;
ALLEGRO_BITMAP* gasolina = NULL;
ALLEGRO_BITMAP* escalera = NULL;
bool key[4] = { false, false, false, false };
float nivelPiso = 494.0;
float salto = 0.0;
int subiendo_escalera = 0;
int saltando = 0;
int vivo = 1;
int random = 1;
int barril_encendido = 0;
int gasolinaAnimacion = 0;
ALLEGRO_BITMAP* gasolinaA = NULL;

int initialize(){
    if(!al_init()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }
    if(!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }
    if(!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        fprintf(stderr, "Error al crear el contador!\n");
        return -1;
    }
    display = al_create_display(896,544);
    if(!display) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_timer(timer);
        return 0;
    }
    event_queue = al_create_event_queue();
    if(!event_queue) {
        fprintf(stderr, "Error al crear la cola de eventos!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
    crearImagenes();
    gasolinaA = gasolinaAnimada[0];
    if (errorImagenes()){
        return -1;
    }
    xM = 40;
    yM = nivelPiso;
    al_draw_bitmap(marioX[0], xM, yM, 0);
    crearEscaleras();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_clear_to_color(al_map_rgb(0,0,0));
    escaleras(escalera);
    barrels(image2);
    platforms(image);
    martillos(martillo);
    gasolina_inicial(gasolina);
    al_flip_display();
    al_start_timer(timer);
    return 1;
}

int verificarBarrilEncendido(){
    BarrilL *temp1 = lista_barriles;
    while(temp1 != NULL){
        if(temp1->barril_x <= 100 && temp1->barril_y == 494){
            return 1;
        }
        temp1 = temp1->siguiente;
    }
    BarrilVertical *temp2 = lista_barriles_verticales;
    while(temp2 != NULL){
        if(temp2->barril_x <= 100 && temp2->barril_y == 494){
            return 1;
        }
        temp2 = temp2->siguiente;
    }
    BarrilMixto *temp3 = lista_barriles_mixtos;
    while(temp3 != NULL){
        if(temp3->barril_x <= 100 && temp3->barril_y == 494){
            return 1;
        }
        temp3 = temp3->siguiente;
    }
    return 0;
}

void crearImagenes(){
    image = createImage("estructuras","estructuras_sprite_3.png");
    image2 = createImage("estructuras","estructuras_sprite_0.png");
    martillo = createImage("estructuras","estructuras_sprite_1.png");
    gasolina = createImage("gasolina","gasolina_sprite_0.png");
    marioX[0] = createImage("jumpman_caminar","jumpman_sprite_0.png");
    marioX[1] = createImage("jumpman_caminar","jumpman_sprite_1.png");
    marioX[2] = createImage("jumpman_caminar","jumpman_sprite_2.png");
    marioY[0] = createImage("jumpman_caminar","jumpman_sprite_3.png");
    marioY[1] = createImage("jumpman_caminar","jumpman_sprite_4.png");
    marioY[2] = createImage("jumpman_caminar","jumpman_sprite_5.png");
    marioZ[0] = createImage("jumpman_subiendo","jumpman_subiendo_sprite_1.png");
    marioZ[1] = createImage("jumpman_subiendo","jumpman_subiendo_sprite_4.png");
    marioM[0] = createImage("jumpman_rodando","jumpman_rodando_sprite_0.png");
    marioM[1] = createImage("jumpman_rodando","jumpman_rodando_sprite_1.png");
    marioM[2] = createImage("jumpman_rodando","jumpman_rodando_sprite_2.png");
    marioM[3] = createImage("jumpman_rodando","jumpman_rodando_sprite_3.png");
    marioM[4] = createImage("jumpman_muerto","Jumpman_muerto_sprite_0.png");
    barrilV[0] = createImage("barril","barril_sprite_0.png");
    barrilV[1] = createImage("barril","barril_sprite_1.png");
    barrilV[2] = createImage("barril","barril_sprite_2.png");
    barrilV[3] = createImage("barril","barril_sprite_3.png");
    barrilVertical[0] = createImage("barril","barril_sprite_4.png");
    barrilVertical[1] = createImage("barril","barril_sprite_5.png");
    fuegoI[0] = createImage("fuego","fuego_sprite_0.png");
    fuegoI[1] = createImage("fuego","fuego_sprite_1.png");
    fuegoI[2] = createImage("fuego","fuego_sprite_2.png");
    fuegoI[3] = createImage("fuego","fuego_sprite_3.png");
    escalera = createImage("estructuras","escalera_sprite_0.png");
    gasolinaAnimada[0] = createImage("gasolina","gasolina_sprite_1.png");
    gasolinaAnimada[1] = createImage("gasolina","gasolina_sprite_2.png");
}

int errorImagenes(){
    if(!image || !image2 || !martillo || !gasolina || !escalera || !marioX[0] || !marioX[1]
       || !marioX[2] || !marioY[0] || !marioY[1] || !marioY[2] || !marioZ[0] || !marioZ[1] || !marioM[0] || !marioM[1]
       || !marioM[2] || !marioM[3] || !marioM[4] || !barrilV[0] || !barrilV[1] || !barrilV[2] || !barrilV[3]
       || !barrilVertical[0] || !barrilVertical[1] || !fuegoI[0] || !fuegoI[1] || !fuegoI[2] || !fuegoI[3]
       || !gasolinaAnimada[0] || !gasolinaAnimada[1]) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_event_queue(event_queue);
        return 1;
    }
    return 0;
}

void finishExecution(){
    al_destroy_display(display);
    al_destroy_bitmap(image);
    al_destroy_bitmap(image2);
    al_destroy_bitmap(martillo);
    al_destroy_bitmap(gasolina);
    al_destroy_bitmap(escalera);
    al_destroy_bitmap(marioX[0]);
    al_destroy_bitmap(marioX[1]);
    al_destroy_bitmap(marioX[2]);
    al_destroy_bitmap(marioY[0]);
    al_destroy_bitmap(marioY[1]);
    al_destroy_bitmap(marioY[2]);
    al_destroy_bitmap(marioZ[0]);
    al_destroy_bitmap(marioZ[1]);
    al_destroy_bitmap(marioM[0]);
    al_destroy_bitmap(marioM[1]);
    al_destroy_bitmap(marioM[2]);
    al_destroy_bitmap(marioM[3]);
    al_destroy_bitmap(marioM[4]);
    al_destroy_bitmap(barrilV[0]);
    al_destroy_bitmap(barrilV[1]);
    al_destroy_bitmap(barrilV[2]);
    al_destroy_bitmap(barrilV[3]);
    al_destroy_bitmap(barrilVertical[0]);
    al_destroy_bitmap(barrilVertical[1]);
    al_destroy_bitmap(fuegoI[0]);
    al_destroy_bitmap(fuegoI[1]);
    al_destroy_bitmap(fuegoI[2]);
    al_destroy_bitmap(fuegoI[3]);
    al_destroy_bitmap(gasolinaAnimada[0]);
    al_destroy_bitmap(gasolinaAnimada[1]);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
}

void reading(){
    int i = 0;
    int j = 0;
    int* k = &i;
    mario = marioX;
    while(1)
    {
        //printf("hor = %d || ver = %d || mix = %d || fire = %d\n",hay_barril_,hay_barril_vertical,hay_barril_mixto,hay_fuego);
        random++;
        if(!barril_encendido){
            if (verificarBarrilEncendido()){
                barril_encendido = 1;
            }
        }
        if(random>27){
            random = 1;
        }
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if (dentroLimite() == -1){
        }
        else if (choque() == -1){
        }
        else if(ev.type == ALLEGRO_EVENT_TIMER) {
            if(countKeys()==1) {
                if (key[KEY_UP] && hay_escaleras(1) && !saltando && vivo) {
                    nivelPiso -= 1;
                    j++;
                    mario = marioZ;
                    k = &j;
                }
                if (key[KEY_DOWN] && hay_escaleras(0) && !saltando && vivo) {
                    nivelPiso += 1;
                    j++;
                    mario = marioZ;
                    k = &j;
                }
                if (key[KEY_LEFT] && xM >= 4.0 && !subiendo_escalera && vivo) {
                    xM -= 2.0;
                    i++;
                    if (saltando == 1){
                        i = 6;
                    }
                    mario = marioY;
                    k = &i;
                }
                if (key[KEY_RIGHT] && xM <= 860.0 && !subiendo_escalera && vivo) {
                    xM += 2.0;
                    i++;
                    if (saltando == 1){
                        i = 6;
                    }
                    mario = marioX;
                    k = &i;
                }
                redraw = true;
                if (i > 8) {
                    i = 0;
                }
                if (j > 9){
                    j = 0;
                }
            }
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = true;
                    break;
                case ALLEGRO_KEY_DOWN:

                    key[KEY_DOWN] = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = true;
                    i++;
                    break;
                case ALLEGRO_KEY_SPACE:
                    if (!subiendo_escalera && !saltando && vivo) {
                        CreateThread(NULL, 0, saltar, NULL, 0, 0);
                    }
                    break;
                case ALLEGRO_KEY_B:
                    nuevoBarril();
                    CreateThread(NULL, 0, barrilThread, ultimo(), 0, 0);
                    break;
                case ALLEGRO_KEY_V:
                    nuevoBarrilVertical();
                    CreateThread(NULL, 0, barrilVerticalThread, ultimoBarrilVertical(), 0, 0);
                    break;
                case ALLEGRO_KEY_M:
                    nuevoBarrilMixto();
                    CreateThread(NULL, 0, barrilMixtoThread, ultimoBarrilMixto(), 0, 0);
                    break;
                case ALLEGRO_KEY_F:
                    nuevoFuego();
                    CreateThread(NULL, 0, fuegoThread, ultimoFuego(), 0, 0);
                    break;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = false;
                    break;
            }
        }
        //printf("redraw = %d\n",redraw);
        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            barrels(image2);
            martillos(martillo);
            if (barril_encendido) {
                if (!gasolinaAnimacion) {
                    CreateThread(NULL, 0, animacionGasolina, NULL, 0, 0);
                }
                gasolina_inicial(gasolinaA);
            }
            else{
                gasolina_inicial(gasolina);
            }
            escaleras(escalera);
            platforms(image);
            yM = nivelPiso - obtenerPiso(xM,nivelPiso) - salto;

            if(hay_barril_ > 0){
                actualizarBarriles(lista_barriles);
            }
            if(hay_barril_vertical > 0){
                //printf("1---> %f %f\n",lista_barriles_verticales->barril_x,lista_barriles_verticales->barril_y);
                actualizarBarrilesVerticales(lista_barriles_verticales);
            }
            if(hay_barril_mixto > 0){
                //printf("1---> %f %f\n",lista_barriles_verticales->barril_x,lista_barriles_verticales->barril_y);
                actualizarBarrilesMixto(lista_barriles_mixtos);
            }
            if(hay_fuego > 0){
                actualizarFuegos(fuegos);
            }

            if (!vivo) {
                if (posicionMuerto == finalMuerto){
                    muertoID = 4;
                    vivo = 1;
                }
                al_draw_bitmap(marioM[muertoID], xM, posicionMuerto, 0);
                if (muertoID == 4){
                    xM = 40.0;
                    yM = 494.0;
                    nivelPiso = 494.0;
                    saltando = 0;
                    barril_encendido = 0;
                    subiendo_escalera = 0;
                    gasolinaAnimacion = 0;
                    while(hay_barril_ > 0){
                        eliminarBarril();
                    }
                    while(hay_barril_vertical > 0){
                        eliminarBarrilVertical();
                    }
                    while(hay_barril_mixto > 0){
                        eliminarBarrilMixto();
                    }
                    while(hay_fuego > 0){
                        eliminarFuego();
                    }
                    //printf("FIN\n");
                }
            }
            else{
                if (k == &i) {
                    al_draw_bitmap(*(mario + ((*k) / 3)), xM, yM, 0);
                }
                else{
                    al_draw_bitmap(*(mario + ((*k) / 5)), xM, yM, 0);
                }
            }
            al_flip_display();
        }
    }
}

DWORD WINAPI fuegoThread(void* fuego){
    FuegoE *fuego_actual = (FuegoE *) fuego;
    while (1){
        if (fuego_actual->nivelPiso > nivelPiso){
            escalerasPorPiso(fuego_actual,1);
            if (!vivo){
                redraw = true;
                return 0;
            }
        }
        else if (fuego_actual->nivelPiso < nivelPiso){
            escalerasPorPiso(fuego_actual,-1);
            if (!vivo){
                redraw = true;
                return 0;
            }
        }
        else{
            int x = xM;
            if (fuego_actual->x < x){
                for (; fuego_actual->x < x; fuego_actual->x += 2.0){
                    if (!vivo){
                        redraw = true;
                        return 0;
                    }
                    fuego_actual->y = fuego_actual->nivelPiso - obtenerPiso(fuego_actual->x,fuego_actual->nivelPiso);
                    redraw = true;
                    Sleep(30);
                }
            }
            else if (fuego_actual->x > x){
                for (; fuego_actual->x > x; fuego_actual->x -= 2.0) {
                    if (!vivo){
                        redraw = true;
                        return 0;
                    }
                    fuego_actual->y = fuego_actual->nivelPiso - obtenerPiso(fuego_actual->x, fuego_actual->nivelPiso);
                    redraw = true;
                    Sleep(30);
                }
            }
        }
        redraw = true;
        Sleep(30);
    }
}

void escalerasPorPiso(FuegoE* fuego_actual, int direccion){
    int id = 0;
    int id_distancia = 0;
    int result = 0;
    float nuevoPiso = 0.0;
    float mov = 2.0;
    if (direccion == -1){
        mov = -2.0;
    }
    switch ((int) fuego_actual->nivelPiso){
        case 494 :{
            id = 10;
            id_distancia = escaleraCercana(fuego_actual, id);
            result = escaleraCercana(fuego_actual, 11);
            if (result < id_distancia){
                id = 11;
            }
            nuevoPiso = 436.0;
            break;
        }
        case 436 :{
            if (direccion == 1){
                id = 8;
                id_distancia = escaleraCercana(fuego_actual, id);
                result = escaleraCercana(fuego_actual, 9);
                if (result < id_distancia){
                    id = 9;
                }
                nuevoPiso = 378.0;
            }
            else{
                id = 10;
                id_distancia = escaleraCercana(fuego_actual, id);
                result = escaleraCercana(fuego_actual, 11);
                if (result < id_distancia){
                    id = 11;
                }
                nuevoPiso = 494.0;
            }
            break;
        }
        case 378 :{
            if (direccion == 1){
                id = 5;
                id_distancia = escaleraCercana(fuego_actual, id);
                result = escaleraCercana(fuego_actual, 6);
                if (result < id_distancia){
                    id_distancia = result;
                    id = 6;
                }
                result = escaleraCercana(fuego_actual, 7);
                if (result < id_distancia){
                    id = 7;
                }
                nuevoPiso = 316.0;
            }
            else{
                id = 8;
                id_distancia = escaleraCercana(fuego_actual, id);
                result = escaleraCercana(fuego_actual, 9);
                if (result < id_distancia){
                    id = 9;
                }
                nuevoPiso = 436.0;
            }
            break;
        }
        case 316 :{
            if (direccion == 1){
                id = 2;
                id_distancia = escaleraCercana(fuego_actual, id);
                result = escaleraCercana(fuego_actual, 3);
                if (result < id_distancia){
                    id_distancia = result;
                    id = 3;
                }
                result = escaleraCercana(fuego_actual, 4);
                if (result < id_distancia){
                    id = 4;
                }
                nuevoPiso = 258.0;
            }
            else{
                id = 5;
                id_distancia = escaleraCercana(fuego_actual, id);
                result = escaleraCercana(fuego_actual, 6);
                if (result < id_distancia){
                    id_distancia = result;
                    id = 6;
                }
                result = escaleraCercana(fuego_actual, 7);
                if (result < id_distancia){
                    id = 7;
                }
                nuevoPiso = 378.0;
            }
            break;
        }
        case 258 :{
            if (direccion == 1){
                id = 0;
                id_distancia = escaleraCercana(fuego_actual, id);
                result = escaleraCercana(fuego_actual, 1);
                if (result < id_distancia){
                    id = 1;
                }
                nuevoPiso = 196.0;
            }
            else{
                id = 2;
                id_distancia = escaleraCercana(fuego_actual, id);
                result = escaleraCercana(fuego_actual, 3);
                if (result < id_distancia){
                    id_distancia = result;
                    id = 3;
                }
                result = escaleraCercana(fuego_actual, 4);
                if (result < id_distancia){
                    id = 4;
                }
                nuevoPiso = 316.0;
            }
            break;
        }
        case 196 :{
            id = 0;
            id_distancia = escaleraCercana(fuego_actual, id);
            result = escaleraCercana(fuego_actual, 1);
            if (result < id_distancia){
                id = 1;
            }
            nuevoPiso = 258.0;
            break;
        }
        default : break;
    }
    //printf("%d %d %d %f %f || %f %f\n",id,id_distancia,result,nuevoPiso,mov,fuego_actual->nivelPiso,nivelPiso);
    moverFuegoEscalera(fuego_actual,escaleras_rangos[id]->x,mov);
    if (!vivo){
        redraw = true;
        return;
    }
    if (mov < 0.0){
        useEscalera(fuego_actual,escaleras_rangos[id]->abajo_y, -1.0 * (mov/2));
        if (!vivo){
            redraw = true;
            return;
        }
    }
    else {
        useEscalera(fuego_actual, escaleras_rangos[id]->arriba_y, -1.0 * (mov/2));
        if (!vivo){
            redraw = true;
            return;
        }
    }
    fuego_actual->nivelPiso = nuevoPiso;
}

int escaleraCercana(FuegoE* fuego_actual, int id){
    return abs((int)fuego_actual->x - escaleras_rangos[id]->x);
}

void moverFuegoEscalera(FuegoE* fuego_actual, float x, float mov){
    if (fuego_actual->x < x){
        if (mov < 0.0){
            mov *= -1.0;
        }
        for (; fuego_actual->x < x; fuego_actual->x += mov) {
            if (!vivo){
                redraw = true;
                return;
            }
            fuego_actual->y = fuego_actual->nivelPiso - obtenerPiso(fuego_actual->x, fuego_actual->nivelPiso);
            redraw = true;
            Sleep(30);
        }
    }
    else {
        if (mov > 0.0){
            mov *= -1.0;
        }
        for (; fuego_actual->x > x; fuego_actual->x += mov) {
            if (!vivo){
                redraw = true;
                return;
            }
            fuego_actual->y = fuego_actual->nivelPiso - obtenerPiso(fuego_actual->x, fuego_actual->nivelPiso);
            redraw = true;
            Sleep(30);
        }
    }
}

void useEscalera(FuegoE* fuego_actual, float y, float mov){
    for (int i = 0; fuego_actual->y != y; i++) {
        if (!vivo) {
            redraw = true;
            return;
        }
        fuego_actual->y += mov;
        redraw = true;
        Sleep(30);
    }
}

void actualizarFuegos(FuegoE* fuego_actual){
    if (fuego_actual->id > 31){
        fuego_actual->id = 0;
    }
    int id = (fuego_actual->id)/16;
    al_draw_bitmap(fuegoI[id], fuego_actual->x, fuego_actual->y, 0);
    fuego_actual->id++;
    if (fuego_actual->siguiente != NULL){
        actualizarFuegos(fuego_actual->siguiente);
    }
}

DWORD WINAPI animacionGasolina(){
    gasolinaAnimacion = 1;
    while (vivo){
        gasolinaA = gasolinaAnimada[0];
        redraw = true;
        Sleep(100);
        gasolinaA = gasolinaAnimada[1];
        redraw = true;
        Sleep(100);
    }
    return 0;
}

DWORD WINAPI barrilMixtoThread(void* BarrilM){
    BarrilMixto *barril_actual = (BarrilMixto *) BarrilM;
    movimientoBarrilMixto(barril_actual,818.0,172.0,2.0,2.0);
    barril_actual->barril_nivel_piso = 258.0;
    movimientoBarrilMixto(barril_actual,46.0,248.0,-2.0,2.0);
    barril_actual->barril_nivel_piso = 316.0;
    movimientoBarrilMixto(barril_actual,818.0,328.0,2.0,2.0);
    barril_actual->barril_nivel_piso = 378.0;
    movimientoBarrilMixto(barril_actual,46.0,404.0,-2.0,2.0);
    barril_actual->barril_nivel_piso = 436.0;
    movimientoBarrilMixto(barril_actual,818.0,480.0,2.0,2.0);
    barril_actual->barril_nivel_piso = 494.0;
    barril_actual->en_plataforma = 1;
    while (barril_actual->barril_x > 0.0){
        if (!vivo){
            redraw = true;
            return 0;
        }
        barril_actual->barril_x += -2.0;
        barril_actual->barril_y = barril_actual->barril_nivel_piso - obtenerPiso(barril_actual->barril_x,barril_actual->barril_nivel_piso);
        redraw = true;
        Sleep(20);
    }
    redraw = true;
    return 0;
}

void movimientoVerticalBarrilMixto(BarrilMixto* barril_actual, float y, float mov){
    for (int i = 0; barril_actual->barril_y < y; i++) {
        if (!vivo) {
            redraw = true;
            return;
        }
        barril_actual->barril_y += mov;
        redraw = true;
        Sleep(20);
    }
    if (barril_actual->barril_y != y) {
        if (!vivo) {
            redraw = true;
            return;
        }
        barril_actual->barril_y = y;
        redraw = true;
        Sleep(20);
    }
}

int movimientoHorizontalBarrilMixto(BarrilMixto* barril_actual, float x, float mov){
    int result = 0;
    while ((barril_actual->barril_x < x && mov > 0.0) || (barril_actual->barril_x > x && mov < 0.0)){
        if (!vivo){
            redraw = true;
            return 0;
        }
        if (barril_actual->barril_x == escaleras_rangos[barril_actual->despues_escalera]->x && barril_actual->barril_y == escaleras_rangos[barril_actual->despues_escalera]->arriba_y)
        {
            if (random > 13) {
                result = escaleras_rangos[barril_actual->despues_escalera]->abajo_y;
                barril_actual->despues_escalera = escaleras_rangos[barril_actual->despues_escalera]->siguiente;
                break;
            }
            else{
                barril_actual->despues_escalera++;
            }
        }
        barril_actual->barril_x += mov;
        barril_actual->barril_y = barril_actual->barril_nivel_piso - obtenerPiso(barril_actual->barril_x,barril_actual->barril_nivel_piso);
        redraw = true;
        Sleep(20);
    }
    return result;
}

void movimientoBarrilMixto(BarrilMixto* barril_actual, float x, float y, float movX, float movY){
    barril_actual->en_plataforma = 1;
    int bajar = movimientoHorizontalBarrilMixto(barril_actual, x, movX);
    barril_actual->en_plataforma = 0;
    if (bajar == 0){
        movimientoVerticalBarrilMixto(barril_actual, y, movY);
    }
    else {
        movimientoVerticalBarrilMixto(barril_actual, bajar, movY);
    }
}

void actualizarBarrilesMixto(BarrilMixto* barril_actual){
    if (barril_actual->barril_id > 31){
        barril_actual->barril_id = 0;
    }
    int id = (barril_actual->barril_id)/16;
    ALLEGRO_BITMAP** images = barrilVertical;
    if (barril_actual->en_plataforma){
        id = (barril_actual->barril_id)/8;
        images = barrilV;
    }
    al_draw_bitmap(*(images+id), barril_actual->barril_x, barril_actual->barril_y, 0);
    barril_actual->barril_id++;
    if (barril_actual->siguiente != NULL){
        actualizarBarrilesMixto(barril_actual->siguiente);
    }
    if (barril_actual->barril_x <= 0){
        eliminarUnBarrilMixto();
    }
}

DWORD WINAPI barrilVerticalThread(void* BarrilV){
    BarrilVertical *barril_actual = (BarrilVertical *) BarrilV;
    float newX = (float) random * 32.0;
    if (newX > barril_actual->barril_x){
        while (barril_actual->barril_x < newX){
            if (!vivo){
                redraw = true;
                return 0;
            }
            barril_actual->barril_x += 2.0;
            barril_actual->barril_y = barril_actual->barril_nivel_piso - obtenerPiso(barril_actual->barril_x,barril_actual->barril_nivel_piso);
            redraw = true;
            Sleep(20);
        }
    }
    barril_actual->barril_x = newX;
    barril_actual->barril_y = barril_actual->barril_nivel_piso - obtenerPiso(barril_actual->barril_x,barril_actual->barril_nivel_piso);
    redraw = true;
    Sleep(20);
    if (!vivo){
        redraw = true;
        return 0;
    }
    movimientobarrilVertical(barril_actual,494.0-obtenerPiso(barril_actual->barril_x,494.0),2.0);
    if (!vivo){
        redraw = true;
        return 0;
    }
    barril_actual->barril_nivel_piso = 494.0;
    while (barril_actual->barril_x > 0.0){
        if (!vivo){
            redraw = true;
            return 0;
        }
        barril_actual->barril_x += -2.0;
        barril_actual->barril_y = barril_actual->barril_nivel_piso - obtenerPiso(barril_actual->barril_x,barril_actual->barril_nivel_piso);
        redraw = true;
        Sleep(20);
    }
    redraw = true;
    return 0;
}

void movimientobarrilVertical(BarrilVertical* barril_actual, float y, float mov){
    for (int i = 0; barril_actual->barril_y < y; i++){
        if (!vivo){
            redraw = true;
            return;
        }
        barril_actual->barril_y += mov;
        redraw = true;
        Sleep(20);
    }
    if (barril_actual->barril_y != y) {
        if (!vivo){
            redraw = true;
            return;
        }
        barril_actual->barril_y = y;
        redraw = true;
        Sleep(20);
    }
}

void actualizarBarrilesVerticales(BarrilVertical* barril_actual){
    if (barril_actual->barril_id > 31){
        barril_actual->barril_id = 0;
    }
    int id = (barril_actual->barril_id)/16;
    ALLEGRO_BITMAP** images = barrilVertical;
    if (barril_actual->barril_nivel_piso == 494.0 || barril_actual->barril_y == 196.0 - obtenerPiso(barril_actual->barril_x,196.0)){
        id = (barril_actual->barril_id)/8;
        images = barrilV;
    }
    al_draw_bitmap(*(images+id), barril_actual->barril_x, barril_actual->barril_y, 0);
    barril_actual->barril_id++;
    if (barril_actual->siguiente != NULL){
        actualizarBarrilesVerticales(barril_actual->siguiente);
    }
    if (barril_actual->barril_x <= 0){
        eliminarUnBarrilVertical();
    }
}

int choque(){
    if ((!hay_barril_ && !hay_barril_vertical && !hay_barril_mixto && !hay_fuego) || !vivo )
    {
        return 0;
    }
    BarrilL* temp = lista_barriles;
    while(temp != NULL && hay_barril_) {
        if (colision(xM+8.0, yM, xM+22.0, yM+30.0, temp->barril_x+4.0, temp->barril_y+12.0, temp->barril_x+26.0, temp->barril_y+30.0)) {
            if (vivo) {
                vivo = 0;
                CreateThread(NULL, 0, muerteChoque, NULL, 0, 0);
                return -1;
            }
        }
        else{
            temp = temp->siguiente;
        }
    }
    BarrilVertical *temp2 = lista_barriles_verticales;
    while(temp2 != NULL && hay_barril_vertical) {
        if (temp2->barril_nivel_piso == 494.0 || temp2->barril_y == 196.0 - obtenerPiso(temp2->barril_x,196.0)) {
            if (colision(xM + 8.0, yM, xM + 22.0, yM + 30.0, temp2->barril_x + 4.0, temp2->barril_y + 12.0,
                         temp2->barril_x + 26.0, temp2->barril_y + 30.0)) {
                if (vivo) {
                    vivo = 0;
                    CreateThread(NULL, 0, muerteChoque, NULL, 0, 0);
                    return -1;
                }
            } else {
                temp2 = temp2->siguiente;
            }
        }
        else{
            if (colision(xM + 8.0, yM, xM + 22.0, yM + 30.0, temp2->barril_x + 0.0, temp2->barril_y + 12.0,
                         temp2->barril_x + 30.0 , temp2->barril_y + 30.0)) {
                if (vivo) {
                    vivo = 0;
                    CreateThread(NULL, 0, muerteChoque, NULL, 0, 0);
                    return -1;
                }
            } else {
                temp2 = temp2->siguiente;
            }
        }
    }
    BarrilMixto *temp3 = lista_barriles_mixtos;
    while(temp3 != NULL && hay_barril_mixto) {
        if (temp3->en_plataforma) {
            if (colision(xM + 8.0, yM, xM + 22.0, yM + 30.0, temp3->barril_x + 4.0, temp3->barril_y + 12.0,
                         temp3->barril_x + 26.0, temp3->barril_y + 30.0)) {
                if (vivo) {
                    vivo = 0;
                    CreateThread(NULL, 0, muerteChoque, NULL, 0, 0);
                    return -1;
                }
            } else {
                temp3 = temp3->siguiente;
            }
        }
        else{
            if (colision(xM + 8.0, yM, xM + 22.0, yM + 30.0, temp3->barril_x + 0.0, temp3->barril_y + 12.0,
                         temp3->barril_x + 30.0 , temp3->barril_y + 30.0)) {
                if (vivo) {
                    vivo = 0;
                    CreateThread(NULL, 0, muerteChoque, NULL, 0, 0);
                    return -1;
                }
            } else {
                temp3 = temp3->siguiente;
            }
        }
    }
    FuegoE *temp4 = fuegos;
    while(temp4 != NULL && hay_fuego) {
        if (colision(xM+8.0, yM, xM+22.0, yM+30.0, temp4->x+4.0, temp4->y+12.0, temp4->x+26.0, temp4->y+30.0)) {
            if (vivo) {
                vivo = 0;
                CreateThread(NULL, 0, muerteChoque, NULL, 0, 0);
                return -1;
            }
        }
        else{
            temp4 = temp4->siguiente;
        }
    }
    return 0;
}

int colision(float i1x, float i1y, float d1x, float d1y, float i2x, float i2y, float d2x, float d2y)
{
    if (i1x > d2x || i2x > d1x || d1y < i2y || d2y < i1y)
        return false;
    return 1;
}

void actualizarBarriles(BarrilL* barril_actual){
    if (barril_actual->barril_id > 31){
        barril_actual->barril_id = 0;
    }
    al_draw_bitmap(barrilV[barril_actual->barril_id/8], barril_actual->barril_x, barril_actual->barril_y, 0);
    barril_actual->barril_id++;
    if (barril_actual->siguiente != NULL){
        actualizarBarriles(barril_actual->siguiente);
    }
    if (barril_actual->barril_x <= 0){
        eliminarBarril();
    }
}

DWORD WINAPI barrilThread(void* barril){
    if (!vivo){
        redraw = true;
        return 0;
    }
    BarrilL *barril_actual = (BarrilL *) barril;
    redraw = true;
    Sleep(20);
    movimientoBarril(barril_actual, 818.0, 172.0, 2.0);
    if (!vivo){
        redraw = true;
        return 0;
    }
    barril_actual->barril_nivel_piso = 258.0;
    movimientoBarril(barril_actual, 46.0, 248.0, -2.0);
    if (!vivo){
        redraw = true;
        return 0;
    }
    barril_actual->barril_nivel_piso = 316.0;
    movimientoBarril(barril_actual, 818.0, 328.0, 2.0);
    if (!vivo){
        redraw = true;
        return 0;
    }
    barril_actual->barril_nivel_piso = 378.0;
    movimientoBarril(barril_actual, 46.0, 404.0, -2.0);
    if (!vivo){
        redraw = true;
        return 0;
    }
    barril_actual->barril_nivel_piso = 436.0;
    movimientoBarril(barril_actual, 818.0, 480.0, 2.0);
    if (!vivo){
        redraw = true;
        return 0;
    }
    barril_actual->barril_nivel_piso = 494.0;
    while (barril_actual->barril_x > 0.0){
        if (!vivo){
            redraw = true;
            return 0;
        }
        barril_actual->barril_x += -2.0;
        barril_actual->barril_y = barril_actual->barril_nivel_piso - obtenerPiso(barril_actual->barril_x,barril_actual->barril_nivel_piso);
        redraw = true;
        Sleep(20);
    }
    redraw = true;
    return 0;
}

void movimientoBarril(BarrilL* barril_actual, float x, float y, float mov){
    while ((barril_actual->barril_x < x && mov > 0.0) || (barril_actual->barril_x > x && mov < 0.0)){
        if (!vivo){
            redraw = true;
            return;
        }
        barril_actual->barril_x += mov;
        barril_actual->barril_y = barril_actual->barril_nivel_piso - obtenerPiso(barril_actual->barril_x,barril_actual->barril_nivel_piso);
        redraw = true;
        Sleep(20);
    }
    for (int i = 0; barril_actual->barril_y < y; i++){
        if (!vivo){
            redraw = true;
            return;
        }
        barril_actual->barril_y += abs((int)mov);
        redraw = true;
        Sleep(20);
    }
    if (barril_actual->barril_y != y) {
        if (!vivo){
            redraw = true;
            return;
        }
        barril_actual->barril_y = y;
        redraw = true;
        Sleep(20);
    }
}

int dentroLimite(){
    if (yM == 430 && xM > 817){
        if (vivo) {
            vivo = 0;
            finalMuerto = 480.0;
            CreateThread(NULL, 0, morir, NULL, 0, 0);
            return -1;
        }
        return 0;
    }
    if (yM == 354 && xM < 47){
        if (vivo) {
            vivo = 0;
            finalMuerto = 404.0;
            CreateThread(NULL, 0, morir, NULL, 0, 0);
            return -1;
        }
        return 0;
    }
    if (yM == 274 && xM > 817){
        if (vivo) {
            vivo = 0;
            finalMuerto = 328.0;
            CreateThread(NULL, 0, morir, NULL, 0, 0);
            return -1;
        }
        return 0;
    }
    if (yM == 198 && xM < 47){
        if (vivo) {
            vivo = 0;
            finalMuerto = 248.0;
            CreateThread(NULL, 0, morir, NULL, 0, 0);
            return -1;
        }
        return 0;
    }
    if (yM == 118 && xM > 817){
        if (vivo) {
            vivo = 0;
            finalMuerto = 172.0;
            CreateThread(NULL, 0, morir, NULL, 0, 0);
            return -1;
        }
        return 0;
    }
    if (yM == 40 && xM < 335){
        if (vivo) {
            vivo = 0;
            finalMuerto = 104.0;
            CreateThread(NULL, 0, morir, NULL, 0, 0);
            return -1;
        }
        return 0;
    }
    if (yM == 40 && xM > 529){
        if (vivo) {
            vivo = 0;
            finalMuerto = 108.0;
            CreateThread(NULL, 0, morir, NULL, 0, 0);
            return -1;
        }
        return 0;
    }
    return 1;
}

DWORD WINAPI morir(){
    posicionMuerto = yM;
    muertoID = 0;
    for (int i = 0; posicionMuerto < finalMuerto; i++){
        muertoID++;
        if (muertoID == 4){
            muertoID = 0;
        }
        posicionMuerto += 4.0;
        redraw = true;
        Sleep(75);
    }
    if (posicionMuerto != finalMuerto) {
        posicionMuerto = finalMuerto;
        yM = posicionMuerto;
        redraw = true;
        Sleep(75);
    }
    //printf("^^^ %f %f %f ^^^\n",yM,posicionMuerto,finalMuerto);
    return 0;
}

DWORD WINAPI muerteChoque(){
    posicionMuerto = yM;
    finalMuerto = posicionMuerto+1;
    muertoID = 0;
    for (int i = 0; i < 30; i++){
        muertoID++;
        if (muertoID == 4){
            muertoID = 0;
        }
        redraw = true;
        Sleep(75);
    }
    finalMuerto = posicionMuerto;
    redraw = true;
    Sleep(750);
    return 0;
}

DWORD WINAPI saltar()
{
    saltando = 1;
    int i;
    for(i = 0; i < 11; i++){
        salto = i*3;
        redraw = true;
        Sleep(40);
    }
    Sleep(100);
    for(; i >= 0; i--){
        salto = i*3;
        redraw = true;
        Sleep(40);
    }
    saltando = 0;
    return 0;
}

int countKeys(){
    int count = 0;
    for (int i = 0; i < 4; i++){
        if (key[i] == true){
            count++;
        }
        if (count == 2){
            break;
        }
    }
    return count;
}

int hay_escaleras(int arriba){
    //printf("x = %f ^ y = %f ^ piso = %f\n",xM,yM,nivelPiso);
    if (xM > 716 && xM < 748) {
        if ((yM < 484.0 && yM >= 426.0 && arriba == 0) || (yM > 426.0 && yM <= 484.0 && arriba == 1)) {
            subiendo_escalera = 1;
            return 1;
        }
        if ((yM < 332.0 && yM >= 270.0 && arriba == 0) || (yM > 270.0 && yM <= 332.0 && arriba == 1)) {
            subiendo_escalera = 1;
            return 1;
        }
        if ((yM < 176.0 && yM >= 114.0 && arriba == 0) || (yM > 114.0 && yM <= 176.0 && arriba == 1)) {
            subiendo_escalera = 1;
            return 1;
        }
        subiendo_escalera = 0;
        return 0;
    }
    else if(xM > 368 && xM < 400){
        if ((yM < 416.0 && yM >= 342.0 && arriba == 0) || (yM > 342.0 && yM <= 416.0 && arriba == 1)) {
            subiendo_escalera = 1;
            return 1;
        }
        subiendo_escalera = 0;
        return 0;
    }
    else if(xM > 112 && xM < 144){
        if ((yM < 408.0 && yM >= 350.0 && arriba == 0) || (yM > 350.0 && yM <= 408.0 && arriba == 1)) {
            subiendo_escalera = 1;
            return 1;
        }
        if ((yM < 252.0 && yM >= 194.0 && arriba == 0) || (yM > 194.0 && yM <= 252.0 && arriba == 1)) {
            subiendo_escalera = 1;
            return 1;
        }
        subiendo_escalera = 0;
        return 0;
    }
    else if(xM > 432 && xM < 464){
        if ((yM < 340.0 && yM >= 262.0 && arriba == 0) || (yM > 262.0 && yM <= 340.0 && arriba == 1)) {
            subiendo_escalera = 1;
            return 1;
        }
        subiendo_escalera = 0;
        return 0;
    }
    else if(xM > 272 && xM < 304){
        if ((yM < 256.0 && yM >= 190.0 && arriba == 0) || (yM > 190.0 && yM <= 256.0 && arriba == 1)) {
            subiendo_escalera = 1;
            return 1;
        }
        subiendo_escalera = 0;
        return 0;
    }
    else if(xM > 496 && xM < 528){
        if ((yM < 108.0 && yM >= 40.0 && arriba == 0) || (yM > 40.0 && yM <= 108.0 && arriba == 1)) {
            subiendo_escalera = 1;
            return 1;
        }
        subiendo_escalera = 0;
        return 0;
    }
    return 0;
}

int obtenerPiso(float x, float nivel){
    int nx = 0;
    int i = 0;
    int j;
    if (nivel > 436) {
        while (x > 432 + (i * 64)) {
            if (x <= 432 + ((i + 1) * 64)) {
                nx = 2 * i + 2;
                break;
            }
            i++;
        }
    }
    else if (nivel > 378){
        nx = 10;
        j = 11;
        while (x > -16 + (i * 64)) {
            if (x <= -16 + ((i + 1) * 64)) {
                nx += 2 * j;
                break;
            }
            j--;
            i++;
        }
    }
    else if (nivel > 316){
        nx = 28;
        j = -2;
        while (x > -16 + (i * 64)) {
            if (x <= -16 + ((i + 1) * 64)) {
                nx += 2 * j;
                break;
            }
            j++;
            i++;
        }
    }
    else if (nivel > 258){
        nx = 46;
        j = 11;
        while (x > -16 + (i * 64)) {
            if (x <= -16 + ((i + 1) * 64)) {
                nx += 2 * j;
                break;
            }
            j--;
            i++;
        }
    }
    else if (nivel > 196){
        nx = 64;
        j = -2;
        while (x > -16 + (i * 64)) {
            if (x <= -16 + ((i + 1) * 64)) {
                nx += 2 * j;
                break;
            }
            j++;
            i++;
        }
    }
    else if (nivel > 128){
        nx = 82;
        if (x <= 432){
            return 92;
        }
        j = -4;
        while (x > 432 + (i * 64)) {
            if (x <= 432 + ((i + 1) * 64)) {
                nx += -2 * j;
                break;
            }
            j++;
            i++;
        }
    }
    else{
        nx = 88;
    }
    return nx;
}

void escaleras(ALLEGRO_BITMAP  *imagen){
    al_draw_bitmap(imagen, 736, 487, 0);
    al_draw_bitmap(imagen, 736, 472, 0);
    al_draw_bitmap(imagen, 320, 510, 0);
    al_draw_bitmap(imagen, 320, 446, 0);

    al_draw_bitmap(imagen, 128, 397, 0);
    al_draw_bitmap(imagen, 128, 412, 0);
    al_draw_bitmap(imagen, 384, 390, 0);
    al_draw_bitmap(imagen, 384, 405, 0);
    al_draw_bitmap(imagen, 384, 420, 0);

    al_draw_bitmap(imagen, 256, 356, 0);
    al_draw_bitmap(imagen, 256, 294, 0);
    al_draw_bitmap(imagen, 448, 340, 0);
    al_draw_bitmap(imagen, 448, 325, 0);
    al_draw_bitmap(imagen, 448, 310, 0);
    al_draw_bitmap(imagen, 736, 332, 0);
    al_draw_bitmap(imagen, 736, 317, 0);

    al_draw_bitmap(imagen, 128, 252, 0);
    al_draw_bitmap(imagen, 128, 237, 0);
    al_draw_bitmap(imagen, 288, 256, 0);
    al_draw_bitmap(imagen, 288, 241, 0);
    al_draw_bitmap(imagen, 672, 274, 0);
    al_draw_bitmap(imagen, 672, 212, 0);

    al_draw_bitmap(imagen, 352, 204, 0);
    al_draw_bitmap(imagen, 352, 140, 0);
    al_draw_bitmap(imagen, 736, 176, 0);
    al_draw_bitmap(imagen, 736, 161, 0);

    al_draw_bitmap(imagen, 512, 108, 0);
    al_draw_bitmap(imagen, 512, 93, 0);
    al_draw_bitmap(imagen, 512, 78, 0);
    al_draw_bitmap(imagen, 256, 104, 0);
    al_draw_bitmap(imagen, 256, 74, 0);
    al_draw_bitmap(imagen, 256, 44, 0);
    al_draw_bitmap(imagen, 320, 104, 0);
    al_draw_bitmap(imagen, 320, 74, 0);
    al_draw_bitmap(imagen, 320, 44, 0);
}

void platforms(ALLEGRO_BITMAP  *imagen){
    int i;
    for (i = 0; i < 14; i++) {
        al_draw_bitmap(imagen, i * 32, 519, 0);
    }
    int j = 2;
    for (; i < 28; i += 2) {
        al_draw_bitmap(imagen, i * 32, 519-j, 0);
        al_draw_bitmap(imagen, (i+1) * 32, 519-j, 0);
        j += 2;
    }
    j = 26;
    for (i = 0; i < 26; i += 2) {
        al_draw_bitmap(imagen, i * 32, 455-j, 0);
        al_draw_bitmap(imagen, (i+1) * 32, 455-j, 0);
        j -= 2;
    }
    j = 0;
    for (i = 2; i < 28; i += 2) {
        al_draw_bitmap(imagen, i * 32, 377-j, 0);
        al_draw_bitmap(imagen, (i+1) * 32, 377-j, 0);
        j += 2;
    }
    j = 26;
    for (i = 0; i < 26; i += 2) {
        al_draw_bitmap(imagen, i * 32, 299-j, 0);
        al_draw_bitmap(imagen, (i+1) * 32, 299-j, 0);
        j -= 2;
    }
    j = 0;
    for (i = 2; i < 28; i += 2) {
        al_draw_bitmap(imagen, i * 32, 221-j, 0);
        al_draw_bitmap(imagen, (i+1) * 32, 221-j, 0);
        j += 2;
    }
    j = 12;
    for (i = 14; i < 26; i += 2) {
        al_draw_bitmap(imagen, i * 32, 143-j, 0);
        al_draw_bitmap(imagen, (i+1) * 32, 143-j, 0);
        j -= 2;
    }
    for (i = 0; i < 14; i++) {
        al_draw_bitmap(imagen, i * 32, 129, 0);
    }
    for (i = 11; i < 17; i++) {
        al_draw_bitmap(imagen, i * 32, 65, 0);
    }
}

void barrels(ALLEGRO_BITMAP  *imagen){
    int i;
    int j = 0;
    for (i = 0; j < 2; i++) {
        if (i == 3){
            j++;
            i = -1;
        }
        else {
            al_draw_bitmap(imagen, 20 * i - 6, 104 - 32 * j, 0);
        }
    }
}

void martillos(ALLEGRO_BITMAP *imagen){
    al_draw_bitmap(imagen, 64, 167, 0);
    al_draw_bitmap(imagen, 800, 398, 0);
}

void gasolina_inicial(ALLEGRO_BITMAP* imagen){
    al_draw_bitmap(imagen, 64, 478, 0);
}

ALLEGRO_BITMAP* createImage(char* carpeta, char* nombreImagen){
    ALLEGRO_PATH* path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);

    ALLEGRO_BITMAP  *imagen = NULL;

    al_drop_path_tail(path);
    al_append_path_component(path, "Graphics");
    al_append_path_component(path, carpeta);
    const char* pathstr = al_path_cstr(path , ALLEGRO_NATIVE_PATH_SEP);
    al_change_directory(pathstr);
    al_destroy_path(path);

    imagen = al_load_bitmap(nombreImagen);
    return imagen;
}