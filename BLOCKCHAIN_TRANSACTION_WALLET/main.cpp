#include "blockchain.h"
#include"wallet.h"
int main() {
	std::cout << "initialing  blockchain\n";
	blockchain myblochain;
	std::cout << "initialing  wallet\n";
	wallet nk, vk;
	std::cout << "creating transactions\n";
	transaction txn1(nk.publickey, vk.publickey, 5.5);
	txn1.signature = nk.sign_transaction(txn1.get_transaction_data());
	transaction txn2(vk.publickey, nk.publickey, 10.5);
	txn2.signature = vk.sign_transaction(txn2.get_transaction_data());
	std::cout << "MINING BLOCK 1......\n";
	myblochain.add_block({ txn1,txn2 });
	std::cout << "MINING BLOCK 2........\n";
	myblochain.add_block({ transaction(nk.publickey,vk.publickey,6.6) });
	std::cout << "\nBLOCKCHAIN:\n";
	myblochain.display_blockchain();
	std::cout << "nk public key " << nk.publickey << std::endl;
	
	return 0;
}