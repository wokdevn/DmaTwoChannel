//
// Created by shun on 2023/6/13.
//

#ifndef TWODMA_UTILMM2S_H
#define TWODMA_UTILMM2S_H


#include "../head/interdma.h"

#define setbit(x,y) x |= (1<<y);
#define clrbit(x,y) x &= ~(1<<y);
#define reversebit(x,y) x^=(1<<y);
#define getbit(x,y) ((x>>y)&1)

const static int LONG_BIT_COUNT = CHAR_BIT * sizeof(long);

void print_b(void *pointer,size_t size);
void revert(char* data,int len,char* r_data);
char *itobs(long n, char *ps);
//convert long to char
char* long2char(long num,char *str);
char* char2bit(char* pack,int len,char* bitpack);
char* bit2char(char* bitpack,int len, char* pack);

char* constrM2S(struct MM2S_First * mm2s_first, char * data);

int getHeadM2S(char* data);
void getParamM2S(struct MM2S_First * mm2s_first, char * data);

int getHeadS2M(char* data);
void getParamS2M(s2mm_f* s2mm_first,char* data);

#endif //TWODMA_UTILMM2S_H
