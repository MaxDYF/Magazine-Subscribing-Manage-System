//
// Created by 邓逸飞 on 24-12-23.
//

#ifndef INTERFACE_H
#define INTERFACE_H

#include "Database.h"

class Interface {
private:
    Database db;

public:
    Interface();
    void addSubscriber();
    void addSubscription();
    void addMagazine();
    void querySubscriber();
    void displayAllSubscribers();
    void displayAllMagazines();
    void editSubscriber();
    void deleteExpiredSubscribers();
    void statistics();
    void start();
};



#endif //INTERFACE_H
