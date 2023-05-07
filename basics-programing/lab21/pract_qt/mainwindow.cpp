#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "userdata.hpp"

#include <QIODevice>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->modeButtonGroup->setId(ui->mode1RadioButton, 1);
    ui->modeButtonGroup->setId(ui->mode2RadioButton, 2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_textFileButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.txt");
    if (!path.isEmpty())
        ui->textFileLineEdit->setText(path);
}

void MainWindow::on_textBinButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.dat");
    if (!path.isEmpty())
        ui->binFileLineEdit->setText(path);
}

// Метод, который вызывается по сигналу нажатия кнопки выполнения
// Здесь программируется реакция на нажатие
void MainWindow::on_execPushButton_clicked()
{
    // Выводим окно сообщения
    // Метод arg() используется для подстановки в строку значений переменных
    // Функция tr() используется для перевода интерфейса на другие языки и
    // возвращает строку QString. Кроме того, использование QString обеспечивает
    // правильную кодировку символов
    QString path_txt = ui->textFileLineEdit->text();
    QString path_bin = ui->binFileLineEdit->text();
    if ((ui->modeButtonGroup->checkedId() == 1) && (path_txt.isEmpty()) && (path_bin.isEmpty()))
        QMessageBox::information(this, "Ошибка!", "Не указан путь к тектовому или к бинарному файлу.");
    else if ((ui->modeButtonGroup->checkedId() == 2) && (path_bin.isEmpty()))
        QMessageBox::information(this, "Ошибка!", "Не указан путь к бинарному файлу.");
    else
    {
        //QMessageBox::information(this, tr("Нажата кнопка выполнения"), tr("Выбран режим %1").arg(ui->modeButtonGroup->checkedId()));
        QString out_text;
        // Создаём текстовый поток, который выводит информацию в строку
        QTextStream ost(&out_text, QIODevice::WriteOnly);
        userdata f(ui->modeButtonGroup->checkedId(), path_txt, path_bin, ost);
        // Выводим информацию в поле вывода
        ui->outTextEdit->setPlainText(out_text);
        // Альтернативный вариант без QTextStream
    //    ui->outTextEdit->setPlainText(tr("Текстовый файл: %1\nДвоичный файл: %2\nРежим: %3")
    //                                  .arg(ui->textFileLineEdit->text())
    //                                  .arg(ui->binFileLineEdit->text())
    //                                  .arg(ui->modeButtonGroup->checkedId())
    //                                  );
    }
}
