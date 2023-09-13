#include "geometrys.h"

color_figure FlatGeometryFig::convertToEnum(std::string color) {
    if (color == "red") {
        return color_figure::RED;
    }
    else if (color == "orange") {
        return color_figure::ORANGE;
    }
    else if (color == "yellow") {
        return color_figure::YELLOW;
    }
    else if (color == "green") {
        return color_figure::GREEN;
    }
    else if (color == "azure") {
        return color_figure::AZURE;
    }
    else if (color == "blue") {
        return color_figure::BLUE;
    }
    else if (color == "purple"){
        return color_figure::PURPLE;
    }
    return color_figure::ERROR;
}

std::string FlatGeometryFig::convertToString(color_figure color) {
    if (color == color_figure::RED) {
        return "red";
    }
    else if (color == color_figure::ORANGE) {
        return "orange";
    }
    else if (color == color_figure::YELLOW) {
        return "yellow";
    }
    else if (color == color_figure::GREEN) {
        return "green";
    }
    else if (color == color_figure::AZURE) {
        return "azure";
    }
    else if (color == color_figure::BLUE) {
        return "blue";
    }
    else if (color == color_figure::PURPLE){
        return "purple";
    }

    return "error";
}
