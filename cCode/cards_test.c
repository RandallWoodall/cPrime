/*
 * Randall Woodall
 * Nobember 3, 2015
 * main_prog.c
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

//Prototypes for all functions used in the program **including other files.
void hand_create(hand *to_create, int which);
void draw(hand *add_to, hand *reference);
int peek(hand *peek_at, int card, int chance, int difficulty);
bool steal(hand *stealer, hand *to_steal, int card);

int main(void)
{
   srand(time(NULL));//Set up srand.
   hand ai;//AI hand.
   hand player;//Player hand.
   int i;//Loop control.
   int outcome;//outcome of peek.

   //Initialize both hands.
   hand_create(&ai, 1);
   hand_create(&player, 0);

   //The only value that needs initialized is card_count.
   ai.card_count = 0;
   player.card_count =0;
   //This can be done at the start of every round when declaring new hands.

   //Call draw 5 time for ai, 7 times for player.
   for(i = 0; i < 5; i++)
      draw(&ai, &player);
   for(i = 0; i < 7; i++)
      draw(&player, &ai);

   printf("\n\n");

   //Print the result in the ai hand.
   for(i = 0; i < ai.card_count; i++)
      printf("AI card %d value: %d suite: %c\n", i, ai.values[i], ai.suite[i]);
   for(i = 0; i < player.card_count; i++)
      printf("Player card %d value: %d suite: %c\n", i, player.values[i], player.suite[i]);

   //Test the peek function.
   printf("\nAttempting to look at ai card 0, continue till visible, normal difficulty.\n");
   printf("Current visibility of ai card 0: %d\n", ai.visibility[0]);
   do {
      ai.visibility[0] = 0;//Reset this to zero to avoid erroring out if caught. **Only for testing**
      outcome = peek(&ai, 0, 25, 2);
      printf("Outcome was %d\n", outcome);
   }while(outcome != 2);

   printf("Current visibility of ai card 0: %d\n\n", ai.visibility[0]);

   //Steal a card from the player to the ai, stealing returns 0 if invalid, 1 if complete.
   printf("Attempting to steal Player cards 7, 6 and 3 as the AI\n");
   printf("Stealing card index at 7 returns: %d\n", steal(&ai, &player, 7));
   printf("Stealing card index at 6 returns: %d\n", steal(&ai, &player, 6));
   printf("Stealing card index at 3 returns: %d\n", steal(&ai, &player, 3));

   for(i = 0; i < ai.card_count; i++)
      printf("AI card %d value: %d suite: %c\n", i, ai.values[i], ai.suite[i]);
   for(i = 0; i < player.card_count; i++)
      printf("Player card %d value: %d suite: %c\n", i, player.values[i], player.suite[i]);

   return(0);
}//End main.
