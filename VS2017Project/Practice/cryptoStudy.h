#pragma once
#include <iostream>
#include <stdlib.h>
#include <aes.h>
#include <randpool.h>
#include <rsa.h>
#include <hex.h>
#include <files.h>
#include <md5.h>
#include <cryptlib.h>
using namespace std;
using namespace CryptoPP;
class CrypStudy {
private:
	//生成RSA的非对称秘钥
	void GenerateRSAKey(unsigned int keyLength, const char *privFilename, const char *pubFilename, const char *seed)
	{
		RandomPool randPool;
		randPool.IncorporateEntropy((byte *)seed, strlen(seed)); //
		RSAES_OAEP_SHA_Decryptor priv(randPool, keyLength);
		HexEncoder privFile(new FileSink(privFilename));
		priv.AccessMaterial().Save(privFile);
		privFile.MessageEnd();

		RSAES_OAEP_SHA_Encryptor pub(priv);
		HexEncoder pubFile(new FileSink(pubFilename));
		pub.AccessMaterial().Save(pubFile);
		pubFile.MessageEnd();
	}
	//加密
	string RSAEncryptString(const char *pubFilename, const char *seed, const char *message)
	{
		FileSource pubFile(pubFilename, true, new HexDecoder);
		RSAES_OAEP_SHA_Encryptor pub(pubFile);

		RandomPool randPool;
		randPool.IncorporateEntropy((byte *)seed, strlen(seed));

		std::string result;
		StringSource(message, true, new PK_EncryptorFilter(randPool, pub, new HexEncoder(new StringSink(result))));
		return result;
	}
	//解密
	string RSADecryptString(const char *privFilename, const char *ciphertext)
	{
		FileSource privFile(privFilename, true, new HexDecoder);
		RSAES_OAEP_SHA_Decryptor priv(privFile);

		std::string result;
		StringSource(ciphertext, true, new HexDecoder(new PK_DecryptorFilter(GlobalRNG(), priv, new StringSink(result))));
		return result;
	}
	RandomPool & GlobalRNG()
	{
		static RandomPool randomPool;
		return randomPool;
	}
public:
	void HelloCryptopp()
	{

		cout << "AES block size is " << AES::BLOCKSIZE << endl;
		cout << "hello cryptopp, includes is corrected" << endl;

	}
	

	void RSAExample()
	{
		char priKey[128] = { 0 };
		char pubKey[128] = { 0 };
		char seed[1024] = { 0 };
		strcpy_s(priKey, "pri");
		strcpy_s(pubKey, "pub");
		strcpy(seed, "seed");
		GenerateRSAKey(1024, priKey, pubKey, seed);
		char message[1024] = { 0 };
		cout << "原始内容：" << "Helloworld" << endl;
		strcpy(message, "Helloworld");
		string encryptedText = RSAEncryptString(pubKey, seed, message);
		cout << "RSA加密：" << encryptedText << endl;
		string decryptedText = RSADecryptString(priKey,encryptedText.c_str());
		cout << "Decrypted Text" << decryptedText << endl;

	}

	void MD5Example()
	{
		//https://www.cryptopp.com/wiki/MD5
		HexEncoder encoder(new FileSink(std::cout));

		std::string msg = "Yoda said, Do or do not. There is no try.";
		std::string digest;

		Weak1::MD5 hash;
		hash.Update((const byte*)msg.data(), msg.size());
		digest.resize(hash.DigestSize());
		hash.Final((byte*)&digest[0]);

		std::cout << "Message: " << msg << std::endl;

		std::cout << "Digest: ";
		StringSource(digest, true, new Redirector(encoder));
		std::cout << std::endl;
	}

};

