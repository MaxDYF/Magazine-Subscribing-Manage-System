//
// Created by 邓逸飞 on 24-12-23.
//

#include "Interface.h"
#include <iostream>
#include <ctime>

#define DATA_FILE_PATH "./data.json"


using namespace std;

Interface::Interface() {
    db.loadFromJson(DATA_FILE_PATH);
}

void Interface::addSubscriber() {
    std::string name, gender, phoneNumber, address;
    cout << "请输入订户姓名: ";;
    cin >> name;
    cout << "请输入订户性别: ";
    cin >> gender;
    cout << "请输入订户手机号: ";
    cin >> phoneNumber;
    cout << "请输入订户单位：";
    cin >> address;

    // 获取新订户ID
    Subscriber subscriber(name, gender, phoneNumber, address, -1);
    int subscriber_uid = db.addSubscriber(subscriber);
    cout << "订户 " << name << " 已成功添加!" << endl;
}

void Interface::querySubscriber() {
    string name, gender, address, phoneNumber;
    cin.ignore();
    cout << "请输入查询条件（姓名、性别、单位）：\n";
    cout << "姓名（输入空则跳过）: ";
    getline(cin, name);
    cout << "性别（输入空则跳过）: ";
    getline(cin, gender);
    cout << "电话号码（输入空则跳过）";
    getline(cin, phoneNumber);
    cout << "单位（输入空则跳过）: ";
    getline(cin, address);

    auto result = db.getSubscribers(name, gender, phoneNumber, address);

    if (result.empty()) {
        cout << "未找到符合条件的订户记录。" << endl;
    }
    else {
        for (const auto &subscriber : result) {
            cout << "找到订户, UID: " << subscriber.getUid() << ", 姓名: " << subscriber.getName() << ", 性别: "
                 << subscriber.getGender() << ", 地址: "
                 << subscriber.getAddress() << endl;
            cout << "\t该用户订阅信息: \n";
            for (const auto &subscription : db.getSubscriber(subscriber.getUid()).getSubscription()) {
                const auto magazine = db.getMagazine(subscription.getMagazine_id());
                cout << "\t订阅了 " << magazine.getName()
                     << ", 共 " << subscription.getCount() << " 本." << endl;
            }
        }
    }
}

void Interface::displayAllSubscribers() {
    const auto result = db.getSubscribers("", "", "", "");
    cout << "当前所有订户信息:\n";
    for (const auto& subscriber : result) {
        if (subscriber.getUid() == -1)
            continue;
        cout << "UID: " << subscriber.getUid() << ", 姓名: " << subscriber.getName() << ", 性别: "
                 << subscriber.getGender() << ", 地址: "
                 << subscriber.getAddress() << endl;
        cout << "\t该用户订阅信息: \n";
        for (const auto &subscription : db.getSubscriber(subscriber.getUid()).getSubscription()) {
            const auto magazine = db.getMagazine(subscription.getMagazine_id());
            cout << "\t订阅了 " << magazine.getName()
                 << ", 共 " << subscription.getCount() << " 本." << endl;
        }
    }
}

void Interface::editSubscriber() {
    int subscriber_id;
    cout << "请输入要编辑的订户ID: ";
    cin >> subscriber_id;
    Subscriber &subscriber = db.getSubscriber(subscriber_id);
    if (subscriber.getUid() == -1) {
        cout << "未找到该订户记录!" << endl;
        return;
    }
    string name, gender, phoneNumber, address;
    cout << "修改订户信息: \n";
    cout << "请输入新的姓名: ";
    cin.ignore();
    getline(cin, name);
    cout << "请输入新的性别: ";
    getline(cin, gender);
    cout << "请输入新的手机号: ";
    getline(cin, phoneNumber);
    cout << "请输入新的单位: ";
    getline(cin, address);
    // 更新订户信息
    subscriber.setGender(gender);
    subscriber.setAddress(address);
    subscriber.setName(name);
    subscriber.setPhoneNumber(phoneNumber);

    cout << "订户信息已更新!" << endl;
}

void Interface::deleteExpiredSubscribers() {
    int now = time(nullptr);
    auto result = db.getSubscriptions(-1, now - 1);
    for (const auto &subscription : result) {
        std::string subscriber_name, magazine_name;
        subscriber_name = db.getSubscriber(subscription.getSubscriber_Uid()).getName();
        magazine_name = db.getMagazine(subscription.getMagazine_id()).getName();
        cout << "删除订户 " << subscriber_name << " 订阅的 " << magazine_name <<"，因为订阅已过期!" << endl;
        db.removeSubscription(subscription.getSubscriptionId());
    }
}

void Interface::statistics() {
    std::map<std::string, int> statistics_gender;
    std::map<std::string, int> statistics_magazine;
    auto result = db.getSubscriptions(-1, -1);
    for (const auto &subscription : result) {
        auto subscriber = db.getSubscriber(subscription.getSubscriber_Uid());
        auto magazine = db.getMagazine(subscription.getMagazine_id());
        statistics_gender[subscriber.getGender()]++;
        statistics_magazine[magazine.getName()] += subscription.getCount();
    }
    cout << "统计结果: \n\n";
    cout << "性别统计如下: \n";
    for (const auto &statistics : statistics_gender) {
        cout << statistics.first << ": 共 " << statistics.second << " 人" << endl;
    }
    cout << endl;
    cout << "杂志订阅统计如下：\n";
    for (const auto &statistics : statistics_magazine) {
        cout << statistics.first << ": 共订阅 " << statistics.second << " 本" << endl;
    }
}
void Interface::addSubscription() {
    int subscriber_id, magazine_id, startTime, endTime, count;
    cout << "请输入订户的UID: ";
    cin >> subscriber_id;
    cout << "请输入杂志的ID: ";
    cin >> magazine_id;
    cout << "请输入订阅的数量: ";
    cin >> count;
    cout << "请输入订阅终止年、月、日: ";
    startTime = time(nullptr);
    int year, month, day;
    cin >> year >> month >> day;
    tm timeinfo;
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = 0;
    timeinfo.tm_min = 0;
    timeinfo.tm_sec = 0;
    endTime = mktime(&timeinfo);
    Subscription subscription(-1, subscriber_id, magazine_id, startTime, endTime, count);
    db.addSubscription(subscription);
    cout << "成功添加!" << endl;
}

void Interface::addMagazine() {
    Magazine_Info magazine_info;
    string name;
    double price_float;
    cout << "请输入新杂志的名称: ";
    cin >> name;
    cout << "请输入价格: ";
    cin >> price_float;
    int price = price_float * 100;
    magazine_info.setName(name);
    magazine_info.setPrice(price);
    db.addMagazine(magazine_info);
    cout << "杂志成功添加!" << endl;
}
void Interface::displayAllMagazines() {
    const auto result = db.getMagazines();
    int maxlen = 0;
    for (const auto &magazine : result) {
        maxlen = max(maxlen, (int)magazine.getName().size());
    }
    cout << "当前所有杂志信息:\n";
    cout << setw(7) << "杂志ID" << setw(maxlen + 3) << right << "杂志名"  << setw(10) << right << "售价" << '\n';
    for (const auto& magazine : result) {
        if (magazine.getId() == -1)
            continue;
        double price = 1.0 * magazine.getPrice() / 100.0;
        cout << setw(7) << magazine.getId() << setw(maxlen + 3) << magazine.getName() << setw(10) <<
             fixed << setprecision(2) << price << endl;
    }
}



void Interface::start() {
    int choice;
    try {

        do {
            cout << "\n--- 订户管理系统 ---\n";
            cout << "1. 添加新订户\n";
            cout << "2. 查询订户\n";
            cout << "3. 添加订阅\n";
            cout << "4. 添加杂志\n";
            cout << "5. 显示所有订户\n";
            cout << "6. 显示所有杂志\n";
            cout << "7. 编辑订户信息\n";
            cout << "8. 删除已过期订户\n";
            cout << "9. 统计信息\n";
            cout << "0. 退出\n";
            cout << "请输入选择: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addSubscriber();
                break;
                case 2:
                    querySubscriber();
                break;
                case 3:
                    addSubscription();
                break;
                case 4:
                    addMagazine();
                break;
                case 5:
                    displayAllSubscribers();
                break;
                case 6:
                    displayAllMagazines();
                break;
                case 7:
                    editSubscriber();
                break;
                case 8:
                    deleteExpiredSubscribers();
                break;
                case 9:
                    statistics();
                break;
                case 0:
                    cout << "退出系统！\n";
                break;
                default:
                    cout << "无效选择，请重新输入。\n";
            }
            db.saveAsJson(DATA_FILE_PATH);
        } while (choice != 0);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return;
    }
}
