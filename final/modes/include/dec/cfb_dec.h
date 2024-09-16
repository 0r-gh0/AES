#ifndef CFB_DEC_H
#define CFB_DEC_H

#include "../../../main.h"  // For HexWord and data types
#include "../../../run/include/enc_dec.h"  // For encryption functions
#include "../../../run/include/algo.h"
#include "../../../run/include/utils.h"

// Function prototype for CfBDec
void CfbDec(HexWord* input_2, HexWord* keyScheduling, FILE *iFile, FILE *oFile);

#endif // CFB_DEC_H