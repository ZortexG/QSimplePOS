#pragma once

#include <QtWidgets/QMainWindow>

#include "posservice.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void handlelogout();
    void navmenu();
    void navmanager();
    void back();
    void navtables();
private slots:
    void loginAsEmployee();
    void loginAsManager();
    void navchecks();
    void onManagerAddMenuItem();
    void onManagerChangeTableCount();
    void onOpenTable();

private:
    void refreshTablesView();
    void refreshChecksView();
    void refreshPlainMenuView();
    int selectedTableNumber() const;
    void openTableDialog(int tableNumber);

    Ui::MainWindowClass ui;
    posservice m_service;
};

