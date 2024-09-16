==================== readme  ====================
To Run the AES Program, proceed as follows :

    1) Open the main.c
    2) Enter the key in Hex String Format (128-bit)
    3) In line #85 enter the Input file (By Default : hi.txt)
    4) Output File can be found in the Same Directory (By Default : encrypt.bin)
    5) For Verification the Same Encrypted File is Decrypted (By Default : decrypt.bin)
    6) To Select the Modes of Operation, Uncomment the lines for ENC (92 - 95) & DEC (113 - 116)
    
    USAGE : 

==================== E C B ====================
To perform ECB Mode : Uncomment these Lines
EcbEnc(keyScheduling, iFile, oFile);
EcbDec(keyScheduling, iFile, oFile);

And Compile using this Command
gcc -o aes main.c run/prog/utils.c run/prog/algo.c run/prog/enc_dec.c modes/prog/enc/ecb_enc.c modes/prog/dec/ecb_dec.c

==================== C B C ====================
To perform CBC Mode : Uncomment these Lines
CbcEnc(input_2, keyScheduling, iFile, oFile);
CbcDec(input_2, keyScheduling, iFile, oFile);

And Compile using this Command
gcc -o aes main.c run/prog/utils.c run/prog/algo.c run/prog/enc_dec.c modes/prog/enc/cbc_enc.c modes/prog/dec/cbc_dec.c

==================== O F B ====================
To perform OFB Mode : Uncomment these Lines
OfbEnc(input_2, keyScheduling, iFile, oFile);
OfbDec(input_2, keyScheduling, iFile, oFile);

And Compile using this Command
gcc -o aes main.c run/prog/utils.c run/prog/algo.c run/prog/enc_dec.c modes/prog/enc/ofb_enc.c modes/prog/dec/ofb_dec.c

==================== C F B ====================
To perform CFB Mode : Uncomment these Lines
CfbEnc(input_2, keyScheduling, iFile, oFile);
CfbDec(input_2, keyScheduling, iFile, oFile);

And Compile using this Command
gcc -o aes main.c run/prog/utils.c run/prog/algo.c run/prog/enc_dec.c modes/prog/enc/cfb_enc.c modes/prog/dec/cfb_dec.c

==================== E N D ====================
