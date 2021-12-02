#include <QApplication>
#include <QWidget>
#include <QFrame>
#include <QGridLayout>
#include <QGraphicsView>
#include <QSizePolicy>
#include <QTime>
#include <iostream>
#include "mainwindow.h"
#include "draw.h"
#include "graph.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  Graph graph;
  MainWindow window;
  QSizePolicy qsp(QSizePolicy::Preferred,QSizePolicy::Preferred);
  qsp.setHeightForWidth(true);
  window.setSizePolicy(qsp);
  QPushButton* psh = window.getNodeButton();
  QPushButton* vrg = window.getEdgeButton();
  QLineEdit* lftdt = window.getLeftEdit();
  QLineEdit* rgtdt = window.getRightEdit();
  Draw* dr_l= window.getDraw();
  Draw* dr_r= window.getDrawR();

  QObject::connect(psh, &QPushButton::clicked, &graph, &Graph::addNode);
  QObject::connect(&window, &MainWindow::addNode, &graph, &Graph::addNode);
  QObject::connect(&graph, &Graph::nodeAddedS, dr_l, &Draw::drawN);
  QObject::connect(&graph, &Graph::nodeAddedS, dr_r, &Draw::drawN);

  QObject::connect(vrg, &QPushButton::clicked, &window, &MainWindow::onMakeEgdePushButtonClicked);
  QObject::connect(&window, &MainWindow::edgeS, &graph,  &Graph::addEdge);
  QObject::connect(&graph, &Graph::edgeAddedS, dr_l, &Draw::drawE);
  QObject::connect(&graph, &Graph::edgeAddedS, dr_r, &Draw::drawE);

  QObject::connect(dr_l, &Draw::drawnE, lftdt, &QLineEdit::clear);
  QObject::connect(dr_l, &Draw::drawnE, rgtdt, &QLineEdit::clear);

  QObject::connect(&window, &MainWindow::goS, &graph, &Graph::MainColoration);
  QObject::connect(&graph, &Graph::get_max_color, &window, &MainWindow::max_color);
  QObject::connect(&graph, &Graph::finish, &window, &MainWindow::finish);
  QObject::connect(&window, &MainWindow::resetS, &graph, &Graph::reset);
  QObject::connect(&graph, &Graph::callTimer, &window, &MainWindow::pause);

  window.show();
  return app.exec();
}
