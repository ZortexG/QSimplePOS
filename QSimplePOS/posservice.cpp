#include "posservice.h"
#include <QDateTime>

posservice::posservice() : m_tablecount(10) {

}
bool posservice::init() {
	if (m_repo.load(m_tablecount, m_menuitems, m_checks)) {
		return true;
	}
	m_tablecount = 10;
	m_menuitems.clear();
	m_menuitems.push_back(menuitem("a", 0.01));
	return persist();
}
bool posservice::persist() const {
	return m_repo.save(m_tablecount, m_menuitems, m_checks);
}
int posservice::tablecount() const {
	return m_tablecount;
}
void posservice::settablecount(int count) {
	if (count < 1) {
		return;
	}
	m_tablecount = count;
	const QList<int> keys = m_openorders.keys();
	for (int i = 0; i < keys.size(); ++i) {
		if (keys[i] > m_tablecount) {
			m_openorders.remove(keys[i]);
		}
	}
}
const QVector<menuitem>& posservice::menuitems() const {
	return m_menuitems;
}
void posservice::addmenuitem(const menuitem& item) {
	m_menuitems.push_back(item);
}
void posservice::additem(int tablenum, const menuitem& item) {
	if (tablenum<1 || tablenum>m_tablecount) {
		return;
	}
	if(!m_openorders.contains(tablenum)) {
		m_openorders.insert(tablenum, tableorder(tablenum));
	}
	m_openorders[tablenum].addItem(item);
}
bool posservice::tablestat(int tablenum) const {
	return m_openorders.contains(tablenum) && !m_openorders[tablenum].isempty();
}
const tableorder* posservice::openorder(int tablenum) const {
	QMap<int, tableorder>::const_iterator it = m_openorders.find(tablenum);
	if (it == m_openorders.end()) {
		return nullptr;
	}
	return &it.value();
}
bool posservice::closeorder(int tablenum) {
	if(!m_openorders.contains(tablenum)) {
		return false;
	}
	const tableorder order = m_openorders.value(tablenum);
	if(order.isempty()) {
		return false;
	}
	checkrecord record(tablenum, order.items(), order.total(), QDateTime::currentDateTime());
	m_checks.push_back(record);
	m_openorders.remove(tablenum);

	return persist();
}
const QVector<checkrecord>& posservice::checks() const {
	return m_checks;
}