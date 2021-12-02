#ifndef GRAPH_H
#define GRAPH_H
#include <QObject>
#include <QVector>
#include <QPair>
#include <QLine>

class Node
{
private:

    int x, y, n, show_n;
    bool high;
public:
    int get_x();
    int get_y();
    int get_n();
    int get_show_n();
    bool isHigh();
    void set_x(const int);
    void set_y(const int);
    void set_n(const int);
    void set_show_n(const int);
    void setHigh();
    void setNotHigh();
    void drawNode();
    Node(const int, const int, const int);
    bool operator!= (const Node&);
};



class Graph : public QObject
{
    Q_OBJECT
public:
    QVector<Node> Nodes;
    QVector<QLine> Edges;
    ;
    Graph(){};
    ~Graph(){};
public slots:
    void addEdge(int, int);
    void addNode();
    void MainColoration();
    void reset();
signals:
    void edgeAddedS(const QVector<QLine>);
    void nodeAddedS(const QVector<Node>);
    void get_max_color(int max_color);
    void finish();
    void callTimer();
private:
    void Coloration();
    void CheckReColoration(int xk_number);
    void light_node(int i);
    QVector<QVector<int>> AdjacencyList;
    QVector<bool> used;
};


#endif // GRAPH_H
