#ifndef ECB_ENC_H
#define ECB_ENC_H

#include "../../../main.h"  // For HexWord and data types
#include "../../../run/include/enc_dec.h"  // For encryption functions
#include "../../../run/include/algo.h"
#include "../../../run/include/utils.h"

// Function prototype for EcbEnc
void EcbEnc(HexWord* keyScheduling, FILE *iFile, FILE *oFile);

#endif // ECB_ENC_H
