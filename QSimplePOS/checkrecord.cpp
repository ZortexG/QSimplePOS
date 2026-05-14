#include "checkrecord.h"
#include <QJsonArray>

checkrecord::checkrecord()
	: tablenumber(0), total(0.0), closedtime(QDateTime::currentDateTime()) {

}
checkrecord::checkrecord(int tablenumber, const QVector<menuitem> & items, double total, const QDateTime& closedtime)
	: tablenumber(tablenumber), items(items), total(total), closedtime(closedtime) {

}
QJsonObject checkrecord::toJson() const {
	QJsonObject json;
	json.insert("table", tablenumber);
	json.insert("total", total);
	json.insert("closedtime", closedtime.toString(Qt::ISODate));

	QJsonArray itemsArray;
	for (int i = 0; i < items.size(); ++i) {
		itemsArray.append(items[i].toJson());
	}
	json.insert("items", itemsArray);
	return json;
}
checkrecord checkrecord::fromJson(const QJsonObject& json) {
	checkrecord record;
	record.tablenumber = json.value("table").toInt();
	record.total = json.value("total").toDouble();
	record.closedtime = QDateTime::fromString(json.value("closedtime").toString(), Qt::ISODate);

	const QJsonArray itemsArray = json.value("items").toArray();
	for (int i = 0; i < itemsArray.size(); ++i) {
		record.items.push_back(menuitem::fromJson(itemsArray[i].toObject()));
	}
	return record;
}

const QVector<menuitem>& checkrecord::getItems() const {
	return items;
}

QDateTime checkrecord::closedAt() const {
	return closedtime;
}
int checkrecord::tableNumber() const {
	return tablenumber; 
}
double checkrecord::getTotal() const { 
	return total; 
}
