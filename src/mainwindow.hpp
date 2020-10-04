#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "field.hpp"
//#include <QtConcurrent/QtConcurrent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    CS_OBJECT(MainWindow)
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent* e);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *e);
    
private :
    CS_SLOT_1(Private, void on_actionRun_triggered())
    CS_SLOT_2(on_actionRun_triggered) 
    
private:
    bool run = false;
    bool write_im = false;
    Field* f;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
