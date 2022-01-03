#pragma once

#include <QMainWindow>

class Ui_CarmHashMainWindow;

class CarmHashMainWindow : public QMainWindow {
    Q_OBJECT
public:
    CarmHashMainWindow();
    ~CarmHashMainWindow();
private:
    void addCheatToHistory(const QString &cheat);
    Ui_CarmHashMainWindow *m_ui;
};
