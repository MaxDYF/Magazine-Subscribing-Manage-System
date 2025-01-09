//
// Created by 邓逸飞 on 2024/12/23.
//

#ifndef MAGAZINE_H
#define MAGAZINE_H

#include <string>
#include <vector>
#include "Subscriber.h"
#include "json.hpp"

class Basic_Magazine {

};
class Magazine_Info {
    friend class Magazine;
    friend bool operator==(const Magazine_Info &, const Magazine_Info &);
private:
    std::string name;
    int price; // 默认以“分“为最低单位，使用int类型避免浮点误差
    int id;

public:
    Magazine_Info();
    Magazine_Info(const std::string &name, int price, int id);
    Magazine_Info getInfo() const;
    virtual void setName(const std::string &name);
    virtual void setPrice(int price);
    virtual void setId(int id);
    std::string getName() const;
    int getPrice() const;
    int getId() const;
    nlohmann::json jsonify() const;
    void parseJson(const nlohmann::json &json);
};

class Magazine : public Magazine_Info, public Basic_Magazine{
private:
    std::vector<Subscription> subscriptions;
public:
    Magazine();
    Magazine(const Magazine_Info &magazine_info);
    void addSubscriber(const Subscription &subscription);
    void removeSubscriber(int subscription_id);
    std::vector<Subscription> get_subscriptions() const;
};
bool operator==(const Magazine_Info &, const Magazine_Info &);

#endif //MAGAZINE_H
