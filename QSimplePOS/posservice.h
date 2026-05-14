#pragma once
#include <QMap>
#include <QVector>
#include "checkrecord.h"
#include "menuitem.h"
#include "tableorder.h"
#include "posrepo.h"

class posservice
{
public:
	posservice();
	
	bool init();
	bool persist() const;

	int tablecount() const;
	void settablecount(int count);

	const QVector<menuitem>& menuitems() const;
	void addmenuitem(const menuitem& item);

	void additem(int tablenum, const menuitem& item);
	bool tablestat(int tablenum) const;
	const tableorder* openorder(int tablenum) const;
	bool closeorder(int tablenum);

	const QVector<checkrecord>& checks() const;
private:
	posrepo m_repo;
	int m_tablecount;
	QVector<menuitem> m_menuitems;
	QMap<int, tableorder> m_openorders;
	QVector<checkrecord> m_checks;
};

