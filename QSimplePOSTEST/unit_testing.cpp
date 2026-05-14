#include <QtTest>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>

#include "menuitem.h"
#include "checkrecord.h"

class TestModels : public QObject
{
    Q_OBJECT

private slots:
    void testMenuItemInitialization();
    void testMenuItemSerialization();

    void testCheckRecordInitialization();
    void testCheckRecordSerialization();
};

void TestModels::testMenuItemInitialization()
{
    menuitem item1;
    QCOMPARE(item1.name, QString(""));
    QCOMPARE(item1.price, 0.0);

    menuitem item2("Burger", 5.99);
    QCOMPARE(item2.name, QString("Burger"));
    QCOMPARE(item2.price, 5.99);
}

void TestModels::testMenuItemSerialization()
{
    menuitem original("Pizza", 12.50);
    QJsonObject json = original.toJson();

    menuitem restored = menuitem::fromJson(json);

    QCOMPARE(restored.name, original.name);
    QCOMPARE(restored.price, original.price);
}

void TestModels::testCheckRecordInitialization()
{
    checkrecord record1;
    QCOMPARE(record1.tableNumber(), 0);
    QCOMPARE(record1.getTotal(), 0.0);
    QCOMPARE(record1.getItems().size(), 0);

    QVector<menuitem> items;
    items.push_back(menuitem("Fries", 2.99));
    items.push_back(menuitem("Soda", 1.50));

    QDateTime now = QDateTime::currentDateTime();
    checkrecord record2(5, items, 4.49, now);

    QCOMPARE(record2.tableNumber(), 5);
    QCOMPARE(record2.getTotal(), 4.49);
    QCOMPARE(record2.getItems().size(), 2);
    QCOMPARE(record2.closedAt().toString(Qt::ISODate), now.toString(Qt::ISODate));
}

void TestModels::testCheckRecordSerialization()
{
    QVector<menuitem> items;    
    items.push_back(menuitem("Salad", 4.99));
    items.push_back(menuitem("Tea", 1.99));

    QDateTime closedTime = QDateTime::currentDateTime();
    checkrecord original(3, items, 6.98, closedTime);

    QJsonObject json = original.toJson();
    checkrecord restored = checkrecord::fromJson(json);

    QCOMPARE(restored.tableNumber(), original.tableNumber());
    QCOMPARE(restored.getTotal(), original.getTotal());
    QCOMPARE(restored.getItems().size(), original.getItems().size());
    QCOMPARE(restored.closedAt().toString(Qt::ISODate), original.closedAt().toString(Qt::ISODate));

    QCOMPARE(restored.getItems()[0].name, original.getItems()[0].name);
    QCOMPARE(restored.getItems()[1].price, original.getItems()[1].price);
}

QTEST_APPLESS_MAIN(TestModels)

#include "unit_testing.moc"