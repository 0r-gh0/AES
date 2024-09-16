#ifndef OFB_DEC_H
#define OFB_DEC_H

#include "main.h"  // For HexWord and data types
#include "enc_dec.h"  // For encryption functions
#include "algo.h"
#include "utils.h"

// Function prototype for OfBEnc
void OfbDec(HexWord* input_2, HexWord* keyScheduling, FILE *iFile, FILE *oFile);

#endif // OFB_DEC_H