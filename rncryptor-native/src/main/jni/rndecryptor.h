#ifndef RNDECRYPTOR_H
#define RNDECRYPTOR_H

#include "rncryptor.h"

#include <iostream>
using std::string;

class RNDecryptor : public RNCryptor {

	RNCryptorPayloadComponents unpackEncryptedData(string encryptedData);
	bool hmacIsValid(RNCryptorPayloadComponents components, string password);

	public:
		string decrypt(string encryptedData, string password);
};

#endif
