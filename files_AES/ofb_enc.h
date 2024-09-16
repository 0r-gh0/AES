#ifndef OFB_ENC_H
#define OFB_ENC_H

#include "main.h"  // For HexWord and data types
#include "enc_dec.h"  // For encryption functions
#include "algo.h"
#include "utils.h"

// Function prototype for OfbEnc
void OfbEnc(HexWord* input_2, HexWord* keyScheduling, FILE *iFile, FILE *oFile);

#endif // OFB_ENC_H