#include"rulesSDK.h"
#include<iostream>
#include<fstream>
#include <stdlib.h>

using namespace std;

int SDK[9][9],SDK_result[9][9];
bool SDK_Check(int S[][9],int x,int y,int k){
    for(int i =0;i<9;i++){
        if(S[x][i] == k) return false;
    }
    for(int i=0;i<9;i++){
        if(S[i][y] == k) return false;
    }
    int a = x/3, b = y/3;
    for(int i=3*a;i<3*a+3;i++){
        for(int j=3*b;j<3*b+3;j++){
            if(S[i][j] == k) return false;
        }
    }
    return true;
}
void SDK_answer(int Q[][9],int S[][9],int x,int y){
    if(y==9){
        if(x==8){
            for(int i=0;i<9;i++){
                for(int j=0;j<9;j++){
                    Q[i][j] = S[i][j];
                }
            }
        }
        else {
            SDK_answer(Q,S,x+1,0);
        }
    } else if(S[x][y] == 0){
        for(int k =1;k<=9;k++){
            if(SDK_Check(S,x,y,k)){
                S[x][y] = k;
                SDK_answer(Q,S,x,y+1);
                S[x][y] = 0;
            }
        }
    }
    else {
        SDK_answer(Q,S,x,y+1);
    }
}
void SDK_create(string level){
    ifstream file;
    file.open(level.c_str(),ios::in);
    if(file.fail()){
		cout << " Error opening"<< endl;
        system("pause");
        exit (0);
    }
    else {
        for(int i =0 ;i< 9;i++){
            for(int j=0;j<9;j++){
                file >> SDK[i][j];
            }
        }
    }
    file.close();
}

void SDK_printf(){
    for(int i =0 ;i< 9;i++){
        for(int j=0;j<9;j++){
            cout << SDK[i][j] <<" ";
        }
        cout << endl;
    }
}
int* SDK_showArr(string level){
    SDK_create(level);
    SDK_answer(SDK_result,SDK,0,0);
    static int SDK_show[81];
    int dem = 0;
    for(int i =0;i<9;i++){
        for(int j=0;j<9;j++){
            SDK_show[dem] = SDK[i][j];
            dem ++;
            cout << SDK_result[i][j] << " ";
        }
        cout << endl;
    }
    return SDK_show;
}
int* SDK_showArrResult(){
    static int SDK_show[81];
    int dem = 0;
    for(int i =0;i<9;i++){
        for(int j=0;j<9;j++){
            SDK_show[dem] = SDK_result[i][j];
            dem ++;
        }
    }
    return SDK_show;
}




