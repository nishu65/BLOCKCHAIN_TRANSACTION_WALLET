#include "wallet.h"
#include <iostream>
#include <vector>

wallet::wallet() {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, nullptr);
    if (!ctx) {
        std::cerr << "Error initializing EVP key context" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        std::cerr << "Error initializing key generation" << std::endl;
        EVP_PKEY_CTX_free(ctx);
        exit(EXIT_FAILURE);
    }
    if (EVP_PKEY_CTX_set_ec_paramgen_curve_nid(ctx, NID_secp256k1) <= 0) {
        std::cerr << "Error initializing curve NID" << std::endl;
        EVP_PKEY_CTX_free(ctx);
        exit(EXIT_FAILURE);
    }
    if (EVP_PKEY_generate(ctx, &key) <= 0) {
        std::cerr << "Error generating EC key" << std::endl;
        EVP_PKEY_CTX_free(ctx);
        exit(EXIT_FAILURE);
    }

    BIO* bio = BIO_new(BIO_s_mem());
    if (!bio) {
        std::cerr << "Error creating BIO" << std::endl;
        EVP_PKEY_CTX_free(ctx);
        exit(EXIT_FAILURE);
    }
    if (!PEM_write_bio_PUBKEY(bio, key)) {
        std::cerr << "Error writing public key to BIO" << std::endl;
        BIO_free(bio);
        EVP_PKEY_CTX_free(ctx);
        exit(EXIT_FAILURE);
    }
    char* pubkey_buffer;
    size_t len = BIO_get_mem_data(bio, &pubkey_buffer);
    publickey = std::string(pubkey_buffer, len);
    BIO_free(bio);
    EVP_PKEY_CTX_free(ctx);
}

std::string wallet::sign_transaction(const std::string& data) {
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        std::cerr << "Error creating message digest context" << std::endl;
        return "";
    }
    if (EVP_DigestSignInit(mdctx, nullptr, EVP_sha256(), nullptr, key) <= 0) {
        std::cerr << "Error initializing digest sign" << std::endl;
        EVP_MD_CTX_free(mdctx);
        return "";
    }
    if (EVP_DigestSignUpdate(mdctx, data.c_str(), data.length()) <= 0) {
        std::cerr << "Error updating digest sign" << std::endl;
        EVP_MD_CTX_free(mdctx);
        return "";
    }
    size_t siglen = 0;
    if (EVP_DigestSignFinal(mdctx, nullptr, &siglen) <= 0) {
        std::cerr << "Error finalizing digest sign (getting length)" << std::endl;
        EVP_MD_CTX_free(mdctx);
        return "";
    }
    std::vector<unsigned char> signature(siglen);
    if (EVP_DigestSignFinal(mdctx, signature.data(), &siglen) <= 0) {
        std::cerr << "Error finalizing digest sign" << std::endl;
        EVP_MD_CTX_free(mdctx);
        return "";
    }
    EVP_MD_CTX_free(mdctx);
    return std::string(signature.begin(), signature.end());
}
bool wallet::verify_signature(const std::string& data, const std::string& signature) {
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        std::cerr << "error creating md context for verify\n";
        return false;
    }
    if (EVP_DigestVerifyInit(mdctx,nullptr,EVP_sha256(),nullptr,key)<=0) {
        std::cerr << "error initialize digestverify\n";
        return false;
    }
    if (EVP_DigestVerifyUpdate(mdctx,data.c_str(),data.length())<=0) {
        std::cerr << "error updating digestverify\n";
        return false;
    }
    bool verified = EVP_DigestVerifyFinal(mdctx, (const unsigned char*)signature.data(), signature.length()) == 1;
    EVP_MD_CTX_free(mdctx);
    return verified;
}
wallet::~wallet() {
    EVP_PKEY_free(key);
}
