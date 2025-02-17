#pragma once

#include<vector>
#include<chrono>
#include<string>
#include"transaction.h"

class block {
public:
	int index;
	std::vector<transaction>txncs;
	std::string data;
	std::string previous_hash;
	time_t timestamp;
	int  nonce;
	std::string hash;
	block(int  idx, std::vector<transaction>txnc, std::string prev_hash);
		std::string calculate_hash();
		std::string mine_block(int difficulty);
	
};
