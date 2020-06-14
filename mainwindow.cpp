#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "indexes.h"
#include "archive.h"
#include "unarchive.h"
#include <QFileDialog>
#include <QDesktopServices>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::callback(std::string status) {
    QString qstrting = QString::fromUtf8(status.c_str());
    ui->statusString->setText(qstrting);
}

void MainWindow::callArchive(std::string &input, std::string &output) {
    ui->statusString->setText("Processing...");
    QThread *thread = new QThread;
    archive *arch = new archive(input, output);
    arch->moveToThread(thread);
    connect(arch, SIGNAL(send(std::string)), this, SLOT(callback(std::string)));
    connect(thread, SIGNAL(started()), arch, SLOT(doWork()));
    thread->start();
}

void MainWindow::callUnarchive(std::string &input, std::string &output) {
    ui->statusString->setText("Processing...");
    QThread *thread = new QThread;
    unarchive *unarch = new unarchive(input, output);
    unarch->moveToThread(thread);
    connect(unarch, SIGNAL(send(std::string)), this, SLOT(callback(std::string)));
    connect(thread, SIGNAL(started()), unarch, SLOT(doWork()));
    thread->start();
}

void MainWindow::on_actionIndex_triggered() {
    QString Qdirectory;
    try {
        QString path = QFileDialog::getOpenFileName(nullptr, "Directory Dialog", "");
        if (path != "") {
            ui->directory->setText(path);
        }
    } catch (...) {
        ui->directory->setText("File isn't selected");
    }
}

void MainWindow::on_actionRun_triggered() {
    std::string input = ui->directory->text().toStdString();
    std::string output = ui->inputString->text().toStdString();
    try {
       callArchive(input, output);
    } catch (...) {
        ui->statusString->setText("Failed");
    }
}

void MainWindow::on_actionStop_triggered() {
    std::string input = ui->directory->text().toStdString();
    std::string output = ui->inputString->text().toStdString();
    try {
       callUnarchive(input, output);
    } catch (...) {
        ui->statusString->setText("Failed");
    }
}
