/*
 * Randall Woodall
 * Nobember 3, 2015
 * test.c
 * Purpose: test platform, handler method.
 */

#include <stdio.h>
#include <time.h>

//
//typedef and definitions for bool
//Randall Woodall
//Allow bools here and through the program.
#define true 1
#define false 0
typedef short bool;

//All external files called below.
#include "cards.c"
#include "ideck.c"
#include "ai.c"

//Prototypes for all functions used in the program **including other files.
//cards.c
void hand_create(hand *to_create, int which);
void draw(hand *add_to, hand *reference);
int peek(hand *peek_at, int card, int chance, int difficulty);
bool steal(hand *stealer, hand *to_steal, int card);
//ideck.c
void setup_ideck(ideck *setup);
void update_ideck(hand *player, hand *ai, ideck *deck);
int bin_search(ideck *deck, int i, int hand);
//ai.c
int calc_prob(ideck *deck);

int main(void)
{
   srand(time(NULL));//Set up srand.
   hand ai;//AI hand.
   hand player;//Player hand.
   ideck deck;//Imaginary deck for the ai to use.
   int i;//Loop control.
   int prob;//Probability of a win.

   //Start two hands, fill them to five cards each, also call the ideck to update correctly.
   hand_create(&ai, 1);
   hand_create(&player, 0);
   setup_ideck(&deck);
   for(i = 0; i < 2; i++)
   {
       draw(&ai, &player);
       draw(&player, &ai);
   }
   update_ideck(&player, &ai, &deck);
   for(i = 2; i < 10; i++)
   {
       draw(&ai, &player);
       draw(&player, &ai);
       update_ideck(&player, &ai, &deck);
   }
   //Unfortunately this takes a good deal of lines, however, when compared to a linear model, this is very fast.

   //Alright, now that the hands and ideck are setup, let's call the calc_prob function.
   prob = calc_prob(&deck);

   //And let's just see the output on the screen.
   printf("Value returned from calc_prob: %d\n", prob);

   return(0);
}//End main.
