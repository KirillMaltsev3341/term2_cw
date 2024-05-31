/**
 * @file doFuncs.cpp
 * @brief Implementation of methods (doFunctions) for Handler class
 * @version 0.1.0
 * @date 2024-05-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Handler.h"
#include "Output.h"
#include "Parser.h"
#include "ImageEditor.h"

#include <algorithm>


void hdlr::Handler::doHelp()
{
    Output::help();
}

void hdlr::Handler::doInfo()
{
    std::string input_file_name;
    
    if (flags_[INPUT_IDX].entered) {
        input_file_name = flags_[INPUT_IDX].parameter;
    } else {
        input_file_name = last_argument_;
    }

    ie::ImagePNG image_png;
    image_png.readImageFromFile(input_file_name.c_str());
    image_png.showInfo();
}

void hdlr::Handler::doCircle()
{
    int x0, y0, radius, thickness;
    bool fill;
    ie::ColorRGBA color, fill_color;
    std::string input_file_name;
    std::string output_file_name = "out.png";

    psr::parseCoords(x0, y0, flags_[CENTER_IDX].parameter);
    psr::parseNumber(radius, flags_[RADIUS_IDX].parameter);
    psr::parseNumber(thickness, flags_[THICKNESS_IDX].parameter);
    psr::parseColorRGBA(color, flags_[COLOR_IDX].parameter);
    fill = flags_[FILL_IDX].entered;
    if (fill) {
        psr::parseColorRGBA(fill_color, flags_[FILL_COLOR_IDX].parameter);
    }
    getFinFoutNames(input_file_name, output_file_name);
    

    psr::checkValueValidity(radius, [](int radius) { return (radius > 0); });
    psr::checkValueValidity(thickness, [](int thickness) { return (thickness > 0); });

    ie::ImagePNG image_png;
    image_png.readImageFromFile(input_file_name.c_str());
    image_png.drawCircle(x0, y0, radius, thickness, color, fill, fill_color);
    image_png.writeImageToFile(output_file_name.c_str());
}

void hdlr::Handler::doRGBFilter()
{
    int component_idx, component_value;
    std::string input_file_name;
    std::string output_file_name = "out.png";

    psr::parseComponentName(component_idx, flags_[COMPONENT_NAME_IDX].parameter);
    psr::parseNumber(component_value, flags_[COMPONENT_VALUE_IDX].parameter);
    getFinFoutNames(input_file_name, output_file_name);

    psr::checkValueValidity(component_value, [](int component_value) { return (component_value >= 0 && component_value <= 255); });    

    ie::ImagePNG image_png;
    image_png.readImageFromFile(input_file_name.c_str());
    image_png.rgbaFilter(component_idx, component_value);
    image_png.writeImageToFile(output_file_name.c_str());
}

void hdlr::Handler::doSplit()
{
    int number_x, number_y, thickness;
    ie::ColorRGBA color;
    std::string input_file_name;
    std::string output_file_name = "out.png";
    
    psr::parseNumber(number_x, flags_[NUMBER_X_IDX].parameter);
    psr::parseNumber(number_y, flags_[NUMBER_Y_IDX].parameter);
    psr::parseNumber(thickness, flags_[THICKNESS_IDX].parameter);
    psr::parseColorRGBA(color, flags_[COLOR_IDX].parameter);
    getFinFoutNames(input_file_name, output_file_name);


    psr::checkValueValidity(number_x, [](int number_x) { return (number_x > 1); });
    psr::checkValueValidity(number_y, [](int number_y) { return (number_y > 1); });
    psr::checkValueValidity(thickness, [](int thickness) { return (thickness > 0); });


    ie::ImagePNG image_png;
    image_png.readImageFromFile(input_file_name.c_str());

    for (int y = image_png.getHeight() / number_y; y < image_png.getHeight(); y += std::max(1, image_png.getHeight() / number_y)) {
        for (int i = 0; i <= thickness/2; i++) {
            image_png.drawBresenhamLine(0, y-i, image_png.getWidth()-1, y-i, color);
            image_png.drawBresenhamLine(0, y+i, image_png.getWidth()-1, y+i, color);
        }
    }
    
    for (int x = image_png.getWidth() / number_x; x < image_png.getWidth(); x += std::max(1, image_png.getWidth() / number_x)) {
        for (int i = 0; i <= thickness/2; i++) {
            image_png.drawBresenhamLine(x-i, 0, x-i, image_png.getHeight()-1, color);
            image_png.drawBresenhamLine(x+i, 0, x+i, image_png.getHeight()-1, color);
        }
    }

    image_png.writeImageToFile(output_file_name.c_str());
}

void hdlr::Handler::doSquaredLines()
{
    int left, up, side_size, thickness;
    bool fill;
    ie::ColorRGBA color, fill_color;

    std::string input_file_name;
    std::string output_file_name = "out.png";

    psr::parseCoords(left, up, flags_[LEFT_UP_IDX].parameter);
    psr::parseNumber(side_size, flags_[SIDE_SIZE_IDX].parameter);
    psr::parseNumber(thickness, flags_[THICKNESS_IDX].parameter);
    psr::parseColorRGBA(color, flags_[COLOR_IDX].parameter);
    fill = flags_[FILL_IDX].entered;
    if (fill) {
        psr::parseColorRGBA(fill_color, flags_[FILL_COLOR_IDX].parameter);
    }
    getFinFoutNames(input_file_name, output_file_name);

    psr::checkValueValidity(side_size, [](int side_size) { return (side_size > 0); });
    psr::checkValueValidity(thickness, [](int thickness) { return (thickness > 0); });

    ie::ImagePNG image_png;
    image_png.readImageFromFile(input_file_name.c_str());

    image_png.drawPolygon(
        {
            {left, up},
            {left+side_size, up},
            {left+side_size, up+side_size},
            {left, up+side_size},
        },
        thickness, color, fill, fill_color);

    image_png.drawLine(left, up, left+side_size, up+side_size, thickness, color);
    image_png.drawLine(left+side_size, up, left, up+side_size, thickness, color);

    image_png.writeImageToFile(output_file_name.c_str());

}

void hdlr::Handler::doOutsideOrnament()
{
    int thickness;
    ie::ColorRGBA color;

    std::string input_file_name;
    std::string output_file_name = "out.png";

    psr::parseNumber(thickness, flags_[THICKNESS_IDX].parameter);
    psr::parseColorRGBA(color, flags_[COLOR_IDX].parameter);
    getFinFoutNames(input_file_name, output_file_name);

    psr::checkValueValidity(thickness, [](int thickness) { return (thickness > 0); });

    ie::ImagePNG image_png_src;
    image_png_src.readImageFromFile(input_file_name.c_str());

    ie::ImagePNG image_png_dest;
    image_png_dest.setSize(image_png_src.getWidth() + 2 * thickness, image_png_src.getHeight() + 2 * thickness);
    image_png_dest.floodFill(0, 0, color);
    image_png_dest.paste(image_png_src, thickness, thickness);

    image_png_dest.writeImageToFile(output_file_name.c_str());
}