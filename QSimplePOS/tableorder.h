#pragma once
#include <QVector>
#include "menuitem.h"
class tableorder
{
public:
	tableorder();
	explicit tableorder(int tableNumber);

	int tablenumber() const;
	void setTablenumber(int tablenumber);

	void addItem(const menuitem& item);
	void clearItems();
	bool isempty() const;
	double total() const;

	const QVector<menuitem>& items() const;

private:
	int m_tablenumber;
	QVector<menuitem> m_items;
};

