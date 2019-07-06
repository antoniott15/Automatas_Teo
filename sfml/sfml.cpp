//
//  main.cpp"
//  sfml
//
//  Created by Antonio Toche on 6/12/19.
//  Copyright © 2019 Antonio Toche. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Header.h"

#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <SFML/Window.hpp>

int rectEquationX(float x1, float x2)
{
    int posx = (x2 + x1) / 2;
    return posx + 5;
}

int rectEquationY(float y1, float y2)
{
    int posy = (y2 + y1) / 2;
    return posy + 5;
}

void setDirection(float x1, float y1, float x2, float y2, sf::RenderWindow &window)
{
    sf::CircleShape triangle;
    triangle.setRadius(10);
    triangle.setPointCount(3);
    float newX1 = rectEquationX(x1, x2);
    float newY1 = rectEquationY(y1, y2);
    float newPosY1 = (y2 + newY1) / 2;
    float newPosX1 = (x2 + newX1) / 2;
    /* float pendient = (y2 - newPosY1) / (x2 - newPosX1);
    pendient = atan(pendient);
    sf::Rect<float> size = triangle.getGlobalBounds();
    triangle.setOrigin(sf::Vector2f((size.width/2)/5,(size.height/2)/5));
    std::cout << "Arco tang: " << pendient << std::endl;
    triangle.setRotation(pendient*10);*/
    triangle.setPosition(newPosX1, newPosY1);
    triangle.setFillColor(sf::Color(255, 0, 0));
    triangle.setOutlineColor(sf::Color(0, 0, 255));
    window.draw(triangle);
}

void setLines(float x1, float y1, float x2, float y2, sf::RenderWindow &window, char peso)
{
    setDirection(x1, y1, x2, y2, window);
    std::string weight = std::to_string(peso);
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("Quicksand-Bold.ttf"))
    {
        std::cout << "error loading font" << std::endl;
    }
    text.setString(peso);
    text.setFillColor(sf::Color(63, 63, 63));
    int posX = rectEquationX(x1, x2);
    int posY = rectEquationY(y1, y2);
    text.setPosition(posX, posY);
    text.setFont(font);
    text.setCharacterSize(20);
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(x1 + 10, y1 + 10)),
        sf::Vertex(sf::Vector2f(x2 + 10, y2 + 10))};

    window.draw(line, 10, sf::Lines);
    window.draw(text);
}

void setCircle(float x, float y, sf::RenderWindow &window, char i)
{
    std::string weight = std::to_string(i);
    sf::CircleShape nodeDraw(360);
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("Quicksand-Bold.ttf"))
    {
        std::cout << "error loading font" << std::endl;
    }
    text.setString(weight);
    text.setFillColor(sf::Color(0, 255, 0));
    text.setPosition(x + 9, y + 9);
    text.setFont(font);
    text.setCharacterSize(20);
    nodeDraw.setRadius(20);
    nodeDraw.setFillColor(sf::Color(255, 255, 255));
    nodeDraw.setOutlineColor(sf::Color(0, 178, 209));
    nodeDraw.setOutlineThickness(5);
    nodeDraw.setPosition(x, y);
    window.draw(nodeDraw);
    window.draw(text);
}

int main()
{

    sf::RenderWindow window(sf::VideoMode(1200, 1200), ("Graph Project"));
    std::vector<node> nodes;
    std::vector<edge> edges;
    std::vector<float> posx, posy;
    std::vector<char> pesos;
    std::vector<float> conexion1;
    std::vector<float> conexion2;
    int valueNode1, rows, i;
    char valuePeso;
    std::string file = "../input.txt", line;
    std::fstream f(file);
    float valuex, valuey, valueX, valueY;
    if (f.is_open())
    {
        std::getline(f, line);
        std::string::size_type cz = 0;
        rows = stoi(line, &cz);

        for (i = 0; i < rows; i++)
        {
            getline(f, line);
            std::stringstream s(line);
            s >> valueNode1 >> valuex >> valuey;
            posx.push_back(valuex);
            posy.push_back(valuey);
        }
        getline(f, line);
        while (getline(f, line))
        {
            std::stringstream j(line);
            j >> valueX >> valueY >> valuePeso;
            conexion1.push_back(valueX);
            conexion2.push_back(valueY);
            pesos.push_back(valuePeso);
        }
    }
    for (int i = 0; i < pesos.size(); i++)
    {
        float pos1 = conexion1.at(i) - 1;
        float pos2 = conexion2.at(i) - 1;
        float x1 = posx.at(pos1);
        float y1 = posy.at(pos1);
        float x2 = posx.at(pos2);
        float y2 = posy.at(pos2);
        std::cout << "x1 " << x1 << "y1 " << y1 << "x2 " << x2 << "y2 " << y2 << std::endl;
        edges.push_back(edge(x1, y1, x2, y2));
    }

    for (int i = 0; i < rows; i++)
    {
        nodes.push_back(node(posx.at(i), posy.at(i)));
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear(sf::Color(0, 202, 165));

        for (int i = 0; i < rows; i++)
        {
            char number = i + 97;
            setCircle(nodes.at(i)._posX, nodes.at(i)._posY, window, i);
        }

        for (int i = 0; i < pesos.size(); i++)
        {
            char peso = pesos.at(i);
            setLines(edges.at(i)._posX1, edges.at(i)._posY1, edges.at(i)._posX2, edges.at(i)._posY2, window, peso);
        }

        window.display();
    }

    return 0;
}