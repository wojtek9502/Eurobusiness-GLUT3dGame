#ifndef ROUND_HPP_INCLUDED
#define ROUND_HPP_INCLUDED

#include <iostream>
#include "Dice.hpp"
#include<windows.h>

using namespace std;

int key;
bool is_game_loaded=false;
bool camera_move=false;

//0=player1    1=player2

void print_player_info(Dice d1,Player ptab[], int player, string desc)
{
     //player1
    if(player==0)
    {
            cout << "####################################################" << endl;
            cout << "## Tura gracza " << desc  << endl;
            cout << "## Wyrzucono: " << d1.show_dice_result() << "                                   ##" /**/ << endl;
            cout << "## Gotowka: " << ptab[0].cash<< "" <<endl;
            cout << "##                                                ##" << endl;
            cout << "#####  Wcisnij ENTER aby zakonczyc swoja ture  #####" << endl;
            cout << "####################################################" << endl << endl;
    }
    else
    {
            cout << "####################################################" << endl;
            cout << "## Tura gracza " << desc  << endl;
            cout << "## Wyrzucono: " << d1.show_dice_result() << "                                   ##" /**/ << endl;
            cout << "## Gotowka: " << ptab[1].cash<< "" <<endl;
            cout << "##                                                ##" << endl;
            cout << "#####  Wcisnij ENTER aby zakonczyc swoja ture  #####" << endl;
            cout << "####################################################" << endl << endl;
    }

}

void move_player(Player ptab[], int player_number, int n_numbers_on_dice)
{
    int steps_to_field=3;
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
        cout << "p1 is my turn= " << ptab[0].is_my_turn << endl;
        if(ptab[0].is_my_turn==true)
        {
            //tura gracza1
            move_player(ptab,1,d1.show_dice_result());
            print_player_info(d1,ptab, 0, p_desc);

            ptab[0].is_my_turn=false;
        }
        else
        {
            string p_desc = "Gracz2 kwadrat";
            ///tura gracza 2
            move_player(ptab,2,d1.show_dice_result());
            print_player_info(d1,ptab,1, p_desc);

            ptab[0].is_my_turn=true;
        }
    }
}




#endif // ROUND_HPP_INCLUDED
