/*
 * Randall Woodall
 * hand_structure.c
 * Purpose: This is a data class for a hand of cards.
 * hmph....And they say c is hard to force into object orientation.
 */

//
//typedef: hand.
//Holds the instance data for a hand of cards.
typedef struct hand //Defined as a type so that we can make objects.
{
   int player_ai;//0 for the player hand, 1 for the ai hand.  Basically used for calculations.
   char suite[10];//Array to hold card suites. (max ten cards atm).
   int values[10];//Literally the numbers on the cards.
   int card_count;//Count of filled values, also happens to be our current index to fill.
   bool visibility[10];//0 denotes visible to owner, 1 denotes visible to all. (Mainly for ai cards.)
   int draws;//Number of draws on the next round.  Set to one every cycle, set to 0 for a cycle if you steal.
   bool stolen[10];
}hand;//End the typedef for the hand.

//Function prototypes
void hand_create(hand *to_create, int which);
void draw(hand *add_to, hand *reference);
int peek(hand *peek_at, int card, int chance, int difficulty);
bool steal(hand *stealer, hand *to_steal, int card);

//
//Function: hand_create
//This would be a constructor if we were writing java. Simply initializes needed values.
void hand_create(hand *to_create, int which)
{
   int i;//Loop counter.

   //!!MAKE SURE 0 OR 1 IS SENT HERE AS WHICH!!
   //0 for player, 1 for ai.
   (*to_create).player_ai = which;

   //Set all card visibilities to 0.
   for(i = 0; i < 10; i++)
   {
      (*to_create).visibility[i] = false;
      (*to_create).stolen[i] = false;
   }//End for.

   //Initialize card_count to 0.
   (*to_create).card_count = 0;

   //Initialize draws to 2 cards.
   (*to_create).draws = 2;
}//End hand_create function.

//
//Function: draw.
//Draws a card, checks its validity, pulls a new card if invalid.
void draw(hand *add_to, hand *reference)//The alter hand and the referene hand.
{
   int number;//To be generated.
   int suite_num;//To be generated.
   int i;//Loop controller.
   bool is_good;//Usage as boolean to verify unique cards.
   bool is_prime;//Used to check primeness.
   char suite;//Value of suite after interpretation.

   do {
      //!!This assumes that random is included in main, and that srand has been called.
      number = rand() % 50 + 1;

      //Get our suite, if card is not prime. is_prime needs to start as true.
      is_prime = true;
      for(i = 2; i < number; i++)
      {

         if(number == 2)
            is_prime = true;
         else if(number % i == 0)
            is_prime = false;
      }//End for checking primeness.
      if(!is_prime || number == 1)
      {
         suite_num = rand() % 2 + 1;
         if(suite_num == 1)
            suite = 'c';
         else
            suite = 't';
      }
      else //Suite must be prime.
         suite = 'p';

      //Initialize is_good to true, will be changed if it's bad.
      is_good = true;

      //Check for existence, add_to, then reference.
      for(i = 0; i < (*add_to).card_count; i++)
          if((*add_to).values[i] == number && (*add_to).suite[i] == suite)
            is_good = false;
      for(i = 0; i < (*reference).card_count; i++)
          if((*reference).values[i] == number && (*reference).suite[i] == suite)
            is_good = false;
   }while(is_good == false);

   //We got to this point, then we have a unique card that does not exist in a hand.
   (*add_to).values[(*add_to).card_count] = number;
   (*add_to).suite[(*add_to).card_count] = suite;
   //Increment the counter.
   (*add_to).card_count++;
}//End draw function.

//
//Function: peek
//Attempts to reveal a card to the user with risk of getting caught.
//-1 = error, 0 = caught, 1 = not caught, no card seen, 2 = success + card seen.
int peek(hand *peek_at, int card, int chance, int difficulty)
{
   int risk;//Risk of getting caught.
   int roll;//The random number.
   bool success;//Whether or not the peek was successfull.

   //First, make sure that card is not already visible, return -1 if it has been.
   if((*peek_at).visibility[card] == true)
      return(-1);//!!THIS RETURN MEANS ERROR. LET USER TRY A DIFFERENT INPUT OR CARD.

   //Big split here, player or ai.
   if((*peek_at).player_ai == 1)//If this is the player hand peeking at the ai.
   {
      if(difficulty == 1)
      {
         //Check validity of input.
         if(chance <= 50 && chance >= 1)
            risk = chance;
         else//Not a valid input.
            return(-1);
      }//End easy setup.
      else if(difficulty == 2 || difficulty == 3)//else difficulty was not 0.
      {
         if(chance <= 25 && chance >= 1)
            risk = 2 * chance;
         else//Not valid input.
            return(-1);
      }//End medium/hard setup.
      else//Difficulty is not 1, 2, or 3.
      {
         if(chance <= 13 && chance >= 1)
            risk = 4 * chance;
         else//Not valid input.
            return(-1);
      }//End honey badger setup.
   }//End player section.
   else//We must be dealing with the computer hand.
   {
      if(difficulty == 1)
         return(-1);//AI should not be sending this....
      else if(difficulty == 2)//Difficulty was not 0
      {
         if(chance <= 25 && chance >= 1)//Again, ai should not send invalid.
            risk = 2 * chance;
         else//Not valid.
            return(-1);
      }//End normal setup.
      else if(difficulty == 3)//Not 0 or 1.
      {
         if(chance <= 50 && chance >= 1)
            risk = chance;
         else//Not valid.
            return(-1);
      }//End hard setup.
      else//Not 0, 1, or 2
      {
         if(chance <= 75 && chance >= 1)
            risk = 0;
         else//Not valid input.
            return(-1);
      }//End honey badger setup.
   }//End ai section.

   //Generate a random number.
   roll = rand() % 100 + 1;

   //If we see it, change the value of visibility.
   if(roll <= chance)//If we were successfull.
   {
      (*peek_at).visibility[card] = true;
      success = true;
   }
   else//We didn't see it, success is false.
      success = false;

   //Roll for getting caught.
   roll = rand() % 100 + 1;

   //Check to see if we got caught.
   if(roll <= risk)//We got caught.
      return(0);//Denotes getting caught.
   else//We didn't get caught.
      return(1 + success);//Will be 1 if we didn't get caught, 2 if we also saw a card.
}//End peek function

//
//Function steal
//Purpose: Steals a card from the other hand.
bool steal(hand *stealer, hand *to_steal, int card)
{
   //First, check that there is space left in the hand, return if not.
   //Also checks to see if the card to steal is valid (not stolen before, in range.
   if((*stealer).card_count >= 9 || card >= (*to_steal).card_count || (*to_steal).stolen[card] == true)
   {
      draw(stealer, to_steal);
      return(false);
   }

   //Now that we know there is space in the hand, we can make the steal.
   (*stealer).suite[(*stealer).card_count] = (*to_steal).suite[card];
   (*stealer).values[(*stealer).card_count] = (*to_steal).values[card];
   //Obviously it is visible, we all know where it is.
   (*stealer).visibility[(*stealer).card_count] = true;
   //Has been stolen.
   (*stealer).stolen[(*stealer).card_count] = true;
   (*stealer).card_count++;
   //Card is currently duplicated.

   //Remove the card from the other hand, shift everything down, call deal to replace the card.
   while(card < (*to_steal).card_count)
   {
      (*to_steal).suite[card] = (*to_steal).suite[card + 1];
      (*to_steal).values[card] = (*to_steal).values[card + 1];
      (*to_steal).visibility[card] = (*to_steal).visibility[card + 1];
      card++;
   }//End while.
   (*to_steal).card_count--;

   //Now call deal to refill the lost card.
   draw(to_steal, stealer);

   //Finaly, move the stealer's draw to 0.
   (*to_steal).draws = 0;

   //Steal was successfull, return as such.
   return(true);
}//End steal function
