//
//  Header.h
//  sfml
//
//  Created by Antonio Toche on 6/12/19.
//  Copyright © 2019 Antonio Toche. All rights reserved.
//

#ifndef Header_h
#define Header_h
class node
{
public:
    float _posX, _posY;

    node(float x, float y) : _posX(x), _posY(y)
    {
    }
};

class edge
{
public:
    float _posX1, _posY1, _posX2, _posY2;

    edge(float x1, float y1, float x2, float y2) : _posX1(x1), _posY1(y1), _posX2(x2), _posY2(y2)
    {
    }
};

#endif /* Header_h */
