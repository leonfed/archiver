#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    ui->statusString->setText("Choose file");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::callArchive(std::string &input, std::string &output) {
    ui->statusString->setText("Processing...");
    archive *arch = new archive(input, output);
    arch->doWork();
    ui->statusString->setText("Done...");
}

void MainWindow::callUnarchive(std::string &input, std::string &output) {
    ui->statusString->setText("Processing...");
    unarchive *unarch = new unarchive(input, output);
    unarch->doWork();
    ui->statusString->setText("Done...");
}

void MainWindow::on_actionIndex_triggered() {
    QString Qdirectory;
    try {
        QString path = QFileDialog::getOpenFileName(nullptr, "Directory Dialog", "");
        if (path != "") {
            ui->directory->setText(path);
        }
        ui->statusString->setText("File is seleceted");
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
