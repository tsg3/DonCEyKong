#include "GUI/window.h"

int main(){

    int execution = initialize();

    switch (execution){
        case 1: break;
        case 0: return 0;
        case -1: return -1;
        default: return 1;
    }

    reading();

    finishExecution();

    return 0;
}