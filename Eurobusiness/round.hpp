#ifndef ROUND_HPP_INCLUDED
#define ROUND_HPP_INCLUDED

#include <iostream>
#include "Dice.hpp"
#include<windows.h>
#include <vector>
#include "fields.hpp"
#include "buying_mechanic.hpp"

//@TODO
//przesuwac pionki wzgledem liczby wyrzuconych oczek na odpowiednie miejsca okreslone w klasie pola.
//np pionek1 wylosowal 6 na kostce, idzie i trafia na pole 16, wiec zmienia swoja pozycje na pozycje zapisana w obiekcie Pole o id 16 i w tym id sa wspolrzedne gdzie powinien sie znajdowac ow pionek

using namespace std;

int key;
bool is_game_loaded=false;
bool camera_move=false;

//0=player1    1=player2

void print_player_info(Dice d1, Player ptab[], Field pfields[], int player)
{
    system("cls");
     //player1
    if(player==0)
    {
            cout << "####################################################" << endl;
            cout << "## Tura gracza Gracz1 kula" << endl;
            cout << "## Wyrzucono: " << d1.show_dice_result() << "                                   ##" /**/ << endl;
            cout << "## Gotowka: " << ptab[0].cash<< "" <<endl;
            cout << "## Jestes na polu: " << pfields[ ptab[0].im_on_field ].name<< "" <<endl;
            cout << "##                                                ##" << endl;
            cout << "#####  Wcisnij ENTER aby zakonczyc swoja ture  #####" << endl;
            cout << "####################################################" << endl << endl;
    }
    else
    {
            cout << "####################################################" << endl;
            cout << "## Tura gracza Gracz2 kwadrat" << endl;
            cout << "## Wyrzucono: " << d1.show_dice_result() << "                                   ##" /**/ << endl;
            cout << "## Gotowka: " << ptab[1].cash << "" <<endl;
            cout << "## Jestes na polu: " << pfields[ ptab[1].im_on_field ].name << "" <<endl;
            cout << "##                                                ##" << endl;
            cout << "#####  Wcisnij ENTER aby zakonczyc swoja ture  #####" << endl;
            cout << "####################################################" << endl << endl;
    }


}

void print_players_position(Player ptab[])
{
     ptab[0].print_position("Gracz1 kulka");
     ptab[1].print_position("Gracz2 kwadrat");
     cout << "p1 is my turn= " << ptab[0].is_my_turn << endl;
}


void move_player(Player ptab[], Field pfields[], int player_number, int n_numbers_on_dice)
{
    int next_field_calc = 0;
    if(player_number==0)
    {
       next_field_calc = (ptab[0].im_on_field + n_numbers_on_dice)%40; //wyznacz nastepne pole
       ptab[0].position_x = pfields[next_field_calc].p1_position_x; //przesun na wspolrzedne w tym polu
       ptab[0].position_z = pfields[next_field_calc].p1_position_z;
       ptab[0].im_on_field =  next_field_calc;  ///zaktualizuj pole im_on_field gracza
    }
   else
   {
        next_field_calc = (ptab[1].im_on_field + n_numbers_on_dice)%40; //wyznacz nastepne pole
        ptab[1].position_x = pfields[next_field_calc].p2_position_x;
        ptab[1].position_z = pfields[next_field_calc].p2_position_z;
        ptab[1].im_on_field =  next_field_calc;
   }
}

void next_round(Player ptab[], Field pfields[])
{

    if(is_game_loaded==false)
    {
       is_game_loaded=true;
    }
    else if(camera_move==true)
    {

    }
    else
    {
        if(ptab[0].is_my_turn==true)
        {
            //tura gracza1
            Dice d1;
            d1.throw_dice();
            move_player(ptab, pfields, 0, d1.show_dice_result());
            print_player_info(d1, ptab, pfields, 0);
            buy_field(ptab, 0, pfields, ptab[0].im_on_field);

            ptab[0].is_my_turn=false;
        }
        else
        {
            ///tura gracza 2
             Dice d2;
             d2.throw_dice();
             move_player(ptab, pfields, 1, d2.show_dice_result());
             print_player_info(d2, ptab, pfields, 1);
             buy_field(ptab, 1, pfields, ptab[1].im_on_field);

            ptab[0].is_my_turn=true;
        }
    }
}




#endif // ROUND_HPP_INCLUDED
