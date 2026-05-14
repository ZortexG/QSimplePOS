#pragma once
#include <QString>
class QWidget;
class mgrmenu
{
public:
	static bool getmenuitem(QWidget* parent, QString& name, double& price);
	static bool getTableCount(QWidget* parent, int currentValue, int& newValue);
};

