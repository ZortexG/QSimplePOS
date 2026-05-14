#include "tableorder.h"
tableorder::tableorder() : m_tablenumber(0) {

}
tableorder::tableorder(int tableNumber) : m_tablenumber(tableNumber) {

}

int tableorder::tablenumber() const {
	return m_tablenumber;
}
void tableorder::setTablenumber(int tablenumber) {
	m_tablenumber = tablenumber;
}
void tableorder::addItem(const menuitem& item) {
	m_items.push_back(item);
}
void tableorder::clearItems() {
	m_items.clear();
}
bool tableorder::isempty() const {
	return m_items.isEmpty();
}
double tableorder::total() const {
	double value = 0.0;
	for (int i = 0; i < m_items.size(); ++i) {
		value += m_items[i].price;
	}
	return value;
}
const QVector<menuitem> & tableorder::items() const {
	return m_items;
}