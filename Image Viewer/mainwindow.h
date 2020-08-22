#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QFileDialog>
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QList>
#include "ScaledLabel.h"
#include "SmartPtr.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() {}

private slots:
    void on_action_triggered() { open(); }
    void on_action_2_triggered();
    void openRecent();
    void open();

    void on_action_4_triggered();
    void on_action_5_triggered();
    void on_action_6_triggered();


private:
    SmartPtr<Ui::MainWindow> ui;

    SmartPtr<QMenu> fileMenu;
    SmartPtr<QMenu> recentFilesMenu;

    QString currentFilePath;
    SmartPtr<QAction> openAction;
    QList<QAction*> recentFileActionList;
    const int maxFileNr;

    void createActionsAndConnections();
    void createMenus();

    void loadFile(const QString& filePath);
    void adjustForCurrentFile(const QString& filePath);
    void updateRecentActionList();
};

#endif // MAINWINDOW_H
