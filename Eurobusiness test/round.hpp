#ifndef ROUND_HPP_INCLUDED
#define ROUND_HPP_INCLUDED
#include "Dice.hpp"
#include <iostream>
#include "Player.hpp"
#include<windows.h>

using namespace std;

int key;
bool is_game_loaded=false;
bool camera_move=false;

//0=player1    1=player2
void print_player_info(Dice d1, string desc)
{
    cout << "####################################################" << endl;
    cout << "## Tura gracza " << desc  << endl;
    cout << "## Wyrzucono: " << d1.show_dice_result() << "                                   ##" /**/ << endl;
    cout << "##                                                ##" << endl;
    cout << "#####  Wcisnij ENTER aby zakonczyc swoja ture  #####" << endl;
    cout << "####################################################" << endl << endl;
}

void move_player(Player ptab[], int player_number, int n_numbers_on_dice)
{
        //poruszanie. Kazde pole ma 16 "Krokow"
        int steps_to_field = 5;
        for(int i=0; i<n_numbers_on_dice; i++)
        {
            for(int j=0; j<steps_to_field; j++)
            {
                 if(player_number==1)
                    ptab[0].position_x-=j;
                 else
                    ptab[1].position_x-=j;
            }
        }
        ptab[0].print_position("Gracz1 kulka");
        ptab[1].print_position("Gracz2 kwadrat");
}

void move_for_test(Player ptab[], string direction)
{
        if(direction=="up")
            ptab[0].position_z--;
        if(direction=="down")
            ptab[0].position_z++;
        if(direction=="left")
            ptab[0].position_x--;
        if(direction=="right")
            ptab[0].position_x++;

        ptab[0].print_position("Gracz1 kulka");
        //ptab[1].print_position("Gracz2 kwadrat");
}

void next_round(Player ptab[])
{
        Dice d1;
        d1.throw_dice();

    if(is_game_loaded==false)
    {
       is_game_loaded=true;
    }
    else if(camera_move==true)
    {

    }
    else
    {
        string p_desc = "Gracz1 kulka";
        //cout << "p1 is my turn= " << ptab[0].is_my_turn << endl;
        if(ptab[0].is_my_turn==true)
        {
            //tura gracza1 odkomentowac move player
            //move_player(ptab,1,d1.show_dice_result());
           // print_player_info(d1, p_desc);

            ptab[0].is_my_turn=false;
        }
        else
        {
            string p_desc = "Gracz2 kwadrat";
            ///tura gracza 2 POTEM ODBLOKOWAC MOVE
            //move_player(ptab,2,d1.show_dice_result());
           // print_player_info(d1, p_desc);

            ptab[0].is_my_turn=true;
        }
    }
}




#endif // ROUND_HPP_INCLUDED