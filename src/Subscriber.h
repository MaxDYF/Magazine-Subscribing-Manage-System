//
// Created by 邓逸飞 on 24-12-23.
//

#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <vector>
#include <string>

#include "json.hpp"
#include "Subscription.h"


class Subscriber_Info {
private:
    int uid;
    std::string name;
    std::string gender;
    std::string phoneNumber;
    std::string address;
public:
    Subscriber_Info();
    Subscriber_Info(const std::string& name, const std::string& gender, const std::string& phoneNumber, const std::string& address, int uid);
    Subscriber_Info getInfo() const;
    void setName(const std::string& name);
    void setGender(const std::string& gender);
    void setPhoneNumber(const std::string& phoneNumber);
    void setUid(int uid);
    void setAddress(const std::string& address);
    std::string getName() const;
    std::string getGender() const;
    std::string getPhoneNumber() const;
    std::string getAddress() const;
    int getUid() const;
    nlohmann::json jsonify() const;
    void parseJson(const nlohmann::json &json);
};
class Subscriber : public Subscriber_Info{
private:
    std::vector<Subscription> subscription;
public:
    Subscriber();
    Subscriber(const std::string& name, const std::string& gender, const std::string& phoneNumber, const std::string& address, int uid);
    std::vector<Subscription> getSubscription();
    void addSubscription(const Subscription &subscription);
    void removeSubscription(int subscription_id);
};



#endif //SUBSCRIBER_H
