# Deck Manager
 C++ program to manage a collection of Magic: The Gathering cards and decks.

I wanted to do a small project to practice C++. A common project is to create an "Accounting Program" and I wanted to do something like that but a bit different. I like Magic: The Gathering so I figured I could do something with that. This ended up being a bit more involved, but I also wanted to get some more practice with classes. While I haven't finished it, I did learn quite a bit about working on C++ projects and it was pretty fun.

I would like to come back to this clean it up and finish it, but if I wanted to really write a program to manage a MTG collection I would probably be better off coding it in python. As it is, you have to either enter cards one by one into the command prompt, or edit the .txt files in the "decklists," "proposedDecklists" and "collections" folders.

As it is, the code relies on several classes and inheritance to manage the menu, submenus, decklists and collections. 
Input files and output files are basic .txt files. You can either create a .txt file and put in card information that way which the program can access, or manually enter cards in one at a time to either a deck or collection. 
I have distinguished between a deck that is "proposed" versus a deck that is "published." If a deck is "proposed," changes to it do not affect your collection of cards. If you publish a proposed deck, all of the cards are added to your collection. I want to add another property where you can modify a "published" deck and re-add it to your collection without re-adding all of the cards. Something like taking out 5 cards and putting in 5 new ones should be pretty easy to do.

The program cannot currently check if commander decks are legal, or verify whether a card you want to add to a deck is a valid MTG card. Commander legality depends on the color identity of the commander, but the program doesn't actually have any information on card data. I have found a large carddata.json file with this information, but I have not yet written the code to parse the json yet.
