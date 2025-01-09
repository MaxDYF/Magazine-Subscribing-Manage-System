//
// Created by 邓逸飞 on 2024/12/23.
//

#include "Magazine.h"
Magazine_Info::Magazine_Info() {
    this->name = "";
    this->id = -1;
    this->price = 0;
}
Magazine_Info::Magazine_Info(const std::string &name, int price, int id) {
    this->name = name;
    this->id = id;
    this->price = price;
}

std::string Magazine_Info::getName() const {
    return this->name;
}
Magazine::Magazine() : Magazine_Info() {
}
Magazine::Magazine(const Magazine_Info &magazine_info) : Magazine_Info(magazine_info) {
}
void Magazine::addSubscriber(const Subscription &subscription) {
    this->subscriptions.push_back(subscription);
}
void Magazine::removeSubscriber(int subscription_id) {
    for (auto it = this->subscriptions.begin(); it != this->subscriptions.end(); ++it) {
        if (it->getMagazine_id() == subscription_id) {
            this->subscriptions.erase(it);
            break;
        }
    }
}
std::vector<Subscription> Magazine::get_subscriptions() const {
    return this->subscriptions;
}
nlohmann::json Magazine_Info::jsonify() const {
    nlohmann::json json;
    json["name"] = this->name;
    json["id"] = this->id;
    json["price"] = this->price;
    return json;
}
int Magazine_Info::getId() const {
    return this->id;
}
int Magazine_Info::getPrice() const {
    return this->price;
}
void Magazine_Info::parseJson(const nlohmann::json &json) {
    if (json.contains("name") == false)
        throw std::invalid_argument("Magazine_Info::parseJson: name not found.");
    if (json.contains("id") == false)
        throw std::invalid_argument("Magazine_Info::parseJson: id not found.");
    if (json.contains("price") == false)
        throw std::invalid_argument("Magazine_Info::parseJson: price not found.");
    this->name = json["name"].get<std::string>();
    this->id = json["id"].get<int>();
    this->price = json["price"].get<int>();
}


void Magazine_Info::setId(int id) {
    this->id = id;
}
void Magazine_Info::setPrice(int price) {
    this->price = price;
}
void Magazine_Info::setName(const std::string &name) {
    this->name = name;
}
Magazine_Info Magazine_Info::getInfo() const {
    return *this;
}
bool operator==(const Magazine_Info &a, const Magazine_Info &b) {
    return a.id == b.id;
}





