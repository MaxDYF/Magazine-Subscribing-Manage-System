//
// Created by 邓逸飞 on 24-12-23.
//

#include "Subscriber.h"

Subscriber_Info::Subscriber_Info() {
    this->uid = -1; // -1表示空用户
}
Subscriber_Info::Subscriber_Info(const std::string& name, const std::string& gender, const std::string& phoneNumber, const std::string &address, int uid = -1) {
    this->name = name;
    this->gender = gender;
    this->phoneNumber = phoneNumber;
    this->uid = uid;
    this->address = address;
}
Subscriber::Subscriber() : Subscriber_Info(){
}
Subscriber::Subscriber(const std::string& name, const std::string& gender, const std::string& phoneNumber, const std::string &address, int uid = -1) : Subscriber_Info(name, gender, phoneNumber, address, uid){
}


std::vector<Subscription> Subscriber::getSubscription() {
    return this->subscription;
}
void Subscriber::addSubscription(const Subscription& subscription) {
    this->subscription.push_back(subscription);
}

void Subscriber::removeSubscription(int subscription_id) {
    for (auto it = subscription.begin(); it != subscription.end();) {
        if (it->getSubscriber_Uid() == subscription_id) {
            subscription.erase(it++);
        } else ++it;
    }
}

Subscriber_Info Subscriber_Info::getInfo() const {
    return *this;
}




nlohmann::json Subscriber_Info::jsonify() const {
    nlohmann::json json;
    json["name"] = this->name;
    json["gender"] = this->gender;
    json["phoneNumber"] = this->phoneNumber;
    json["uid"] = this->uid;
    json["address"] = this->address;
return json;
}
void Subscriber_Info::parseJson(const nlohmann::json& json) {
    if (json.contains("uid") == false)
        throw std::invalid_argument("Subscriber_Info::parseJson: uid does not exist");
    if (json.contains("name") == false)
        throw std::invalid_argument("Subscriber_Info::parseJson: name does not exist");
    if (json.contains("gender") == false)
        throw std::invalid_argument("Subscriber_Info::parseJson: gender does not exist");
    if (json.contains("phoneNumber") == false)
        throw std::invalid_argument("Subscriber_Info::parseJson: phoneNumber does not exist");
    if (json.contains("address") == false)
        throw std::invalid_argument("Subscriber_Info::parseJson: address does not exist");
    this->uid = json["uid"].get<int>();
    this->name = json["name"].get<std::string>();
    this->gender = json["gender"].get<std::string>();
    this->phoneNumber = json["phoneNumber"].get<std::string>();
    this->address = json["address"].get<std::string>();
}
void Subscriber_Info::setGender(const std::string &gender) {
    this->gender = gender;
}
void Subscriber_Info::setPhoneNumber(const std::string &phoneNumber) {
    this->phoneNumber = phoneNumber;
}
void Subscriber_Info::setName(const std::string &name) {
    this->name = name;
}
void Subscriber_Info::setUid(int uid) {
    this->uid = uid;
}
void Subscriber_Info::setAddress(const std::string &address) {
    this->address = address;
}


std::string Subscriber_Info::getAddress() const {
    return this->address;
}
std::string Subscriber_Info::getGender() const {
    return this->gender;
}
std::string Subscriber_Info::getPhoneNumber() const {
    return this->phoneNumber;
}
int Subscriber_Info::getUid() const {
    return this->uid;
}
std::string Subscriber_Info::getName() const {
    return this->name;
}


bool operator==(const Subscriber_Info& lhs, const Subscriber_Info& rhs) {
    return lhs.uid == rhs.uid;
}