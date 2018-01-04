#ifndef BUYING_MECHANIC_HPP_INCLUDED
#define BUYING_MECHANIC_HPP_INCLUDED
#include "fields.hpp"

bool buying_decision_stop = false;

void buy_field(Player ptab[], int player_number, Field pfields[], int field_number)
{
    if(pfields[field_number].owner==-2  || ptab[player_number].cash < pfields[field_number].prize)
        cout << "Nie mozesz kupic tego pola" << endl;
    else
    {
        cout << "Mozesz kupic to pole" << endl;

    }

}



#endif // BUYING_MECHANIC_HPP_INCLUDED
