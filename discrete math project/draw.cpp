#include <QPainter>
#include "draw.h"
#include <QPoint>
#include <QLine>
#include <iostream>
Draw::Draw(QWidget *parent) : QWidget(parent){};
void Draw::paintEvent(QPaintEvent *e)
{
  Q_UNUSED(e);
  if (this->objectName() == "widget")
  {
      doPainting(true);
  }
  else
  {
      doPainting(false);
  }
}

void Draw::doPainting(bool x)
{
  QPainter painter(this);
  painter.setPen(Qt::blue);
  painter.setBrush(QBrush(QColor(255, 255, 255)));
  for(auto e : edges)
  {
      painter.drawLine(e);
  }
  for(auto n : nodes)
  {
      if (n.isHigh())
      {
          painter.setBrush(QBrush(QColor(36, 99, 224)));
      }
      else
      {
          painter.setBrush(QBrush(QColor(255, 255, 255)));
      }
      painter.drawEllipse(QPoint(n.get_x(), n.get_y()), 20, 20);
      if (x)
      {
          painter.drawText(QRectF(n.get_x() - 20, n.get_y() - 20, 40, 40), Qt::AlignCenter, QString("%1").arg(n.get_n()));
      }
      else
      {
          painter.drawText(QRectF(n.get_x() - 20, n.get_y() - 20, 40, 40), Qt::AlignCenter, QString("%1").arg(n.get_show_n()));
      }

  }
}

void Draw::drawN(QVector<Node> d)
{
    if (!d.isEmpty())
    {
            nodes = d;
            update();
    }
}
void Draw::drawE(QVector<QLine> d)
{
    if (!d.isEmpty())
    {
            edges = d;
            update();
            emit drawnE();
    }
}
