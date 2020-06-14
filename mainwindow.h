#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QProgressBar>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void callArchive(std::string &input, std::string &output);

    void callUnarchive(std::string &input, std::string &output);

private slots:
    void on_actionIndex_triggered();

    void on_actionRun_triggered();

    void on_actionStop_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
