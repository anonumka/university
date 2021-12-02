#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
QPushButton* MainWindow::getNodeButton()
{
    return ui->nodeButton;
}
QPushButton* MainWindow::getEdgeButton()
{
    return ui->vergeButton;
}
QLineEdit* MainWindow::getLeftEdit()
{
    return ui->leftEdit;
}
QLineEdit* MainWindow::getRightEdit()
{
    return ui->rightEdit;
}
Draw* MainWindow::getDraw()
{
    return ui->widget;
}
Draw* MainWindow::getDrawR()
{
    return ui->widget_2;
}
int MainWindow::getSpeed()
{
    return this->speed;
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_nodeButton_clicked()
{
    ui->openButton->setEnabled(false);
    count_node++;
}

void MainWindow::on_openButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(0, "Open Dialog", "../Graph-main", "*.txt");
    if (!path.isEmpty())
    {
        ui->openButton->setEnabled(false);
        QFile file_txt(path);
        file_txt.open(QFile::ReadOnly);
        QTextStream ist(&file_txt);
        int node = 0;
        int edge = 0;
        ist >> node;
        for (int i = 0; i < node; i++)
        {
            emit addNode();
            MainWindow::on_nodeButton_clicked();
        }
        ist >> edge;
        for (int i = 0; i < edge; i++)
        {
            QString tmp;
            ist >> tmp;
            ui->leftEdit->setText(tmp);
            ist >> tmp;
            ui->rightEdit->setText(tmp);
            MainWindow::onMakeEgdePushButtonClicked();
        }
    }
}

void MainWindow::onMakeEgdePushButtonClicked()
{
    QString left = QString(ui->leftEdit->text());
    if (left == "")
    {
        QMessageBox::warning(this, "Error!", "Левое поле пустое.");
        return;
    }
    QString right = QString(ui->rightEdit->text());
    if (right == "")
    {
        QMessageBox::warning(this, "Error!", "Правое поле пустое.");
        return;
    }
    if ( (left.toInt() > count_node) || (right.toInt() > count_node))
    {
        QMessageBox::warning(this, "Error!", QString("Неверно введены вершины. Всего %1 вершин.").arg(count_node));
        return;
    }

    QVector<QLineEdit*> lineEdits = {ui->leftEdit, ui->rightEdit};
    QVector<int> values;

    for (const QLineEdit* lineEdit : lineEdits)
    {
        bool ok = false;
        int value = lineEdit->text().toInt(&ok);
        if (ok)
        {
            values.push_back(value);
        }
    }


    if (!values.empty())
        emit edgeS(values[0], values[1]);

}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    speed = value;
}

void MainWindow::on_goButton_clicked()
{
    ui->goButton->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);
    ui->resetButton->setEnabled(true);
    emit goS();
}

void MainWindow::on_resetButton_clicked()
{
    ui->label_3->setText("Выполнено!");
    QEventLoop el;
    QTimer t;
    connect(&t, SIGNAL(timeout()), &el, SLOT(quit()));
    t.start(3000);
    el.exec();
    ui->goButton->setEnabled(true);
    ui->horizontalSlider->setEnabled(true);
    ui->label_3->setText("");
    emit resetS();
}
void MainWindow::pause()
{
    QEventLoop el;
    QTimer t;
    connect(&t, SIGNAL(timeout()), &el, SLOT(quit()));
    t.start(speed);
    el.exec();
    return;
}

void MainWindow::max_color(int max_color)
{
    ui->label->setText(QString("%1").arg(max_color));
}
void MainWindow::finish()
{
    QMessageBox::information(this, "Finish", "Coloration completed");
    ui->resetButton->setEnabled(true);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->label_2->setText(QString("Скорость визуализации: %1 с").arg((static_cast<float>(position)) / 1000));
}
