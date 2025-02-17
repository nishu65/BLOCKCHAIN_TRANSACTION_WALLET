#include"block.h"
#include<sstream>
#include<openssl/sha.h>
#include<iomanip>
std::string sha256(const std::string str) {
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256((const unsigned char*)str.c_str(), str.length(), hash);
	std::stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
	}
	return ss.str();
}
block::block(int idx, std::vector<transaction> txn, std::string prev_hash) {
	index = idx;
	txncs = txn;
	previous_hash = prev_hash;
	auto now = std::chrono::system_clock::now();
	timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
	nonce = 0;
	hash = mine_block(2);


}
std::string block::calculate_hash() {
	std::stringstream ss;
	ss << index << timestamp << previous_hash << nonce;
	for (transaction txn : txncs) {
		ss << txn.get_transaction_data();
	}
	return sha256(ss.str());
	

}
std::string block::mine_block(int difficulty) {
	std::string target(difficulty, '0');
	std::cout << "minig block difficulty:"<<difficulty<<std::endl;
	do {
		nonce++;
		hash = calculate_hash();
	} while (hash.substr(0, difficulty) != target);
	std::cout << "block mined 1 hash:"<<hash<<std::endl;
	return hash;
}