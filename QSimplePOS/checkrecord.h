#pragma once
#include <QDateTime>
#include <QJsonObject>
#include <QVector>

#include "menuitem.h"
class checkrecord
{
public:
    checkrecord();
    checkrecord(int tablenumber, const QVector<menuitem>& items, double total, const QDateTime& closedtime);

    QJsonObject toJson() const;
    static checkrecord fromJson(const QJsonObject& json);

    const QVector<menuitem>& getItems() const;
    QDateTime closedAt() const;
    int tableNumber() const;
    double getTotal() const;

private:
    int tablenumber;
    QVector<menuitem> items;
    double total;
    QDateTime closedtime;
};

