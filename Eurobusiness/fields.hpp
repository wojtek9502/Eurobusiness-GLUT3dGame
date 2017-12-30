#ifndef FIELDS_HPP_INCLUDED
#define FIELDS_HPP_INCLUDED

using namespace std;
class Field
{
public:
    int id;
    string name;
    GLfloat position_x_start;
    GLfloat position_x_end;
    GLfloat position_y_start;
    GLfloat position_y_end;
    GLfloat position_z_start;
    GLfloat position_z_end;
    float prize;
    int owner;   ///-1 none, 1 player1, 2 player2

    Field(int id, string name,
           GLfloat position_x_start, GLfloat position_y_start, GLfloat position_z_start,
           GLfloat position_x_end, GLfloat position_y_end, GLfloat position_z_end,
           float prize, int owner)
    {
        this->id=id;
        this->name=name;

        this->position_x_start=position_x_start;
        this->position_x_end=position_x_end;

        this->position_y_start=position_y_start;
        this->position_y_end=position_y_end;

        this->position_z_start=position_z_start;
        this->position_z_end=position_z_end;

        this->prize=prize;
        this->owner=owner;
    }
};


#endif // FIELDS_HPP_INCLUDED
