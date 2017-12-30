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
        ptab[0].print_position("Gracz1 kulka");
        ptab[1].print_position("Gracz2 teapot");
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

void next_round(Player ptab[])
{
    system("cls");
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
        if(ptab[0].is_my_turn==true)
        {
            //tura gracza1
            move_player(ptab,0,d1.show_dice_result());
            print_player_info(d1, p_desc);

            ptab[0].is_my_turn=false;
        }
        else
        {
            string p_desc = "Gracz2 teapot";
            ///tura gracza 2
            move_player(ptab,1,d1.show_dice_result());
            print_player_info(d1, p_desc);

            ptab[0].is_my_turn=true;
        }
    }
}




#endif // ROUND_HPP_INCLUDED
