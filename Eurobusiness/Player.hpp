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

Player(int id, string name, float cash, GLfloat position_x, GLfloat position_y, GLfloat position_z)
{
    this->id=id;
    this->name=name;
    this->cash=cash;
    this->position_x;
    this->position_y;
    this->position_z;
}
};


 vector<Player> generate_players( vector<Player>& players)
{
    ///dodawanie slow tutaj wg wzoru (id, slowo, kategoria, litery_do_usuniecia(moga sie powtarzac), gotowe slowo)
    //
    players.push_back(Player(1,"Player1",START_CASH,0.0, 0.0, 0.0));
    players.push_back(Player(2,"Player2",START_CASH,20.0, 0.0, 0.0));
    return players;
}








#endif // PLAYER_HPP_INCLUDED
