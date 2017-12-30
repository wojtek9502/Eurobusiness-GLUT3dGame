#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED
#define START_CASH 2000.0

#include <string>
#include <vector>


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
}
};


 vector<Player> generate_players( vector<Player>& players)
{

    players.push_back(Player(1,"Player1",START_CASH,0.0, 0.0, 0.0,true));
    players.push_back(Player(2,"Player2",START_CASH,20.0, 0.0, 0.0,false));
    return players;
}








#endif // PLAYER_HPP_INCLUDED
