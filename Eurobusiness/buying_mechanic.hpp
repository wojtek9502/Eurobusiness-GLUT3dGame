#ifndef BUYING_MECHANIC_HPP_INCLUDED
#define BUYING_MECHANIC_HPP_INCLUDED
#include "fields.hpp"

bool buy_time_end=false;

void buy_field(Player ptab[], int player_number, Field pfields[], int field_number)
{
    cout << "  player number= " << player_number+1 << " field_name=" << pfields[field_number].name << endl;
        pfields[field_number].owner=player_number;  //przypisz miasto do gracza1
        ptab[player_number].cash -= pfields[field_number].prize;  //odejmij kase
}

bool check_buy_field(Player ptab[], int player_number, Field pfields[], int field_number)
{
        if(pfields[field_number].owner==-2 ||
           pfields[field_number].owner== 1 ||
           pfields[field_number].owner== 0 ||
           ptab[player_number].cash < pfields[field_number].prize)
            return false;
      if(pfields[field_number].owner==-1)
            return true;
}





#endif // BUYING_MECHANIC_HPP_INCLUDED
