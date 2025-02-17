#pragma once

#include<vector>
#include"block.h"
class blockchain {
public:
	std::vector<block>chain;
	blockchain();
	block create_genesis_block();
	block get_last_block();
	void add_block(std::vector<transaction>txns);
	void display_blockchain();
};
