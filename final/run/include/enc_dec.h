#ifndef ENC_DEC_H
#define ENC_DEC_H

#include "algo.h"  // For AES algorithm functions
#include "utils.h"  // For utility functions and global sBox
#include "main.h"  // For HexWord and HexByte data types

// Function prototypes from enc_dec.c
void Encrypt(HexWord *in, HexWord *key, HexWord *out);
void Decrypt(HexWord *in, HexWord *key, HexWord *out);

#endif // ENC_DEC_H
