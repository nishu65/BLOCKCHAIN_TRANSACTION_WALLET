#include"blockchain.h"
#include<iostream>
blockchain::blockchain() {
	chain.push_back(create_genesis_block());
}
block blockchain::create_genesis_block() {
	return block(0, {}, "0");

}
block blockchain::get_last_block() {
	return chain.back();
}
void blockchain::add_block(std::vector<transaction>txns) {
	if (txns.empty()) {
		std::cerr<<"empty block not added\n";
	}
	block prevblock= get_last_block();
	block newblock(chain.size(), txns, prevblock.hash);
	chain.push_back(newblock);
}
void blockchain::display_blockchain() {

	for (auto blocks : chain) {
		auto timepoint = std::chrono::system_clock::from_time_t(blocks.timestamp);
		time_t tt = std::chrono::system_clock::to_time_t(timepoint);
		std::cout << "Block :" << blocks.index << std::endl;
		for (auto txn : blocks.txncs) {
			std::cout << " " << txn.sender << "->" << txn.receiver<< ":" << txn.amount<<"btc\n";
		}
		std::cout << " PREVIOUS HASH :" << blocks.previous_hash << std::endl;
		std::cout << "HASH :" << blocks.hash<< std::endl;
		std::cout << "TIMESTAMP :" << blocks.timestamp << std::endl;
		std::cout << "NONCE :" << blocks.nonce << std::endl;
		std::cout << "------------------------------------------------------------------------>\n";
	}
}