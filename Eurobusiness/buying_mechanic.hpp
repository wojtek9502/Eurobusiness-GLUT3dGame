#ifndef BUYING_MECHANIC_HPP_INCLUDED
#define BUYING_MECHANIC_HPP_INCLUDED
#include "fields.hpp"


void buy_field(Player ptab[], int player_number, Field pfields[], int field_number)
{

}

void check_buy_field(Player ptab[], int player_number, Field pfields[], int field_number)
{

        if(pfields[field_number].owner==-2  || ptab[player_number].cash < pfields[field_number].prize)
            cout << "Nie mozesz kupic tego pola" << endl;
        else if(pfields[field_number].owner==-1)
            cout << "Wcisnij 't' aby kupic to pole" << endl;
}



#endif // BUYING_MECHANIC_HPP_INCLUDED
