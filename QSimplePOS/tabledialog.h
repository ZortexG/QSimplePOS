#pragma once

#include <QDialog>
#include "ui_tabledialog.h"
#include "posservice.h"

class TableDialog : public QDialog
{
    Q_OBJECT

public:
    TableDialog(int tableNumber, posservice& service, QWidget *parent = nullptr);
    ~TableDialog();

    bool wasTableClosed() const;

private slots:
    void onAddItem();
    void onCloseTable();

private:
    void refreshOrder();
    void populateMenu();

    Ui::TableDialog ui;
    int m_tableNumber;
    posservice& m_service;
    bool m_closedTable;
};

