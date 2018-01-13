#ifndef BUYING_MECHANIC_HPP_INCLUDED
#define BUYING_MECHANIC_HPP_INCLUDED
#include "fields.hpp"

bool buy_time_end=false;

void buy_field(Player ptab[], int player_number, Field pfields[], int field_number)
{
        pfields[field_number].owner=player_number;  //przypisz miasto do gracza1
        ptab[player_number].cash -= pfields[field_number].prize;  //odejmij kase
         cout << endl <<"Gracz" << player_number+1 << "  kupil pole: " << pfields[field_number].name << endl;
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

void buy(Player ptab[], Field pfields[])
{
     if(ptab[0].is_my_turn==true)
     {
          if(check_buy_field(ptab,1,pfields,ptab[1].im_on_field)==true) //czy moze kupic
                 {
                    buy_field(ptab,1,pfields,ptab[1].im_on_field); //kupowanie
                 }
     }
     else
     {
          if(check_buy_field(ptab,0,pfields,ptab[0].im_on_field)==true) //czy moze kupic
                 {
                    buy_field(ptab,0,pfields,ptab[0].im_on_field); //kupowanie
                 }
     }
}



#endif // BUYING_MECHANIC_HPP_INCLUDED
