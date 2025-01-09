//
// Created by 邓逸飞 on 24-12-23.
//

#ifndef DATABASE_H
#define DATABASE_H

#include <unordered_map>
#include <vector>
#include <list>
#include "Magazine.h"
#include "Subscriber.h"
#include "Subscription.h"
#include "json.hpp"


class Database {
private:
    std::unordered_map<int, Magazine> magazines;
    std::unordered_map<int, Subscriber> subscribers;
    std::unordered_map<int, Subscription> subscriptions;
    int magazine_user_count;
    int subscriber_user_count;
    int subscription_count;
    int getNewMagazineId();
    int getNewSubscriberId();
    int getNewSubscriptionId();
public:
    Database();
    int addMagazine(Magazine magazine);
    int addSubscriber(Subscriber subscriber);
    int addSubscription(Subscription subscriber);
    void removeSubscriber(int subscriber_uid);
    void removeMagazine(int magazine_id);
    void removeSubscription(int subscription_id);
    Magazine& getMagazine(int magazine_id);
    Subscriber& getSubscriber(int subscriber_uid);
    Subscription& getSubscription(int subscriber_uid);
    std::list<Magazine_Info> getMagazines();
    std::list<Subscriber_Info> getSubscribers(const std::string &name, const std::string &gender, const std::string &phoneNumber, const std::string &address);
    std::list<Subscription> getSubscriptions(int greaterThan, int lessThan);
    nlohmann::json jsonify() const;
    void parseJson(nlohmann::json json);
    void saveAsJson(const std::string& save_path) const;
    void loadFromJson(const std::string& load_path);
};

#endif //DATABASE_H
