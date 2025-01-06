//
// Created by 邓逸飞 on 24-12-23.
//

#include "Subscription.h"

#include "Subscriber.h"

Subscription::Subscription(int subscription_id, int subscriber_uid, int magazine_id, int beginTime, int endTime, int count) {
    this->subscription_id = subscription_id;
    this->subscriber_uid = subscriber_uid;
    this->magazine_id = magazine_id;
    this->beginTime = beginTime;
    this->endTime = endTime;
    this->count = count;
}
Subscription::Subscription() {
    this->subscription_id = -1;
    this->subscriber_uid = -1;
    this->magazine_id = -1;
    this->beginTime = -1;
    this->endTime = -1;
    this->count = 0;
}
int Subscription::getCount() const {
    return this->count;
}
int Subscription::getBeginTime() const {
    return this->beginTime;
}
int Subscription::getEndTime() const {
    return this->endTime;
}
int Subscription::getMagazine_id() const {
    return this->magazine_id;
}
int Subscription::getSubscriber_Uid() const {
    return this->subscriber_uid;
}
int Subscription::getSubscriptionId() const {
    return this->subscription_id;
}
nlohmann::json Subscription::jsonify() const {
    nlohmann::json json;
    json["subscription_id"] = subscription_id;
    json["subscriber_uid"] = subscriber_uid;
    json["magazine_id"] = magazine_id;
    json["beginTime"] = beginTime;
    json["endTime"] = endTime;
    json["count"] = count;
    return json;
}
void Subscription::parseJson(const nlohmann::json &json) {
    subscription_id = json["subscription_id"].get<int>();
    subscriber_uid = json["subscriber_uid"].get<int>();
    magazine_id = json["magazine_id"].get<int>();
    beginTime = json["beginTime"].get<int>();
    endTime = json["endTime"].get<int>();
    count = json["count"].get<int>();
}
void Subscription::setMagazineId(int magazine_id) {
    this->magazine_id = magazine_id;
}
void Subscription::setSubscriberUid(int subscriber_uid) {
    this->subscriber_uid = subscriber_uid;
}
void Subscription::setBeginTime(int beginTime) {
    this->beginTime = beginTime;
}
void Subscription::setEndTime(int endTime) {
    this->endTime = endTime;
}
void Subscription::setSubscriptionId(int subscription_id) {
    this->subscription_id = subscription_id;
}
void Subscription::setCount(int count) {
    this->count = count;
}








