#include "tabledialog.h"
#include <QMessageBox>

TableDialog::TableDialog(int tableNumber, posservice& service, QWidget *parent)
    : QDialog(parent), m_tableNumber(tableNumber), m_service(service), m_closedTable(false)
{
    ui.setupUi(this);
    setWindowTitle(QString("Table %1").arg(tableNumber));

    populateMenu();
    refreshOrder();

    connect(ui.addButton, &QPushButton::clicked, this, &TableDialog::onAddItem);
    connect(ui.closeButton, &QPushButton::clicked, this, &TableDialog::onCloseTable);
    connect(ui.doneButton, &QPushButton::clicked, this, &QDialog::accept);
}

TableDialog::~TableDialog() {}

bool TableDialog::wasTableClosed() const
{
    return m_closedTable;
}

void TableDialog::populateMenu()
{
    const QVector<menuitem>& menu = m_service.menuitems();
    for (int i = 0; i < menu.size(); ++i) {
        QListWidgetItem* item = new QListWidgetItem(
            QString("%1 - $%2").arg(menu[i].name).arg(QString::number(menu[i].price, 'f', 2)));
        item->setData(Qt::UserRole, i);
        ui.menuList->addItem(item);
    }
}

void TableDialog::refreshOrder()
{
    ui.orderList->clear();
    const tableorder* order = m_service.openorder(m_tableNumber);
    
    if (!order) {
        ui.totalLabel->setText("Total: $0.00");
        return;
    }

    const QVector<menuitem>& items = order->items();
    for (int i = 0; i < items.size(); ++i) {
        ui.orderList->addItem(QString("%1 - $%2").arg(items[i].name).arg(QString::number(items[i].price, 'f', 2)));
    }
    ui.totalLabel->setText(QString("Total: $%1").arg(QString::number(order->total(), 'f', 2)));
}

void TableDialog::onAddItem()
{
    if (!ui.menuList->currentItem()) {
        QMessageBox::information(this, "Menu", "Select an item");
        return;
    }

    int index = ui.menuList->currentItem()->data(Qt::UserRole).toInt();
    m_service.additem(m_tableNumber, m_service.menuitems()[index]);
    refreshOrder();
}

void TableDialog::onCloseTable()
{
    if (!m_service.tablestat(m_tableNumber)) {
        QMessageBox::information(this, "Close Table", "Table not open");
        return;
    }

    m_service.closeorder(m_tableNumber);
    m_closedTable = true;
    accept();
}
