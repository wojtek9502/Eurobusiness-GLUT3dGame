#ifndef ROUND_HPP_INCLUDED
#define ROUND_HPP_INCLUDED
#include "Dice.hpp"
#include <iostream>
#include "Player.hpp"
#include<windows.h>

using namespace std;

int key;
bool is_game_loaded=false;

void wait_on_enter_fun()
{
    char temp = 'x';
    while (temp != '\n')
    cin.get(temp);
}

void move_player(Player ptab[], int player_number, int n_numbers_on_dice)
{
    if(is_game_loaded==false)
    {
       is_game_loaded=true;
    }
    else
    {
        wait_on_enter_fun();
        //poruszanie. Kazde pole ma 16 "Krokow"

        int steps_to_field = 5;
        for(int i=0; i<n_numbers_on_dice; i++)
        {
            for(int j=0; j<steps_to_field; j++)
            {
                 if(player_number==0)
                    ptab[0].position_x-=j;
                 else
                    ptab[1].position_x-=j;
            }
        }
    }


}

void next_round(Player ptab[])
{
        Dice d1;
        d1.throw_dice();

        if(ptab[0].is_my_turn==true)
        {
            cout << "###############################" << endl;
            cout << "Tura gracza1" << endl;
            cout << "Wurzucono: " << 2 /*d1.show_dice_result()*/ << endl;
            cout << "###############################" << endl << endl;

            //tura gracza1
            //cout << "Tura gracza1" << endl;
           // move_player(ptab,0,d1.throw_dice());
            move_player(ptab,0,2);

            ptab[0].is_my_turn=false;

        }
        else
        {
            //tura gracza2
            cout << "###############################" << endl;
            cout << "Tura gracza2" << endl;
            cout << "Wurzucono: " << 1 /*d1.show_dice_result()*/ << endl;
            cout << "###############################" << endl << endl;

            // move_player(ptab,1,d1.throw_dice())
            move_player(ptab,1,1);

            ptab[0].is_my_turn=true;
        }
}




#endif // ROUND_HPP_INCLUDED
