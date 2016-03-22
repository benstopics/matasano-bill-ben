// encryption.h



unsigned char *HexToBase2(unsigned char *hex);

unsigned char *HexToBase64(unsigned char *hex);

unsigned char *Base2ToBase64(unsigned char *base2, size_t size);

unsigned char *EncodeHexString(unsigned char *buffer, size_t size);

unsigned char *XorEqualLengthBuffers(unsigned char *bufferA, unsigned char *bufferB, size_t size);

size_t GetHexSizeOfStr(unsigned char *str);

unsigned char shifter(unsigned char byte, int shift[]);

unsigned char *Base2ToHex(unsigned char datum);