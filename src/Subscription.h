//
// Created by 邓逸飞 on 24-12-23.
//

#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H
#include "json.hpp"


class Subscription {
private:
    int subscription_id;
    int subscriber_uid;
    int magazine_id;
    int count;
    int beginTime;
    int endTime;
public:
    Subscription();
    Subscription(int subscription_id, int subscriber_uid, int magazine_id, int beginTime, int endTime, int count);
    void setSubscriptionId(int subscription_id);
    void setSubscriberUid(int subscriber_uid);
    void setMagazineId(int magazine_id);
    void setBeginTime(int beginTime);
    void setEndTime(int endTime);
    void setCount(int count);
    int getSubscriber_Uid() const;
    int getMagazine_id() const;
    int getCount() const;
    int getBeginTime() const;
    int getEndTime() const;
    int getSubscriptionId() const;
    nlohmann::json jsonify() const;
    void parseJson(const nlohmann::json &json);
};



#endif //SUBSCRIPTION_H
