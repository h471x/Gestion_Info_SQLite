#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QWidget>
#include <QStackedWidget>
#include <QFrame>
#include <QPushButton>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_HomeBtn_clicked();

    void on_MenuBtn_clicked();

    void on_AdminBtn_clicked();

    void on_FindBtn_clicked();

    void on_FlowsBtn_clicked();

    void on_OptionsBtn_clicked();

    void on_HelpBtn_clicked();

//    void updateColumnWidths();

private:
    Ui::MainWindow *Mainui;
};
#endif // MAINWINDOW_H
