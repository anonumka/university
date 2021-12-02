#include "graph.h"
#include <QPushButton>
#include <QRandomGenerator>
#include <QDateTime>
#include <QPair>
#include <QLine>
#include <iostream>

int max_color = 1;
int iteration = 0;

int Node::get_x()
{
    return x;
}
int Node::get_y()
{
    return y;
}
int Node::get_n()
{
    return n;
}
int Node::get_show_n()
{
    return show_n;
}
bool Node::isHigh()
{
    return high;
}
void Node::set_x(const int t)
{
    x = t;
}
void Node::set_y(const int t)
{
    y = t;
}
void Node::set_n(const int t)
{
    n = t;
}
void Node::set_show_n(const int t)
{
    show_n = t;
}
void Node::setHigh()
{
    high = true;
}
void Node::setNotHigh()
{
    high = false;
}
Node::Node(const int xv, const int yv, const int nv)
{
    set_x(xv);
    set_y(yv);
    set_n(nv);
    set_show_n(0);
    setNotHigh();
}

bool Node::operator!= (const Node& n)
{
    return (this->get_n()!=n.n || this->isHigh() != n.high);
}

int sgn6(int x)
{
    if (x > 7)
    {
        return -1;
    }
    else if (x == 7)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void Graph::addEdge(int u, int v)
{
    AdjacencyList[u - 1].push_back(v - 1);
    AdjacencyList[v - 1].push_back(u - 1);
    QPoint uP = QPoint(Nodes[u - 1].get_x(), Nodes[u - 1].get_y());
    QPoint vP = QPoint(Nodes[v - 1].get_x(), Nodes[v - 1].get_y());
    QLine l = QLine(uP, vP);
    Edges.push_back(l);
    emit edgeAddedS(Edges);
}
void Graph::addNode()
{
    std::cout << "graph slot got called\n";
    int n, x, y;
    if (!Nodes.isEmpty())
    {
        n = Nodes.last().get_n() + 1;


        x = Nodes.last().get_x() + (100 * sgn6(n)) ;
        if (n > 6)
        {
        y = static_cast<int>(( 270 + sqrt(-x * x + 594 * x - 24705)));
        }
        else
        {
         y = static_cast<int>(( 270 - sqrt(-x * x + 594 * x - 24705)));
        }

    }
    else
    {
        n = 1;
        x = 47;
        y = static_cast<int>(270 - sqrt(-x * x + 594 * x - 24705));
    }

    Nodes.push_back(Node(x, y, n));
    AdjacencyList.push_back(QVector<int>());
    used.push_back(false);
    emit nodeAddedS(Nodes);
}


void Graph::Coloration()
{
    max_color = 0;
    for (int i = 1; i < Nodes.length(); i++)
    {
        if (!used[i])
        {
            QVector<int> AdjacencyVector;
            for (int j = 0; j < AdjacencyList[i].length(); j++)
            {
                int member = Nodes[AdjacencyList[i][j]].get_n() - 1;
                if (Nodes[i].get_n() > member)
                {
                    int member_n = Nodes[member].get_show_n();
                    AdjacencyVector.push_back(member_n);
                }
            }
            std::sort(AdjacencyVector.begin(), AdjacencyVector.end());
            int member_color = 1;
            for (int j = 0; j < AdjacencyVector.length(); j++)
            {
                if (member_color == AdjacencyVector[j])
                    member_color++;
            }
            Nodes[i].set_show_n(member_color);
            if (max_color < member_color)
                max_color = member_color;
        }
        else
        {
            used[i] = false;
            int member_color = Nodes[i].get_show_n();
            if (max_color < member_color)
                max_color = member_color;
        }
        light_node(i);
    }
    emit get_max_color(max_color);
}

void Graph::light_node(int i)
{
    Nodes[i].setHigh();
    emit nodeAddedS(Nodes);
    emit callTimer();
    Nodes[i].setNotHigh();
    emit nodeAddedS(Nodes);
}

void Graph::CheckReColoration(int xk_number)
{
    auto x = Nodes[0];
    if (xk_number == 0)
    {
        for (int i = 0; i < Nodes.length(); i++)
        {
            if (Nodes[i].get_show_n() == max_color)
            {
                x = Nodes[i];
                break;
            }
        }
    }
    else if (xk_number == 0 || xk_number == 1)
    {
        return;
    }
    else
    {
        x = Nodes[xk_number - 1];
    }
    int x_n = x.get_n() - 1;
    if (x_n == 1) return;
    QVector<int> AdjacencyVector;
    for (int i = 0; i < AdjacencyList[x_n].length(); i++)
    {
            int member = AdjacencyList[x_n][i];
            int member_n = Nodes[member].get_n();
            if (member_n - 1 < x_n)
                AdjacencyVector.push_back(member_n);
    }
    std::sort(AdjacencyVector.begin(), AdjacencyVector.end());
    int vector_len = AdjacencyVector.length() - 1;
    for (int j = vector_len; j >= 0; j--)
    {
        if ( AdjacencyVector[j] <= x_n)
        {
            x_n = AdjacencyVector[j];
            break;
        }
    }
    AdjacencyVector.clear();
    auto xk = Nodes[x_n - 1];
    int xk_num = xk.get_n() - 1;
    if (AdjacencyList[xk_num].isEmpty()) return;
    for (int i = 0; i < AdjacencyList[xk_num].length(); i++)
    {
            int member = AdjacencyList[x_n - 1][i];
            int member_n = Nodes[member].get_n();
            if (member_n <= xk_num) AdjacencyVector.push_back(member_n);
    }
    std::sort(AdjacencyVector.begin(), AdjacencyVector.end());
    int jk = xk.get_show_n();
    int new_jk = jk + 1;
    for (int i = 0; i < AdjacencyVector.length(); i++)
    {
        int color_node = AdjacencyVector[i] - 1;
        auto jk_other_node = Nodes[color_node];
        if ( new_jk == jk_other_node.get_show_n() )
        {
            new_jk++;
            i = 0;
        }
        if (new_jk == max_color) break;
    }
    AdjacencyVector.clear();
    if (new_jk == max_color)
    {
        int prev_member = xk.get_n();
        Graph::CheckReColoration(prev_member);
    }
    else
    {
        for (int i = 0; i < x_n; i++) used[i] = true;
        Nodes[x_n - 1].set_show_n(new_jk);
        light_node(x_n - 1);
        int tmp_max_color = max_color;
        Graph::Coloration();
        if (max_color < tmp_max_color) return;
        Graph::CheckReColoration(0);
    }
}

void Graph::MainColoration()
{
    max_color = 1;
    Nodes[0].set_show_n(max_color);
    light_node(0);
    Graph::Coloration();
    Graph::CheckReColoration(0);
    emit nodeAddedS(Nodes);
    emit get_max_color(max_color);
    emit finish();
}
void Graph::reset()
{
    max_color = 0;
    for(int i = 0; i < this->used.length(); i++)
    {
        this->used[i] = false;
        Nodes[i].setNotHigh();
        Nodes[i].set_show_n(0);
    }
    emit nodeAddedS(Nodes);
    emit get_max_color(max_color);
}
