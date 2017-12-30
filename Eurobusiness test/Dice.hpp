#ifndef DICE_HPP_INCLUDED
#define DICE_HPP_INCLUDED
#include<ctime>
#include<ios>
#include<iostream>


class Dice
{
private:
    int number;

public:
    Dice() {};

    void throw_dice()
    {
        srand(time(NULL));
        number= 1 + rand()%6;
    }

    int show_dice_result()
    {
        return number;
    }





};

#endif // DICE_HPP_INCLUDED
