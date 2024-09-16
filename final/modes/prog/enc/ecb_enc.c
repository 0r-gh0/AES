#include "../../include/enc/ecb_enc.h"  // For EcbEnc.c
#include "../../../run/include/enc_dec.h"
#include "../../../run/include/algo.h"
#include "../../../run/include/utils.h"
#include "../../../main.h"

void EcbEnc(HexWord* keyScheduling, FILE *iFile, FILE *oFile) { 
    unsigned char pad, t_run, byteRead, temp_i = 0, temp_j = 0, tempCounter = 0, buff[16], out_buff[16];
    HexWord in[4], output[4];
    
    while ((byteRead = fread(buff, 1, 16, iFile)) == 16) {
        in[0].bytes[0].nibbles.low = buff[0];
        in[0].bytes[0].nibbles.high = buff[0] >> 4;
        in[0].bytes[1].nibbles.low = buff[1];
        in[0].bytes[1].nibbles.high = buff[1] >> 4;
        in[0].bytes[2].nibbles.low = buff[2];
        in[0].bytes[2].nibbles.high = buff[2] >> 4;
        in[0].bytes[3].nibbles.low = buff[3];
        in[0].bytes[3].nibbles.high = buff[3] >> 4;
        
        in[1].bytes[0].nibbles.low = buff[4];
        in[1].bytes[0].nibbles.high = buff[4] >> 4;
        in[1].bytes[1].nibbles.low = buff[5];
        in[1].bytes[1].nibbles.high = buff[5] >> 4;
        in[1].bytes[2].nibbles.low = buff[6];
        in[1].bytes[2].nibbles.high = buff[6] >> 4;
        in[1].bytes[3].nibbles.low = buff[7];
        in[1].bytes[3].nibbles.high = buff[7] >> 4;
        
        in[2].bytes[0].nibbles.low = buff[8];
        in[2].bytes[0].nibbles.high = buff[8] >> 4;
        in[2].bytes[1].nibbles.low = buff[9];
        in[2].bytes[1].nibbles.high = buff[9] >> 4;
        in[2].bytes[2].nibbles.low = buff[10];
        in[2].bytes[2].nibbles.high = buff[10] >> 4;
        in[2].bytes[3].nibbles.low = buff[11];
        in[2].bytes[3].nibbles.high = buff[11] >> 4;
        
        in[3].bytes[0].nibbles.low = buff[12];
        in[3].bytes[0].nibbles.high = buff[12] >> 4;
        in[3].bytes[1].nibbles.low = buff[13];
        in[3].bytes[1].nibbles.high = buff[13] >> 4;
        in[3].bytes[2].nibbles.low = buff[14];
        in[3].bytes[2].nibbles.high = buff[14] >> 4;
        in[3].bytes[3].nibbles.low = buff[15];
        in[3].bytes[3].nibbles.high = buff[15] >> 4;

        Encrypt(in, keyScheduling, output);
        
        out_buff[0] = output[0].bytes[0].nibbles.high << 4 | output[0].bytes[0].nibbles.low;
        out_buff[1] = output[0].bytes[1].nibbles.high << 4 | output[0].bytes[1].nibbles.low;
        out_buff[2] = output[0].bytes[2].nibbles.high << 4 | output[0].bytes[2].nibbles.low;
        out_buff[3] = output[0].bytes[3].nibbles.high << 4 | output[0].bytes[3].nibbles.low;
        
        out_buff[4] = output[1].bytes[0].nibbles.high << 4 | output[1].bytes[0].nibbles.low;
        out_buff[5] = output[1].bytes[1].nibbles.high << 4 | output[1].bytes[1].nibbles.low;
        out_buff[6] = output[1].bytes[2].nibbles.high << 4 | output[1].bytes[2].nibbles.low;
        out_buff[7] = output[1].bytes[3].nibbles.high << 4 | output[1].bytes[3].nibbles.low;
        
        out_buff[8] = output[2].bytes[0].nibbles.high << 4 | output[2].bytes[0].nibbles.low;
        out_buff[9] = output[2].bytes[1].nibbles.high << 4 | output[2].bytes[1].nibbles.low;
        out_buff[10] = output[2].bytes[2].nibbles.high << 4 | output[2].bytes[2].nibbles.low;
        out_buff[11] = output[2].bytes[3].nibbles.high << 4 | output[2].bytes[3].nibbles.low;
        
        out_buff[12] = output[3].bytes[0].nibbles.high << 4 | output[3].bytes[0].nibbles.low;
        out_buff[13] = output[3].bytes[1].nibbles.high << 4 | output[3].bytes[1].nibbles.low;
        out_buff[14] = output[3].bytes[2].nibbles.high << 4 | output[3].bytes[2].nibbles.low;
        out_buff[15] = output[3].bytes[3].nibbles.high << 4 | output[3].bytes[3].nibbles.low;
        
        fwrite(out_buff, 1, 16, oFile);
    }

    // PKCS7 Padding
    while (tempCounter < byteRead) {
        if (temp_j == 4) {
            temp_j = 0;
            temp_i++; } 
        in[temp_i].bytes[temp_j].nibbles.low = buff[tempCounter];
        in[temp_i].bytes[temp_j].nibbles.high = buff[tempCounter] >> 4;
        temp_j++;
        tempCounter++;
    }
    
    pad = 16 - byteRead;
    t_run = byteRead;
    
    while (t_run < 16) {
        in[t_run / 4].bytes[t_run % 4].nibbles.low = pad;
        in[t_run / 4].bytes[t_run % 4].nibbles.high = pad >> 4;
        t_run++;
    }
    
    Encrypt(in, keyScheduling, output);
    
    out_buff[0] = output[0].bytes[0].nibbles.high << 4 | output[0].bytes[0].nibbles.low;
    out_buff[1] = output[0].bytes[1].nibbles.high << 4 | output[0].bytes[1].nibbles.low;
    out_buff[2] = output[0].bytes[2].nibbles.high << 4 | output[0].bytes[2].nibbles.low;
    out_buff[3] = output[0].bytes[3].nibbles.high << 4 | output[0].bytes[3].nibbles.low;
    
    out_buff[4] = output[1].bytes[0].nibbles.high << 4 | output[1].bytes[0].nibbles.low;
    out_buff[5] = output[1].bytes[1].nibbles.high << 4 | output[1].bytes[1].nibbles.low;
    out_buff[6] = output[1].bytes[2].nibbles.high << 4 | output[1].bytes[2].nibbles.low;
    out_buff[7] = output[1].bytes[3].nibbles.high << 4 | output[1].bytes[3].nibbles.low;
    
    out_buff[8] = output[2].bytes[0].nibbles.high << 4 | output[2].bytes[0].nibbles.low;
    out_buff[9] = output[2].bytes[1].nibbles.high << 4 | output[2].bytes[1].nibbles.low;
    out_buff[10] = output[2].bytes[2].nibbles.high << 4 | output[2].bytes[2].nibbles.low;
    out_buff[11] = output[2].bytes[3].nibbles.high << 4 | output[2].bytes[3].nibbles.low;
    
    out_buff[12] = output[3].bytes[0].nibbles.high << 4 | output[3].bytes[0].nibbles.low;
    out_buff[13] = output[3].bytes[1].nibbles.high << 4 | output[3].bytes[1].nibbles.low;
    out_buff[14] = output[3].bytes[2].nibbles.high << 4 | output[3].bytes[2].nibbles.low;
    out_buff[15] = output[3].bytes[3].nibbles.high << 4 | output[3].bytes[3].nibbles.low;
    
    fwrite(out_buff, 1, 16, oFile);
}