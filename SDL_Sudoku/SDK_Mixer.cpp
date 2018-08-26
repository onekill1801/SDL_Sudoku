#include"SDK_Mixer.h"
#include<SDL_mixer.h>

using namespace std;

bool Sound_init(){
    bool succes = true;
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            cout << "Error Audio "<<endl;
            succes = false;
        }
    if( TTF_Init() == -1 )
    {
        cout << "Error TTFonts"<<endl;
        succes = false;
    }
    return succes;
}
bool Sound_load(){
}
void Sound_Close(){
}


