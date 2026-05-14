#include "mgrmenu.h"

#include <QDialog>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QInputDialog>
#include <QLineEdit>
#include <QVBoxLayout>

bool mgrmenu::getmenuitem(QWidget* parent, QString& itemName, double& itemPrice)
{
    QDialog dialog(parent);
    dialog.setWindowTitle("Add items");

    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    QFormLayout* form = new QFormLayout();

    QLineEdit* nameEdit = new QLineEdit();
    QDoubleSpinBox* priceEdit = new QDoubleSpinBox();
    priceEdit->setMinimum(0.0);
    priceEdit->setMaximum(100000.0);
    priceEdit->setDecimals(2);

    form->addRow("Item name:", nameEdit);
    form->addRow("Price:", priceEdit);
    layout->addLayout(form);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttons);

    QObject::connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted)
    {
        return false;
    }

    itemName = nameEdit->text().trimmed();
    itemPrice = priceEdit->value();

    return !itemName.isEmpty();
}

bool mgrmenu::getTableCount(QWidget* parent, int currentValue, int& newValue)
{
    bool ok = false;
    const int value = QInputDialog::getInt(
        parent,
        "Change Table Count",
        "How many tables?",
        currentValue,
        1,
        500,
        1,
        &ok);

    if (!ok)
    {
        return false;
    }

    newValue = value;
    return true;
}