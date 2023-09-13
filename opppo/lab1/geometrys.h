#include <iostream>
#include <cstring>
#include <string>

enum class color_figure {
    RED = 0,
    ORANGE = 1,
    YELLOW = 2,
    GREEN = 3,
    AZURE = 4,
    BLUE = 5,
    PURPLE = 6,
    ERROR = 7
};

class FlatGeometryFig {
protected:
    std::string date_edit;
    color_figure color;
public:
    FlatGeometryFig() {}
    ~FlatGeometryFig() {}

    color_figure convertToEnum(std::string color);
    std::string convertToString(color_figure color);
    color_figure getColor() { return color; };

    std::string current_date() {
        time_t now = time(0);
        char* date_time = ctime(&now);
        std::string res(date_time);
        return res;
    }

    virtual void print() = 0;
    virtual int checkParamsCircle(int, int, int) = 0;
    virtual int checkParamsRectangle(float, float) = 0;
    virtual int checkParamsTriangle(float, float, float) = 0;
};

class Circle : public FlatGeometryFig {
private:
    int x, y, r;
public:
    Circle(int x, int y, int r, std::string color)
        : FlatGeometryFig () {
        this->x = x;
        this->y = y;
        this->r = r;
        this->color = this->convertToEnum(color);
        this->date_edit = current_date();
    }

    void print() override {
        std::cout << "circle (" << x << ", " << y << ", " << r << "), color = " << convertToString(color)
             << ", last date edit = " << date_edit;
    }

    int checkParamsCircle(int x, int y, int r) override {
        if (this->x == x && this->y == y && this->r == r) {
            return 1;
        }
        return 0;
    }

    int checkParamsRectangle(float, float) override { return 0; };
    int checkParamsTriangle(float, float, float) override { return 0; };
};

class Rectangle : public FlatGeometryFig {
private:
    float x1, x2;
public:
    Rectangle(float x1, float x2, std::string color)
        : FlatGeometryFig () {
        this->x1 = x1;
        this->x2 = x2;
        this->color = this->convertToEnum(color);
        this->date_edit = current_date();
    }

    void print() override {
        std::cout << "rectangle (" << x1 << ", " << x2 << "), color = " << convertToString(color)
             << ", last date edit = " << date_edit;
    }

    int checkParamsRectangle(float x1, float x2) override {
        if (this->x1 == x1 && this->x2 == x2) {
            return 1;
        }
        return 0;
    }

    int checkParamsCircle(int, int, int) override { return 0; };
    int checkParamsTriangle(float, float, float) override { return 0; };
};

class Triangle : public FlatGeometryFig {
private:
    float x1, x2, x3;
public:
    Triangle(float x1, float x2, float x3, std::string color)
        : FlatGeometryFig () {
        this->x1 = x1;
        this->x2 = x2;
        this->x3 = x3;
        this->color = this->convertToEnum(color);
        this->date_edit = current_date();
    }

    void print() override {
        std::cout << "triangle (" << x1 << ", " << x2 << ", " << x3 << "), color = " << convertToString(color)
             << ", last date edit = " << date_edit;
    }

    int checkParamsTriangle(float x1, float x2, float x3) override {
        if (this->x1 == x1 && this->x2 == x2 && this->x3 == x3) {
            return 1;
        }
        return 0;
    }

    int checkParamsCircle(int, int, int) override { return 0; };
    int checkParamsRectangle(float, float) override { return 0; };
};
