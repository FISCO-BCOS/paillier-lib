/** @file callpaillier.h
 *  @author shawnhe
 *  @date 20190816
 */

#include "callpaillier.h"
#include "paillier.h"
#include <arpa/inet.h>
#include <cstring>

std::string CallPaillier::paillierAdd(const std::string& cipher1, const std::string& cipher2)
{
    std::string result;

    // check cipher, cipher = pkLen(4 bytes) + PK(pkLen bytes) +
    // ciphertext(2*pkLen bytes)
    if (cipher1.length() != cipher2.length() || cipher1.substr(0, 4) != cipher2.substr(0, 4))
    {
        throw CallException((char*)"add invalid ciphers");
    }

    // parse the length of public-key
    S32 bytelen = 0;
    U8 blen[4] = {0};
    CharToByte(cipher1.c_str(), 4, blen, &bytelen);
    U16 len = 0;
    memcpy((char*)&len, (char*)blen, sizeof(len));
    // nLen to be written into result
    U16 nLen = len;
    U32 pkLen = (ntohs(len) + 2) * 2 - 4;
    U32 cipherLen = 3 * pkLen + 4;

    if ((pkLen != 512 && pkLen != 1024) || cipher1.length() != cipherLen)
    {
        throw CallException((char*)"add invalid ciphers");
    }

    // Check whether the public-keys are the same
    std::string pk1 = cipher1.substr(4, pkLen);
    std::string pk2 = cipher2.substr(4, pkLen);
    if (pk1 != pk2)
    {
        throw CallException((char*)"add invalid ciphers");
    }

    // format paillier inputs for add
    std::string c1 = cipher1.substr(pkLen + 4);
    std::string c2 = cipher2.substr(pkLen + 4);
    S32 BN_Len = S32(pkLen / 2);
    U8* BN_PK = new U8[BN_Len + 1];
    U8* BN_C1 = new U8[2 * BN_Len + 1];
    U8* BN_C2 = new U8[2 * BN_Len + 1];
    U8* BN_Result = new U8[2 * BN_Len + 1];
    CharToByte(c1.c_str(), 2 * pkLen, BN_C1, &bytelen);
    CharToByte(c2.c_str(), 2 * pkLen, BN_C2, &bytelen);
    CharToByte(pk1.c_str(), pkLen, BN_PK, &bytelen);

    PAI_HomAdd(BN_Result, BN_C1, BN_C2, BN_PK, BN_Len / 4);

    // encode result
    U32 BN_CryptLen = cipherLen / 2;
    U8* BN_CryptResult = new U8[BN_CryptLen + 1];
    memcpy((char*)BN_CryptResult, (char*)&nLen, sizeof(nLen));
    memcpy((char*)(BN_CryptResult + sizeof(nLen)), BN_PK, BN_Len);
    memcpy((char*)(BN_CryptResult + sizeof(nLen) + BN_Len), BN_Result, 2 * BN_Len);
    for (size_t i = 0; i < BN_CryptLen; i++)
    {
        char tmp[3] = {0};
        sprintf(tmp, "%02X", BN_CryptResult[i]);
        result.append(tmp);
    }
    delete[] BN_PK;
    delete[] BN_C1;
    delete[] BN_C2;
    delete[] BN_Result;
    delete[] BN_CryptResult;
    return result;
}

std::vector<unsigned char> CallPaillier::paillierAdd(
    const std::vector<unsigned char>& cipher1, const std::vector<unsigned char>& cipher2)
{
    // check cipher, cipher = pkLen(4 bytes) + PK(pkLen bytes) +
    // ciphertext(2*pkLen bytes)
    if (cipher1.size() != cipher2.size())
    {
        throw CallException((char*)"add invalid ciphers");
    }

    // parse the length of public-key
    S32 bytelen = 0;
    U16 len = 0;
    // memcpy((char *)&len, (char *)cipher1.data(), sizeof(len));
    std::copy(cipher1.begin(), cipher1.begin() + sizeof(len), (char*)&len);

    // nLen to be written into result
    U16 nLen = ntohs(len);
    U16 pkLen = nLen;

    // Check whether the public-keys are the same
    //   if (std::memcmp(cipher1.data() + 2, cipher2.data() + 2, pkLen) != 0) {
    //     throw CallException((char *)"add invalid ciphers");
    //   }

    // format paillier inputs for add
    S32 BN_Len = S32(pkLen);
    U8* BN_PK = new U8[BN_Len + 1];
    U8* BN_C1 = new U8[2 * BN_Len + 1];
    U8* BN_C2 = new U8[2 * BN_Len + 1];
    U8* BN_Result = new U8[2 * BN_Len + 1];

    std::copy(cipher1.begin() + 2, cipher1.begin() + 2 + pkLen, BN_PK);
    std::copy(cipher1.begin() + 2 + pkLen, cipher1.end(), BN_C1);
    std::copy(cipher2.begin() + 2 + pkLen, cipher2.end(), BN_C2);

    PAI_HomAdd(BN_Result, BN_C1, BN_C2, BN_PK, BN_Len / 4);

    // encode result
    U32 BN_CryptLen = cipher1.size();
    U8* BN_CryptResult = new U8[BN_CryptLen + 1];
    memcpy((char*)BN_CryptResult, (char*)&len, sizeof(nLen));
    memcpy((char*)(BN_CryptResult + sizeof(nLen)), BN_PK, BN_Len);
    memcpy((char*)(BN_CryptResult + sizeof(nLen) + BN_Len), BN_Result, 2 * BN_Len);

    std::vector<unsigned char> result(BN_CryptResult, BN_CryptResult + BN_CryptLen);

    //   for (size_t i = 0; i < BN_CryptLen; i++) {
    //     char tmp[3] = {0};
    //     sprintf(tmp, "%02X", BN_CryptResult[i]);
    //     result.append(tmp);
    //     //   }

    delete[] BN_PK;
    delete[] BN_C1;
    delete[] BN_C2;
    delete[] BN_Result;
    delete[] BN_CryptResult;
    return result;
}