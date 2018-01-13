#ifndef DICE_HPP_INCLUDED
#define DICE_HPP_INCLUDED
#include<ctime>
#include<iostream>
#include<windows.h>


class Dice
{
private:
    int number;

public:
    Dice()
    {

    };

    void throw_dice()
    {
        srand(time(NULL));
        number= (1 + rand()%1000) %6 + 1 ;
    }

    int show_dice_result()
    {
        return number;

        //only for test. Uncomment return on top.
        //return 1+rand()%2;
    }





};

#endif // DICE_HPP_INCLUDED
