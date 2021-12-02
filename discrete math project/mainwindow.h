#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include "draw.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void onMakeEgdePushButtonClicked();
    void on_nodeButton_clicked();
    void on_openButton_clicked();
    void pause();
    void max_color(int max_color);
    void finish();
signals:
    void addNode();
    void edgeS(int, int);
    void goS();
    void resetS();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int speed = 0;
    int count_node = 0;
    int getSpeed();
    QPushButton* getNodeButton();
    QPushButton* getEdgeButton();
    QLineEdit* getLeftEdit();
    QLineEdit* getRightEdit();
    Draw* getDraw();
    Draw* getDrawR();

private slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_goButton_clicked();
    void on_resetButton_clicked();
    void on_horizontalSlider_sliderMoved(int position);

virtual int heightForWidth ( int w ) const { return w*675/1362;};
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
