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

    int throw_dice()
    {
        srand(time(NULL));
        number= 1 + rand()%6;
        return number;
    }

    void print_throw_result()
    {
        cout << number;
    }

};

#endif // DICE_HPP_INCLUDED
