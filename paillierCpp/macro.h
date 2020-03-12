/* 
This code is from an open source platform BCOS, URL:https://github.com/bcosorg/bcos/tree/master/libpaillier
*/

#ifndef __HEADER_MACRO_H__
#define __HEADER_MACRO_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define WRONG 0
#define RIGHT 1

//macro for common bn
#define WordLen 32
#define ByteLen 8
#define WordByteLen (WordLen / ByteLen)
#define LSBOfWord 0x00000001
#define MSBOfWord 0x80000000
#define Plus 0x00000000
#define Minus 0x00000001

//macro for BN in paillier
#define BNMAXWordLen 2058

#ifdef __cplusplus
}
#endif

#endif
