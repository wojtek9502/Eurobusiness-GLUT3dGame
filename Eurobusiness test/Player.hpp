#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED
#define START_CASH 2000.0

#include <string>
#include <iostream>


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

Player(int id, string name, float cash, GLfloat position_x, GLfloat position_y, GLfloat position_z, bool is_my_turn)
{
    this->id=id;
    this->name=name;
    this->cash=cash;
    this->position_x=position_x;
    this->position_y=position_y;
    this->position_z=position_z;
    this->is_my_turn=is_my_turn;
}

void print_position(string player_desc)
{
    cout << "Dane po ruchu" << endl;
    cout << player_desc << endl;
    cout << "x = " << position_x << endl;
    cout << "y = " << position_y << endl;
    cout << "z = " << position_z << endl;
    cout << endl;
}
};


#endif // PLAYER_HPP_INCLUDED
