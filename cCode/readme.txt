Basic Readme

1.) Controls

a: shifts selection to the left, or up, by one unit

d: shifts selection to the right, or down,  by one unit

q: selects the currently selected option



2.) Objective

2.1) You want to get the highest number of prime cards in your hand.  The problem?
So does the AI.  While the AI is very simple, it's very good at this.  In order to 
make the game more interesting than just drawing cards, we added a betting 
feature that lets you bet on your cards.  

2.2) To make it even more interesting, we included cheating in the rules!
There is a penalty for getting caught cheating, the chances of getting caught 
increase with the chances taken on the cheat.  The peak function will allow you to 
try and peak at one of the AI's cards.  If you are successfull, you will see a card.
If you fail to see a card, but don't get caught, the game moves on as usual.  
If you fail to see a card AND get caught, the AI gets to see one of your cards.

2.3) The steal function is exactly what it sounds like, you -- or the AI -- can 
steal a card from the other player.  Be careful to steal a worthwhile card, though!



3.) Known bugs

3.1) Ocasionaly the AI will raise, forcing you to match or forfeit.  

3.2) The AI is currently very buggy.

3.3) There are a few graphics glitches, causing an auto selection of the peak command.  



4.) Extra Libraries

4.4) This program currently requires the ncurses-dev library installed to compile!


5.) Improvement plans

5.1) Massive overhaul of the game into c++ with a GUI + a change to OO design
