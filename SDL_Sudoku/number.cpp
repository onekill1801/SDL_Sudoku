#include<iostream>
#include"number.h"
#include<SDL.h>
#include"SDK_GUI.h"
#include <SDL_image.h>

using namespace std;

void numberTwo(SDL_Renderer renderer,SDL_Texture image){
//    SDL_Rect oneNumber = { 0,0,99,99};
    SDL_Rect oneNumber = { 100,0,99,99};
    SDL_Rect vitri = { 21,21,49,49};

    SDL_RenderCopy(renderer,image,&oneNumber,&vitri);
//    SDL_RenderCopy(renderer,image,&x,&y);

}
void numberOne(SDL_Renderer renderer,SDL_Texture image){
//    SDL_Rect oneNumber = { 0,0,99,99};
    SDL_Rect oneNumber = { 0,0,99,99};
    SDL_Rect vitri = { 21,71,49,49};

    SDL_RenderCopy(renderer,image,&oneNumber,&vitri);
//    SDL_RenderCopy(renderer,image,&x,&y);

}
