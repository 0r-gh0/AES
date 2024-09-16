#ifndef CBC_ENC_H
#define CBC_ENC_H

#include "../../../main.h"  // For HexWord and data types
#include "../../../run/include/enc_dec.h"  // For encryption functions
#include "../../../run/include/algo.h"
#include "../../../run/include/utils.h"

// Function prototype for CbcEnc
void CbcEnc(HexWord* input_2, HexWord* keyScheduling, FILE *iFile, FILE *oFile);

#endif // CBC_ENC_H