#ifndef ROUND_HPP_INCLUDED
#define ROUND_HPP_INCLUDED
#include "Dice.hpp"
#include <iostream>

using namespace std;

int key;

void wait_on_enter_fun()
{
    char temp = 'x';
    while (temp != '\n')
    cin.get(temp);
}

void next_round(Player ptab[])
{

        Dice d1;
        if(ptab[1].is_my_turn==true)
        {
            //tura gracza1
            //cout << "Tura gracza1" << endl;
            d1.throw_dice();
    //      cout << "Wyrzuciles " << d1.print_throw_result();


            ptab[1].is_my_turn=false;

        }
        else
        {
            //tura gracza2
           // cout << "Tura gracza2" << endl;
            d1.throw_dice();

            ptab[1].is_my_turn=true;
        }
}




#endif // ROUND_HPP_INCLUDED
