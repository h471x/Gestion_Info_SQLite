#ifndef THEME_H
#define THEME_H

#include <QObject>
#include <QWidget>
#include "ui_mainwindow.h"

class ThemeSwitcher : public QObject
{
    Q_OBJECT

public:
    ThemeSwitcher(Ui::MainWindow* ui);

public slots:
    void toggleTheme();

private:
    Ui::MainWindow* ui;
    bool isDark;
};

#endif // THEME_H
