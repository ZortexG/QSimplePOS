#include "menuitem.h"

menuitem::menuitem() : name(""), price(0.0) {
}
menuitem::menuitem(const QString& name, double price) : name(name), price(price) {
}

QJsonObject menuitem::toJson() const {
	QJsonObject json;
	json.insert("name", name);
	json.insert("price", price);
	return json;
}
menuitem menuitem::fromJson(const QJsonObject& json) {
	return menuitem(json.value("name").toString(), json.value("price").toDouble());
}