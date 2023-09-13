#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>

#include "list.h"

using namespace std;

int commandAdd(ifstream &ist, List *objs) {
    std::string command;
    ist >> command;
    if (command == "circle") {
        int x = 0, y = 0, r = 0;
        string tmp_color = "";
        ist >> x >> y >> r >> tmp_color;
        if (x == 0 || y == 0 || r == 0 || tmp_color == "") {
            cout << "error input file: not enough data";
            return 1;
        }

        FlatGeometryFig* new_obj = new Circle(x, y, r, tmp_color);
        objs->addList(new_obj);
    }
    else if (command == "rectangle") {
        float x1 = 0, x2 = 0;
        string tmp_color = "";
        ist >> x1 >> x2 >> tmp_color;
        if (x1 == 0 || x2 == 0 || tmp_color == "") {
            cout << "error input file: not enough data";
            return 1;
        }

        FlatGeometryFig* new_obj = new Rectangle(x1, x2, tmp_color);
        objs->addList(new_obj);
    }
    else if (command == "triangle") {
        float x1 = 0, x2 = 0, x3 = 0;
        string tmp_color = "";
        ist >> x1 >> x2 >> x3 >> tmp_color;
        if (x1 == 0 || x2 == 0 || x3 == 0 || tmp_color == "") {
            cout << "error input file: not enough data";
            return 1;
        }

        FlatGeometryFig* new_obj = new Triangle(x1, x2, x3, tmp_color);
        objs->addList(new_obj);
    }
    else {
        cout << "error input file: not found object";
        return 1;
    }
    return 0;
}

int commandRem(ifstream &ist, List *objs) {
    // *
    // color    ?
    // (figure) color   ?
    //          (?, ?, ?)

    std::string command;
    ist >> command;

    if (command == "*") {
        objs->deleteList();
    }
    else if (command == "color") {
        ist >> command;
        FlatGeometryFig *check;
        if (check->convertToEnum(command) != color_figure::ERROR) {
            int tmp_size = objs->getSize();

            for (int i = 0; i < tmp_size; ++i) {
                check = objs->getElem(i);
                if (check->getColor() == check->convertToEnum(command)) {
                    objs->deleteElem(i);

                    i = 0;
                    tmp_size = objs->getSize();
                }
            }
        }
        else {
            return 1;
        }
    }
    else if (command == "circle") {
        FlatGeometryFig *check;
        int x, y, r;
        ist >> x >> y >> r;

        int tmp_size = objs->getSize();
        for (int i = 0; i < tmp_size; ++i) {
            check = objs->getElem(i);
            if (check->checkParamsCircle(x, y, r)) {
                objs->deleteElem(i);

                i = 0;
                tmp_size = objs->getSize();
            }
        }
    }
    else if (command == "rectangle") {
        FlatGeometryFig *check;
        float x1, x2;
        ist >> x1 >> x2;

        int tmp_size = objs->getSize();
        for (int i = 0; i < tmp_size; ++i) {
            check = objs->getElem(i);
            if (check->checkParamsRectangle(x1, x2)) {
                objs->deleteElem(i);

                i = 0;
                tmp_size = objs->getSize();
            }
        }
    }
    else if (command == "triangle") {
        FlatGeometryFig *check;
        float x1, x2, x3;
        ist >> x1 >> x2 >> x3;

        int tmp_size = objs->getSize();
        for (int i = 0; i < tmp_size; ++i) {
            check = objs->getElem(i);
            if (check->checkParamsTriangle(x1, x2, x3)) {
                objs->deleteElem(i);

                i = 0;
                tmp_size = objs->getSize();
            }
        }
    }

    return 0;
}

int main()
{
    List objs;
    ifstream ist("input.txt");

    if (!ist.is_open()) {
        cout << "File is not opened";
    }

    string command;
    ist >> command;

    while (!ist.eof()) {
        if (command == "add") {
            commandAdd(ist, &objs);
        }
        else if (command == "rem") {
            commandRem(ist, &objs);
        }
        else if (command == "print") {
            objs.printList();
            cout << "---------\n";
        }
        else {
            cout << "Command not found.";
        }

        ist >> command;
    }

    return 0;
}
