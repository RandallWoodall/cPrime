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

//Prototypes for all functions used in the program **including other files.
//cards.c
void hand_create(hand *to_create, int which);
void draw(hand *add_to, hand *reference);
int peek(hand *peek_at, int card, int chance, int difficulty);
bool steal(hand *stealer, hand *to_steal, int card);
//ai.c
void setup_ideck(ideck *setup);
void update_ideck(hand *player, hand *ai, ideck *deck);
int bin_search(ideck *deck, int i, int hand);

int main(void)
{
   srand(time(NULL));//Set up srand.
   hand ai;//AI hand.
   hand player;//Player hand.
   ideck deck;//Imaginary deck for the ai to use.
   int i;//Loop control.
   int outcome;//outcome of peek.

   //Initialize both hands + ideck.
   hand_create(&ai, 1);
   hand_create(&player, 0);
   setup_ideck(&deck);

   //The only value that needs initialized is card_count.
   ai.card_count = 0;
   player.card_count =0;
   //This can be done at the start of every round when declaring new hands.

   for(i = 0; i < 2; i++)
   {
      draw(&ai, &player);
      draw(&player, &ai);
   }//End for.
   update_ideck(&player, &ai, &deck);

   //First, let's see the values in the array.
   printf("First, what does the computer see in the ideck?\n");
   for(i = 0; i < 85; i++)
   {
      printf("%d %c ", deck.all_cards[i], deck.all_suite[i]);
   }
   printf("\n");

   //Now that we have seen this, let's see the individual hands.
   printf("Now, what does the computer say is in each hand?\n");
   for(i = 0; i < 10; i++)
      printf("ai_cards[%d] = %2d, known_p_cards[%d] = %2d\n", i, deck.ai_cards[i], i, deck.known_p_cards[i]);

   //Now, let's assume the ai peeks at a player card. (changing manually for time's sake.)
   printf("What if we peek at a player card?\n");
   player.visibility[1] = true;
   //Add another card to each.
   draw(&ai, &player);
   draw(&player, &ai);
   //Update the ideck.
   update_ideck(&player, &ai, &deck);
   printf("\n");
   //Re-print.
   for(i = 0; i < 10; i++)
      printf("ai_cards[%d] = %2d, known_p_cards[%d] = %2d\n", i, deck.ai_cards[i], i, deck.known_p_cards[i]);

   //Alright, so that works, now, what happens if we steal the visible card?
   printf("What happens if we steal a card?\n");
   steal(&ai, &player, 1);
   draw(&player, &ai);
   update_ideck(&player, &ai, &deck);
   printf("\n");
   for(i = 0; i < 10; i++)
      printf("ai_cards[%d] = %2d, known_p_cards[%d] = %2d\n", i, deck.ai_cards[i], i, deck.known_p_cards[i]);

   //If the player steals our card.
   printf("What if the player steals our card?\n");
   steal(&player, &ai, 2);
   draw(&ai, &player);
   update_ideck(&player, &ai, &deck);
   printf("\n");
   for(i = 0; i < 10; i++)
      printf("ai_cards[%d] = %2d, known_p_cards[%d] = %2d\n", i, deck.ai_cards[i], i, deck.known_p_cards[i]);

   //Finaly, what is actually in the hands?
   printf("What is the actual set of cards in the hands?\n");
   printf("Random looking values simply means the hand is currently undefined at that point.\n");
   for(i = 0; i < 10; i++)
      printf("ai-number: %d - value: %2d - suite: %c | player -number: %d - value: %2d - suite: %c\n", i, ai.values[i], ai.suite[i], i, player.values[i], player.suite[i]);

   printf("Now the final hat trick, what is in the final deck?\n");
   for(i = 0; i < 85; i++)
      printf("%d %c ", deck.all_cards[i], deck.all_suite[i]);
   printf("\n");

   return(0);
}//End main.
