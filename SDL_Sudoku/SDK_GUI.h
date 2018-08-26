#ifndef SDK_GUI_H_INCLUDED
#define SDK_GUI_H_INCLUDED

#include<SDL.h>
#include<iostream>
#include"SDK_Mixer.h"

const int SCREEN_WIDTH = 998;
const int SCREEN_HEIGTH = 657;

void GUI_Convert();
bool init();
bool loadMedia();
void close();
void startGame();
SDL_Texture* loadTexture( std::string path );



#endif // SDK_GUI_H_INCLUDED
