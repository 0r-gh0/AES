#ifndef ECB_DEC_H
#define ECB_DEC_H

#include "../../../main.h"  // For HexWord and data types
#include "../../../run/include/enc_dec.h"  // For decryption functions
#include "../../../run/include/algo.h"
#include "../../../run/include/utils.h"

// Function prototype for EcbDec
void EcbDec(HexWord* keyScheduling, FILE *iFile, FILE *oFile);

#endif // ECB_DEC_H
