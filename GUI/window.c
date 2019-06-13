#include <stdio.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"

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
    escalera = createImage("estructuras","escalera_sprite_0.png");
    xM = 40;
    yM = nivelPiso;
    al_draw_bitmap(marioX[0], xM, yM, 0);


    if(!image || !image2 || !martillo || !gasolina || !escalera || !marioX[0] || !marioX[1]
    || !marioX[2] || !marioY[0] || !marioY[1] || !marioY[2] || !marioZ[0] || !marioZ[1] || !marioM[0] || !marioM[1] || !marioM[2] || !marioM[3]) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_event_queue(event_queue);
        return -1;
    }
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
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if (dentroLimite() == -1){
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
                    mario = marioY;
                    k = &i;
                }
                if (key[KEY_RIGHT] && xM <= 860.0 && !subiendo_escalera && vivo) {
                    xM += 2.0;
                    i++;
                    mario = marioX;
                    k = &i;
                }
                redraw = true;
                if (i > 14) {
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
        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            barrels(image2);
            martillos(martillo);
            gasolina_inicial(gasolina);
            escaleras(escalera);
            platforms(image);
            yM = nivelPiso - obtenerPiso(xM) - salto;
            if (!vivo) {
                //printf("y %f   p %f   f %f   m %d\n",yM, posicionMuerto,finalMuerto,muertoID);
                if (posicionMuerto == finalMuerto){
                    muertoID = 4;
                    vivo = 1;
                }
                al_draw_bitmap(marioM[muertoID], xM, posicionMuerto, 0);
                if (muertoID == 4){
                    xM = 40.0;
                    yM = 494.0;
                    nivelPiso = 494.0;
                }
            }
            else{
                al_draw_bitmap(*(mario + ((*k) / 5)), xM, yM, 0);
            }
            al_flip_display();
        }
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
            finalMuerto = 178.0;
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
    posicionMuerto = finalMuerto;
    yM = posicionMuerto;
    //printf("^^^ %f %f %f ^^^\n",yM,posicionMuerto,finalMuerto);
    Sleep(75);
    redraw = true;
    return 0;
}

DWORD WINAPI saltar()
{
    saltando = 1;
    int i;
    for(i = 0; i < 11; i++){
        Sleep(40);
        salto = i*3;
        redraw = true;
    }
    Sleep(100);
    for(; i >= 0; i--){
        Sleep(40);
        salto = i*3;
        redraw = true;
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

int obtenerPiso(float x){
    int nx = 0;
    int i = 0;
    int j;
    if (nivelPiso > 436) {
        while (x > 432 + (i * 64)) {
            if (x <= 432 + ((i + 1) * 64)) {
                nx = 2 * i + 2;
                break;
            }
            i++;
        }
    }
    else if (nivelPiso > 378){
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
    else if (nivelPiso > 316){
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
    else if (nivelPiso > 258){
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
    else if (nivelPiso > 196){
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
    else if (nivelPiso > 128){
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