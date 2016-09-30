/*
 * ai.c
 * November 11, 2015
 * Purpose: This houses all the AI functions.
 */

#define MAX_PRIMES 15
#define HAND_MAX 10
#define DECK_TOTAL 85

//Function prototypes.
//The original plan was to place all ai functions (mine and matt's) into this file.
int calc_prob(ideck *deck, int *player_prime_loc);

//
//Randall Woodall
//Function: calc_prob
//This function will use what the ai knows to calculate card locations and estimate chance of winning.
int calc_prob(ideck *deck, int *player_prime_loc)
{
   //First things first, let's find a way to get the probability of a card being in a hand,
   //controlled by number of known cards on the table.
   int ai_primes[HAND_MAX];//The prime cards from the ai hand.
   int player_primes[HAND_MAX];//The prime cards that are visible in the player hand.
   int all_primes[MAX_PRIMES];//All the prime cards on the table, used for calculating probability.
   int rem_primes[MAX_PRIMES];//Primes unknown.
   int ai_count;//Count of ai primes.
   int player_count;//Count of player primes.
   int total_count;//Total count of prime cards.
   int rem_count;//Count of remaining primes.
   int prime_sum;//Sum of primes in hands;
   int rem_sum;//Sum of primes in the deck;
   int player_sum;//Sum of the player primes.
   int ai_sum;//Sum of the ai primes.
   int player_visible;//count of visible player cards.
   int points;//This is a sum of possitive and negative aspects.
   int i;//For loop control.
   //Let's get all the primes we know about and count them.
   for(i = 0, ai_count = 0, player_count = 0, total_count = 0, player_sum = 0, ai_sum = 0, player_visible = 0, *player_prime_loc = -1; i < HAND_MAX; i++)
   {
      if((*deck).known_p_cards[i] != -1)
      {
         player_visible++;
      }
      if((*deck).p_card_suite[i] == 'p')
      {
         player_primes[player_count] = (*deck).known_p_cards[i];
         player_sum += (*deck).known_p_cards[i];
         all_primes[total_count] = (*deck).known_p_cards[i];
         if(player_count == 0 || (*deck).known_p_cards[i] > (*deck).known_p_cards[*player_prime_loc])
            *player_prime_loc = i;
         player_count++;
         total_count++;
      }//End if.
      if((*deck).ai_suite[i] == 'p')
      {
         ai_primes[ai_count] = (*deck).ai_cards[i];
         ai_sum += (*deck).ai_cards[i];
         all_primes[total_count] = (*deck).ai_cards[i];
         ai_count++;
         total_count++;
      }//End if.
   }//End for.

   //Count the primes remaining in the deck.
   for(i = 0, rem_count = 0; i < DECK_TOTAL; i++)
   {
      if((*deck).all_suite[i] == 'p')
      {
         rem_primes[rem_count] = (*deck).all_cards[i];
         rem_count++;
      }//End if.
   }//End for.

   //Add up the primes in hands.
   for(i = 0; i < total_count; i++)
   {
       prime_sum += all_primes[i];
   }//End for.
   //Add up the sum of the remaining.
   for(i = 0; i < rem_count; i++)
   {
       rem_sum += rem_primes[i];
   }//End for.

   //Initialize our count.
   points = 0;

   //**We need a count of the visible player cards to compare effectively.**
   //Keep in mind through this, that the ideck values are guesses.
   if(total_count >= (*deck).actual_count / 2)
   {
       //If we see 50% prime cards...
      points++;
   }
   else//We see less than 50% the primes (impacted by card counts).
   {
      points--;
   }
   //Points should be 1, as this is very generous for measuring.

   //Alright, now the same system, but with values instead of counts.
   if(prime_sum >= (prime_sum + rem_sum) / 2)
   {
      //We see 50% of the possible value, should be rare that we ever make it here.
      points++;
   }
   else//We see less than half the potential total value of the deck.
   {
      points--;
   }

   //Now that we have these initial two, count of ai against count of player.
   if(ai_count > player_count && player_visible >= ai_count)//Only we see more player cards than ai primes.
   {
      points++;
   }
   else//ai has less than or equal to the player count
   {
      //will be here unless we are peeking a lot at player cards.
      points--;
   }

   //Let's compare the value of the ai primes to the player's
   if(ai_sum > player_sum)//Must be greater than player sum.
   {
      points++;
   }
   else//player must have equal or higher value.
   {
      points--;
   }

   //First return statement
   if(points < -2)
      return -2;
   if(points > 2)
      return 2;

   return(points);
}//End calc_prob function.
