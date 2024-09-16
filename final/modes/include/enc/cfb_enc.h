#ifndef CFB_ENC_H
#define CFB_ENC_H

#include "../../../main.h"  // For HexWord and data types
#include "../../../run/include/enc_dec.h"  // For encryption functions
#include "../../../run/include/algo.h"
#include "../../../run/include/utils.h"

// Function prototype for CfbEnc
void CfbEnc(HexWord* input_2, HexWord* keyScheduling, FILE *iFile, FILE *oFile);

#endif // CFB_ENC_H