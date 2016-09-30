/*
 * ideck.c
 * November 11, 2015
 * Purpose: house everything needed for the ideck.
 */

//
//Randall Woodall
//Typedef: ideck
//Purpose: imaginary deck for the ai to use

typedef struct ideck
{
   int all_cards[85];//All cards in deck
   int known_p_cards[10];//All known player cards
   int ai_cards[10];
   char all_suite[85];
   char p_card_suite[10];
   char ai_suite[10];
   int actual_count;//This is a special variable, will be the actual number of cards in each hand.
}ideck;
//End ideck typedeff

//Function prototypes.
void setup_ideck(ideck *setup);
void update_ideck(hand *player, hand *ai, ideck *deck);
int bin_search(ideck *deck, int i, int hand);

//
//Randall Woodall
//Function: setup_ideck
//Initial setup for ideck, simply makes the deck.
//**CALL IMMEDIATELY AFTER RESERVING IDECK**
void setup_ideck(ideck *setup)
{
   int i;//Loop control.
   int n;//Number to store in the deck.
   int k;//For checking prime.
   bool prime;//Holds true if the nubmer == prime.

   //Initialize n.
   n = 0;

   //Start the outer loop. This is special because control vars move at different speeds.
   //By mathematical necessity, i == 84 when n == 50.
   for(i = 0; i < 85; i++)
   {
      prime = true;//Assume prime.

      n++;//We want our first value to = 1, not 0.
      for(k = 2; k < n; k++)
         if(n % k == 0)
            prime = false;
      //k for ended by single internal statement.

      if(prime == true && n != 1)//Never entered loop, or was prime.
      {
         (*setup).all_cards[i] = n;
         (*setup).all_suite[i] = 'p';
      }//End if.
      else//Prime must not be true.
      {
         (*setup).all_cards[i] = n;
         (*setup).all_suite[i] = 'c';
         i++;
         (*setup).all_cards[i] = n;
         (*setup).all_suite[i] = 't';
      }//End else.
   }//End for.

   //Next, lets fill the player and ai arrays with -1.
   for(i = 0; i < 10; i++)
   {
      (*setup).known_p_cards[i] = -1;
      (*setup).ai_cards[i] = -1;
   }//End for.

   //Assume this is called when created, initialize actual_count to 2 (starting hand).
   (*setup).actual_count = 2;
}//End setup_ideck function.

//
//Randall Woodall
//Function: update_ideck
//This should be called whenever the ai is asked to make a choice. Gives it all it can know.
//Call immediately after a normal draw set. + after the first draw of the round.
void update_ideck(hand *player, hand *ai, ideck *deck)
{
   int i;//Loop control(#1).
   int n;//Loop control(#2).
   int k;//Location control.
   bool verified;

   //Initialize i and n to 0, verified to false.
   n = 0;
   verified = false;

   while(!verified)//LOL "while NOT verified" :)
   {
      //Set verified to true so we can check for changes.
      verified = true;//If anything was out of line, check until it is all in line for a full run.

      //Start with the ai hand, check to see all values are recorded.
      for(i = 0; i < 10 && i < (*deck).actual_count; i++)
      {
         //Now, the cards should all be in line.  If a card is missing, it must have been stolen.
         if((*ai).values[i] != (*deck).ai_cards[i] && (*deck).ai_cards[i] != -1)//-1 denotes no value.
         {
            verified = false;

            //shift all pseudo elements down.
            for(n = i; n < 9; n++)
            {
               (*deck).ai_cards[n] = (*deck).ai_cards[n + 1];
               (*deck).ai_suite[n] = (*deck).ai_suite[n + 1];
            }
         }//End if.
         else if((*ai).values[i] != (*deck).ai_cards[i] && (*deck).ai_cards[i] == -1)
         {
            verified = false;
            //We are just adding a card.
            (*deck).ai_cards[i] = (*ai).values[i];
            (*deck).ai_suite[i] = (*ai).suite[i];

            //Last thing is to pull from the ideck.
            k = bin_search(deck, i, 0);
            if(k != -1)
            {
               (*deck).all_cards[k] = -1;
               (*deck).all_suite[k] = 'a';
            }
         }//End else if.
      }//End ai checking.
   }//End while.
   verified = false;
   while(!verified)
   {
      verified = true;

      //Now for the player hand.  We need to make sure we didn't steal.
      for(i = 0; i < 10 && i < (*deck).actual_count; i++)
      {
         //First check for cards that have been stolen.
         if((*player).visibility[i] == false && (*deck).known_p_cards[i] != -1)
         {
            verified = false;
            //We must have stolen it.

            //Don't bother "adding" to the ai hand, it will have found it already.

            //Shift all pseudo elements down.
            for(n = i; n < 9; n++)
            {
               (*deck).known_p_cards[i] = (*deck).known_p_cards[i + 1];
               (*deck).p_card_suite[i] = (*deck).p_card_suite[i + 1];
            }
         }//End if
         else if((*player).visibility[i] == true && (*deck).known_p_cards[i] == -1)
         {
            verified = false;
            //We probably peeked at a card.
            (*deck).known_p_cards[i] = (*player).values[i];
            (*deck).p_card_suite[i] = (*player).suite[i];

            //Now we need to locate and pull the card from the deck.
            k = bin_search(deck, i, 1);
            if(k != -1)
            {
               (*deck).all_cards[k] = -1;
               (*deck).all_suite[k] = 'a';
            }
         }//End else if
      }//End player checking.
   }//End while.

   //Increase actual count to match up with the next set of cards.
   (*deck).actual_count++;
}//End update_ideck function

//
//Randall Woodal
//Function bin_search
//Binary searches the ideck for values so it can remove them.
int bin_search(ideck *deck, int i, int hand)
{
   int left, right, middle, itarg, target, suite;

   right = 84;//Highest possible index.
   left = 0;//Lowest possible index.
   itarg = -1;//Initialize for use in the loop control.

   if(hand == 0)
   {
      target = (*deck).ai_cards[i];
      suite = (*deck).ai_suite[i];
   }
   else
   {
      target = (*deck).known_p_cards[i];
      suite = (*deck).p_card_suite[i];
   }

   while(right >= left && itarg == -1)
   {
      middle = (right + left) / 2;
      if((*deck).all_cards[middle] == target && (*deck).all_suite[middle] == suite)
         itarg = middle;
      else if((*deck).all_cards[middle] > target)
         right = middle - 1;
      else
         left = middle + 1;
   }

   return(itarg);
}//End binsearch function.
