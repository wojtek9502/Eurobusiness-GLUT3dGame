#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED
#define START_CASH 2000.0

#include <string>
#include <iostream>
#include "fields.hpp"


using namespace std;

class Player{

public:
    int id;
    string name;
    float cash;
    GLfloat position_x;
    GLfloat position_y;
    GLfloat position_z;
    bool is_my_turn;
    int im_on_field;

Player(int id, string name, float cash, GLfloat position_x, GLfloat position_y, GLfloat position_z, bool is_my_turn)
{
    this->id=id;
    this->name=name;
    this->cash=cash;
    this->position_x=position_x;
    this->position_y=position_y;
    this->position_z=position_z;
    this->is_my_turn=is_my_turn;
    im_on_field=0;
}

void print_position(string player_desc)
{
    cout << player_desc << endl;
    cout << "x = " << position_x << endl;
    cout << "z = " << position_z << endl;
    cout << endl;
}
};










#endif // PLAYER_HPP_INCLUDED
