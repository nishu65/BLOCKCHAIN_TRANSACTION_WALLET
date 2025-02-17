#pragma once

#include <iostream>
#include<sstream>
#include<string>
class transaction {
public:
	std::string sender;
	std::string receiver;
	double amount;
	std::string signature;

	transaction(std::string s, std::string r, double amt);
	std::string get_transaction_data();
};

