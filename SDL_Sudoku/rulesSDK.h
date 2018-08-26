#ifndef RULESSDK_H_INCLUDED
#define RULESSDK_H_INCLUDED
#include<iostream>

void SDK_create(std::string level);
void SDK_answer(int Q[][9],int S[][9],int x,int y);
void SDK_printf();
int* SDK_showArrResult();
int* SDK_showArr(std::string level);

#endif // RULESSDK_H_INCLUDED
