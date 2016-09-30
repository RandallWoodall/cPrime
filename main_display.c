/*
 * Display for cards and selection tool
 * Matthew B.
 */

#include <stdio.h>
#include <stdlib.h>

void display_card(hand to_show, int select, int hand_trak);
int game_turn(int ai_cash, int player_cash, int pot, int i);
int betting(int ai_cash, int player_cash, int pot, int i);
void match_ai(int ai_cash, int player_cash, int pot, int i, int bet_match);
void forfeit(int i);


///////////////////////////////////////////
//Function: print out card art and values//
///////////////////////////////////////////
void display_card(hand to_show, int select, int hand_trak){
  int j;
    /////////////
    //First row//
    /////////////
	for(j = 0; j < to_show.card_count; j++){
		if(to_show.stolen[j] == 1){//card has been stolen
			if(j != select){
                                printf(RED"_______________"WHITE);
                        }
                          else if(j == select){ //card is selected
                                printf(YELLOW"______________"WHITE);
                        }
		}
		else{//card has not been stolen
			if(to_show.visibility[j] == 1 || hand_trak == 1){//card us visible on screen
			  if(j != select){
				printf("_______________");
			  }
			  else if(j == select){ //card is selected
				printf(YELLOW"______________"WHITE);
			  }
			}
			else if(to_show.visibility[j] == 0){//card is not visible on screen
			  if(j != select){
				printf("_______________");
			  }
			  else if(j == select){ //card is selected
				printf(YELLOW"______________"WHITE);
			  }
			}
		}
	}//end row 1
    printf("\n");
    //////////////
    //second row//
    //////////////
    for(j = 0; j < to_show.card_count; j++){
		if(to_show.stolen[j] == 1){//card has been stolen
                        if( j != select){
                                if(to_show.values[j] == -99){
                                        printf(RED"|             |"WHITE);
                                }
                                else if(to_show.values[j] < 10){
                                        printf(RED"|%d            |"WHITE , to_show.values[j]);
                                }
                                else{
                                        printf(RED"|%d           |"WHITE , to_show.values[j]);
                                }
                        }
			else if(j == select){ // card is selected
                                if(to_show.values[j] == -99){
                                        printf(YELLOW"|             |"WHITE);
                                }
                                else if(to_show.values[j] < 10){
                                        printf(YELLOW"|%d            |"WHITE, to_show.values[j]);
                                }
                                else{
                                        printf(YELLOW"|%d           |"WHITE, to_show.values[j]);
                                }
                        }
                }
		else{
			if(to_show.visibility[j] == 1 || hand_trak == 1){
				if( j != select){
					if(to_show.values[j] == -99){
						printf("|             |");
					}
					else if(to_show.values[j] < 10){
						printf("|%d            |", to_show.values[j]);
					}
					else{
						printf("|%d           |", to_show.values[j]);
					}
				}
				else if(j == select){ // card is selected
					if(to_show.values[j] == -99){
						printf(YELLOW"|             |"WHITE);
					}
					else if(to_show.values[j] < 10){
						printf(YELLOW"|%d            |"WHITE, to_show.values[j]);
					}
					else{
						printf(YELLOW"|%d           |"WHITE, to_show.values[j]);
					}
				}
			}
			//Card is not visible on screen
			else if(to_show.visibility[j] == 0){
				if(j != select){
					printf("| \\         / |");
				}
				else if(j == select){ // card is selected
					printf(YELLOW"| \\         / |"WHITE);
				}
			}
		}
    }//end second row
    printf("\n");	
    /////////////
    //third row//
    /////////////
    for(j = 0; j < to_show.card_count; j++){
	if(to_show.stolen[j] == 1){
		if(j != select){
                                printf(RED"|             |"WHITE);
                        }
                        else if(j == select){ // card is selected
                                printf(YELLOW"|             |"WHITE);
                        }
	}
	else{
		if(to_show.visibility[j] == 1 || hand_trak == 1){//Card is visible on screen
			if(j != select){
				printf("|             |");
			}
			else if(j == select){ // card is selected
				printf(YELLOW"|             |"WHITE);
			}
		}
		//Card is not visible on screen
		else if(to_show.visibility[j] == 0){//Card is not visible on screen
			if(j != select){
				printf("| \\         / |");
			}
			else if(j == select){ // card is selected
				printf(YELLOW"| \\         / |"WHITE);
			}		
		}
	}
    }//end row 3
    printf("\n");

    //fourth row
    for(j = 0; j < to_show.card_count; j++){
	if(to_show.stolen[j] == 1){//card has been stolen before
		if(to_show.suite[j] == 't'){
                                if(j != select){
                                        printf(RED"|      X      |"WHITE);
                                }
                                else if(j == select){ // card is selected
                                        printf(YELLOW"|      X      |"WHITE);
                                }
                        }
                        else if(to_show.suite[j] == 'c'){
                                if(j != select){
                                        printf(RED"|    X   X    |"WHITE);
                                }
                                else if(j == select){ // card is selected
                                        printf(YELLOW"|    X   X    |"WHITE);
                                }
                        }
                        else if(to_show.suite[j] == 'p'){
                                if(j != select){
                                        printf(RED"|    X X X    |"WHITE);
                                }
                                else if(j == select){ // card is selected
                                        printf(YELLOW"|    X X X    |"WHITE);
                                }
                        }
	}
	else{//card has not been stolen before
		if(to_show.visibility[j] == 1 || hand_trak == 1){//Card is visible on screen
			if(to_show.suite[j] == 't'){
				if(j != select){
					printf("|      X      |");
				}
				else if(j == select){ // card is selected
					printf(YELLOW"|      X      |"WHITE);
				}
			}
			else if(to_show.suite[j] == 'c'){
				if(j != select){
					printf("|    X   X    |");
				}
				else if(j == select){ // card is selected
					printf(YELLOW"|    X   X    |"WHITE);
				}
			}
			else if(to_show.suite[j] == 'p'){
				if(j != select){
					printf("|    X X X    |");
				}
				else if(j == select){ // card is selected
					printf(YELLOW"|    X X X    |"WHITE);
				}
			}
		}
		else if(to_show.visibility[j] == 0){//Card is not visible on screen
			if(j != select){
				printf("|  \\_     _/  |");
			}
			else if(j == select){ // card is selected
				printf(YELLOW"|  \\_     _/  |"WHITE);
			}
		}
	}
    }//end row 4
    printf("\n");

    //fifth row
    for(j = 0; j < to_show.card_count; j++){
	if(to_show.stolen[j] == 1){//card has been stolen before
		if(to_show.suite[j] == 't'){
                                if(j != select){
                                        printf(RED"|      X      |"WHITE);
                                }
                                else if(j == select){ // card is selected
                                        printf(YELLOW"|      X      |"WHITE);
                                }
                        }
                        else if(to_show.suite[j] == 'c'){
                                if(j != select){
                                        printf(RED"|     X X     |"WHITE);
                                }
                                else if(j == select){ // card is selected
                                        printf(YELLOW"|     X X     |"WHITE);
                                }
                        }
                        else if(to_show.suite[j] == 'p'){
                                if(j != select){
                                        printf(RED"|     XXX     |"WHITE);
                                }
                                else if(j == select){ // card is selected
                                        printf(YELLOW"|     XXX     |"WHITE);
                                }
                        }
	}
	else{//card has not been stolen
		if(to_show.visibility[j] == 1 || hand_trak == 1){//Card is visible on screen
			if(to_show.suite[j] == 't'){
				if(j != select){
					printf("|      X      |");
				}
				else if(j == select){ // card is selected
					printf(YELLOW"|      X      |"WHITE);
				}
			}
			else if(to_show.suite[j] == 'c'){
				if(j != select){
					printf("|     X X     |");
				}
				else if(j == select){ // card is selected
					printf(YELLOW"|     X X     |"WHITE);
				}
			}
			else if(to_show.suite[j] == 'p'){
				if(j != select){
					printf("|     XXX     |");
				}
				else if(j == select){ // card is selected
					printf(YELLOW"|     XXX     |"WHITE);
				}
			}
		}
		else if(to_show.visibility[j] == 0){//Card is not visible on screen
			if(j != select){
				printf("|  \\_     _/  |");
			}
			else if(j == select){ // card is selected
				printf(YELLOW"|  \\_     _/  |"WHITE);
			}
		}
	}
    }
    printf("\n");
	
    //sixth row
    for(j = 0; j < to_show.card_count; j++){
	if(to_show.stolen[j] == 1){//card has been stolen
		if(to_show.suite[j] == 't'){
                                if(j != select){
                                        printf(RED"|    XXXXX    |"WHITE);
                                }
                                else if(j == select){ // card is selected
                                        printf(YELLOW"|    XXXXX    |"WHITE);
                                }
                        }
                        else if(to_show.suite[j] == 'c'){
                                if(j != select){
                                        printf(RED"|      X      |"WHITE);
                                }
                                else if(j == select){ // card is selected
                                        printf(YELLOW"|      X      |"WHITE);
                                }
                        }
                        else if(to_show.suite[j] == 'p'){
                                if(j != select){
                                        printf(RED"|    XXXXX    |"WHITE);
                                }
                                else if(j == select){ // card is selected
                                        printf(YELLOW"|    XXXXX    |"WHITE);
                                }
                        }
	}
	else{//card has not ben stolen
		if(to_show.visibility[j] == 1 || hand_trak == 1){//card is visible on screen
			if(to_show.suite[j] == 't'){
				if(j != select){
					printf("|    XXXXX    |");
				}
				else if(j == select){ // card is selected
					printf(YELLOW"|    XXXXX    |"WHITE);
				}
			}
			else if(to_show.suite[j] == 'c'){
				if(j != select){
					printf("|      X      |");
				}
				else if(j == select){ // card is selected
					printf(YELLOW"|      X      |"WHITE);
				}
			}
			else if(to_show.suite[j] == 'p'){
				if(j != select){
					printf("|    XXXXX    |");
				}
				else if(j == select){ // card is selected
					printf(YELLOW"|    XXXXX    |"WHITE);
				}
			}
		}
		else if(to_show.visibility[j] == 0){//Card is not visible on screen
			if(j != select){
				printf("|    \\_ _/    |");
			}
			else if(j == select){ // card is selected
				printf(YELLOW"|    \\_ _/    |"WHITE);
			}
		}
	}
    }
    printf("\n");

    //seventh row
    for(j = 0; j < to_show.card_count; j++){
	if(to_show.stolen[j] == 1){//card has been stolen
		if(to_show.suite[j] == 't'){
                                if(j != select){
                                        printf(RED"|      X      |"WHITE);
                                }
                                else if(j == select){ // card is selected
                                        printf(YELLOW"|      X      |"WHITE);
                                }
                        }
                        else if(to_show.suite[j] == 'c'){
                                if(j != select){
                                        printf(RED"|     X X     |"WHITE);
                                }
                                else if(j == select){ // card is selected
                                        printf(YELLOW"|     X X     |"WHITE);
                                }
                        }
                        else if(to_show.suite[j] == 'p'){
                                if(j != select){
                                        printf(RED"|     XXX     |"WHITE);
                                }
                                else if(j == select){ // card is selected
                                        printf(YELLOW"|     XXX     |"WHITE);
                                }
                        }
	}
	else{//card has not been stolen
		if(to_show.visibility[j] == 1 || hand_trak == 1){//Card is printed on screen
			if(to_show.suite[j] == 't'){
				if(j != select){
					printf("|      X      |");
				}
				else if(j == select){ // card is selected
					printf(YELLOW"|      X      |"WHITE);
				}
			}
			else if(to_show.suite[j] == 'c'){
				if(j != select){
					printf("|     X X     |");
				}
				else if(j == select){ // card is selected
					printf(YELLOW"|     X X     |"WHITE);
				}
			}
			else if(to_show.suite[j] == 'p'){
				if(j != select){
					printf("|     XXX     |");
				}
				else if(j == select){ // card is selected
					printf(YELLOW"|     XXX     |"WHITE);
				}
			}
		}
		else if(to_show.visibility[j] == 0){//Card is not visible to the player
			if(j != select){
				printf("|   __/ \\__   |");
			}
			else if(j == select){ // card is selected
				printf(YELLOW"|   __/ \\__   |"WHITE);
			}
		}
	}
    }
    printf("\n");

    //eighth row
    for(j = 0; j < to_show.card_count; j++){
	if(to_show.stolen[j] == 1){//card has been stolen
		if(to_show.suite[j] == 't'){//Suite symbols
                                if(j != select){
                                        printf(RED"|      X      |"WHITE);
                                }
                                else if(j == select){ // card is selected
                                        printf(YELLOW"|      X      |"WHITE);
                                }
                        }
                        else if(to_show.suite[j] == 'c'){
                                if(j != select){
                                        printf(RED"|    X   X    |"WHITE);
                                }
                                else if(j == select){ // card is selected
                                        printf(YELLOW"|    X   X    |"WHITE);
                                }
                        }
                        else if(to_show.suite[j] == 'p'){
                                if(j != select){
                                        printf(RED"|    X X X    |"WHITE);
                                }
                                else if(j == select){ // card is selected
                                        printf(YELLOW"|    X X X    |"WHITE);
                                }
                        }
	}
	else{//card has not been stolen
		if(to_show.visibility[j] == 1 || hand_trak == 1){//Card is visible on screen
			if(to_show.suite[j] == 't'){//Suite symbols
				if(j != select){
					printf("|      X      |");
				}
				else if(j == select){ // card is selected
					printf(YELLOW"|      X      |"WHITE);
				}
			}
			else if(to_show.suite[j] == 'c'){
				if(j != select){
					printf("|    X   X    |");
				}
				else if(j == select){ // card is selected
					printf(YELLOW"|    X   X    |"WHITE);
				}
			}
			else if(to_show.suite[j] == 'p'){
				if(j != select){
					printf("|    X X X    |");
				}
				else if(j == select){ // card is selected
					printf(YELLOW"|    X X X    |"WHITE);
				}
			}
		}
		else if(to_show.visibility[j] == 0){
			if(j != select){
				printf("|   /     \\   |");
			}
			else if(j == select){ // card is selected
				printf(YELLOW"|   /     \\   |"WHITE);
			}
		}
	}
    }
    printf("\n");


    //
    //ninth row
    for(j = 0; j < to_show.card_count; j++){
	if(to_show.stolen[j] == 1){//card has been stolen
                if(j != select){
                                printf(RED"|             |"WHITE);
                        }
                        else if(j == select){ // card is selected
                                printf(YELLOW"|             |"WHITE);
                        }
        }
	else{//card has not been stolen
		if(to_show.visibility[j] == 1 || hand_trak == 1){
			if(j != select){
				printf("|             |");
			}
			else if(j == select){ //card is selected
				printf(YELLOW"|             |"WHITE);
			}
		}
		else if(to_show.visibility[j] == 0){
			if(j != select){
				printf("|  /       \\  |");
			}
			else if(j == select){ // card is selected
				printf(YELLOW"|  /       \\  |"WHITE);
			}
		}
	}
    }
	printf("\n");
    //
    //tenth row
    for(j = 0; j < to_show.card_count; j++){
	if(to_show.stolen[j] == 1){//card has been stolen
                if(j != select){
                                printf(RED"|             |"WHITE);
                        }
                        else if(j == select){ // card is selected
                                printf(YELLOW"|             |"WHITE);
                        }
        }
	else{//card has not been stolen
		if(to_show.visibility[j] == 1 || hand_trak == 1){
			if(j != select){
				printf("|             |");
			}
			else if(j == select){ //card is selected
				printf(YELLOW"|             |"WHITE);
			}
		}
		else if(to_show.visibility[j] == 0){
			if(j != select){
				printf("|  /       \\  |");
			}
			else if(j == select){ // card is selected
				printf(YELLOW"|  /       \\  |"WHITE);
			}
		}
	}
    }
    printf("\n");
    //
    //eleventh row
    for(j = 0; j < to_show.card_count; j++){
	if(to_show.stolen[j] == 1){//card has been stolen
		if( j != select){
                                if(to_show.values[j] == -99){
                                        printf(RED"|_____________|"WHITE);
                                }
                                else if(to_show.values[j] < 10){
                                        printf(RED"|____________%d|"WHITE , to_show.values[j]);
                                }
                                else{
                                        printf(RED"|___________%d|"WHITE , to_show.values[j]);
                                }
                        }
                        else if(j == select){ // card is selected
                                if(to_show.values[j] == -99){
                                        printf(YELLOW"|_____________|"WHITE);
                                }
                                else if(to_show.values[j] < 10){
                                        printf(YELLOW"|____________%d|"WHITE, to_show.values[j]);
                                }
                                else{
                                        printf(YELLOW"|___________%d|"WHITE, to_show.values[j]);
                                }
                        }
	}
	else{//card has not been stolen
		if(to_show.visibility[j] == 1 || hand_trak == 1){
			if( j != select){
				if(to_show.values[j] == -99){
					printf("|_____________|");
				}
				else if(to_show.values[j] < 10){
					printf("|____________%d|", to_show.values[j]);
				}
				else{
					printf("|___________%d|", to_show.values[j]);
				}
			}
			else if(j == select){ // card is selected
				if(to_show.values[j] == -99){
					printf(YELLOW"|_____________|"WHITE);
				}
				else if(to_show.values[j] < 10){
					printf(YELLOW"|____________%d|"WHITE, to_show.values[j]);
				}
				else{
					printf(YELLOW"|___________%d|"WHITE, to_show.values[j]);
				}
			}
		}
		//Card is not visible on screen
		else if(to_show.visibility[j] == 0){
			if(j != select){
				printf("|_____________|");
			}
			else if(j == select){ // card is selected
				printf(YELLOW"|_____________|"WHITE);
			}
		}
	}
    }
    printf("\n");
}

/////////////////////////////////////////////////////////////////////////
//Function: displays the current stats and options for the coming turn.//
/////////////////////////////////////////////////////////////////////////
int game_turn(int ai_cash, int player_cash, int pot, int i){
  
	printf("\n\n\n");
  
	//Row 1 : current pot
	printf("Current Pot: %d\n", pot);
	//Row 2: player_cash and player options. selection is called here
	if(i == 0){
		printf("Current Cash: %d              "YELLOW"DRAW"WHITE"                PEAK               STEAL               FORFEIT\n", player_cash);
	}
	else if(i == 1){
		printf("Current Cash: %d              DRAW                "YELLOW"PEAK"WHITE"               STEAL               FORFEIT\n", player_cash);
	}
	else if(i == 2){
		printf("Current Cash: %d              DRAW                PEAK               "YELLOW"STEAL"WHITE"               FORFEIT\n", player_cash);
	}
	else if(i == 3){
		printf("Current Cash: %d              DRAW                PEAK               STEAL               "YELLOW"FORFEIT"WHITE"\n", player_cash);
	}
		//Row 3: ai_cash
		printf("Opponent Cash: %d\n", ai_cash);
}

////////////////////////////////////////////////
//Function: Called for betting on current hand//
////////////////////////////////////////////////
int betting(int ai_cash, int player_cash, int pot, int i){
  
	printf("\n\n\n");
  
	//Row 1 : current pot
	printf("Current Pot: %d\n", pot);
	//Row 2: player_cash and player options. selection is called here
	if(i == 0){
		printf("Current Cash: %d              "YELLOW"BET $10"WHITE"                BET $50               BET $100               DONE BETTING               FOLD               ALL IN\n", player_cash);
	}
	else if(i == 1){
		printf("Current Cash: %d              BET $10                "YELLOW"BET $50"WHITE"               BET $100               DONE BETTING               FOLD               ALL IN\n", player_cash);
	}
	else if(i == 2){
		printf("Current Cash: %d              BET $10                BET $50               "YELLOW"BET $100"WHITE"               DONE BETTING               FOLD               ALL IN\n", player_cash);
	}
	else if(i == 3){
		printf("Current Cash: %d              BET $10                BET $50               BET $100               "YELLOW"DONE BETTING"WHITE"               FOLD               ALL IN\n", player_cash);
	}
	else if(i == 4){
		printf("Current Cash: %d              BET $10                BET $50               BET $100               DONE BETTING               "YELLOW"FOLD"WHITE"               ALL IN\n", player_cash);
	}
	else if(i == 5){
		printf("Current Cash: %d              BET $10                BET $50               BET $100               DONE BETTING               FOLD               "YELLOW"ALL IN"WHITE"\n", player_cash);
	}
	//Row 3: ai_cash
	printf("Opponent Cash: %d\n", ai_cash);
}
////////////////////////////////////////////////////
//Function: Called to match the player and ai bets//
////////////////////////////////////////////////////
void match_ai(int ai_cash, int player_cash, int pot, int i, int bet_match){
	  
	printf("\n\n\n");
  
	//Row 1 : current pot
	printf("Current Pot: %d                    AI raised bet by: %d\n", pot, bet_match);
	
	//Row 2: player_cash and player options. selection is called here
	if(i == 0){
		printf("Current Cash: %d          "YELLOW"MATCH"WHITE"               FOLD\n", player_cash);
	}
	else if(i == 1){
		printf("Current Cash: %d          MATCH               "YELLOW"FOLD"WHITE"\n", player_cash);
	}

	//Row 3: ai_cash
	printf("Opponent Cash: %d\n", ai_cash);
}
/////////////////////////////////////////////////////////
//Function: Called if the player wishes to end the game//
/////////////////////////////////////////////////////////
void forfeit(int i){
	printf("Are you sure you want to quit?\n");
	
	if(i == 0){
		printf(YELLOW"Yes"WHITE"          No");
	}
	else if(i == 1){
		printf("Yes          "YELLOW"No"WHITE);
	}
}
