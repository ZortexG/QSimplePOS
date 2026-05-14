#pragma once
#include <QJsonObject>
#include <QString>
struct menuitem
{
	QString name;
	double price;

	menuitem();
	menuitem(const QString& name, double price);

	QJsonObject toJson() const;
	static menuitem fromJson(const QJsonObject& json);
};

