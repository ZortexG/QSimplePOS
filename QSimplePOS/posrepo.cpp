#include "posrepo.h"
#include <QCoreApplication>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
posrepo::posrepo(const QString& filepath) : m_filepath(filepath) {

}
QString posrepo::getdata() const {
	if (!m_filepath.isEmpty()) {
		return m_filepath;
	}
	return QDir::currentPath() + "/posdata.json";
}
bool posrepo::load(int& tablecount, QVector<menuitem>& menuitems, QVector<checkrecord>& checks) const {
	QFile file(getdata());
	if (!file.exists()) {
		return false;
	}
	if (!file.open(QIODevice::ReadOnly)) {
		return false;
	}
	const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
	file.close();

	if (!doc.isObject()) {
		return false;
	}
	const QJsonObject root = doc.object();
	tablecount = root.value("tablecount").toInt(10);
	menuitems.clear();
	const QJsonArray menuarray = root.value("menu").toArray();
	for (int i = 0; i < menuarray.size(); ++i) {
		menuitems.push_back(menuitem::fromJson(menuarray[i].toObject()));
	}
	checks.clear();
	const QJsonArray checkarray = root.value("checks").toArray();
	for (int i = 0; i < checkarray.size(); ++i) {
		checks.push_back(checkrecord::fromJson(checkarray[i].toObject()));
	}

	return true;
}
bool posrepo::save(int tablecount, const QVector<menuitem>& menuitems, const QVector<checkrecord>& checks)const {
	QJsonObject root;
	root.insert("tablecount", tablecount);
	QJsonArray menuarray;
	for (int i = 0; i < menuitems.size(); ++i) {
		menuarray.append(menuitems[i].toJson());
	}
	root.insert("menu", menuarray);
	QJsonArray checkarray;
	for (int i = 0; i < checks.size(); ++i) {
		checkarray.append(checks[i].toJson());
	}
	root.insert("checks", checkarray);
	QFile file(getdata());
	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
		return false;
	}
	file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
	file.close();
	return true;
}