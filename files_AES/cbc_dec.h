#ifndef CBC_DEC_H
#define CBC_DEC_H

#include "main.h"  // For HexWord and data types
#include "enc_dec.h"  // For encryption functions
#include "algo.h"
#include "utils.h"

// Function prototype for EcbEnc
void CbcDec(HexWord* input_2, HexWord* keyScheduling, FILE *iFile, FILE *oFile);

#endif // CBC_ENC_H