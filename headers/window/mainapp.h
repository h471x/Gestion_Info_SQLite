#ifndef MAINAPP_H
#define MAINAPP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainApp; }
QT_END_NAMESPACE

class MainApp : public QMainWindow
{
    Q_OBJECT

public: //Constructor
    MainApp(QWidget *parent = nullptr);
    ~MainApp();

private slots:
    void on_HomeBtn_clicked();
    void on_MenuBtn_clicked();
    void on_AdminBtn_clicked();
    void on_FindBtn_clicked();
    void on_FlowsBtn_clicked();
    void on_OptionsBtn_clicked();
    void on_HelpBtn_clicked();

private: //ui
    Ui::MainApp *MainUi;

private: //Methods
    void initMainApp();

};
#endif // MAINAPP_H
