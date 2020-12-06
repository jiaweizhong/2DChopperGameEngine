#ifndef CONSTANTS_H
#define CONSTANTS_H

const unsigned int WINDOW_WIDTH  = 800;
const unsigned int WINDOW_HEIGHT = 600;
const unsigned int FPS = 60;
// datatype consistent with SDL_GetTicks()
// otherwise will have multiple definition error
const unsigned int FRAME_TARGET_TIME = 1000 / FPS; // milli-seconds

#endif