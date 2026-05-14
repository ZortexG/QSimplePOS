#include "mainwindow.h"
#include "tabledialog.h"

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "mgrmenu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.stackedWidget->setCurrentIndex(0);
    ui.mgr_btn->hide();

    m_service.init();

    connect(ui.emp_lgn, &QPushButton::clicked, this, &MainWindow::loginAsEmployee);
    connect(ui.mgr_lgn, &QPushButton::clicked, this, &MainWindow::loginAsManager);

    connect(ui.tbl_btn, &QPushButton::clicked, this, &MainWindow::navtables);
    connect(ui.menu_btn, &QPushButton::clicked, this, &MainWindow::navmenu);
    connect(ui.chk_btn, &QPushButton::clicked, this, &MainWindow::navchecks);
    connect(ui.mgr_btn, &QPushButton::clicked, this, &MainWindow::navmanager);

    connect(ui.menu_back, &QPushButton::clicked, this, &MainWindow::back);
    connect(ui.back_menu, &QPushButton::clicked, this, &MainWindow::back);
    connect(ui.mgr_back, &QPushButton::clicked, this, &MainWindow::back);
    connect(ui.checks_back, &QPushButton::clicked, this, &MainWindow::back);
    connect(ui.logout, &QPushButton::clicked, this, &MainWindow::handlelogout);
 
    connect(ui.mgr_chng_menu, &QPushButton::clicked, this, &MainWindow::onManagerAddMenuItem);
    connect(ui.mgr_chng_tble, &QPushButton::clicked, this, &MainWindow::onManagerChangeTableCount);

    connect(ui.openTableBtn, &QPushButton::clicked, this, &MainWindow::onOpenTable);

    refreshTablesView();
    refreshChecksView();
}

MainWindow::~MainWindow()
{
}

void MainWindow::handlelogout()
{
    close();
}

void MainWindow::loginAsEmployee()
{
    ui.mgr_btn->hide();
    ui.stackedWidget->setCurrentIndex(1);
}

void MainWindow::loginAsManager()
{
    ui.mgr_btn->show();
    ui.stackedWidget->setCurrentIndex(1);
}

void MainWindow::navtables()
{
    refreshTablesView();
    ui.stackedWidget->setCurrentIndex(2);
}

void MainWindow::navmenu()
{
    refreshPlainMenuView();
    ui.stackedWidget->setCurrentIndex(5);
}
void MainWindow::refreshPlainMenuView()
{
    ui.plainMenuList->clear();

    for (const auto& item : m_service.menuitems())
    {
        QString text = QString("%1 - $%2").arg(item.name).arg(QString::number(item.price, 'f', 2));
        ui.plainMenuList->addItem(text);
    }
}
void MainWindow::navchecks()
{
    refreshChecksView();
    ui.stackedWidget->setCurrentIndex(4);
}

void MainWindow::navmanager()
{
    ui.stackedWidget->setCurrentIndex(3);
}

void MainWindow::back()
{
    ui.stackedWidget->setCurrentIndex(1);
}

void MainWindow::onManagerAddMenuItem()
{
    QString itemName;
    double itemPrice = 0.0;
    
    if (!mgrmenu::getmenuitem(this, itemName, itemPrice)) 
    { 
        return; 
    }
    
    m_service.addmenuitem(menuitem(itemName, itemPrice));
    m_service.persist();
    
    QMessageBox::information(this, "Manager", "Item added.");
}

void MainWindow::onManagerChangeTableCount()
{
        int count = m_service.tablecount();
    

    if (!mgrmenu::getTableCount(this, m_service.tablecount(), count)) 
    { 
        return; 
    }
    
    m_service.settablecount(count);
    m_service.persist();
    
    refreshTablesView();
    QMessageBox::information(this, "Manager", "Table updated.");
}

void MainWindow::onOpenTable()
{
    const int tableNumber = selectedTableNumber();
    if (tableNumber < 1)
    {
        QMessageBox::information(this, "Table", "Select table");
        return;
    }

    openTableDialog(tableNumber);
}

void MainWindow::refreshTablesView()
{
    ui.tablesList->clear();

    for (int table = 1; table <= m_service.tablecount(); ++table)
    {
        QString text = QString("Table %1 - Free").arg(table);

        if (m_service.tablestat(table))
        {
            const tableorder *order = m_service.openorder(table);
            text = QString("Table %1 - Open ($%2)")
                       .arg(table)
                       .arg(QString::number(order ? order->total() : 0.0, 'f', 2));
        }

        QListWidgetItem *item = new QListWidgetItem(text);
        item->setData(Qt::UserRole, table);
        ui.tablesList->addItem(item);
    }
}

void MainWindow::refreshChecksView()
{
    ui.checksList->clear();

    for (const auto &record : m_service.checks())
    {
        QStringList names;
        for (const auto &item : record.getItems()) {
            names << item.name; 
        }

        const QString line = QString("%1 | Table %2 | Total: $%3 | Items: %4")
                                 .arg(record.closedAt().toString("yyyy-MM-dd HH:mm:ss"))
                                 .arg(record.tableNumber())
                                 .arg(QString::number(record.getTotal(), 'f', 2))
                                 .arg(names.join(", "));

        ui.checksList->addItem(line);
    }
}

int MainWindow::selectedTableNumber() const
{
    if (!ui.tablesList->currentItem())
    {
        return -1;
    }

    return ui.tablesList->currentItem()->data(Qt::UserRole).toInt();
}

void MainWindow::openTableDialog(int tableNumber)
{
    TableDialog dialog(tableNumber, m_service, this);
    dialog.exec();

    refreshTablesView();
    if (dialog.wasTableClosed()) {
        refreshChecksView();
    }
}