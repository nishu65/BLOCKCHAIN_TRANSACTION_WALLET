#include"transaction.h"
transaction::transaction(std::string s, std::string r, double amt) {
	sender = s;
	receiver = r;
	amount = amt;
	signature = "";

}
std::string transaction::get_transaction_data() {
	std::stringstream ss;
	ss << sender << receiver << amount;
	return ss.str();
}