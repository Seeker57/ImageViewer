#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), maxFileNr(4)
{
    ui->setupUi(this);
    ui->scrollArea->setWidgetResizable(true);
    createActionsAndConnections();
    createMenus();
}

void MainWindow::on_action_2_triggered()
{
    QImage emptyImage = QImage();
    ui->label->setScaledLabel(emptyImage);
    ui->statusBar->showMessage("");
}

void MainWindow::createActionsAndConnections(){
    openAction = new QAction(tr("&Открыть..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    QObject::connect(&openAction, SIGNAL(triggered()), SLOT(open()));
    QObject::connect(&openAction, SIGNAL(triggered()), SLOT(on_action_6_triggered()));

    QAction* recentFileAction = nullptr;
    for(int i = 0; i < maxFileNr; i++){
        recentFileAction = new QAction(this);
        recentFileAction->setVisible(false);
        recentFileActionList.append(recentFileAction);
        QObject::connect(recentFileActionList.at(i), SIGNAL(triggered()), this, SLOT(openRecent()));
        QObject::connect(recentFileActionList.at(i), SIGNAL(triggered()), this, SLOT(on_action_6_triggered()));
    }
}

void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&Файл"));
    fileMenu->addAction(&openAction);

    recentFilesMenu = fileMenu->addMenu(tr("Открыть последние"));
    for(int i = 0; i < maxFileNr; i++)
        recentFilesMenu->addAction(recentFileActionList.at(i));

    updateRecentActionList();
}

void MainWindow::open(){
    QString filePath = QFileDialog::getOpenFileName(
                       this, tr("Open File"), "",
                       tr("Images (*.png *.xpm *.jpg *.gif)"));
        if (!filePath.isEmpty())
            loadFile(filePath);
}

void MainWindow::openRecent(){
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
        loadFile(action->data().toString());
}

void MainWindow::adjustForCurrentFile(const QString &filePath){
    currentFilePath = filePath;
    setWindowFilePath(currentFilePath);

    QSettings settings;
    QStringList recentFilePaths = settings.value("recentFiles").toStringList();
    recentFilePaths.removeAll(filePath);
    recentFilePaths.prepend(filePath);
    while (recentFilePaths.size() > maxFileNr)
        recentFilePaths.removeLast();
    settings.setValue("recentFiles", recentFilePaths);

    foreach (QWidget *widget, QApplication::topLevelWidgets()) {
            MainWindow *mainWin = qobject_cast<MainWindow *>(widget);
            if (mainWin)
                mainWin->updateRecentActionList();
        }
}

void MainWindow::updateRecentActionList(){

    QSettings settings;
    QStringList recentFilePaths =
            settings.value("recentFiles").toStringList();

    int itEnd = 0;
    if(recentFilePaths.size() <= maxFileNr)
        itEnd = recentFilePaths.size();
    else
        itEnd = maxFileNr;

    for (int i = 0; i < itEnd; i++) {
        QString strippedName = QFileInfo(recentFilePaths.at(i)).fileName();
        recentFileActionList.at(i)->setText(strippedName);
        recentFileActionList.at(i)->setData(recentFilePaths.at(i));
        recentFileActionList.at(i)->setVisible(true);
    }

    for (int i = itEnd; i < maxFileNr; i++)
        recentFileActionList.at(i)->setVisible(false);
}

void MainWindow::loadFile(const QString &filePath){
    QFile file(filePath);

    QImage pMap(filePath);
    ui->label->setScaledLabel(pMap);
    ui->statusBar->showMessage(filePath);
    adjustForCurrentFile(filePath);
}

void MainWindow::on_action_4_triggered()
{
    if (ui->label->getZoom() < 1.0)
        ui->label->setZoom(1.0);
    qreal zoom = ui->label->getZoom();
    zoom += 0.10;
    ui->label->setZoom(zoom);
    ui->label->resize(ui->label->size() * ui->label->getZoom());
}

void MainWindow::on_action_5_triggered()
{
    if (ui->label->getZoom() > 1.0)
        ui->label->setZoom(1.0);
    qreal zoom = ui->label->getZoom();
    zoom -= 0.10;
    ui->label->setZoom(zoom);
    ui->label->resize(ui->label->size() * ui->label->getZoom());
}

void MainWindow::on_action_6_triggered()
{
   ui->label->setZoom(1.0);
   ui->label->setStartSize(ui->scrollArea->size());
   ui->label->resize(ui->label->getStartSize());
   ui->label->move(0,0);
}
