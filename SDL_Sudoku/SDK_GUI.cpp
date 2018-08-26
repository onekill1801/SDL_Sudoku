#include<iostream>
#include"SDK_GUI.h"
#include"rulesSDK.h"
#include<SDL.h>
#include <SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<sstream>

using namespace std;

SDL_Window * window = NULL;

SDL_Renderer* renderer = NULL;

string levelNum[4] = {"Level/1.txt","Level/2.txt","Level/3.txt","Level/4.txt"};
int SDK_Arr[9][9],SDK_Arr2[9][9],SDK_Arr3[9][9] ;

bool SDK_TheEnd(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(SDK_Arr[i][j] == 0 && (SDK_Arr2[i][j] != SDK_Arr3[i][j])){
                return false;
            }
        }
    }
    return true;
}

void SDK_insert(int x,int y,int k){
    SDK_Arr2[x][y] = k;
}
void GUI_ConvertResult(){
    int * GUI_Arr ;
    GUI_Arr = SDK_showArrResult();
    int dem=0;
    for(int j=0;j<9;j++){
        for(int i=0;i<9;i++){
            SDK_Arr3[i][j] = *(GUI_Arr + dem++);
        }
    }
}
void GUI_ConvertCreate(string levelNumber){
    int * GUI_Arr ;
    GUI_Arr = SDK_showArr(levelNumber.c_str());
    int dem=0;
    for(int j=0;j<9;j++){
        for(int i=0;i<9;i++){
            SDK_Arr[i][j] = *(GUI_Arr + dem++);
            SDK_Arr2[i][j] = SDK_Arr[i][j];
        }
    }
}
void GUI_Convert(string levelNumber){
    GUI_ConvertCreate(levelNumber);
    GUI_ConvertResult();
}

bool init(){
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) <0){
        cout << "SDL could not init !!!" <<endl;
        success = false;
    }
    else{
        window = SDL_CreateWindow("SUDOKU Tutorial",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGTH,SDL_WINDOW_SHOWN);
        if(window == NULL){
            cout << "Window could not be create ! SDL_Error: "<<endl;
            success= false;
        }
        else{
            renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            if(renderer ==NULL){
                cout << "Renderer could not be create ! " <<endl;
                success = false;
            }
            if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
            {
                cout << " Error Audio "<<endl;
                success = false;
            }
            if( TTF_Init() == -1 )
            {
                cout << "Error TTFonts"<<endl;
                success = false;
            }
        }
    }
    return success;
}

SDL_Texture * image = NULL;

SDL_Texture * texture = NULL;
SDL_Texture * numberImage = NULL;
SDL_Texture * numberDefaultImage = NULL;
SDL_Texture * secondImage = NULL;
SDL_Texture * theendImage = NULL;
SDL_Texture * selectImage = NULL;

// Start chua hoan thien

// The end

SDL_Texture* gTexture = NULL;

Mix_Music* gMusic = NULL;
Mix_Chunk* gButton = NULL;

TTF_Font* gFont = NULL;

bool loadMedia(){
    bool success = true;

    texture = loadTexture("./image/Capture.png");

    numberDefaultImage = loadTexture("./image/newnumber1.png");
    numberImage = loadTexture("./image/newnumber.png");

    secondImage = loadTexture("./image/Capture1 copy copy.png");
    theendImage = loadTexture("./image/Capture3.png");
    selectImage = loadTexture("./image/select1.png");

    image = texture;
    if(texture == NULL ){
        cout << "Error could not loadMedia ."<<endl;
        success = false;
    }
    // Phan moi
    gFont = TTF_OpenFont( "fonts/VNI-Briquet.ttf", 50 );
	if( gFont == NULL )
	{
	    cout << "Error Fonts"<<endl;
		success = false;
	}
    gMusic = Mix_LoadMUS( "Sounds/sounds.wav" );
//    gMusic = Mix_LoadMUS("Sounds/scratch.wav");

    gButton = Mix_LoadWAV("Sounds/tape.wav");

    if(gMusic == NULL || gButton == NULL){
        cout << "Error Music "<<endl;
        success = false;
    }
    return success;
}
void SDK_Time_tff(string textureText){
    SDL_Color textColor = {255 ,249,247,0};
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    gTexture = SDL_CreateTextureFromSurface( renderer, textSurface );

    SDL_FreeSurface( textSurface );

}
SDL_Texture * loadTexture(std :: string path){
    SDL_Texture * newTexture = NULL;
    SDL_Surface * surFace = NULL;
    if(path == "./image/select.png"){
        surFace = IMG_Load(path.c_str());
        //Lam trong suot hinh
        SDL_SetColorKey(surFace,SDL_TRUE,SDL_MapRGB(surFace->format,255,255,255));
    }
    else {
        surFace = IMG_Load(path.c_str());
    }

    if(surFace == NULL){
        cout << "Error could not be create!"<<endl;
    }
    else {
        // convert tu surface sang texture
        newTexture = SDL_CreateTextureFromSurface(renderer,surFace);
        if(newTexture == NULL){
            cout << "newTexture could not be create !"<<endl;
        }
        SDL_FreeSurface(surFace);
    }
    return newTexture;
}

void close(){
    SDL_DestroyRenderer(renderer);
    renderer= NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyTexture(texture);
    texture= NULL;

    SDL_DestroyTexture(secondImage);
    secondImage= NULL;

    SDL_DestroyTexture(theendImage);
    theendImage= NULL;
    SDL_DestroyTexture(numberImage);
    numberImage= NULL;
    SDL_DestroyTexture(numberDefaultImage);
    numberDefaultImage= NULL;
    SDL_DestroyTexture(selectImage);
    selectImage= NULL;
    SDL_DestroyTexture(image);
    image= NULL;

    TTF_CloseFont( gFont );
	gFont = NULL;

    Mix_FreeChunk(gButton);
    gButton=NULL;
    Mix_FreeMusic(gMusic);
    gMusic = NULL;

    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Screen_Start(SDL_Event *e){

    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
        int x,y;
        SDL_GetMouseState(&x,&y);
        bool inside = false,music = false;
        if((x >= 414 && x <= 588) && (y >= 508 && y <= 558)){
             inside = true;
        }
        if((x >= 813 && x <= 883) && (y >= 13 && y <= 56)){
              music = true;
        }
        if(inside){
            switch( e->type ){
                case SDL_MOUSEMOTION:
                cout << x << " : "<<y<<endl;
            break;
            case SDL_MOUSEBUTTONDOWN:
                 image = theendImage;
                 Mix_PlayChannel(-1,gButton,0);
                 break;
            }
        }

        else if(music){
             switch( e->type ){
                case SDL_MOUSEMOTION:
                    cout << x << " : "<<y<<endl;
                    break;
                case SDL_MOUSEBUTTONDOWN:
//                   image = theendImage;
                    if( Mix_PlayingMusic() == 0 ){
                           //Play the music
                           Mix_PlayMusic( gMusic, -1 );
                    }
                    //If music is being played
                    else
                    {
                    //If the music is paused
                    if( Mix_PausedMusic() == 1 ){
                        //Resume the music
                        Mix_ResumeMusic();
                    }
                    //If the music is playing
                    else{
                        //Pause the music
                        Mix_PauseMusic();
                        }
                     }
                    break;
                }
            }
    }
}

void Screen_Level(SDL_Event *e,int startTime1){
//
if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN
              || e->type == SDL_MOUSEBUTTONUP){

    int x,y;
    SDL_GetMouseState(&x,&y);
    bool inside = false;
    if((x >= 193 && x <= 367) && (y >= 292 && y <= 400)){
        inside = true;
    }
    if((x >= 397 && x <= 580) && (y >= 292 && y <= 400)){
        inside = true;
    }
    if((x >= 615 && x <= 798) && (y >= 292 && y <= 400)){
            inside = true;
    }
    if((x >= 397 && x <= 583) && (y >= 450 && y <= 554)){
            inside = true;
    }
    if(inside){
        switch( e->type )
        {
            case SDL_MOUSEMOTION:
                cout << x << " : "<<y<<endl;
                break;
            case SDL_MOUSEBUTTONDOWN:
                image = secondImage;
                Mix_PlayChannel(-1,gButton,0);
                startTime1=1;
                break;
        }
    }
}
}

void Screen_Broard(SDL_Event* e,int button_x,int button_y){
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN
        || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_KEYDOWN){

    int x,y;
    SDL_GetMouseState(&x,&y);
    bool inside = true;
    if(x <= 115 || x >= 159){
        inside = false;
    }
    else if(y <= 74 || y >= 117){
        inside = false;
    }

    if(inside){
        switch( e->type ){
            case SDL_MOUSEMOTION:
                cout << x << " : "<<y<<endl;
                break;
            case SDL_MOUSEBUTTONDOWN:
                image = texture;
                Mix_PlayChannel(-1,gButton,0);
                break;
            case SDL_MOUSEBUTTONUP:
                cout<< " Sau khi click Chuot !!"<<endl;
                break;
            }
    }
    if(e->type == SDL_KEYDOWN){
        switch(e->key.keysym.sym){
            case SDLK_0:
                SDK_insert(button_x,button_y,0);
                break;
            case SDLK_1:
                SDK_insert(button_x,button_y,1);
                break;
            case SDLK_2:
                SDK_insert(button_x,button_y,2);
                break;
            case SDLK_3:
                SDK_insert(button_x,button_y,3);
                break;
            case SDLK_4:
                SDK_insert(button_x,button_y,4);
                break;
            case SDLK_5:
                SDK_insert(button_x,button_y,5);
                break;
            case SDLK_6:
                SDK_insert(button_x,button_y,6);
                break;
            case SDLK_7:
                SDK_insert(button_x,button_y,7);
                break;
            case SDLK_8:
                SDK_insert(button_x,button_y,8);
                break;
            case SDLK_9:
                SDK_insert(button_x,button_y,9);
                break;
            case SDLK_s:
                button_y = button_y + 1;
                break;
            case SDLK_w:
                button_y = button_y - 1;
                if(button_y < 0) button_y = 8;
                break;
            case SDLK_d:
                button_x= button_x +1;
                break;
            case SDLK_a:
                button_x= button_x -1;
                if(button_x < 0) button_x = 8;
                break;
            case SDLK_DOWN:
                button_y = button_y + 1;
                break;
            case SDLK_UP:
                button_y = button_y - 1;
                if(button_y < 0) button_y = 8;
                break;
            case SDLK_RIGHT:
                button_x= button_x +1;
                break;
            case SDLK_LEFT:
                button_x= button_x -1;
                if(button_x < 0) button_x = 8;
                break;
            }
        }
    }
}

SDL_Rect number[10];
SDL_Rect vitri[9][9];
void selectButton(SDL_Rect vitri){
    SDL_RenderCopy(renderer,selectImage,NULL,&vitri);
}

void numberAndVitri(SDL_Texture* imageNum,SDL_Rect numberVitri ,SDL_Rect  vitri){
    SDL_RenderCopy(renderer,imageNum,&numberVitri,&vitri);
}

void kickThuoc(SDL_Rect number[],SDL_Rect vitri[][9]){

    for(int i =0;i<10;i++){
        number[i].x = i*100;
        number[i].y = 0;
        number[i].w = 100;
        number[i].h = 100;
    }
    for(int i =0;i<9;i++){
        for(int j =0;j<9;j++){
            vitri[i][j].x = i*51 + 278 ;
            vitri[i][j].y = j*51 + 130 ;
            vitri[i][j].w = 40;
            vitri[i][j].h = 40;
        }
    }
}

void startGame(){

    kickThuoc(number,vitri);
    if(!init()){
        cout << "init could not be create !"<<endl;
    }
    else {
        if(!loadMedia()){
            cout << "loadMedia could not be create ! "<<endl;
        }
        else {
            stringstream timeText;
            int a = 0,startTime =0;
            bool quit = false,level = false;
            int button_x = 0,button_y=0,Level_I = 0;

            SDL_Rect rect = {135,627,65,24};
            while(!quit){
                SDL_Event e;

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer,image,NULL,NULL);

                if(image == texture){
                    while(SDL_PollEvent(&e) != 0){
                        if(e.type == SDL_QUIT){
                            quit = true;
                        }
                        else {
                            Screen_Start(&e);
                        }
                    }
                }
                else if(image == theendImage){
                    while(SDL_PollEvent(&e) != 0){
                        if(e.type == SDL_QUIT){
                                quit = true;
                        }
                        else if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN
                                || e.type == SDL_MOUSEBUTTONUP){

                        int x,y;
                        SDL_GetMouseState(&x,&y);
                        bool inside = false;
                        if((x >= 193 && x <= 367) && (y >= 292 && y <= 400)){
                            inside = true;
                            Level_I = 0;
                        }
                        if((x >= 397 && x <= 580) && (y >= 292 && y <= 400)){
                            inside = true;
                            Level_I=1;
                        }
                        if((x >= 615 && x <= 798) && (y >= 292 && y <= 400)){
                            inside = true;
                            Level_I=2;
                        }
                        if((x >= 397 && x <= 583) && (y >= 450 && y <= 554)){
                            inside = true;
                            Level_I=3;
                        }
                        if(inside){
                            switch( e.type )
                            {
                                case SDL_MOUSEMOTION:
                                    cout << x << " : "<<y<<endl;
                                    break;
                                case SDL_MOUSEBUTTONDOWN:
                                    image = secondImage;
                                    Mix_PlayChannel(-1,gButton,0);
                                    startTime=SDL_GetTicks();
                                    level = true;
                                    break;
                            }
                        }
                        }
                    }
                }
                else if(image == secondImage){
                if(level){
                    GUI_Convert(levelNum[Level_I]);
                    level= false;
                }
                for(int i=0;i<9;i++){
                    for(int j=0;j<9;j++){
                        if(SDK_Arr[i][j] != 0)
                            numberAndVitri(numberDefaultImage,number[SDK_Arr[i][j]],vitri[i][j]);
                        else
                            numberAndVitri(numberImage,number[SDK_Arr2[i][j]],vitri[i][j]);
                    }
                }


                timeText.str( "" );

                timeText <<a<<a<<" : "<< ((SDL_GetTicks()- startTime)/10000)%7 << ((SDL_GetTicks()- startTime)/1000)%10 ;
                SDK_Time_tff(timeText.str().c_str());


				SDL_RenderCopy(renderer,gTexture,NULL,&rect);

                selectButton(vitri[button_x%9][button_y%9]);
                button_x=button_x%9;
                button_y=button_y%9;
//                cout << button_x << "--------" <<button_y<<endl;

                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT){
                        quit = true;
                    }

                    else if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN
                            || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_KEYDOWN){

                        int x,y;
                        SDL_GetMouseState(&x,&y);
                        bool inside = false,music = false;
                        if((x >= 115 && x <= 159)&&(y >= 74 && y <= 117)){
                            inside = true;
                        }
                        if((x >= 836 && x <= 878)&&(y >= 74 && y <= 117)){
                            music = true;
                        }

                        if(inside){
                            switch( e.type ){
                                case SDL_MOUSEMOTION:
                                    cout << x << " : "<<y<<endl;
                                    break;
                                case SDL_MOUSEBUTTONDOWN:
                                    image = texture;
                                    Mix_PlayChannel(-1,gButton,0);
                                    break;
                                case SDL_MOUSEBUTTONUP:
                                    cout<< " Sau khi click Chuot !!"<<endl;
                                    break;
                                }
                        }
                        if(music){
                                 switch( e.type ){
                                    case SDL_MOUSEMOTION:
                                        cout << x << " : "<<y<<endl;
                                        break;
                                    case SDL_MOUSEBUTTONDOWN:
                    //                   image = theendImage;
                                        if( Mix_PlayingMusic() == 0 ){
                                               //Play the music
                                               Mix_PlayMusic( gMusic, -1 );
                                        }
                                        //If music is being played
                                        else
                                        {
                                        //If the music is paused
                                        if( Mix_PausedMusic() == 1 ){
                                            //Resume the music
                                            Mix_ResumeMusic();
                                        }
                                        //If the music is playing
                                        else{
                                            //Pause the music
                                            Mix_PauseMusic();
                                            }
                                         }
                                        break;
                                    }
                                }
                        if(e.type == SDL_KEYDOWN){
                            switch(e.key.keysym.sym){
                                case SDLK_0:
                                    SDK_insert(button_x,button_y,0);
                                    break;
                                case SDLK_1:
                                    SDK_insert(button_x,button_y,1);
                                    break;
                                case SDLK_2:
                                    SDK_insert(button_x,button_y,2);
                                    break;
                                case SDLK_3:
                                    SDK_insert(button_x,button_y,3);
                                    break;
                                case SDLK_4:
                                    SDK_insert(button_x,button_y,4);
                                    break;
                                case SDLK_5:
                                    SDK_insert(button_x,button_y,5);
                                    break;
                                case SDLK_6:
                                    SDK_insert(button_x,button_y,6);
                                    break;
                                case SDLK_7:
                                    SDK_insert(button_x,button_y,7);
                                    break;
                                case SDLK_8:
                                    SDK_insert(button_x,button_y,8);
                                    break;
                                case SDLK_9:
                                    SDK_insert(button_x,button_y,9);
                                    break;
                                case SDLK_s:
                                    button_y = button_y + 1;
                                    break;
                                case SDLK_w:
                                    button_y = button_y - 1;
                                    if(button_y < 0) button_y = 8;
                                    break;
                                case SDLK_d:
                                    button_x= button_x +1;
                                    break;
                                case SDLK_a:
                                    button_x= button_x -1;
                                    if(button_x < 0) button_x = 8;
                                    break;
                                case SDLK_DOWN:
                                    button_y = button_y + 1;
                                    break;
                                case SDLK_UP:
                                    button_y = button_y - 1;
                                    if(button_y < 0) button_y = 8;
                                    break;
                                case SDLK_RIGHT:
                                    button_x= button_x +1;
                                    break;
                                case SDLK_LEFT:
                                    button_x= button_x -1;
                                    if(button_x < 0) button_x = 8;
                                    break;
                                }
                            }
                        }
//                    numberFive(vitri[5][5]);
                    }
                    if(SDK_TheEnd()){
                        image = theendImage;
                    }
                }


                SDL_RenderPresent(renderer);
            }
        }
    }
    close();
}
