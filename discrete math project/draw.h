#ifndef DRAW_H
#define DRAW_H

#include "graph.h"
#include <QWidget>
#include <QLine>

class Draw : public QWidget
{
    Q_OBJECT
public:
    Draw(QWidget *parent = 0);
    ~Draw(){};
public slots:
    void drawN(QVector<Node>);
    void drawE(QVector<QLine>);
signals:
    void drawnE();
protected:
    void paintEvent(QPaintEvent *e);
private:
    QVector<Node> nodes;
    QVector<QLine> edges;
    void doPainting(bool);
};
#endif // DRAW_H
