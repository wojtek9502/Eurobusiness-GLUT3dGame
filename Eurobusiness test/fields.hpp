#ifndef FIELDS_HPP_INCLUDED
#define FIELDS_HPP_INCLUDED
#include<vector>

using namespace std;
class Field
{
public:
    int id;
    string name;
    GLfloat p1_position_x;
    GLfloat p1_position_y;
    GLfloat p1_position_z;
    GLfloat p2_position_x;
    GLfloat p2_position_y;
    GLfloat p2_position_z;

    float prize;
    int owner;   ///-1 none, 1 player1, 2 player2

    Field(int id, string name,
           GLfloat p1_position_x, GLfloat p1_position_y, GLfloat p1_position_z,
           GLfloat p2_position_x, GLfloat p2_position_y, GLfloat p2_position_z,
           float prize, int owner)
    {
        this->id=id;
        this->name=name;

        this->p1_position_x=p1_position_x;
        this->p1_position_y=p1_position_y;
        this->p1_position_z=p1_position_z;

        this->p2_position_x=p2_position_x;
        this->p2_position_y=p2_position_y;
        this->p2_position_z=p2_position_z;

        this->prize=prize;
        this->owner=owner;
    }

};


#endif // FIELDS_HPP_INCLUDED
