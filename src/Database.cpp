//
// Created by 邓逸飞 on 24-12-23.
//

#include "Database.h"
#include <iostream>
#include <fstream>

Database::Database() {
    this->magazine_user_count = 0;
    this->subscriber_user_count = 0;
    this->subscription_count = 0;
    magazines[-1] = Magazine();
    subscribers[-1] = Subscriber();
    subscriptions[-1] = Subscription();
}


int Database::getNewMagazineId() {
    return ++this->magazine_user_count;
}
int Database::getNewSubscriberId() {
    return ++this->subscriber_user_count;
}
int Database::getNewSubscriptionId() {
    return ++this->subscription_count;
}

Magazine& Database::getMagazine(int magazine_id) {
    Magazine empty;
    if (magazines.contains(magazine_id))
        return magazines[magazine_id];
    else
        return magazines[-1];
}

Subscriber& Database::getSubscriber(int subscriber_uid) {
    if (subscribers.contains(subscriber_uid))
        return subscribers[subscriber_uid];
    else
        return subscribers[-1];
}
Subscription& Database::getSubscription(int subscriber_uid) {
    if (subscribers.contains(subscriber_uid))
        return subscriptions[subscriber_uid];
    else
        return subscriptions[-1];
}

void Database::removeMagazine(int magazine_id) {
    if (magazines.contains(magazine_id))
        magazines.erase(magazine_id);
}
void Database::removeSubscriber(int subscriber_uid) {
    if (subscribers.contains(subscriber_uid))
        subscribers.erase(subscriber_uid);
}
void Database::removeSubscription(int subscription_id) {
    if (subscriptions.contains(subscription_id)) {
        int subscriber_uid = subscriptions[subscription_id].getSubscriber_Uid();
        int magazine_id = subscriptions[subscription_id].getMagazine_id();
        magazines[magazine_id].removeSubscriber(subscriber_uid);
        subscribers[subscriber_uid].removeSubscription(magazine_id);
        subscriptions.erase(subscriber_uid);
    }
}
int Database::addMagazine(Magazine magazine) {
    int magazine_id = this->getNewMagazineId();
    magazine.setId(magazine_id);
    magazines[magazine_id] = magazine;
    return magazine_id;
}
int Database::addSubscriber(Subscriber subscriber) {
    int new_subscriber_id = this->getNewSubscriberId();
    subscriber.setUid(new_subscriber_id);
    subscribers[new_subscriber_id] = subscriber;
    return new_subscriber_id;
}
int Database::addSubscription(Subscription subscription) {
    int new_subscription_id = this->getNewSubscriptionId();
    subscription.setSubscriptionId(new_subscription_id);
    subscriptions[new_subscription_id] = subscription;
    magazines[subscription.getMagazine_id()].addSubscriber(subscription);
    subscribers[subscription.getSubscriber_Uid()].addSubscription(subscription);
    return new_subscription_id;
}

nlohmann::json Database::jsonify() const {
    nlohmann::json json;
    json["magazines"] = nlohmann::json();
    json["magazine_user_count"] = magazine_user_count;
    json["subscriber_user_count"] = subscriber_user_count;
    json["subscription_count"] = subscription_count;
    for (const auto &[key, magazine] : magazines) {
        if (key != -1)
            json["magazines"][std::to_string(key)] = magazine.jsonify();
    }
    json["subscribers"] = nlohmann::json();
    for (const auto &[key, subscriber] : subscribers) {
        if (key != -1)
            json["subscribers"][std::to_string(key)] = subscriber.jsonify();
    }
    json["subscriptions"] = nlohmann::json();
    for (const auto &[key, subscription] : subscriptions) {
        if (key != -1)
            json["subscriptions"][std::to_string(key)] = subscription.jsonify();
    }
    return json;
}

void Database::parseJson(nlohmann::json json) {
    this->magazine_user_count = json["magazine_user_count"].get<int>();
    this->subscriber_user_count = json["subscriber_user_count"].get<int>();
    this->subscription_count = json["subscription_count"].get<int>();
    this->magazines.clear();
    this->subscribers.clear();
    this->subscriptions.clear();
    magazines[-1] = Magazine();
    subscribers[-1] = Subscriber();
    subscriptions[-1] = Subscription();
    for (const auto &item : json["magazines"].items()) {
        Magazine magazine;
        magazine.parseJson(item.value().get<nlohmann::json>());
        this->magazines[std::stoi(item.key())] = std::move(magazine);
    }
    for (const auto &item : json["subscribers"].items()) {
        Subscriber subscriber;
        subscriber.parseJson(item.value().get<nlohmann::json>());
        this->subscribers[std::stoi(item.key())] = std::move(subscriber);
    }
    for (const auto &item : json["subscriptions"].items()) {
        Subscription subscription;
        subscription.parseJson(item.value().get<nlohmann::json>());
        this->subscriptions[std::stoi(item.key())] = subscription;
        int magazine_id = subscription.getMagazine_id();
        int subscriber_uid = subscription.getSubscriber_Uid();
        this->magazines[magazine_id].addSubscriber(subscription);
        this->subscribers[subscriber_uid].addSubscription(subscription);
    }
}

std::vector<Subscriber_Info> Database::getSubscribers(const std::string &name = "", const std::string &gender = "", const std::string &phoneNumber = "", const std::string &address = "") {
    std::vector<Subscriber_Info> subscribers;
    for (const auto &[key, subscriber] : this->subscribers) {
        if (key != -1)
            if (name.empty() || name == subscriber.getName())
                if (gender.empty() || gender == subscriber.getGender())
                    if (phoneNumber.empty() || phoneNumber == subscriber.getPhoneNumber())
                        if (address.empty() || address == subscriber.getAddress())
                            subscribers.push_back(subscriber);
    }
    sort(subscribers.begin(), subscribers.end(), [](const Subscriber_Info &a, const Subscriber_Info &b) {return a.getUid() < b.getUid();});
    return subscribers;
}
std::vector<Subscription> Database::getSubscriptions(int expire_greaterThan = -1, int expire_lessThan = -1) {
    std::vector<Subscription> subscriptions;
    for (const auto &[key, subscription] : this->subscriptions) {
        if (key != -1)
            if (expire_greaterThan == -1 || subscription.getEndTime() >= expire_greaterThan)
                if (expire_lessThan == -1 || subscription.getEndTime() <= expire_lessThan)
                    subscriptions.push_back(subscription);
    }
    sort(subscriptions.begin(), subscriptions.end(), [](const Subscription &a, const Subscription &b) {return a.getSubscriptionId() < b.getSubscriptionId();});
    return subscriptions;
}
std::vector<Magazine_Info> Database::getMagazines() {
    std::vector<Magazine_Info> magazines;
    for (const auto &[key, magazine] : this->magazines) {
        if (magazine.getId() != -1)
            magazines.emplace_back(magazine.getInfo());
    }
    std::sort(magazines.begin(), magazines.end(), [](const Magazine_Info &a, const Magazine_Info &b) {return a.getId() < b.getId();});
    return magazines;
}

void Database::saveAsJson(const std::string& save_path) const {
    std::fstream file;
    file.open(save_path, std::ios::out | std::ios::trunc);
    if (file.is_open()) {
        file << jsonify();
        file.close();
    }
    else
        std::cerr << "Save File Error!" << std::endl;
}
void Database::loadFromJson(const std::string &load_path){
    std::fstream file;
    file.open(load_path, std::ios::in);
    if (file.is_open()) {
        nlohmann::json json;
        file >> json;
        parseJson(json);
        file.close();
    }
}

