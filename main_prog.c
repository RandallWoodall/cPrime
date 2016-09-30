/*
 * Randall Woodall && Matthew B
 * Dec 5, 2015
 * main_prog.c
 * Purpose: handles all ai decisions and player decisions
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <curses.h>
//
//typedef and definitions for bool
//Randall Woodall
//Allow bools here and through the program.
/*
#define true 1
#define false 0
typedef short bool;
*/

//Macros to make this pretty
#define YELLOW "\x1B[33m"
#define WHITE "\x1B[0m"
#define RED "\033[31m"

//All external files called below.
#include "cards.c"
#include "start_up.c"
#include "main_display.c"
#include "ideck.c"
#include "ai.c"

//Prototypes for all functions used in the program **including other files.
/*
void hand_create(hand *to_create, int which);
void draw(hand *add_to, hand *reference);
int peek(hand *peek_at, int card, int chance, int difficulty);
bool steal(hand *stealer, hand *to_steal, int card);
int main_select(int i, int n, int *done);
int main_menu(int i);
int instructions(int i);
int game_mode(int i);
void display_card(hand to_show, int select, int hand_trak);
int game_turn(int ai_wallet, int player_wallet, int pot, int i);
int game_over(int i);
int betting(int ai_wallet, int player_wallet, int pot, int i);
void forfeit(int i);
int bin_search(ideck *deck, int i, int hand);
void setup_ideck(ideck *setup);
void update_ideck(hand *player, hand *ai, ideck *deck);
*/

int main(void)
{
   srand(time(NULL));//Set up srand.
   hand ai;//AI hand.
   hand player;//Player hand.
   ideck deck;//ideck
   int i;//Loop control.
   int outcome;//outcome of peek.
   int select;  //return for main_menu
   int temp;
   int difficulty;
   int n; //number of selection options
   int j;//loop counter for drawing
   int fix_me; //place holer for item selection
   int done; //to exit selection loops
   int run; //overall game loop
   int menu_run;//controls loop for the main menu
   int hand_trak;//value of 1 or 0 that keeps track of the print

   int ai_prime_total;//temporary ai final score
   int player_prime_total;//temporary player final score
   int player_wallet;//player cash
   int ai_wallet;//ai cash
   int pot;//cash up for grabs

   int peek_res;//The return from the functin peek
   int chance;//User input chance to win peek
   int accepted_chance;//Max chance for the difficulty level
   int hold_select;//this is to hold the value for the selected card
   int all_visible;//chscks to see if the player has a card the ai does not know, prevents an unlikely, but possible infinate loop
   int p;//counter for all_visible loop
   
   //These variables are for the ai to decide on what to do in betting
   int low_raise;
   int low_match;
   int med_raise;
   int med_match;
   int high_raise;
   int high_match;
   
   //these variable are for the ai to decide to draw, peek, or steal
   int peek_norm;
   int peek_prime;
   int steal_prime;
   int peek_chance;

   int fold;//variable to end a round
   int all_in;//variable to bet all current money
   int quit;//will exit the game to the game over screen
   int player_error;//will store the amount the player overbet if the player bets more than the ai has

   int ai_decision;//this will take the return from calc_prob and will be the basis of the ai's desisions.
   int bet_match;//for the player and ai to match the others bet
   int desision_rand;//random for the ai brain
   int ai_bet;//amount ai will bet (multiplied by 10 later)
   int player_prime_loc;//highest prime in the players hand that the ai knows about

   do{//OVERALLGAME LOOP
		/////////////////////////////////
		///////////*MAIN MENU*///////////
		/////////////////////////////////
		menu_run = 1;
		while(menu_run == 1){
			i = 0;
			n = 2; //2 option, instructions and game_mode
			main_menu(i);
			while(1){
				select = main_select(i, n, &done);
				i = select;
				if(done == 1){
					break;
				}

				else{
					main_menu(select);
				}
				//i = select;
			}

			////////////////////////////////////
			///////////*INSTRUCTIONS*///////////
			////////////////////////////////////
			if(select == 1){
				i = 0;
				n = 1; //only one option, back to main menu
				instructions(i);
				done = 0;
				while(1){
					select = main_select(i, n, &done);
					if(select < n && select >= i){
						select = -1; //-1 will fall through everything else, and return to main
						break;
					}
				}
			}
			
			/////////////////////////////////
			///////////*GAME MODE*///////////
			/////////////////////////////////
			if(select == 0){
				i = 0;
				n = 5; //5 options, easy, medium, hard, cheating, and main
				game_mode(i);
				done = 0;
				while(1){
					select = main_select(i, n, &done);
					i = select;

					//main menu selected//
					if(done == 1 && select == 0){
						select = -1;
						break;
					}
					//difficluty selected//
					else if(done == 1 && (select == 1 || select == 2 || select == 3 || select ==4)){
						difficulty = select;
						menu_run = 0;
						select = 0; //temperorary to get me out of the main loop **testing only**
						break;
					}

					else{
						game_mode(select);
					}
				}
			}
		}//exiting main menu, starting game
		////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////
		//NOT SURE WHERE THIS SHOULD ALL GO AND IF IT RESETS THE HANDS//
		////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////
		//Initialize or reset the wallets.
		player_wallet = 1000;
		ai_wallet = 1000;
		pot = 0;
		quit = 0;

		while(player_wallet > 0 && ai_wallet > 0){//game loop
			if(quit == 1){//quit has been called, ignore everything else
				break;
			}
			fold = 0;//Set fold back to false
			all_in = 0;

			//Initialize both hands.
			hand_create(&ai, 1);
			hand_create(&player, 0);

			//The only value that needs initialized is card_count.
			ai.card_count = 0;
			player.card_count = 0;

			//Initialize iDesk
			setup_ideck(&deck);

			//This can be done at the start of every round when declaring new hands.

			//Initiate Game, start with 3 cards
			for(i = 0; i < 2; i++){
				draw(&ai, &player);
			}
			for(i = 0; i < 2; i++){
				draw(&player, &ai);
			}

			update_ideck(&player, &ai, &deck);//loads ai initial cards

			////////////////////////////////
			//////////*GAME START*//////////
			////////////////////////////////

			//////////*PLAYER MOVE SELECTION*//////////
			for(j = 0; j < 8; j++){//round loop
				if(quit == 1){//quit has been called, ignore everything else
					break;
				}
				i = 0;
				n = 4;
				system("clear");
                display_card(ai, -1, 0);
                game_turn(ai_wallet, player_wallet, pot, i);
                display_card(player, -1, 1);
				while(1){
					if(quit == 1){//quit has been set, ignore all else
						break;
					}

					select = main_select(i, n, &done);
					i = select;
					////////
					//DRAW//
					////////
					if(done == 1 && select == 0){
						draw(&player, &ai);
						break;
					}

					////////
					//PEEK//
					///////

					else if(done == 1 && select == 1){
						//Not the last turn, peek function called
						i = 0;
						n = ai.card_count;
						system("clear");
						//initial display, defaults to first card
						while(1){
							system("clear");
							display_card(ai, i, 0);
							game_turn(ai_wallet, player_wallet, pot, 1);
							display_card(player, -1, 1);
							select = main_select(i, n, &done);
							i = select;
							if(done == 1 && select < n && select >= 0){//q has been selected, exiting loop
								do{
									system("clear");
									display_card(ai, i, 0);
									game_turn(ai_wallet, player_wallet, pot, 1);
									display_card(player, -1, 1);
									if(difficulty == 1){
										printf("Input a Chance between 1 and 50: ");
										accepted_chance = 50;
									}
									else if(difficulty == 2 || difficulty == 3){
										printf("Input a Chance between 1 and 25: ");
										accepted_chance = 25;
									}
									else if(difficulty == 4){
										printf("Input a Chance between 1 and 13: ");
										accepted_chance = 13;
									}
									scanf("%d", &chance);//Get user input
								}while(chance > accepted_chance);//Keep user in loop until a valid input is entered
	
								peek_res = peek(&ai, select, chance, difficulty);
	
								hold_select = select;
								i = 0;
								n = 1;
	
								while(1){
									system("clear");

									display_card(ai, hold_select, 0);
									game_turn(ai_wallet, player_wallet, pot, 1);

									if(peek_res == -1){
										printf("You can see the card already dude, just draw a card and we'll act like this never happened\n");
										printf(YELLOW"OK then\n"WHITE);
									}
									else if(peek_res == 0 && difficulty != 1){
										printf("You dirty cheater, you got caught... Show one of your cards to the other guy, and lets call it even.\n");
										printf(YELLOW"OK then\n"WHITE);
										//ai will random a card to look at here
										if(difficulty == 2){
											chance = 25;
										}
										else if(difficulty == 3){
											chance = 50;
										}
										else if(difficulty == 4){
											chance = 75;
										}
										all_visible = 0;
										for(p = 0; p < player.card_count; p++){
											if(player.visibility == 0){
												all_visible++;
												break;
											}
										}
										if(all_visible == 1){
											//do nothing, just skip the next step
										}
										else{//Not every player card is visible
											do{
												desision_rand = rand() % (player.card_count);//random card to peek at
											}while(player.visibility[desision_rand] != 0);
											do{
												peek_res = peek(&player, desision_rand, chance, difficulty);
											}while(peek_res != 2);
										}
									}
									else if(peek_res == 0 && difficulty == 1){
										printf("You're lucky that this is easy, you filthy cheater. The ai would have seen one of your cards\n");
										printf(YELLOW"OK then\n"WHITE);
									}
									else if(peek_res == 1){
										printf("At Least you didn't get caught!\n");
										printf(YELLOW"OK then\n"WHITE);
									}
									else if(peek_res == 2){
										printf("SUCCESS!!!\n");
										printf(YELLOW"OK then\n"WHITE);
									}
									display_card(player, -1, 1);
									
									select = main_select(0, 1, &done);
									i = select;

									if(done == 1){
										break;
									}
								}	
								break;
							}
						}
					}

					/////////
					//STEAL//
					/////////
					else if(done == 1 && select ==2){
                        i = 0;
                        n = ai.card_count;
                        system("clear");
						//initial display, defaults to first card
                        display_card(ai, i, 0);
                        game_turn(ai_wallet, player_wallet, pot, 2);
                        display_card(player, -1, 1);
                        while(1){
                            select = main_select(i, n, &done);
                            i = select;
                            if(done == 1 && select < n && select >= 0){//q has been selected, exiting loop
                                steal(&player, &ai, i);
                                //draw(&ai, &player);
                                break;
                            }
                            else{//reprint screen for select
                                system("clear");
                                display_card(ai, i, 0);
                                game_turn(ai_wallet, player_wallet, pot, 1);
                                display_card(player, -1, 1);
                            }
                        }
                         break;
					}
					/////////////
					//EXIT GAME//
					/////////////
					else if(done == 1 && select == 3){
						i = 0;
						n = 2;
						done = 0;
						system("clear");
						forfeit(i);
						while(1){
							select = main_select(i, n, &done);
							i = select;

							if(select == 0 && done == 1){
								quit = 1;
								break;
							}
							else if(select == 1 && done == 1){
								i = 0;
								n = 4;
								system("clear");
								display_card(ai, -1, 0);
								game_turn(ai_wallet, player_wallet, pot, i);
								display_card(player, -1, 1);
								break;
							}
							else{
								system("clear");
								forfeit(i);
							}

						}
					}

					else{
						system("clear");
        	        	display_card(ai, -1, 0);
        		   		game_turn(ai_wallet, player_wallet, pot, i);
	                	display_card(player, -1, 1);
					}
				}


				/////////////////
				/////////////////
				/////AI TURN/////
				/////////////////
				/////////////////
				player_prime_loc = -1;
				ai_decision = calc_prob(&deck, &player_prime_loc);//find out how good the ai's hand is
				desision_rand = rand() % 100 + 1;//generate a random for desicion making between 1 and 100
				peek_res == -5;//to check if the ai peeks
				
				if(difficulty == 1){
					peek_chance = 0;
					if(ai_decision == -2){
						peek_norm = 0;
						peek_prime = 0;
						steal_prime = 50;
					}
					else if(ai_decision == -1){
						peek_norm = 0;
						peek_prime = 0;
						steal_prime = 40;
					}
					else if(ai_decision == 0){
						peek_norm = 0;
						peek_prime = 0;
						steal_prime = 30;
					}
					else if(ai_decision == 1){
						peek_norm = 0;
						peek_prime = 0;
						steal_prime = 20;
					}
					else if(ai_decision == 2){
						peek_norm = 0;
						peek_prime = 0;
						steal_prime = 10;
					}
				}
				if(difficulty == 2){
					peek_chance = 25;
					if(ai_decision == -2){
						peek_norm = 60;
						peek_prime = 50;
						steal_prime = 50;
					}
					else if(ai_decision == -1){
						peek_norm = 55;
						peek_prime = 45;
						steal_prime = 40;
					}
					else if(ai_decision == 0){
						peek_norm = 45;
						peek_prime = 40;
						steal_prime = 35;
					}
					else if(ai_decision == 1){
						peek_norm = 40;
						peek_prime = 35;
						steal_prime = 30;
					}
					else  if(ai_decision == 2){
						peek_norm = 35;
						peek_prime = 25;
						steal_prime = 25;
					}
				}
				if(difficulty == 3){
					peek_chance = 50;
					if(ai_decision == -2){
						peek_norm = 75;
						peek_prime = 25;
						steal_prime = 75;
					}
					else if(ai_decision == -1){
						peek_norm = 65;
						peek_prime = 25;
						steal_prime = 70;
					}
					else if(ai_decision == 0){
						peek_norm = 60;
						peek_prime = 25;
						steal_prime = 60;
					}
					else if(ai_decision == 1){
						peek_norm = 55;
						peek_prime = 25;
						steal_prime = 55;
					}
					else if(ai_decision == 2){
						peek_norm = 50;
						peek_prime = 25;
						steal_prime = 50;
					}
				}
				if(difficulty == 4){
					peek_chance = 75;
					if(ai_decision == -2){
						peek_norm = 100;
						peek_prime = 5;
						steal_prime = 95;
					}
					else if(ai_decision == -1){
						peek_norm = 100;
						peek_prime = 10;
						steal_prime = 90;
					}
					else if(ai_decision == 0){
						peek_norm = 100;
						peek_prime = 15;
						steal_prime = 85;
					}
					else if(ai_decision == 1){
						peek_norm = 100;
						peek_prime = 20;
						steal_prime = 80;
					}
					else if(ai_decision == 2){
						peek_norm = 100;
						peek_prime = 25;
						steal_prime = 75;
					}
				}
				
				if(player_prime_loc == -1){//player has no prime that the ai knows about
					if(desision_rand <= peek_norm && desision_rand >= 1){//40% to peak
						do{
							desision_rand = rand() % (j + 2);//random card to peek at
						}while(player.visibility[desision_rand] != 0);
						do{
							chance = rand() % peek_chance;//generate random chance between 1 and 50
						}while(chance == 0);//chance cannot be 0
						peek_res = peek(&player, desision_rand, chance, difficulty);
						draw(&ai, &player);
					}
					else{//draw a card
						draw(&ai, &player);
					}
				}

				else{//player has a prime, and the ai knows it
					if(desision_rand < peek_prime && desision_rand >= 0){//ai chose to peek
						do{
							desision_rand = rand() % (j + 2);//choose a random card
						}while(player.visibility[desision_rand] != 0);
						do{
							chance = rand() % peek_chance;//generate a random chance
							if(difficulty == 4){
								chance = 75;
							}
						}while(chance == 0);//chance cannot be 0
						peek_res = peek(&player, desision_rand, chance, difficulty);
						draw(&ai, &player);
                    }
						
					else if(desision_rand <= steal_prime && desision_rand >= peek_prime){//ai chose to steal
						steal(&ai, &player, player_prime_loc);
					}
						
					else{//default to draw
						draw(&ai, &player);
					}
				}

				if(peek_res == 0 && difficulty != 1){
					//select a card to look at
					i = 0;
					n = player.card_count;
					system("clear");
                    //initial display, defaults to first card
                    display_card(ai, i, 0);
                    game_turn(ai_wallet, player_wallet, pot, 1);
                    display_card(player, -1, 1);
                    while(1){
						select = main_select(i, n, &done);
						i = select;

                        if(done == 1){
                            if(difficulty == 1){//this should never happen
                                chance = 50;
                            }
							else if(difficulty == 2 || difficulty == 3){
                                chance = 25;
                            }
                            else{//if all works well, we should never get here
                                chance = 13;
                            }
                            do{//run through until you see the card
                                peek_res = peek(&ai, select, chance, difficulty);
                            }while(peek_res != 2);
                            break;
						}		
						else{//reprint screen
							system("clear");
							display_card(ai, i, 0);
                        	game_turn(ai_wallet, player_wallet, pot, 1);
			                display_card(player, -1, 1);
						}
                    }//end while(1)
				}

				update_ideck(&player, &ai, &deck);

				//////////*BETTING*//////////
				if(player_wallet != 0 && ai_wallet != 0){
					i = 0;
					n = 6;
					bet_match = 0;
					system("clear");
                    display_card(ai, -1, 0);
                    betting(ai_wallet, player_wallet, pot, i);
                    display_card(player, -1, 1);
					while(1){
						if(quit == 1){//quit has been set, ignore everything
							break;
						}
						select = main_select(i, n, &done);
						i = select;
						if(done == 1 && select == 0){//Bet $10
							if(player_wallet >= 10){
								pot += 10;
								player_wallet -= 10;
								bet_match += 10;
							}
							system("clear");
							display_card(ai, -1, 0);
							betting(ai_wallet, player_wallet, pot, i);
							display_card(player, -1, 1);
						}

						else if(done == 1 && select == 1){//Bet $50
							if(player_wallet >= 50){
								pot += 50;
								player_wallet -= 50;
								bet_match += 50;
							}
							system("clear");
							display_card(ai, -1, 0);
							betting(ai_wallet, player_wallet, pot, i);
							display_card(player, -1, 1);
						}

						else if(done == 1 && select == 2){//Bet $100
							if(player_wallet >= 100){
								pot += 100;
								player_wallet -= 100;
								bet_match += 100;
							}
							system("clear");
							display_card(ai, -1, 0);
							betting(ai_wallet, player_wallet, pot, i);
							display_card(player, -1, 1);
						}

						else if(done == 1 && select ==3){//done betting
							break;
						}

						else if(done == 1 && select ==4){
							fold = 1;
							break;
						}

						else if(done == 1 && select ==5){
							all_in = player_wallet;
							pot += all_in;
							if(all_in > ai_wallet){
								all_in = ai_wallet;
							}
							bet_match = all_in;
							player_wallet = 0;
							break;
						}

						else{
							system("clear");
							display_card(ai, -1, 0);
							betting(ai_wallet, player_wallet, pot, i);
							display_card(player, -1, 1);
						}
						if(bet_match > ai_wallet){
							player_error = ai_wallet - bet_match;
							player_wallet += player_error;
							bet_match = ai_wallet;
						}
					}


					//////////////////
					//////////////////
					////AI BETTING////
					//////////////////
					//////////////////
					player_prime_loc = -1;
					ai_decision = calc_prob(&deck, &player_prime_loc);//find out how good the ai's hand is
					desision_rand = rand() % 100 + 1;//generate a random for desicion making between 1 and 100
						
					if(ai_decision == -2){
						low_raise = 10;
						low_match = 40;
						med_raise = 5;
						med_match = 25;
						high_raise = 5;
						high_match = 20;
					}
					else if(ai_decision == -1){
						low_raise = 30;
						low_match = 50;
						med_raise = 20;
						med_match = 50;
						high_raise = 10;
						high_match = 50;
					}
					else if(ai_decision == 0){
						low_raise = 50;
						low_match = 45;
						med_raise = 40;
						med_match = 55;
						high_raise = 45;
						high_match = 50;
					}
					else if(ai_decision == 1){
						low_raise = 60;
						low_match = 40;
						med_raise = 50;
						med_match = 50;
						high_raise = 40;
						high_match = 60;
					}
					else if(ai_decision == 2){
						low_raise = 75;
						low_match = 25;
						med_raise = 60;
						med_match = 40;
						high_raise = 50;
						high_match = 50;
					}
						
					if(bet_match >= 0 && bet_match <= 500){//bets between 0 and 500 dollars
						if(desision_rand >= low_raise && desision_rand <= 1){//5% chance to match and raise the bet
							pot += bet_match;
							ai_wallet = ai_wallet - bet_match;
							bet_match = 0;
							//ai will raise bet up to 150
							ai_bet = rand() % 16;
							bet_match = ai_bet * 10;
							if(bet_match > ai_wallet){//ai is pretty much saying all in
								bet_match = ai_wallet;
							}
							else if(bet_match > player_wallet){//ai will not bet more than the player has
								bet_match = player_wallet;
							}
							pot += bet_match;
							ai_wallet = ai_wallet - bet_match;
						}
						else if(j > 2 && desision_rand >= low_match && desision_rand < low_raise){//ai is going to fold
							fold = -1;
							bet_match = 0;
						}
						else{//Just match the player for now
							pot += bet_match;
							ai_wallet = ai_wallet - bet_match;
							bet_match = 0;
						}
					}
					else if(bet_match >= 501 && bet_match <= 750){//bets between 501 and 750 dollars
						if(desision_rand >= med_raise && desision_rand <= 1){//5% chance to match and raise the bet
							pot += bet_match;
							ai_wallet = ai_wallet - bet_match;
							bet_match = 0;
							//ai will raise bet up to 150
							ai_bet = rand() % 16;
							bet_match = ai_bet * 10;
							if(bet_match > ai_wallet){//ai is pretty much saying all in
								bet_match = ai_wallet;
							}
							else if(bet_match > player_wallet){//ai will not bet more than the player has
								bet_match = player_wallet;
							}
							pot += bet_match;
							ai_wallet = ai_wallet - bet_match;
						}
						else if(j > 2 && desision_rand >= med_match && desision_rand < med_raise){//ai is going to fold
							fold = -1;
							bet_match = 0;
						}
						else{//Just match the player for now
							pot += bet_match;
							ai_wallet = ai_wallet - bet_match;
							bet_match = 0;
						}
					}
					else{//bets above 750
						if(desision_rand >= high_raise && desision_rand <= 1){//5% chance to match and raise the bet
							pot += bet_match;
							ai_wallet = ai_wallet - bet_match;
							bet_match = 0;
							//ai will raise bet up to 150
							ai_bet = rand() % 16;
							bet_match = ai_bet * 10;
							if(bet_match > ai_wallet){//ai is pretty much saying all in
								bet_match = ai_wallet;
							}
							else if(bet_match > player_wallet){//ai will not bet more than the player has
								bet_match = player_wallet;
							}
							pot += bet_match;
							ai_wallet = ai_wallet - bet_match;
						}
						else if(j > 2 && desision_rand >= high_match && desision_rand < high_raise){//ai is going to fold
							fold = -1;
							bet_match = 0;
						}
						else{//Just match the player for now
							pot += bet_match;
							ai_wallet = ai_wallet - bet_match;
							bet_match = 0;
						}
					}

					//////////////////////////////
					//////////////////////////////
					//player to match the ai bet//
					//////////////////////////////
					//////////////////////////////
					if(bet_match != 0){
						i = 0;
						n = 2;
						system("clear");
						display_card(ai, -1, 0);
						match_ai(ai_wallet, player_wallet, pot, i, bet_match);
						display_card(player, -1, 1);
						while(1){
							if(quit == 1){//quit has been set, ignore everything
								break;
							}
							select = main_select(i, n, &done);
							i = select;
							if(done == 1 && select == 0){//player is going to match the ai's bet
								pot += bet_match;
								player_wallet -= bet_match;
								break;
							}

							else if(done == 1 && select == 1){//player has folded
								fold = 1;
								break;
							}

							else{
								system("clear");
								display_card(ai, -1, 0);
								match_ai(ai_wallet, player_wallet, pot, i, bet_match);
								display_card(player, -1, 1);
							}
						}
					}
				}
				
				if(fold != 0){
					break;
				}
			}//END ROUND
			player_prime_total = 0;
			ai_prime_total = 0;
			for(i = 0; i < player.card_count; i ++){
				if(player.suite[i] == 'p'){
					player_prime_total += player.values[i];
				}
			}
			for(i = 0; i < ai.card_count; i ++){
				if(ai.suite[i] == 'p'){
					ai_prime_total += ai.values[i];
				}
			}
			while(1){
				if(quit == 1){
					break;
				}
				system("clear");
				display_card(ai, -1, 1);
				betting(ai_wallet, player_wallet, pot, i);
				printf("AI FINAL SCORE = %d\n", ai_prime_total);
                printf("Round over, press Q to continue\n");
				printf("PLAYER FINAL SCORE = %d\n", player_prime_total);
				display_card(player, -1, 1);
				select = main_select(0, 0, &done);
				if(done == 1){
					break;
				}
            }
			if(quit == 1){
				//Do nothing, just skip the winner calculation.
				break;//break out of main game loop
			}
			else if(fold == -1){//ai has folded
				player_wallet += pot;
				pot =0;//reset the pot for the next round
			}
			else if(fold == 1){//player has folded
				ai_wallet += pot;
				pot =0;//reset the pot for the next round
			}
			else if(player_prime_total > ai_prime_total){//PLAYER WINS THE ROUND
				player_wallet += pot;
				pot =0;//reset the pot for the next round
			}
			else if(player_prime_total < ai_prime_total){//AI WINS THE ROUND
				ai_wallet += pot;
				pot =0;//reset the pot for the next round
			}
		}//end of game loop

		//////////////////////////////
		//////////*END GAME*//////////
		//////////////////////////////
		i = 0;
		n = 2;
		game_over(i);
		while(1){
			select = main_select(i, n, &done);
			i = select;

			if(done == 1 && select == 0){
				//start game over
				run = 1;
				break;
			}
			else if(done == 1 && select ==1){
				run = 0; //Exits game
				break;
			}
			else{
				game_over(i);
			}
		}
   }while(run == 1);//END OVERALL GAME LOOP
   system("clear");
}//main end


   ////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////
   ////////////////////REFERENCE CODE//////////////////////
   ////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////
   /*
   //Test the peek function.
   printf("\nAttempting to look at ai card 0, continue till visible, normal difficulty.\n");
   printf("Current visibility of ai card 0: %d\n", ai.visibility[0]);
   do {
      ai.visibility[0] = 0;//Reset this to zero to avoid erroring out if caught. **Only for testing**
      outcome = peek(&ai, 0, 25, 2);
      printf("Outcome was %d\n", outcome);
   }while(outcome != 2);

   printf("Current visibility of ai card 0: %d\n\n", ai.visibility[0]);

   //Steal a card from the player to the ai.
   printf("Attempting to steal Player cards 7, 6 and 3 as the AI\n");
   steal(&ai, &player, 7);
   steal(&ai, &player, 6);
   steal(&ai, &player, 3);

   for(i = 0; i < ai.card_count; i++)
      printf("AI card %d value: %d suite: %c\n", i, ai.values[i], ai.suite[i]);
   for(i = 0; i < player.card_count; i++)
      printf("Player card %d value: %d suite: %c\n", i, player.values[i], player.suite[i]);

   return(0);
}//End main.
*/
