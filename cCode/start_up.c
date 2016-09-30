/*
 * Main menu displays
 * Matthew B.
 */
int main_menu(int i);
int main_select(int i, int n, int *done);
int game_mode(int i);
int game_over(int i);
int instructions(int i);


int main_menu(int i){

system("clear");
  if(i == 0){
    printf("              XXXXXXXX                    XXXXXXXXXXXXXX    XXXXXXXXXXXXXX    XXXXXXXXXXXXXXXX  XX            XX  XXXXXXXXXXXXXXXX\n");
    printf("             XXXXXXXXXX                   XXXXXXXXXXXXXXX   XXXXXXXXXXXXXXX   XXXXXXXXXXXXXXXX  XXX          XXX  XXXXXXXXXXXXXXXX\n");
    printf("            XXXXXXXXXXXX                  XXXXXX      XXXX  XXXXXX      XXXX  XXXXXXXXXXXXXXXX  XXXX        XXXX  XXXXXXXXXXXXXXXX\n");
    printf("           XXXXXXXXXXXXX                  XXXXXX       XXX  XXXXXX       XXX  XXXXXXXXXXXXXXXX  XXXXX      XXXXX   XXXXXXXXXXXXXXX\n");
    printf("          XXXXXX    XXXXXX                  XXXX        XX    XXXX        XX  XXX   XXXX   XXX  XXXXXX    XXXXXX    XXXX       XXX\n");
    printf("          XXXXX      XXXXX                  XXXX        XX    XXXX        XX  XX    XXXX    XX  XXXXXXX  XXXXXXX    XXXX        XX\n");
    printf("          XXXX                              XXXX       XXX    XXXX       XXX        XXXX        XXXXXXXXXXXXXXXX    XXXX          \n");
    printf("          XXXX                              XXXX      XXXX    XXXX      XXXX        XXXX        XXXXXXXXXXXXXXXX    XXXX          \n");
    printf("          XXXX                              XXXXXXXXXXXXX     XXXXXXXXXXXX          XXXX        XXXXXXXXXXXXXXXX    XXXX          \n");
    printf("          XXXX                              XXXXXXXXXXXX      XXXXXXXXXXX           XXXX        XXXXXXXXXXXXXXXX    XXXX          \n");
    printf("          XXXX                              XXXX              XXXXXXXXX             XXXX        XXXX  XXXX  XXXX    XXXXXXXXXX    \n");
    printf("          XXXX                XXXXXXXX      XXXX              XXXXXXXXX             XXXX        XXXX   XX   XXXX    XXXXXXXXXXXXX \n");
    printf("          XXXX                XXXXXXXX      XXXX              XXXX  XXXX            XXXX        XXXX        XXXX    XXXXXXXXXXXXX \n");
    printf("          XXXX                              XXXX              XXXX  XXXX            XXXX        XXXX        XXXX    XXXXXXXXXX    \n");
    printf("          XXXX                              XXXX              XXXX   XXX            XXXX        XXXX        XXXX    XXXX          \n");
    printf("          XXXX                              XXXX              XXXX   XXXX           XXXX        XXXX        XXXX    XXXX          \n");
    printf("          XXXX                              XXXX              XXXX    XXX           XXXX        XXXX        XXXX    XXXX          \n");
    printf("          XXXX                              XXXX              XXXX    XXXX          XXXX        XXXX        XXXX    XXXX          \n");
    printf("          XXXXX      XXXXX                  XXXX              XXXX     XXX    XX    XXXX    XX  XXXX        XXXX    XXXX        XX\n");
    printf("          XXXXXX    XXXXXX                  XXXX              XXXX     XXXX   XXX   XXXX   XXX  XXXX        XXXX    XXXX       XXX\n");
    printf("           XXXXXXXXXXXXXX                  XXXXXX            XXXXXX     XXX   XXXXXXXXXXXXXXXX  XXXX        XXXX   XXXXXXXXXXXXXXX\n");
    printf("            XXXXXXXXXXXX                  XXXXXXXX          XXXXXXXX    XXXX  XXXXXXXXXXXXXXXX  XXXX        XXXX  XXXXXXXXXXXXXXXX\n");
    printf("             XXXXXXXXXX                   XXXXXXXX          XXXXXXXX    XXXX  XXXXXXXXXXXXXXXX  XXXX        XXXX  XXXXXXXXXXXXXXXX\n");
    printf("              XXXXXXXX                    XXXXXXXX          XXXXXXXX    XXXX  XXXXXXXXXXXXXXXX  XXXX        XXXX  XXXXXXXXXXXXXXXX\n");


    printf("\n\n");

    printf(YELLOW"           START GAME"WHITE);
    printf("                                                                                    INSTRUCTIONS         \n");
  }

  else if(i == 1){
    printf("              XXXXXXXX                    XXXXXXXXXXXXXX    XXXXXXXXXXXXXX    XXXXXXXXXXXXXXXX  XX            XX  XXXXXXXXXXXXXXXX\n");
    printf("             XXXXXXXXXX                   XXXXXXXXXXXXXXX   XXXXXXXXXXXXXXX   XXXXXXXXXXXXXXXX  XXX          XXX  XXXXXXXXXXXXXXXX\n");
    printf("            XXXXXXXXXXXX                  XXXXXX      XXXX  XXXXXX      XXXX  XXXXXXXXXXXXXXXX  XXXX        XXXX  XXXXXXXXXXXXXXXX\n");
    printf("           XXXXXXXXXXXXX                  XXXXXX       XXX  XXXXXX       XXX  XXXXXXXXXXXXXXXX  XXXXX      XXXXX   XXXXXXXXXXXXXXX\n");
    printf("          XXXXXX    XXXXXX                  XXXX        XX    XXXX        XX  XXX   XXXX   XXX  XXXXXX    XXXXXX    XXXX       XXX\n");
    printf("          XXXXX      XXXXX                  XXXX        XX    XXXX        XX  XX    XXXX    XX  XXXXXXX  XXXXXXX    XXXX        XX\n");
    printf("          XXXX                              XXXX       XXX    XXXX       XXX        XXXX        XXXXXXXXXXXXXXXX    XXXX          \n");
    printf("          XXXX                              XXXX      XXXX    XXXX      XXXX        XXXX        XXXXXXXXXXXXXXXX    XXXX          \n");
    printf("          XXXX                              XXXXXXXXXXXXX     XXXXXXXXXXXX          XXXX        XXXXXXXXXXXXXXXX    XXXX          \n");
    printf("          XXXX                              XXXXXXXXXXXX      XXXXXXXXXXX           XXXX        XXXXXXXXXXXXXXXX    XXXX          \n");
    printf("          XXXX                              XXXX              XXXXXXXXX             XXXX        XXXX  XXXX  XXXX    XXXXXXXXXX    \n");
    printf("          XXXX                XXXXXXXX      XXXX              XXXXXXXXX             XXXX        XXXX   XX   XXXX    XXXXXXXXXXXXX \n");
    printf("          XXXX                XXXXXXXX      XXXX              XXXX  XXXX            XXXX        XXXX        XXXX    XXXXXXXXXXXXX \n");
    printf("          XXXX                              XXXX              XXXX  XXXX            XXXX        XXXX        XXXX    XXXXXXXXXX    \n");
    printf("          XXXX                              XXXX              XXXX   XXX            XXXX        XXXX        XXXX    XXXX          \n");
    printf("          XXXX                              XXXX              XXXX   XXXX           XXXX        XXXX        XXXX    XXXX          \n");
    printf("          XXXX                              XXXX              XXXX    XXX           XXXX        XXXX        XXXX    XXXX          \n");
    printf("          XXXX                              XXXX              XXXX    XXXX          XXXX        XXXX        XXXX    XXXX          \n");
    printf("          XXXXX      XXXXX                  XXXX              XXXX     XXX    XX    XXXX    XX  XXXX        XXXX    XXXX        XX\n");
    printf("          XXXXXX    XXXXXX                  XXXX              XXXX     XXXX   XXX   XXXX   XXX  XXXX        XXXX    XXXX       XXX\n");
    printf("           XXXXXXXXXXXXXX                  XXXXXX            XXXXXX     XXX   XXXXXXXXXXXXXXXX  XXXX        XXXX   XXXXXXXXXXXXXXX\n");
    printf("            XXXXXXXXXXXX                  XXXXXXXX          XXXXXXXX    XXXX  XXXXXXXXXXXXXXXX  XXXX        XXXX  XXXXXXXXXXXXXXXX\n");
    printf("             XXXXXXXXXX                   XXXXXXXX          XXXXXXXX    XXXX  XXXXXXXXXXXXXXXX  XXXX        XXXX  XXXXXXXXXXXXXXXX\n");
    printf("              XXXXXXXX                    XXXXXXXX          XXXXXXXX    XXXX  XXXXXXXXXXXXXXXX  XXXX        XXXX  XXXXXXXXXXXXXXXX\n");



    printf("\n\n");

    printf("           START GAME");
    printf(YELLOW"                                                                                    INSTRUCTIONS        \n"WHITE);
  }
}

int main_select(int i, int n, int *done){

  int ch;
  *done = 0;

  keypad(stdscr, TRUE);

  fflush(stdin);

  while(1){
    system("/bin/stty raw"); //prepare the console for getchar
    ch = getchar();
    system("/bin/stty cooked");
    //sensing keys left and right
    if(ch == 'a'){
      i--;
      //i = i % n;
      if(i < 0)
        i = 0;
      return(i);
    }

    if(ch == 'd'){
      i++;
      //i = i % n;
      if(i >= n)
        i = n-1;
      return(i);
    }

    if(ch == 'q'){
      *done = 1;
      return(i);
    }
  }
}

int instructions(int i){

  system("clear");
  printf("          RULES OF THE GAME          \n\n\n");
  printf("Game Start:\n");
  printf("  1. After confirming the difficulty, the game will start by dealing 2 cards to the AI and 2 cards to the player.\n");
  printf("  2. The players and the AI's wallet will start at $1000, this money will later determine the winner.\n\n");

  printf("How to Win:\n");
  printf("  1. The goal of the game is to get the greatest sum of prime of prime number cards in your hand. The player will place bets depending on how good they think their hand\n");
  printf("     is. The winner of the round will get the money that was bet on that round.\n");
  printf("  2. The winner of the game will be the person who ends up with with all the money. The person or AI with $0 left in their wallet, loses that game.\n\n");

  printf("Playing the game:\n");
  printf("  1. After the initial dealing is done, the player will beprompted for their first move, where they can choose to either draw, peek, or steal a card.\n\n");
  printf("     Draw:   This is the safest move for the player to make, no risk no reward, this option lets the player draw a card, then move to the next turn.\n\n");
  printf("     Peek:   This option allows the user to choose one of the opponents cards, and input a percent value. This value will be how likely it is that you will get to see\n");
  printf("             that card. Be carefull though, depending on your the chance of you getting caught will increase. caught or not, you draw at the end of the turn\n\n");
  printf("     Caught: If you lose a peek, the enemy gets to look at one of your cards, but will not have the luxery of choosing which card they get to see.\n\n");
  printf("     Steal:  This option will allow you to steal one of the other players cards, regardless of if you know the card or not.\n\n");
  printf("  2. This will be repeated until the round how gone through 8 turns. At this point the winner will be calculated and a new round will be started, as long as both players\n");
  printf("     still have something to bet with(your soul does not count).\n\n\n");

  printf(YELLOW"Back to Main Menu"WHITE);
  
}

int game_mode(int i){

  system("clear");
  if(i == 1){
    printf("GAME MODE\n\n\n");

    printf("Main Menu\n\n");

    printf(YELLOW"Childs Play\n\n"WHITE);

    printf("Medium\n\n");

    printf("Lumberjack\n\n");

    printf("Honey Badger\n\n");
  }

  else if(i == 2){
    printf("GAME MODE\n\n\n");

    printf("Main Menu\n\n");

    printf("Childs Play\n\n");

    printf(YELLOW"Medium\n\n"WHITE);

    printf("Lumberjack\n\n");

    printf("Honey Badger\n\n");
  }

  else if(i == 3){
    printf("GAME MODE\n\n\n");

    printf("Main Menu\n\n");

    printf("Childs Play\n\n");

    printf("Medium\n\n");

    printf(YELLOW"Lumberjack\n\n"WHITE);

    printf("Honey Badger\n\n");
  }

  else if(i == 4){
    printf("GAME MODE\n\n\n");

    printf("Main Menu\n\n");

    printf("Childs Play\n\n");

    printf("Medium\n\n");

    printf("Lumberjack\n\n");

    printf(YELLOW"Honey Badger\n\n"WHITE);
  }

  else if(i == 0){

    printf("GAME MODE\n\n\n");

    printf(YELLOW"Main Menu\n\n"WHITE);

    printf("Childs Play\n\n");

    printf("Medium\n\n");

    printf("Lumberjack\n\n");

    printf("Honey Badger\n\n");

  }

}

int game_over(int i){
	system("clear");
  if(i == 0){
    printf("    XXXXXXXX           XXXXXX       XX            XX  XXXXXXXXXXXXXXXX          XXXXXXXX      XXXX        XXXX  XXXXXXXXXXXXXXXX  XXXXXXXXXXXXXX  \n");
    printf("   XXXXXXXXXX          XXXXXX       XXX          XXX  XXXXXXXXXXXXXXXX         XXXXXXXXXX     XXXX        XXXX  XXXXXXXXXXXXXXXX  XXXXXXXXXXXXXXX \n");
    printf("  XXXXXXXXXXXX        XXXXXXXX      XXXX        XXXX  XXXXXXXXXXXXXXXX        XXXXXXXXXXXX    XXXX        XXXX  XXXXXXXXXXXXXXXX  XXXXXX      XXXX\n");
    printf(" XXXXXXXXXXXXX        XXXXXXXX      XXXXX      XXXXX   XXXXXXXXXXXXXXX       XXXXXXXXXXXXX    XXXX        XXXX   XXXXXXXXXXXXXXX  XXXXXX       XXX\n");
    printf("XXXXXX    XXXXXX     XXXXXXXXXX     XXXXXX    XXXXXX   XXXX        XXX      XXXXXX    XXXXXX  XXXX        XXXX   XXXX        XXX    XXXX        XX\n");
    printf("XXXXX      XXXXX     XXXXXXXXXX     XXXXXXX  XXXXXXX   XXXX         XX      XXXXX      XXXXX  XXXX        XXXX   XXXX         XX    XXXX        XX\n");
    printf("XXXX                 XXXXXXXXXX     XXXXXXXXXXXXXXXX   XXXX                 XXXX        XXXX  XXXXX      XXXXX   XXXX               XXXX       XXX\n");
    printf("XXXX                 XXXXXXXXXX     XXXXXXXXXXXXXXXX   XXXX                 XXXX        XXXX  XXXXX      XXXXX   XXXX               XXXX      XXXX\n");
    printf("XXXX                XXXX    XXXX    XXXXXXXXXXXXXXXX   XXXX                 XXXX        XXXX  XXXXX      XXXXX   XXXX               XXXXXXXXXXXX  \n");
    printf("XXXX                XXXX    XXXX    XXXXXXXXXXXXXXXX   XXXX                 XXXX        XXXX   XXXX      XXXX    XXXX               XXXXXXXXXXX   \n");
    printf("XXXX                XXXX    XXXX    XXXX  XXXX  XXXX   XXXXXXXXXX           XXXX        XXXX   XXXX      XXXX    XXXXXXXXXX         XXXXXXXXX     \n");
    printf("XXXX                XXXX    XXXX    XXXX   XX   XXXX   XXXXXXXXXXXXX        XXXX        XXXX   XXXX      XXXX    XXXXXXXXXXXXX      XXXXXXXXX     \n");
    printf("XXXX               XXXXXXXXXXXXXX   XXXX        XXXX   XXXXXXXXXXXXX        XXXX        XXXX    XXXX    XXXX     XXXXXXXXXXXXX      XXXX  XXXX    \n");
    printf("XXXX    XXXXXXXX   XXXXXXXXXXXXXX   XXXX        XXXX   XXXXXXXXXX           XXXX        XXXX    XXXX    XXXX     XXXXXXXXXX         XXXX  XXXX    \n");
    printf("XXXX    XXXXXXXX   XXXXXXXXXXXXXX   XXXX        XXXX   XXXX                 XXXX        XXXX    XXXX    XXXX     XXXX               XXXX   XXX    \n");
    printf("XXXX    XXXXXXXX   XXXXX    XXXXX   XXXX        XXXX   XXXX                 XXXX        XXXX    XXXX    XXXX     XXXX               XXXX   XXXX   \n");
    printf("XXXX        XXXX  XXXXX      XXXXX  XXXX        XXXX   XXXX                 XXXX        XXXX    XXXX    XXXX     XXXX               XXXX    XXX   \n");
    printf("XXXX        XXXX  XXXXX      XXXXX  XXXX        XXXX   XXXX                 XXXX        XXXX     XXXX  XXXX      XXXX               XXXX    XXXX  \n");
    printf("XXXXX      XXXXX  XXXXX      XXXXX  XXXX        XXXX   XXXX         XX      XXXXX      XXXXX     XXXX  XXXX      XXXX         XX    XXXX     XXX  \n");
    printf("XXXXXX    XXXXXX  XXXX        XXXX  XXXX        XXXX   XXXX        XXX      XXXXXX    XXXXXX     XXXXXXXXXX      XXXX        XXX    XXXX     XXXX \n");
    printf(" XXXXXXXXXXXXXX   XXXX        XXXX  XXXX        XXXX   XXXXXXXXXXXXXXX       XXXXXXXXXXXXXX       XXXXXXXX       XXXXXXXXXXXXXXX   XXXXXX     XXX \n");
    printf("  XXXXXXXXXXXX    XXXX        XXXX  XXXX        XXXX  XXXXXXXXXXXXXXXX        XXXXXXXXXXXX        XXXXXXXX      XXXXXXXXXXXXXXXX  XXXXXXXX    XXXX\n");
    printf("   XXXXXXXXXX     XXXX        XXXX  XXXX        XXXX  XXXXXXXXXXXXXXXX         XXXXXXXXXX          XXXXXX       XXXXXXXXXXXXXXXX  XXXXXXXX    XXXX\n");
    printf("    XXXXXXXX      XXXX        XXXX  XXXX        XXXX  XXXXXXXXXXXXXXXX          XXXXXXXX           XXXXXX       XXXXXXXXXXXXXXXX  XXXXXXXX    XXXX\n");

    printf("\n\n");

    printf(YELLOW"           PLAY AGAIN?"WHITE);
    printf("                                                                                    EXIT GAME         \n");
  }

  if(i == 1){
    printf("    XXXXXXXX           XXXXXX       XX            XX  XXXXXXXXXXXXXXXX          XXXXXXXX      XXXX        XXXX  XXXXXXXXXXXXXXXX  XXXXXXXXXXXXXX  \n");
    printf("   XXXXXXXXXX          XXXXXX       XXX          XXX  XXXXXXXXXXXXXXXX         XXXXXXXXXX     XXXX        XXXX  XXXXXXXXXXXXXXXX  XXXXXXXXXXXXXXX \n");
    printf("  XXXXXXXXXXXX        XXXXXXXX      XXXX        XXXX  XXXXXXXXXXXXXXXX        XXXXXXXXXXXX    XXXX        XXXX  XXXXXXXXXXXXXXXX  XXXXXX      XXXX\n");
    printf(" XXXXXXXXXXXXX        XXXXXXXX      XXXXX      XXXXX   XXXXXXXXXXXXXXX       XXXXXXXXXXXXX    XXXX        XXXX   XXXXXXXXXXXXXXX  XXXXXX       XXX\n");
    printf("XXXXXX    XXXXXX     XXXXXXXXXX     XXXXXX    XXXXXX   XXXX        XXX      XXXXXX    XXXXXX  XXXX        XXXX   XXXX        XXX    XXXX        XX\n");
    printf("XXXXX      XXXXX     XXXXXXXXXX     XXXXXXX  XXXXXXX   XXXX         XX      XXXXX      XXXXX  XXXX        XXXX   XXXX         XX    XXXX        XX\n");
    printf("XXXX                 XXXXXXXXXX     XXXXXXXXXXXXXXXX   XXXX                 XXXX        XXXX  XXXXX      XXXXX   XXXX               XXXX       XXX\n");
    printf("XXXX                 XXXXXXXXXX     XXXXXXXXXXXXXXXX   XXXX                 XXXX        XXXX  XXXXX      XXXXX   XXXX               XXXX      XXXX\n");
    printf("XXXX                XXXX    XXXX    XXXXXXXXXXXXXXXX   XXXX                 XXXX        XXXX  XXXXX      XXXXX   XXXX               XXXXXXXXXXXX  \n");
    printf("XXXX                XXXX    XXXX    XXXXXXXXXXXXXXXX   XXXX                 XXXX        XXXX   XXXX      XXXX    XXXX               XXXXXXXXXXX   \n");
    printf("XXXX                XXXX    XXXX    XXXX  XXXX  XXXX   XXXXXXXXXX           XXXX        XXXX   XXXX      XXXX    XXXXXXXXXX         XXXXXXXXX     \n");
    printf("XXXX                XXXX    XXXX    XXXX   XX   XXXX   XXXXXXXXXXXXX        XXXX        XXXX   XXXX      XXXX    XXXXXXXXXXXXX      XXXXXXXXX     \n");
    printf("XXXX               XXXXXXXXXXXXXX   XXXX        XXXX   XXXXXXXXXXXXX        XXXX        XXXX    XXXX    XXXX     XXXXXXXXXXXXX      XXXX  XXXX    \n");
    printf("XXXX    XXXXXXXX   XXXXXXXXXXXXXX   XXXX        XXXX   XXXXXXXXXX           XXXX        XXXX    XXXX    XXXX     XXXXXXXXXX         XXXX  XXXX    \n");
    printf("XXXX    XXXXXXXX   XXXXXXXXXXXXXX   XXXX        XXXX   XXXX                 XXXX        XXXX    XXXX    XXXX     XXXX               XXXX   XXX    \n");
    printf("XXXX    XXXXXXXX   XXXXX    XXXXX   XXXX        XXXX   XXXX                 XXXX        XXXX    XXXX    XXXX     XXXX               XXXX   XXXX   \n");
    printf("XXXX        XXXX  XXXXX      XXXXX  XXXX        XXXX   XXXX                 XXXX        XXXX    XXXX    XXXX     XXXX               XXXX    XXX   \n");
    printf("XXXX        XXXX  XXXXX      XXXXX  XXXX        XXXX   XXXX                 XXXX        XXXX     XXXX  XXXX      XXXX               XXXX    XXXX  \n");
    printf("XXXXX      XXXXX  XXXXX      XXXXX  XXXX        XXXX   XXXX         XX      XXXXX      XXXXX     XXXX  XXXX      XXXX         XX    XXXX     XXX  \n");
    printf("XXXXXX    XXXXXX  XXXX        XXXX  XXXX        XXXX   XXXX        XXX      XXXXXX    XXXXXX     XXXXXXXXXX      XXXX        XXX    XXXX     XXXX \n");
    printf(" XXXXXXXXXXXXXX   XXXX        XXXX  XXXX        XXXX   XXXXXXXXXXXXXXX       XXXXXXXXXXXXXX       XXXXXXXX       XXXXXXXXXXXXXXX   XXXXXX     XXX \n");
    printf("  XXXXXXXXXXXX    XXXX        XXXX  XXXX        XXXX  XXXXXXXXXXXXXXXX        XXXXXXXXXXXX        XXXXXXXX      XXXXXXXXXXXXXXXX  XXXXXXXX    XXXX\n");
    printf("   XXXXXXXXXX     XXXX        XXXX  XXXX        XXXX  XXXXXXXXXXXXXXXX         XXXXXXXXXX          XXXXXX       XXXXXXXXXXXXXXXX  XXXXXXXX    XXXX\n");
    printf("    XXXXXXXX      XXXX        XXXX  XXXX        XXXX  XXXXXXXXXXXXXXXX          XXXXXXXX           XXXXXX       XXXXXXXXXXXXXXXX  XXXXXXXX    XXXX\n");


  

    printf("\n\n");

    printf("           PLAY AGAIN?");
    printf(YELLOW"                                                                                    EXIT GAME         \n"WHITE);
  }
}
