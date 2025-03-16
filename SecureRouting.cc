#include <omnetpp.h>
#include <iostream>
#include <string>
#include <openssl/sha.h>

using namespace omnetpp;

class SecureRouting : public cSimpleModule {
private:
    std::string hashMessage(const std::string& message);

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(SecureRouting);

void SecureRouting::initialize() {
    EV << "Secure Routing Protocol Initialized.\n";
}

void SecureRouting::handleMessage(cMessage *msg) {
    std::string originalMsg = msg->getName();
    std::string hashedMsg = hashMessage(originalMsg);

    EV << "Received message: " << originalMsg << "\n";
    EV << "Hashed message: " << hashedMsg << "\n";

    delete msg;
}

std::string SecureRouting::hashMessage(const std::string& message) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(message.c_str()), message.length(), hash);

    std::string hashedMsg;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        char buffer[3];
        sprintf(buffer, "%02x", hash[i]);
        hashedMsg += buffer;
    }
    return hashedMsg;
}
