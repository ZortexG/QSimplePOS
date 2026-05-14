#pragma once
#include <QString>
#include <QVector>

#include "checkrecord.h"
#include "menuitem.h"

class posrepo
{
public:
	explicit posrepo(const QString& filepath = QString());

	bool load(int& tablecount, QVector<menuitem>& menuitems, QVector<checkrecord>& checks) const;
	bool save(int tablecount, const QVector<menuitem>& menuitems, const QVector<checkrecord>& checks) const;

private:
	QString getdata() const;
	QString m_filepath;
};