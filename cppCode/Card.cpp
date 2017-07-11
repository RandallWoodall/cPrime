#include "Card.h"
#include <iostream>

//Default constructor uses default values.  Good practice should always define values.
Card::Card(int number, bool isPrime) {
   this->number = number;
   this->isPrime = isPrime;
   //Say hello to the world.
   std::cout << "Hello world from card " << number << "!" << std::endl;
}//End constructor.

//Destructor.
Card::~Card() {
   std::cout << "Farewell world!" << std::endl;
   std::cout << "Card " << number << " was just destroyed." << std::endl;
}//End destructor.

//Normal accessors
int Card::getNumber() {
   return number;
}
bool Card::getIsPrime() {
   return isPrime;
}
//End accessors.
