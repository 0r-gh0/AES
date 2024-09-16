#ifndef ALGO_H
#define ALGO_H

#include "utils.h"  // For utility functions and the global sBox
#include "main.h"  // For HexWord, HexByte, and any other types or constants

// Function prototypes
void keyExpansion( HexWord *rowKeyArray, HexWord *keyScheduling,  unsigned char sizeNK);

void wordXOR( HexWord *A,  HexWord *B, HexWord *temp);

void subBytes( HexWord *A, HexWord *temp);

void InvSubBytes( HexWord *A, HexWord *temp);

void shiftRows( HexWord *inWord, HexWord *temp);

void InvShiftRows( HexWord *inWord, HexWord *temp);

HexByte galoisMul( HexByte A,  HexByte B);

void MixColumns( HexWord *A, HexWord *temp);

void InvMixColumns( HexWord *A, HexWord *temp);

#endif // ALGO_H
