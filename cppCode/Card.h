#ifndef CARDS
#define CARDS

class Card {
 private:
   int number;
   bool isPrime;

 public:
   Card(int number = 0, bool isPrime = false);
   ~Card();
   int getNumber();
   bool getIsPrime();
};//End card class

#endif
