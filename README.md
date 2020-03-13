# paillier-lib

![](https://github.com/FISCO-BCOS/FISCO-BCOS/raw/master/docs/images/FISCO_BCOS_Logo.svg?sanitize=true)



[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](http://makeapullrequest.com)
[![GitHub issues](https://img.shields.io/github/issues/FISCO-BCOS/paillier-lib.svg)](https://github.com/FISCO-BCOS/paillier-lib/issues)
![GitHub All Releases](https://img.shields.io/github/downloads/FISCO-BCOS/paillier-lib/total.svg)
[![GitHub license](https://img.shields.io/github/license/FISCO-BCOS/paillier-lib.svg)](https://github.com/FISCO-BCOS/paillier-lib/blob/master/LICENSE)

paillier同态加密算法库，具体包括：

1. java库：实现了完整的paillier同态库，可完成加解密和同态加运算。

2. cpp接口：提供同态加接口，核心算法由c语言实现，并用c++实现了调用协议的封装。

[FISCO BCOS](https://github.com/FISCO-BCOS/FISCO-BCOS/tree/master)隐私模块中同态加密的预编译合约便是调用此cpp同态接口。java同态库和cpp同态接口的密文封装协议是一致的， 即通过java同态库生成的密文可以直接调用cpp同态接口完成加同态运算，生成的同态密文可以调用java同态库解密。

## 关键特性

- 公私钥对生成和编解码
- 基于RSA的数据加解密接口
- 密文的paillier加法同态运算
- java库提供了完整的同态功能支持，cpp接口为链上预编译合约提供密文加同态支持

## Java库说明

### 公私钥模块（PaillierKeyPair）

- 接口名称：generateGoodKeyPair
- 接口功能说明：生成同态加密的公私钥对，2048位

| 输入参数     | 参数类型     | 参数说明                                   |
| :----------- | :----------- | :----------------------------------------- |
| 无    |           |             |
| **输出参数** | **参数类型** | **参数说明**                               |
| 返回值       | KeyPair      | 生成的密钥对 （其他 ：成功    null：失败） |

- 接口名称：generateStrongKeyPair
- 接口功能说明：生成同态加密的公私钥对，4096位

| 输入参数     | 参数类型     | 参数说明                                   |
| :----------- | :----------- | :----------------------------------------- |
| 无    |           |             |
| **输出参数** | **参数类型** | **参数说明**                               |
| 返回值       | KeyPair      | 生成的密钥对 （其他 ：成功    null：失败） |


### 同态算法模块（PaillierCipher）

- 接口名称：encryption
- 接口功能说明：对数据进行同态加密

| 输入参数     | 参数类型     | 参数说明                         |
| :----------- | :----------- | :------------------------------- |
| m            | BigInteger   | 待加密的操作数                   |
| publickey    | PublicKey    | 加密公钥，可以通过公私钥模块获取 |
| **输出参数** | **参数类型** | **参数说明**                     |
| 返回值       | String       | 成功：密文    失败：空串         |

- 接口名称：decryption
- 接口功能说明：对加密数据进行解密还原操作数

| 输入参数     | 参数类型     | 参数说明                         |
| :----------- | :----------- | :------------------------------- |
| ciphertext   | String       | 密文                             |
| privateKey   | PrivateKey   | 解密私钥，可以通过公私钥模块获取 |
| **输出参数** | **参数类型** | **参数说明**                     |
| 返回值       | BigInteger   | 成功：明文    失败：空串         |

- 接口名称：ciphertextAdd
- 接口功能说明：加法同态实现

| 输入参数     | 参数类型     | 参数说明                           |
| :----------- | :----------- | :--------------------------------- |
| ciphertext1  | String       | 同态加密后的操作数1                |
| ciphertext2  | String       | 同态加密后的操作数2                |
| **输出参数** | **参数类型** | **参数说明**                       |
| 返回值       | String       | 成功：同态加法的密文    失败：空串 |

### 使用教程

**生成jar包**

生成的jar文件位于paillierJava/dist目录
```bash
# 下载
git clone https://github.com/FISCO-BCOS/paillier-lib.git
# 编译
cd paillier-lib/paillierJava && gradle build
```

**开发示例**

```java
// generate the key pair for encrypt and decrypt
KeyPair keypair = PaillierKeyPair.generateGoodKeyPair();
RSAPublicKey pubKey = (RSAPublicKey)keypair.getPublic();
RSAPrivateKey priKey = (RSAPrivateKey)keypair.getPrivate();

// encrypt the first number with public key
BigInteger i1 = BigInteger.valueOf(1000000);
String c1 = PaillierCipher.encryption(i1, pubKey);

// encrypt the second number with same public key
BigInteger i2 = BigInteger.valueOf(2012012012);
String c2 = PaillierCipher.encryption(i2, pubKey);

// paillier add with numbers
String c3 = PaillierCipher.ciphertextAdd(c1,c2);

// decrypt the result
BigInteger o3 = PaillierCipher.decryption(c3, priKey);
```

## Cpp接口说明

### 密文同态加接口

- 接口名称：paillierAdd
- 接口功能说明：加法同态接口

| 输入参数     | 参数类型     | 参数说明                           |
| :----------- | :----------- | :--------------------------------- |
| cipher1      | string       | 同态加密后的操作数1                |
| cipher2      | string       | 同态加密后的操作数2                |
| **输出参数** | **参数类型** | **参数说明**                       |
| 返回值       | string       | 成功：同态加法的密文    失败：空串 |

### 编译运行

```bash
# 假设当前在paillier-lib目录
mkdir build && cd build
# CentOS请使用cmake3
cmake ..
# 编译paillierCpp库以及测试代码
make
# 运行测试代码
./testAdd
```
## 贡献代码

- 我们欢迎并非常感谢您的贡献，请参阅[代码贡献流程](CONTRIBUTING.md)。
- 如项目对您有帮助，欢迎star支持！

## 加入社区

**FISCO BCOS开源社区**是国内活跃的开源社区，社区长期为机构和个人开发者提供各类支持与帮助。已有来自各行业的数千名技术爱好者在研究和使用FISCO BCOS。如您对FISCO BCOS开源技术及应用感兴趣，欢迎加入社区获得更多支持与帮助。

![](https://raw.githubusercontent.com/FISCO-BCOS/LargeFiles/master/images/QR_image.png)

## License

![license](https://img.shields.io/badge/license-Apache%20v2-blue.svg)

Paillier的开源协议为[APACHE LICENSE 2.0](http://www.apache.org/licenses/). 详情参考[LICENSE](./LICENSE)。
