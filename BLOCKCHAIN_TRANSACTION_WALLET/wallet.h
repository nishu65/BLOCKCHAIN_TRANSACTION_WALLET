#pragma once

#include<openssl/evp.h>
#include<openssl/pem.h>
#include<string>
class wallet {
public:
	EVP_PKEY* key;
	std::string publickey;
	wallet();
	std::string sign_transaction(const std::string& data);
	bool verify_signature(const std::string &data,const std::string &signature );
	~wallet();
};

