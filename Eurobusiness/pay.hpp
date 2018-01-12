#ifndef PAY_HPP_INCLUDED
#define PAY_HPP_INCLUDED
#include "Player.hpp"
#include "fields.hpp"
int calculate_cash_to_pay(Field pfields[], int field_number)
{
   return pfields[field_number].prize / 2;
}

void pay_to_player(Player ptab[], int how)
{
    //jesli ture ma gracz1 placi graczowi2
    if(ptab[0].is_my_turn==true)
    {
        ptab[0].cash-=how;
        ptab[1].cash+=how;
    }
    else
    {
        ptab[1].cash-=how;
        ptab[0].cash+=how;
    }
    cout << endl << "Jestes na nieswoim polu. Placisz przeciwnikowi: " << how << endl << endl;
}

void check_field_owner(Player ptab[], int player_number, Field pfields[], int field_number)
{
          if(pfields[ field_number ].owner==player_number)
            cout << endl << "Jestes na swoim polu" << endl << endl;
          else if(pfields[ field_number ].owner==-1 || pfields[ field_number ].owner==-2)
          {

          }
          else
            {
                int to_pay = calculate_cash_to_pay(pfields, field_number);
                pay_to_player(ptab,to_pay);

            }
}


#endif // PAY_HPP_INCLUDED
