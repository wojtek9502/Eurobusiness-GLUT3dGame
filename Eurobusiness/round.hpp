#ifndef ROUND_HPP_INCLUDED
#define ROUND_HPP_INCLUDED

#include <iostream>
#include "Dice.hpp"
#include<windows.h>
#include <vector>
#include "fields.hpp"
#include "buying_mechanic.hpp"
#include "pay.hpp"

//@TODO
//przesuwac pionki wzgledem liczby wyrzuconych oczek na odpowiednie miejsca okreslone w klasie pola.
//np pionek1 wylosowal 6 na kostce, idzie i trafia na pole 16, wiec zmienia swoja pozycje na pozycje zapisana w obiekcie Pole o id 16 i w tym id sa wspolrzedne gdzie powinien sie znajdowac ow pionek

using namespace std;

bool is_game_loaded=false;
bool camera_move=false;

//player1=kula player2=kwadrat!!!
//0=player1    1=player2

void check_go_through_start(Player ptab[], int player_number)
{
    //cout << "aktualne pole: " << ptab[0].im_on_field << " poprzednie pole: " << ptab[0].prev_field_nr;
    if(ptab[player_number].prev_field_nr > ptab[player_number].im_on_field)
    {
        ptab[player_number].cash += 500;
        cout << endl << "Otrzymujesz 500 za przejscie przez start" << endl << endl;
    }
}

void check_win(Player ptab[])
{
   // cout << "g1: " << ptab[0].cash << endl;
    //cout << "g2: " << ptab[1].cash << endl;

        if(ptab[0].cash < 0 )
        {
            system("cls");
            cout << "Gracz1 zbankrutowal." << endl << "WYGRYWA GRACZ2" << endl;
            cout << "Wcisnij ESC aby wyjsc." << endl;
            exit(1);
        }

        if(ptab[1].cash < 0)
        {
            system("cls");
            cout << "Gracz2 zbankrutowal." << endl << "WYGRYWA GRACZ1" << endl;
            cout << "Wcisnij ESC aby wyjsc." << endl;
            exit(2);
    }

}

void print_owned_field(int player_number, Field pfields[])
{
    cout << "Twoje miasta to:" << endl;
    for(int i=0; i<40; i++)
    {
        if(player_number==pfields[i].owner)
        {
            cout << pfields[i].name << ", ";
        }
    }
    cout << endl;
}

void print_player_info(Dice d1, Player ptab[], int player_number, Field pfields[], string player_description)
{
            cout << "####################################################" << endl;
            cout << "## Tura gracza Gracz" << player_number+1 << " " << player_description << endl;    //Nie zmienac na player_number++ !!!
            cout << "## Wyrzucono: " << d1.show_dice_result() << endl;
            cout << "## Gotowka: " << ptab[player_number].cash<< "" <<endl;
            cout << "## Jestes na polu: " << pfields[ ptab[player_number].im_on_field ].name
                    << "  Koszt: " << pfields[ ptab[player_number].im_on_field ].prize <<endl;
            cout << "##                                                  " << endl;
            cout << "####################################################" << endl << endl;

            if(check_buy_field(ptab,player_number,pfields,ptab[player_number].im_on_field)==false)
                cout << "Nie mozesz kupic tego pola" << endl;
            else
                cout << "Wcisnij 't' aby kupic to pole" << endl;

}



void print_players_position(Player ptab[])
{
     ptab[0].print_position("Gracz1 kulka");
     ptab[1].print_position("Gracz2 kwadrat");
     cout << "p1 is my turn= " << ptab[0].is_my_turn << endl;
}



int calculate_tax(int player_number, Field pfields[])
{
    int n_fields = 0;
    ///podatek obliczany na podstawie: liczba miast * 40
    //zliczenie liczby miast

    for(int i=0; i<40; i++)
    {
        if(player_number==pfields[i].owner)
        {
            n_fields++;
        }
    }

    return 40*n_fields;

}

void check_enter_on_special_fields(Player ptab[], int player_number, Field pfields[])
{
    switch(ptab[player_number].im_on_field)
    {
        //parking platny
        case 4:
            {
                cout << "Parking platny, placisz 400" << endl;
                ptab[player_number].cash -= 400;
            }break;

        case 30: //idziesz do wiezienia
            {
                cout << "Idziesz do wiezienia" << endl;
                ptab[player_number].im_on_field=9;
                ptab[player_number].in_prison=true;
                ptab[player_number].round_to_freedom=3;
            }break;

        case 38: //podatek od wzbogacenia
            {
               int to_pay = calculate_tax(player_number,pfields);
               cout << "Podatek od wzbogacenia, placisz: " << to_pay << endl;
               ptab[0].cash -= to_pay;
            }break;

        case 10: //wiezienie
        {

        }
    }
}

void move_player(Player ptab[], Field pfields[], int player_number, int n_numbers_on_dice)
{
    int next_field_calc = 0;
    if(player_number==0)
    {
       next_field_calc = (ptab[0].im_on_field + n_numbers_on_dice)%40; //wyznacz nastepne pole
       ptab[0].position_x = pfields[next_field_calc].p1_position_x; //przesun na wspolrzedne w tym polu
       ptab[0].position_z = pfields[next_field_calc].p1_position_z;
       ptab[0].prev_field_nr = ptab[0].im_on_field; //zapis poprzedniego numeru pola (potrzebny przy przejsciu przez start)
       ptab[0].im_on_field =  next_field_calc;  ///zaktualizuj pole im_on_field gracza
    }
   else
   {
        next_field_calc = (ptab[1].im_on_field + n_numbers_on_dice)%40; //wyznacz nastepne pole
        ptab[1].position_x = pfields[next_field_calc].p2_position_x;
        ptab[1].position_z = pfields[next_field_calc].p2_position_z;
        ptab[1].prev_field_nr = ptab[1].im_on_field;
        ptab[1].im_on_field =  next_field_calc;
   }
}

void move_player_on_field(Field pfields[], int field_nr, Player ptab[])
{
    if(ptab[0].is_my_turn==true)
    {
       ptab[0].position_x = pfields[field_nr].p1_position_x; //przesun na wspolrzedne w tym polu
       ptab[0].position_z = pfields[field_nr].p1_position_z;
       ptab[0].im_on_field =  field_nr;  ///zaktualizuj pole im_on_field gracza
    }
   else
   {
       ptab[1].position_x = pfields[field_nr].p2_position_x; //przesun na wspolrzedne w tym polu
       ptab[1].position_z = pfields[field_nr].p2_position_z;
       ptab[1].im_on_field =  field_nr;  ///zaktualizuj pole im_on_field gracza
   }
}

void check_prison(Player ptab[], int player_number)
{
    if(ptab[player_number].in_prison==true && ptab[player_number].round_to_freedom!=0)
    {
        cout << "Jestes w wiezieniu jeszcze przez " <<  ptab[player_number].round_to_freedom << " rund" << endl;
        ptab[player_number].prev_field_nr=9;
        ptab[player_number].im_on_field=9;
        ptab[player_number].round_to_freedom -= 1;
    }
    else
    {
        ptab[player_number].in_prison=false;
    }
}

void next_round(Player ptab[], Field pfields[])
{
    system("cls");
    check_win(ptab);

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
            check_prison(ptab,0);

            if(ptab[0].in_prison==false)  ///jak jest w wiezieniu to sie nie rusza
            {
                move_player(ptab, pfields, 0, d1.show_dice_result());
            }
            else
            {
                move_player_on_field(pfields,10,ptab);
            }

            check_go_through_start(ptab, 0);
            check_enter_on_special_fields(ptab, 0, pfields);
            check_field_owner(ptab, 0, pfields, ptab[0].im_on_field);
            print_player_info(d1, ptab, 0 , pfields, "kula");
            print_owned_field(0,pfields);


            ptab[0].is_my_turn=false;
           // cout << "Koniec tury gracza1" << endl;
              //cout << "Start tury gracza2" << endl;


        }
        else
        {
            ///tura gracza 2
             Dice d2;
             d2.throw_dice();

             check_prison(ptab,1);
             if(ptab[1].in_prison==false)  ///jak jest w wiezieniu to sie nie rusza
            {
                move_player(ptab, pfields, 1, d2.show_dice_result());
            }
            else
            {
                move_player_on_field(pfields, 10, ptab);
            }

             check_go_through_start(ptab, 1);
             check_enter_on_special_fields(ptab, 1, pfields);
             check_field_owner(ptab, 1, pfields, ptab[1].im_on_field);
             print_player_info(d2, ptab, 1, pfields, "kwadrat");
             print_owned_field(1,pfields);


             ptab[0].is_my_turn=true;
              //cout << "Koniec tury gracza2" << endl;
              //cout << "Start tury gracza1" << endl;


        }
    }
}




#endif // ROUND_HPP_INCLUDED
