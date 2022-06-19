//Jaime Cabriales
//COSC-2436-V01
//April 12, 2020
//THIS IS A LINK TO THE GAME MAP


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
using namespace std;

//Function Prototypes
void topScrn(char Name);
void PauseMenu(char Name);
void MainMenu();
void SaveGame(char Name);
void LoadGame();
void Inventory();
void Help();
void exitProgram();
void Clearer();

struct ListNode
{
	char Name;
	ListNode* Up;
	ListNode* Down;
	ListNode* Left;
	ListNode* Right;
	string roomEntrance; //Event when you enter a room for the first time
	string roomEvent; //Event UP
	string roomEvent2; //Event DOWN
	string roomEvent3; //Event LEFT
	string roomEvent4; //Event RIGHT
	string roomSubEvent; //SubEvent for displaying text after a condition was met
	string roomSubEvent2; //Second SubEvent for displaying text after a condition was met
	string roomSubEvent3; //Third SubEvent for displaying text after a condition was met
	string roomEnd; //Event when you exit the room after meeting conditions.

	ListNode()
	{
		Name = ' ';
		Up = NULL;
		Down = NULL;
		Left = NULL;
		Right = NULL;
		roomEntrance = "Null";
		roomEvent = "Null";
		roomEvent2 = "Null";
		roomEvent3 = "Null";
		roomEvent4 = "Null";
		roomSubEvent = "Null";
		roomSubEvent2 = "Null";
		roomSubEvent3 = "Null";
		roomEnd = "Null";
	}
};

class Items
{
private:
	string name, desc;
public:
	Items() { name = "NULL"; desc = "NULL"; }
	Items(string name, string desc)
	{
		this->name = name;
		this->desc = desc;
	}

	string getName() { return name; }
	void setName(string name) { this->name = name; }

	string getDesc() { return desc; }
	void setDesc(string desc) { this->desc = desc; }

	virtual void display()
	{
		cout << "Name: " << name << endl;
		cout << "Description: " << desc << endl;
	}
};

class Trinket : public Items //Trinket is a special item that can be used for in events
{
private:
	int quantity; //Quantity is the number of uses each special item (Trinket) has
public:
	Trinket() : Items() { quantity = 0; }
	Trinket(string name, string desc, int quantity) : Items(name, desc)
	{
		this->quantity = quantity;
	}
	int getQuantity() { return quantity; }
	void setQuantity(int quantity) { this->quantity = quantity; }
};


//Special variales for game conditions.
int Gem = 0; //Gem = 1 is when you get the gem, Gem = 2 is when you use it on the door.
int Banana = 0;//if = 0, it means no bamama, if = 1, You got the nana, if = 2, you gave some to the chip.
int Torch = 0;//If 1 = You got the torch, if = 2, you used it to burn the web.
int Lever = 0;//If 1 = You pulled it.
int Rock = 0;//If 1 = You have.


//Variables for conditions.
//These are room specific.
//Events 1 = room1Event1
//Events 2 = room1Event2
//Events 3 = roomAEvent1
//Events 4 = roomAEvent2
//Events 5 = roomBEvent1
//Events 6 = roomDEvent1
//Events 7 = roomDEvent2
//Events 8 = roomEEvent1
//Events 9 = roomQEvent1
int Events[10];
int inventoryGold;
char loadedRoomName;

int main()
{
	for (int x = 0; x < 24; x++)
	{
		system("cls");
		cout << "Checking for savefile." << endl;
		system("cls");
		cout << "Checking for savefile.." << endl;
		system("cls");
		cout << "Checking for savefile..." << endl;
	}

	//Checks to see if a savefile exsists
	//If not it will create one
	ifstream inFile;
	inFile.open("SaveFile.txt");

	if (inFile.is_open())
	{
		cout << "Save File found" << endl;
		system("PAUSE");
	}
	else
	{
		cout << "Unable to open file" << endl;
		cout << "Creating SaveFile..." << endl;
		ofstream outFile("SaveFile.txt");
		system("PAUSE");
	}

	/////////////////////////////////////////////////////
	//Room 1 only goes up to room A
	ListNode* room1 = new ListNode();
	room1->Name = '1';

	//I decided to put the texts near the actual node rooms
	//To see what room has what.
	room1->roomEntrance = "You awake in a dank, semi-dark room... \n\n"
		"You check yourself for supplies or something useful. \n"
		"You find a note reading...\n"
		"YOU HAVE BEEN EXILED. PERISH IN THIS DUNGEON IF YOU ARE GUILTY. \n"
		"With no memories to call yours, you stand up and get ready. \n\n"
		"UP: You see a cell door. \n"
		"DOWN: You see nothing behind you. \n"
		"LEFT: You see a key. \n"
		"RIGHT: You see a shield. \n\n"
		"What do you wish to do: ";

	room1->roomEvent = "You look UP and see a door in front of you. \n"
		"You need a key to open this door. \n";

	room1->roomEvent2 = "You go RIGHT and see a shield. \n"
		"The shield is made of a iron frame with a reinforced wooden core. \n"
		"You try to pick it up, but it crumbled into pieces. \n";

	room1->roomEvent3 = "You head LEFT and see a key. \n"
		"The key is a small normal looking key made from iron. \n"
		"** KEY ACQUIRED ** \n";

	room1->roomSubEvent = "You already picked up the key! \n";

	room1->roomSubEvent2 = "You already tried to pick up the shield! \n";

	room1->roomEvent4 = "You head DOWN and see a wall. \n"
		"What are you looking for? \n";

	room1->roomEnd = "You unlock the door with the key. \n";
	"You brace yourself as you head onward trough the door. \n"
		"You walk through a corridor until you find another room. \n"
		"You enter and the door locks behind you. \n";

	/////////////////////////////////////////////////////////
	//LEFT is NULL, UP is NULL, RIGHT is roomB, DOWN is NULL
	ListNode* roomA = new ListNode();
	roomA->Name = 'A';
	room1->Up = roomA;

	//roomA events
	roomA->roomEntrance = "As you enter the room, you see... \n\n"
		"UP: You glance and see a wall with a torch. \n"
		"DOWN: You check and see that the door is shut and can't be opened. \n"
		"LEFT: You turn see it's just a wall. \n"
		"RIGHT: You peek and see a door. \n\n"
		"What do you wish to do: ";;

	roomA->roomEvent = "You look UP and grab the torch in the wall, now you can see better. \n"
		"** TORCH ACQUIRED ** \n";

	roomA->roomSubEvent = "You already have the Torch! \n";

	roomA->roomEvent2 = "You see a door to your RIGHT. \n"
		"It is not locked. You can go through. \n"
		"Do you want to go through the door? \n"
		"W = YES, S = NO: ";

	roomA->roomEvent3 = "You walk to the LEFT. \n"
		"You see a wall and nothing more. \n"
		"You should move on, clock is ticking! \n";

	roomA->roomEvent4 = "You turn DOWN. \n"
		"The door is locked. You can't go back. \n";

	roomA->roomEnd = "You go through the door and move foward... \n";

	/////////////////////////////////////////////////////////////
	//LEFT is roomA, UP is roomG, need gem to advance, DOWN is NULL, RIGHT is roomC
	ListNode* roomB = new ListNode();
	roomB->Name = 'B';
	roomB->Left = roomA;
	roomA->Right = roomB;

	roomB->roomEntrance = "As soon as you enter the room, you see a mystical door... \n\n"
		"It's shine almost blinds you. \n"
		"UP: Ahead is the magical door. \n"
		"DOWN: You see several barrels of assoreted fruits. \n"
		"RIGHT: You find another door, this time a normal one. \n"
		"LEFT: You can go to the previous room. \n\n"
		"What do you wish to do: ";

	roomB->roomEvent = "You turn UP. \n"
		"You walk towards the magical door. \n"
		"It shimmers with a bright blueish, while color. \n"
		"You try to pry it open, but to no avail. \n"
		"You see a weird shaped hole in the middle of it. \n";

	roomB->roomSubEvent = "Would you like to use the gem on the door? \n"
		"W = YES, S = NO: ";

	roomB->roomEvent2 = "You rotate DOWN. \n"
		"You walk to several barrels, each full of different fruits. \n"
		"You see a open barrel of bananas. \n"
		"Would you like to grab a banana: \n"
		"W = YES, S = NO: ";

	roomB->roomSubEvent2 = "You pocketed one banana. \n"
		"Fine, take another one for the road. \n"
		"Oops, another just in case. \n"
		"Just take them all already. \n"
		"** ACQUIRED 4 BANANAS ** \n";

	roomB->roomEvent3 = "You sping LEFT. \n"
		"You see the door you came through. \n"
		"Wanna go back? \n"
		"W = YES, S = NO: ";

	roomB->roomEvent4 = "You go RIGHT. \n"
		"You see a regular door in front of you. \n"
		"It's unlocked. \n"
		"Want to go through? \n"
		"W = YES, S = NO: ";

	roomB->roomEnd = "As you insert the gem onto the door. \n"
		"The door cracks open slowly. \n"
		"The gem starts to dust away as the door slowly opens. \n"
		"It opens and you venture forth. \n";

	////////////////////////////////////////////////////////////
	ListNode* roomC = new ListNode();
	roomC->Name = 'C';
	roomB->Right = roomC;
	roomC->Left = roomB;

	roomC->roomEntrance = "You enter a corner hallway... \n\n"
		"UP: You see a hallway. \n"
		"LEFT: You see the door you came from. \n\n"
		"What do you wish to do: ";

	roomC->roomEvent = "You run UP. \n"
		"You can proceed to the next room."
		"Do you want to go foward? \n"
		"W = YES, S = NO: ";

	roomC->roomEvent2 = "You head LEFT. \n"
		"You can go back to the previous room. \n"
		"Do you want to go back? \n"
		"W = YES, S = NO: ";

	////////////////////////////////////////////////////////////
	ListNode* roomD = new ListNode();
	roomD->Name = 'D';
	roomD->Down = roomC;
	roomC->Up = roomD;

	roomD->roomEntrance = "You arrive at 3 hallway crossway... \n\n"
		"DOWN: You see the way you came from. \n"
		"LEFT: A study door lies to your left side. \n"
		"RIGHT: A grand looking door lies in that paty. \n\n"
		"What do you wish to do: ";

	roomD->roomEvent = "You head DOWN. \n"
		"You came from this hallway. \n"
		"You can go back to the previous room. \n"
		"Do you want to go back? \n"
		"W = YES, S = NO: ";

	roomD->roomEvent2 = "You sprint LEFT. \n"
		"A big sturdy door stands in your way. \n"
		"You try to pry it open. No can do. \n";

	roomD->roomSubEvent = "You already tried to open it. \n"
		"What makes you think you can open it now? \n";

	roomD->roomEvent3 = "You walk RIGHT. \n"
		"You walk towards a corridor. \n"
		"It heads to a straight corridor. \n"
		"You see a weird glimmer at the end of the hall. \n"
		"Do you wish to proceed? \n"
		"W = YES, S = NO: ";

	roomD->roomEnd = "You leave the weird 3 way hallways. \n"
		"You head to the straight hallway.\n";

	/////////////////////////////////////////////////////////////
	ListNode* roomE = new ListNode();
	roomE->Name = 'E';
	roomE->Left = roomD;
	roomD->Right = roomE;

	roomE->roomEntrance = "You stop halfway through the hallway... \n\n"
		"LEFT: The path you came from, the only other way to walk. \n"
		"RIGHT: You are near the end of the hallway.\n\n"
		"What do you wish to do: ";

	roomE->roomEvent = "You sprint LEFT \n"
		"This leads back to the previous hallway. \n"
		"Do you wish to proceed? \n"
		"W = YES, S = NO: ";

	roomE->roomEvent2 = "You go RIGHT \n"
		"You arrive at the end of the hallway. \n"
		"You see a gem in a hand pedestal. \n"
		"This was the thing glimmering at the end of the hallway. \n"
		"You decide to take it. \n\n"
		"** GEM ACQUIRED **\n";

	roomE->roomSubEvent = "You already have the gem!. \n"
		"You want more?! Don't be greedy... \n";

	roomE->roomEnd = "With gem in hand. \n"
		"You decide to continue your journey. \n";

	////////////////////////////////////////////////////////////
	ListNode* roomF = new ListNode();
	roomF->Name = 'F';
	roomB->Up = roomF;
	roomF->Down = roomB;

	roomF->roomEntrance = "You pass the gem-locked door... \n\n"
		"UP: You see another hallways. Too many of thoses huh? \n"
		"DOWN: Behind you is the gem-locked door. Now open. \n"
		"RIGHT: You see a heavy wooden door. You couldn't move it before. \n\n"
		"What do you wish to do: ";

	roomF->roomEvent = "You prance UP \n"
		"This leads to another one of those 3 way hallways. \n"
		"Do you wish to proceed? \n"
		"W = YES, S = NO: ";

	roomF->roomEvent2 = "You turn DOWN \n"
		"This leads back to the previous room. \n"
		"You will pass under the glorious gem-locked door. \n"
		"Do you wish to proceed? \n"
		"W = YES, S = NO: ";

	roomF->roomEvent3 = "You glide RIGHT \n"
		"You see the same door from the other room. \n"
		"Give it up, it won't open. \n";

	////////////////////////////////////////////////////////////
	ListNode* roomG = new ListNode();
	roomG->Name = 'G';
	roomF->Up = roomG;
	roomG->Down = roomF;

	roomG->roomEntrance = "You keep walking foward and stop... \n\n"
		"UP: You see a dead end? WHAT?! \n"
		"DOWN: YOU SHALL NOT PAS- I mean, that's where you came from. \n"
		"LEFT: You see a door, is it locked? \n\n"
		"What do you wish to do: ";

	roomG->roomEvent = "You hop foward, I mean UP. \n"
		"You reach a wall. \n"
		"You push it a bit and you press a button. \n"
		"It's a secret room?! \n"
		"Enter? \n"
		"W = YES, S = NO: ";

	roomG->roomEvent2 = "You turn DOWN. \n"
		"You came from this way. \n"
		"Want to go back? \n"
		"W = YES, S = NO: ";

	roomG->roomEvent3 = "You peek LEFT. \n"
		"You open the door. \n"
		"Hey look, a hallway! \n"
		"Want to move foward? \n"
		"W = YES, S = NO: ";

	////////////////////////////////////////////////////////////
	ListNode* roomH = new ListNode();
	roomH->Name = 'H';
	roomH->Down = roomG;
	roomG->Up = roomH;

	roomH->roomEntrance = "You reach the next room... \n\n"
		"UP: You see a dead end with something on the wall. \n"
		"DOWN: You back to the 3 way hallway. \n\n"
		"What do you wish to do: ";

	roomH->roomEvent = "You reach what seems like a dead end! \n"
		"But you see a lever. Do you want to pull it down? \n"
		"W = YES, S = NO: ";

	roomH->roomSubEvent = "You grabbed hard and pulled down. \n"
		"Now it's stuck in that position. \n"
		"I wonder what it does?. \n";

	roomH->roomEvent2 = "You went DOWN, through the secret opening. \n"
		"You went back to the previous room. \n";

	////////////////////////////////////////////////////////////
	ListNode* roomI = new ListNode();
	roomI->Name = 'I';
	roomG->Left = roomI;
	roomI->Right = roomG;

	roomI->roomEntrance = "You stop midway through the hallway... \n\n"
		"LEFT: You see the end of the hallway. \n"
		"RIGHT: You see the door you came through from. \n\n"
		"What do you wish to do: ";

	roomI->roomEvent = "You go LEFT. \n"
		"You can see the end of the hallway if you keep going foward. \n"
		"Continue foward? \n"
		"W = YES, S = NO: ";

	roomI->roomEvent2 = "You moonwalk RIGHT. \n"
		"You cam form this 3 way hallway. \n"
		"Go back? Awoo, Excusme. \n"
		"W = YES, S = NO: ";

	////////////////////////////////////////////////////////////
	ListNode* roomJ = new ListNode();
	roomJ->Name = 'J';
	roomJ->Right = roomI;
	roomI->Left = roomJ;

	roomJ->roomEntrance = "You arrive at a corner hallway. \n\n"
		"UP: You see a cell door. It's halway open. \n"
		"LEFT: Is that? It's can't be. \n"
		"RIGHT: You came from that hallway. \n\n"
		"What do you wish to do: ";

	roomJ->roomEvent = "You go UP. Hmm you can hear something. \n"
		"Want to go see what is it? \n"
		"W = YES, S = NO: ";

	roomJ->roomEvent2 = "You slide to the LEFT. \n"
		"You see faded drawings or markings of some animal. \n"
		"What could these mean? \n";

	roomJ->roomEvent3 = "You moved to the RIGHT. \n"
		"This is the way back hoooommmeee. \n"
		"Want to go back to the previous room? \n"
		"W = YES, S = NO: ";

	////////////////////////////////////////////////////////////
	ListNode* roomK = new ListNode();
	roomK->Name = 'K';
	roomK->Down = roomJ;
	roomJ->Up = roomK;

	roomK->roomEntrance = "You walk towards ANOTHER... 3 way hallway. \n\n"
		"As you stop halfwa- \n\n"
		"UP: You know, go forward? \n"
		"DOWN: Back down and go back? \n"
		"LEFT: Check out that place? \n\n"
		"What do you wish to do: ";

	roomK->roomEvent = "You go UP. \n"
		"You skip happily to the next room. \n";

	roomK->roomSubEvent = "You go UP.\n"
		"** SWOOOooooooShhhhHHH ** \n\n"
		"It's a RANDOM CHIMP EVENT \n"
		"A chimp swings from the left side of the hallway. \n"
		"He blocks your path foward \n"
		"He seems to watch you and look around. \n";

	roomK->roomSubEvent2 = "You shared your bananas with the chimp. \n"
		"He was pretty chill, after he finishes his last one. \n"
		"He swooshes back to the left side of the hallways. \n"
		"With a full belly. \n"
		"He leaves behind a bag of gold! \n"
		"You gladly take it. \n"
		"** 35 GOLD GOT ** \n";

	roomK->roomSubEvent3 = "Maybe he is hungry. \n"
		"Is there any food here? \n";

	roomK->roomEvent2 = "You turn around and DOWN. \n"
		"Will you go back from that corner that you came from? \n"
		"W = YES, S = NO: ";

	roomK->roomEvent3 = "You peak around LEFT. \n"
		"You see a medium sized hole in the wall. \n"
		"You hear chimp noises from it. \n"
		"Are they having fun there? \n"
		"It's too dangerous to go alone. \n";

	////////////////////////////////////////////////////////////
	ListNode* roomL = new ListNode();
	roomL->Name = 'L';
	roomK->Up = roomL;
	roomL->Down = roomK;

	roomL->roomEntrance = "As you leave the chimp infested halls... \n\n"
		"You arrive at a normal hallway, again. \n\n"
		"UP: You see more light finally coming into this maze. \n"
		"DOWN: The chimp halls from which you came. \n"
		"LEFT: A weird room? Smells earthy. \n"
		"What do you wish to do: ";

	roomL->roomEvent = "You move UP. \n"
		"Head to the next room? \n"
		"W = YES, S = NO: ";

	roomL->roomEvent2 = "You swing DOWN. \n"
		"Go back to where you met your chimp friend? \n"
		"W = YES, S = NO: ";

	roomL->roomEvent3 = "You peel to the LEFT. \n"
		"You smell a rainy dirt combination of smells to this room. \n"
		"Head in? \n"
		"W = YES, S = NO: ";

	////////////////////////////////////////////////////////////
	ListNode* roomM = new ListNode();
	roomM->Name = 'M';
	roomM->Right = roomL;
	roomL->Left = roomM;

	roomM->roomEntrance = "You arrive at this soily looking room. \n\n"
		"DOWN: You see something like pile. \n"
		"LEFT: You see more piles. \n"
		"RIGHT: You see the way you came from. \n\n"
		"What do you wish to do: ";

	roomM->roomEvent = "You move DOWN. \n"
		"It's a pile of gravel. \n"
		"You stick your hand in it and find...\n"
		"Nothing. \n";

	roomM->roomEvent2 = "You scatter yourself to the LEFT. \n"
		"You find a pile of rocks. \n"
		"Dig through them? \n"
		"W = YES, S = NO: ";

	roomM->roomEvent3 = "You head back to the RIGHT. \n"
		"Head back now? \n"
		"W = YES, S = NO: ";

	////////////////////////////////////////////////////////////
	ListNode* roomN = new ListNode();
	roomN->Name = 'N';
	roomN->Down = roomL;
	roomL->Up = roomN;

	roomN->roomEntrance = "You arrive! \n\n"
		"UP: Is that a chest? \n"
		"DOWN: A way to go back. \n"
		"RIGHT: A new path is found! \n\n"
		"What do you wish to do: ";

	roomN->roomEvent = "You find a chest! I found it on UP too! \n\n"
		"Sadly. It is locked and you have no key. \n";

	roomN->roomEvent2 = "This is the way back. Which is DOWN. \n"
		"Head back now? To the room that you came from? \n"
		"W = YES, S = NO: ";

	roomN->roomEvent3 = "Let's go RIGHT. \n"
		"You see another hallway, it could be the exit? \n"
		"Move ahead? \n"
		"W = YES, S = NO: ";

	////////////////////////////////////////////////////////////
	ListNode* roomO = new ListNode();
	roomO->Name = 'O';
	roomN->Right = roomO;
	roomO->Left = roomN;

	roomO->roomEntrance = "You arrive... \n\n"
		"Another corner hallway! How splendid! \n"
		"You start smelling less damp air too. \n\n"

		"UP: Another corner perhaps? \n"
		"LEFT: More places from which you came from. \n"
		"What do you wish to do: ";

	roomO->roomEvent = "You go UP, up and away!. \n"
		"You can see another corner but it's lit up more than the ones before. \n"
		"Head foward? \n"
		"W = YES, S = NO: ";

	roomO->roomEvent2 = "Let's slide to the uh, LEFT. \n"
		"Wanna go more places that you already went too? \n"
		"W = YES, S = NO: ";

	////////////////////////////////////////////////////////////
	ListNode* roomP = new ListNode();
	roomP->Name = 'P';
	roomO->Up = roomP;
	roomP->Down = roomO;

	roomP->roomEntrance = "You turn another corner hallway. \n\n"
		"RIGHT: You see a right spiderweb exntending from the roof to the floor. \n"
		"DOWN: I would go back too. \n\n"
		"What do you wish to do: ";

	roomP->roomEvent = "Back DOWN we go. \n"
		"Wanna go back? \n"
		"W = YES, S = NO: ";

	roomP->roomEvent2 = "As you approach the spider web. \n"
		"I semi-big, or should I say maybe dog sized spider. \n"
		"Comes down and rests in from of the spiderweb. \n"
		"Well what can we do now? \n";

	roomP->roomSubEvent = "You used your torch to light the web.\n "
		"The spider hurries back to the hole in the ceiling. \n"
		"You can now move foward. \n";

	////////////////////////////////////////////////////////////
	ListNode* roomQ = new ListNode();
	roomQ->Name = 'Q';
	roomP->Right = roomQ;
	roomQ->Left = roomP;

	roomQ->roomEntrance = "You arrive at ANOTHER 3 way hallway. \n\n"
		"UP: You see a gap. \n"
		"LEFT: You see the path of burnt webs. \n"
		"RIGHT: A cell door is visible, are those stairs? \n"
		"What do you wish to do: ";

	roomQ->roomEvent = "You head UP. \n"
		"A gap is in bewtween you and the next hallway. \n"
		"There is a drawbridge on the other side. \n"
		"Is there a way to make it come down? \n";

	roomQ->roomSubEvent = "Huh, there's a bridge here. \n"
		"This will let me through. \n";

	roomQ->roomSubEvent2 = "This bridge is now lowered. \n"
		"That lever must have done it. \n"
		"You head foward. \n";

	roomQ->roomEvent2 = "You check out LEFT. \n"
		"This is where you came from. \n"
		"Want to smell more webs? \n"
		"W = YES, S = NO: ";

	roomQ->roomEvent3 = "You head RIGHT. \n"
		"You peer out the cell door. \n"
		"It is locked, my luck. \n"
		"You see some stairs and hear noises.\n";

	////////////////////////////////////////////////////////////
	ListNode* roomR = new ListNode();
	roomR->Name = 'R';
	roomR->Down = roomQ;
	roomQ->Up = roomR;

	roomR->roomEntrance = "You cross the bridge. \n\n"
		"You arrive at a nice corner hallway. \n\n"
		"DOWN: That is where the bridge is. \n"
		"RIGHT: A shrine? \n\n"
		"What do you wish to do: ";

	roomR->roomEvent = "You cross DOWN.\n"
		"Want to cross the bridge back? \n"
		"W = YES, S = NO: ";

	roomR->roomEvent2 = "You go RIGHT.\n"
		"You find a shrine, with a indenture in the middle. \n"
		"What can this mean? \n";

	roomR->roomSubEvent = "You inserted the spehrical rock.\n"
		"The shrine accepts it. \n"
		"It lowers the wall behind it.\n"
		"You go foward.\n";

	////////////////////////////////////////////////////////////
	ListNode* room2 = new ListNode();
	room2->Name = '2';
	roomR->Right = room2;

	room2->roomEntrance = "You enter the room... \n\n"
		"You find a ladder in the middle of the room. \n"
		"You climb them. \n"
		"Oh no. This can't be it. \n\n"
		"** THE END ** \n"
		"Thank you for playing! \n";

	////////////////////////////////////////////////////////////
	//Starts the game at room #1
	ListNode* ptr = room1;

	//Shows the main menu
	MainMenu();

	if (loadedRoomName == '1')
	{
		ptr = room1;
	}
	if (loadedRoomName == 'A')
	{
		ptr = roomA;
	}
	if (loadedRoomName == 'B')
	{
		ptr = roomB;
	}
	if (loadedRoomName == 'C')
	{
		ptr = roomC;
	}
	if (loadedRoomName == 'D')
	{
		ptr = roomD;
	}
	if (loadedRoomName == 'E')
	{
		ptr = roomE;
	}
	if (loadedRoomName == 'F')
	{
		ptr = roomF;
	}
	if (loadedRoomName == 'G')
	{
		ptr = roomG;
	}
	if (loadedRoomName == 'H')
	{
		ptr = roomH;
	}
	if (loadedRoomName == 'I')
	{
		ptr = roomI;
	}
	if (loadedRoomName == 'J')
	{
		ptr = roomJ;
	}
	if (loadedRoomName == 'K')
	{
		ptr = roomK;
	}
	if (loadedRoomName == 'L')
	{
		ptr = roomL;
	}
	if (loadedRoomName == 'M')
	{
		ptr = roomM;
	}
	if (loadedRoomName == 'N')
	{
		ptr = roomN;
	}
	if (loadedRoomName == 'O')
	{
		ptr = roomO;
	}
	if (loadedRoomName == 'P')
	{
		ptr = roomP;
	}
	if (loadedRoomName == 'Q')
	{
		ptr = roomQ;
	}
	if (loadedRoomName == 'R')
	{
		ptr = roomR;
	}

	//While the bool variable game is true, the game will run.
	bool game = true;

	while (game != false)
	{
		while (ptr == room1) //Starting room
		{
			//Function to send current room name to map
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'W')
			{
				topScrn(roomName);

				if (Events[1] == 1)
				{
					cout << ptr->roomEnd << endl;
					system("Pause");
					ptr = ptr->Up;
					break;
				}

				cout << ptr->roomEvent << endl;
				system("Pause");
			}
			else if (choice == 'D')
			{
				topScrn(roomName);
				for (int x = 0; x < 1; x++)
				{
					if (Events[2] == 1)
					{
						cout << ptr->roomSubEvent2 << endl;
						system("Pause");
					}
					if (Events[2] == 0)
					{
						cout << ptr->roomEvent2 << endl;
						Events[2] = 1;
						system("Pause");
					}
				}
			}
			else if (choice == 'A')
			{
				topScrn(roomName);
				for (int x = 0; x < 1; x++)
				{
					if (Events[1] == 1)
					{
						cout << ptr->roomSubEvent << endl;
						system("Pause");
					}
					if (Events[1] == 0)
					{
						cout << ptr->roomEvent3 << endl;
						Events[1] = 1;
						system("Pause");
					}
				}

			}
			else if (choice == 'S')
			{
				topScrn(roomName);
				cout << ptr->roomEvent4 << endl;
				system("Pause");
			}

		}

		while (ptr == roomA)
		{
			//Function to send current room name to map
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'W')
			{
				topScrn(roomName);

				if (Events[3] == 1)
				{
					cout << ptr->roomSubEvent << endl;
					system("Pause");
				}
				else if (Events[3] == 0)
				{
					cout << ptr->roomEvent << endl;
					Events[3] = 1;
					Torch = 1;
					system("Pause");
				}

			}

			if (choice == 'D')
			{
				char roomEventChoice;
				topScrn(roomName);
				cout << ptr->roomEvent2 << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "You choose to go through the door. You head to the next room. " << endl;
					system("Pause");
					ptr = ptr->Right;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "You choose not to go through the door. \n";
					system("Pause");
				}
			}

			if (choice == 'A')
			{
				topScrn(roomName);
				cout << ptr->roomEvent3 << endl;
				system("Pause");

			}

			if (choice == 'S')
			{
				topScrn(roomName);
				cout << ptr->roomEvent4 << endl;
				system("Pause");
			}
		}

		while (ptr == roomB)
		{
			//Function to send current room name to map
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'D')
			{
				char roomEventChoice;
				topScrn(roomName);
				cout << ptr->roomEvent4 << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "You choose to go through the door. You head to the next room. " << endl;
					system("Pause");
					ptr = ptr->Right;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "You choose not to go through the door. \n";
					system("Pause");
				}
			}

			if (choice == 'S')
			{
				topScrn(roomName);

				if (Events[5] == 1)
				{
					cout << "You already took some bananas. " << endl;
					system("Pause");
				}
				else if (Events[5] == 0)
				{
					char roomEventChoice;
					cout << ptr->roomEvent2 << endl;
					cin >> roomEventChoice;

					if (roomEventChoice == 'W' && roomEventChoice != 'S')
					{
						cout << ptr->roomSubEvent2 << endl;
						Banana = 1;
						Events[5] = 1;
						system("Pause");
					}
					else if (roomEventChoice == 'S' && roomEventChoice != 'W')
					{
						cout << "You choose not to take some bananas. \n";
						system("Pause");
					}
				}
			}

			if (choice == 'W')
			{
				if (Gem == 1)
				{
					char roomEventChoice;
					cout << ptr->roomSubEvent << endl;
					cin >> roomEventChoice;

					if (roomEventChoice == 'W' && roomEventChoice != 'S')
					{
						cout << ptr->roomEnd << endl;
						system("Pause");
						ptr = ptr->Up;
						Gem = 2;
						break;
					}
					if (roomEventChoice == 'S' && roomEventChoice != 'W')
					{
						cout << "You choose not to go through the door. \n";
						system("Pause");
					}
				}

				if (Gem == 2)
				{
					cout << "THe door has been open and the gem is gone. \n";
					cout << "You can go through without having to use another one. \n";
					cout << "Why are you waiting here? \n";
					cout << "You move foward. \n";
					system("Pause");

					ptr = ptr->Up;
					break;
				}

				topScrn(roomName);
				cout << ptr->roomEvent << endl;
				system("Pause");
			}

			if (choice == 'A')
			{
				char roomEvent3Choice;
				topScrn(roomName);
				cout << ptr->roomEvent3 << endl;
				cin >> roomEvent3Choice;

				if (roomEvent3Choice == 'W' && roomEvent3Choice != 'S')
				{
					cout << "You choose to go through the door. You head to the next room. " << endl;
					system("Pause");
					ptr = roomA;
					break;
				}
				if (roomEvent3Choice == 'S' && roomEvent3Choice != 'W')
				{
					cout << "You choose not to go through the door. \n";
					system("Pause");
				}
			}
		}

		while (ptr == roomC)
		{
			//Function to send current room name to map
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'W')
			{
				char roomEventChoice;
				cout << ptr->roomEvent << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "You choose to go through the door. You head to the next room. " << endl;
					system("Pause");
					ptr = ptr->Up;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "You choose not to go back. \n";
					system("Pause");
				}
			}

			if (choice == 'A')
			{
				char roomEventChoice;
				cout << ptr->roomEvent2 << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "You choose to go to the next room. " << endl;
					system("Pause");
					ptr = ptr->Left;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "You choose not to go foward. \n";
					system("Pause");
				}
			}
		}

		while (ptr == roomD)
		{
			//Function to send current room name to map
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'S')
			{
				char roomEventChoice;
				cout << ptr->roomEvent << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "You choose to go to the previous room. " << endl;
					system("Pause");
					ptr = ptr->Down;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "You choose not to go back. \n";
					system("Pause");
				}
			};

			if (choice == 'A')
			{
				topScrn(roomName);

				if (Events[6] == 1)
				{
					cout << ptr->roomSubEvent << endl;
					system("Pause");
				}
				else if (Events[6] == 0)
				{
					cout << ptr->roomEvent2 << endl;
					Events[6] = 1;
					system("Pause");
				}
			}

			if (choice == 'D')
			{
				topScrn(roomName);

				if (Events[7] == 1)
				{
					cout << "You already took some bananas. " << endl;
					system("Pause");
				}
				else if (Events[7] == 0)
				{
					char roomEventChoice;
					cout << ptr->roomEvent3 << endl;
					cin >> roomEventChoice;

					if (roomEventChoice == 'W' && roomEventChoice != 'S')
					{
						cout << ptr->roomEnd << endl;
						system("Pause");
						ptr = ptr->Right;
						break;
					}
					else if (roomEventChoice == 'S' && roomEventChoice != 'W')
					{
						cout << "You decided to not go to the hallway. \n";
						system("Pause");
					}
				}
			}

		}

		while (ptr == roomE)
		{
			//Function to send current room name to map
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'A')
			{
				topScrn(roomName);

				char roomEventChoice;
				cout << ptr->roomEvent << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "You choose to go to the previous room. " << endl;
					system("Pause");
					ptr = ptr->Left;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "You choose not to go back. \n";
					system("Pause");
				}

				else if (Events[8] == 1)
				{
					cout << ptr->roomEnd << endl;
					system("Pause");
					ptr = ptr->Left;
					break;
				}
			}

			if (choice == 'D')
			{
				topScrn(roomName);

				if (Events[8] == 1)
				{
					cout << ptr->roomSubEvent << endl;
					system("Pause");
				}
				else if (Events[8] == 0)
				{
					cout << ptr->roomEvent2 << endl;
					Events[8] = 1;
					Gem = 1;
					system("Pause");
				}
			}
		}

		while (ptr == roomF)
		{
			//Function to send current room name to map
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'W')
			{
				char roomEventChoice;
				cout << ptr->roomEvent << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "You choose to keep on swiming. I mean walking. You head to the next room. " << endl;
					system("Pause");
					ptr = ptr->Up;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "You choose not to go foward. \n";
					system("Pause");
				}
			}
			if (choice == 'D')
			{
				cout << ptr->roomEvent3 << endl;
				system("Pause");
			}
			if (choice == 'S')
			{
				char roomEventChoice;
				cout << ptr->roomEvent2 << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "You like going through that magic door huh?. You move on foward. " << endl;
					system("Pause");
					ptr = ptr->Down;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "You choose not to go foward. \n";
					system("Pause");
				}
			}
		}

		while (ptr == roomG)
		{
			//Function to send current room name to map
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'W')
			{
				char roomEventChoice;
				cout << ptr->roomEvent << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "Aren't you tired? Sure? Ok, move foward. " << endl;
					system("Pause");
					ptr = ptr->Up;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "You choose not to go foward. \n";
					system("Pause");
				}
			}

			if (choice == 'S')
			{
				char roomEventChoice;
				cout << ptr->roomEvent2 << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "Aren't you tired? Sure? Ok, move foward. " << endl;
					system("Pause");
					ptr = ptr->Down;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "You choose not to go foward. \n";
					system("Pause");
				}
			}

			if (choice == 'A')
			{
				char roomEventChoice;
				cout << ptr->roomEvent3 << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "NOW GO!? LET THE LEGEND COME BACK TO LIFE. " << endl;
					cout << "I'm kidding. Move foward. \n";
					system("Pause");
					ptr = ptr->Left;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "You choose not to go foward. \n";
					system("Pause");
				}
			}
		}

		while (ptr == roomH)
		{
			//Function to send current room name to map
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'W')
			{
				if (Lever == 0)
				{
					char roomEventChoice;
					cout << ptr->roomEvent << endl;
					cin >> roomEventChoice;

					if (roomEventChoice == 'W' && roomEventChoice != 'S')
					{
						cout << ptr->roomSubEvent << endl;
						Lever = 1;
						system("Pause");

					}
					else if (roomEventChoice == 'S' && roomEventChoice != 'W')
					{
						cout << "You choose not to pull the lever. \n";
						system("Pause");
					}
				}
				else if (Lever == 1)
				{
					cout << "You already pulled it. Why come back? \n";
					system("Pause");
				}
			}

			if (choice == 'S')
			{
				cout << ptr->roomEvent2 << endl;
				system("Pause");
				ptr = ptr->Down;
				break;
			}
		}

		while (ptr == roomI)
		{
			//Function to send current room name to map
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'A')
			{
				char roomEventChoice;
				cout << ptr->roomEvent << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "You went foward.";
					system("Pause");
					ptr = ptr->Left;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "You choose not to continue moonwalking foward. \n";
					system("Pause");
				}
			}

			if (choice == 'D')
			{
				char roomEventChoice;
				cout << ptr->roomEvent2 << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "You went back to that hallway. " << endl;
					system("Pause");
					ptr = ptr->Right;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "You choose not to go back to THAT hallway. \n";
					system("Pause");
				}
			}
		}

		while (ptr == roomJ)
		{
			//Function to send current room name to map
			//And validate inputs
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'W')
			{
				char roomEventChoice;
				cout << ptr->roomEvent << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "You went to investigate. \n";
					system("Pause");
					ptr = ptr->Up;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "You choose not to investigate. \n";
					system("Pause");
				}
			}
			if (choice == 'A')
			{
				cout << ptr->roomEvent2 << endl;
				system("Pause");
			}
			if (choice == 'D')
			{
				char roomEventChoice;
				cout << ptr->roomEvent3 << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "Let's go back home." << endl;
					system("Pause");
					ptr = ptr->Right;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "Guess you stay here. " << endl;
					system("Pause");
				}
			}
		}

		while (ptr == roomK)
		{
			//Function to send current room name to map
			//And validate inputs
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'W')
			{
				if (Banana == 0)
				{
					cout << ptr->roomSubEvent << endl;
					cout << ptr->roomSubEvent3 << endl;
					system("Pause");
				}
				if (Banana == 1)
				{
					cout << ptr->roomSubEvent << endl;

					char roomEventChoice;
					cout << "The chimp points to your infinte video game pockets." << endl;
					cout << "He must've smelled those bananas you have on you." << endl;
					cout << "Will you share with him?" << endl;
					cout << "W = YES, S = NO: ";
					cin >> roomEventChoice;

					if (roomEventChoice == 'W' && roomEventChoice != 'S')
					{
						cout << ptr->roomSubEvent2 << endl;
						Banana = 2;
						inventoryGold = 35;
						cout << ptr->roomEvent << endl;
						system("Pause");
						ptr = ptr->Up;
						break;
					}
					if (roomEventChoice == 'S' && roomEventChoice != 'W')
					{
						cout << "You choose not to share the bananas. \n";
						cout << "Don't be mean! \n";
						system("Pause");
					}
				}
				if (Banana == 2)
				{
					cout << ptr->roomEvent << endl;
					system("Pause");
					ptr = ptr->Up;
					break;
				}
			}

			if (choice == 'S')
			{
				char roomEventChoice;
				cout << ptr->roomEvent2 << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "Let's go to the corner." << endl;
					system("Pause");
					ptr = ptr->Down;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "Well, it was worth a shot asking." << endl;
					system("Pause");
				}
			}

			if (choice == 'A')
			{
				cout << ptr->roomEvent3 << endl;
				system("Pause");
			}
		}

		while (ptr == roomL)
		{
			//Function to send current room name to map
			//And validate inputs
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'W')
			{
				char roomEventChoice;
				cout << ptr->roomEvent << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "It's nighttime somewhere you know. \n";
					cout << "You move foward. \n";
					system("Pause");
					ptr = ptr->Up;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "You choose not to move foward. \n";
					system("Pause");
				}
			}

			if (choice == 'S')
			{
				char roomEventChoice;
				cout << ptr->roomEvent2 << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "You go back to try to find your pal chimp. \n";
					system("Pause");
					ptr = ptr->Down;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "You choose not to go find him \n";
					system("Pause");
				}
			}

			if (choice == 'A')
			{
				char roomEventChoice;
				cout << ptr->roomEvent3 << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "You went to dig in what's in the room to the LEFT. \n";
					system("Pause");
					ptr = ptr->Left;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "Well now we will never know. \n";
					system("Pause");
				}
			}

		}

		while (ptr == roomM)
		{
			//Function to send current room name to map
			//And validate inputs
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'S')
			{
				cout << ptr->roomEvent << endl;
				system("Pause");
			}

			if (choice == 'A')
			{
				if (Rock == 0)
				{
					char roomEventChoice;
					cout << ptr->roomEvent2 << endl;
					cin >> roomEventChoice;

					if (roomEventChoice == 'W' && roomEventChoice != 'S')
					{
						cout << "You found a weirdly spherical stone. Cool! \n";
						system("Pause");
						Rock = 1;
					}
					else if (roomEventChoice == 'S' && roomEventChoice != 'W')
					{
						cout << "You choose not to go find him \n";
						system("Pause");
					}
				}
				else if (Rock == 1)
				{
					cout << "There's nothing to look for here anymore. \n";
					system("Pause");
				}
			}

			if (choice == 'D')
			{
				char roomEventChoice;
				cout << ptr->roomEvent3 << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "Let's go!. \n";
					system("Pause");
					ptr = ptr->Right;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "Come on I want to leave! \n";
					system("Pause");
				}
			}
		}

		while (ptr == roomN)
		{
			//Function to send current room name to map
			//And validate inputs
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'W')
			{
				cout << ptr->roomEvent << endl;
				system("Pause");
			}

			if (choice == 'S')
			{
				char roomEventChoice;
				cout << ptr->roomEvent2 << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "Ok, let's head back. \n";
					system("Pause");
					ptr = ptr->Down;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "Come on! I want to get out of here too. \n";
					system("Pause");
				}
			}

			if (choice == 'D')
			{
				char roomEventChoice;
				cout << ptr->roomEvent3 << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "Let's try to get out of here. \n";
					system("Pause");
					ptr = ptr->Right;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "Well then perish if you want, I want out of here. \n";
					system("Pause");
				}
			}
		}

		while (ptr == roomO)
		{
			//Function to send current room name to map
			//And validate inputs
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'W')
			{
				char roomEventChoice;
				cout << ptr->roomEvent << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "UP you go then. \n";
					system("Pause");
					ptr = ptr->Up;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "Well, we won't get anywhere like this. \n";
					system("Pause");
				}
			}

			if (choice == 'A')
			{
				char roomEventChoice;
				cout << ptr->roomEvent2 << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "We are almost done, let's keep going. \n";
					system("Pause");
					ptr = ptr->Left;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "We will never finish like this. \n";
					system("Pause");
				}
			}

		}

		while (ptr == roomP)
		{
			//Function to send current room name to map
			//And validate inputs
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'S')
			{
				char roomEventChoice;
				cout << ptr->roomEvent << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "I agree, let's go back. \n";
					system("Pause");
					ptr = ptr->Down;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "It's kinda spooky here. Let's move. \n";
					system("Pause");
				}
			}

			if (choice == 'D')
			{
				if (Torch == 0)
				{
					cout << ptr->roomEvent2 << endl;
					system("Pause");
				}
				if (Torch == 1)
				{
					cout << "You have a torch remember? " << endl;
					cout << "Use to burn the web? " << endl;
					cout << "W = YES, S = NO: " << endl;

					char roomEventChoice;
					cin >> roomEventChoice;

					if (roomEventChoice == 'W' && roomEventChoice != 'S')
					{
						cout << ptr->roomSubEvent << endl;
						Torch = 2;
					}
					else if (roomEventChoice == 'S' && roomEventChoice != 'W')
					{
						cout << "Well, we are stuck here if you don't. \n";
						system("Pause");
					}
				}
				if (Torch == 2)
				{
					cout << "The path has been cleared." << endl;
					cout << "One more step towards freedom." << endl;
					system("Pause");
					ptr = ptr->Right;
					break;
				}
			}
		}

		while (ptr == roomQ)
		{
			//Function to send current room name to map
			//And validate inputs
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'W')
			{
				if (Lever == 1)
				{
					if (Events[1] == 1)
					{
						cout << ptr->roomSubEvent2 << endl;
						system("Pause");
						ptr = ptr->Up;
						break;
					}
					else if (Events[9] == 0)
					{
						cout << ptr->roomSubEvent << endl;
						system("Pause");
						ptr = ptr->Up;
						break;
					}
				}
				else if (Lever == 0)
				{
					if (Events[9] == 0)
					{
						cout << ptr->roomEvent << endl;
						system("Pause");
						Events[9] = 1;
					}
				}
			}

			if (choice == 'A')
			{
				char roomEventChoice;
				cout << ptr->roomEvent2 << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "Let's go smell some. \n";
					system("Pause");
					ptr = ptr->Left;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "I think I perfer staying here. \n";
					system("Pause");
				}
			}

			if (choice == 'D')
			{
				cout << ptr->roomEvent3 << endl;
				system("Pause");
			}
		}

		while (ptr == roomR)
		{
			//Function to send current room name to map
			//And validate inputs
			char roomName = ptr->Name;
			topScrn(roomName);

			char choice;
			cout << ptr->roomEntrance << endl;
			cin >> choice;

			if (choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D')
			{
				if (choice == 'H')
				{
					Help();
					topScrn(roomName);
				}
				else if (choice == 'M')
				{
					PauseMenu(roomName);
					topScrn(roomName);
				}
				else if (choice == 'I')
				{
					Inventory();
					topScrn(roomName);
				}
				else
				{
					topScrn(roomName);
					cout << "Please enter a valid command." << endl;
					system("Pause");
				}
			}

			if (choice == 'S')
			{
				char roomEventChoice;
				cout << ptr->roomEvent << endl;
				cin >> roomEventChoice;

				if (roomEventChoice == 'W' && roomEventChoice != 'S')
				{
					cout << "You choose to go back and cross the bridge back." << endl;
					system("Pause");
					ptr = ptr->Down;
					break;
				}
				else if (roomEventChoice == 'S' && roomEventChoice != 'W')
				{
					cout << "Well it is cozy here. \n";
					system("Pause");
				}
			}

			if (choice == 'D')
			{
				if (Rock == 1)
				{
					cout << "You remember the spherical rock you picked up. " << endl;
					cout << "Do you want to insert it?" << endl;
					cout << "W = YES, S = NO: ";

					char roomEventChoice;
					cin >> roomEventChoice;

					if (roomEventChoice == 'W' && roomEventChoice != 'S')
					{
						cout << ptr->roomSubEvent << endl;
						system("Pause");
						ptr = ptr->Right;
						break;
					}
					else if (roomEventChoice == 'S' && roomEventChoice != 'W')
					{
						cout << "Then why bring it? \n";
						system("Pause");
					}
				}
				else if (Rock == 0)
				{
					cout << "There must something we can put there? " << endl;
					system("Pause");
				}
			}
		}

		while (ptr == room2)
		{
			//Function to send current room name to map
			//And validate inputs
			char roomName = ptr->Name;
			topScrn(roomName);

			cout << ptr->roomEntrance << endl;
			system("PAUSE");
			game = false;
			break;
		}
	}

	return 0;
}

void topScrn(char Name) //This functions displays the map and information
{
	system("CLS");
	cout << "------------------------------" << endl;
	cout << "|           Dazef            |" << endl;
	cout << "|      A electronic RPG      |" << endl;
	cout << "|----------------------------|" << endl;
	cout << "|   Type H for instructions  |" << endl;
	cout << "|----------------------------|" << endl;
	cout << "|      Type M for menu       |" << endl;
	cout << "|----------------------------|" << endl;
	cout << "|     Type I for Inventory   |" << endl;
	cout << "|----------------------------|" << endl;
	cout << "|      CURRENT LOCATION      |" << endl;
	cout << "|----------------------------|" << endl;
	cout << "|       Current Room: " << Name << "      |" << endl;
	cout << "------------------------------" << endl;
}

void Help() //Shows the instructions for the game.
{
	system("CLS");
	cout << "Typing M will open the menu." << endl;
	cout << "Typing I will open your inventory." << endl;
	cout << "This game has four directions." << endl;
	cout << "UP, DOWN, LEFT, RIGHT." << endl;
	cout << "UP = W, DOWN is S, LEFT is S, RIGHT is D." << endl;
	cout << "You will always spawn in the center of a room." << endl;
	cout << "And you will go back to the center after going a direction." << endl;
	cout << "UP being in front of you." << endl;
	cout << "DOWN being behind you. " << endl;
	cout << "LEFT being your left and RIGHT being your right." << endl;

	system("Pause");

	return;
}

void PauseMenu(char Name) //Main/Pause Menu
{
	system("CLS");
	cout << "-----------------------------=" << endl;
	cout << "|           Dazef            |" << endl;
	cout << "|      A electronic RPG      |" << endl;
	cout << "|----------------------------|" << endl;
	cout << "|        1. New Game         |" << endl;
	cout << "|----------------------------|" << endl;
	cout << "|        2. Save Game        |" << endl;
	cout << "|----------------------------|" << endl;
	cout << "|        3. Load Game        |" << endl;
	cout << "|----------------------------|" << endl;
	cout << "|        4. Exit             |" << endl;
	cout << "|----------------------------|" << endl;
	cout << "|        5. Back to game     |" << endl;
	cout << "------------------------------" << endl;

	int menuChoice;
	cout << "What would you like to do?: ";
	cin >> menuChoice;

	switch (menuChoice)
	{
	case 1:
		cout << "Are you sure you want to start a new game?" << endl;
		cout << "All your progress will be lost!" << endl;
		cout << "1 = YES, 2 = NO" << endl;
		int newGameChoice;

		cin >> newGameChoice;

		if (newGameChoice == 1)
		{
			cout << "Have fun!" << endl;
			Clearer();
			main();
			break;
		}
		else if (newGameChoice == 2)
		{
			cout << "Alright, sending you back to the menu..." << endl;
			system("Pause");
			PauseMenu(Name);
		}

		break;

	case 2:
		cout << "Are you sure you want to save the game?" << endl;
		cout << "1 = YES, 2 = NO" << endl;
		int newGameChoice2;

		cin >> newGameChoice2;

		if (newGameChoice2 == 1)
		{
			cout << "Have fun!" << endl;
			system("Pause");
			SaveGame(Name);
			break;
		}
		else if (newGameChoice2 == 2)
		{
			cout << "Alright, sending you back to the menu..." << endl;
			system("Pause");
			PauseMenu(Name);
		}

	case 3:
		cout << "Are you sure you want to load the save file?" << endl;
		cout << "All your progress will be lost!" << endl;
		cout << "1 = YES, 2 = NO" << endl;
		int newGameChoice3;

		cin >> newGameChoice3;

		if (newGameChoice3 == 1)
		{
			cout << "Have fun!" << endl;
			system("Pause");
			LoadGame();
			break;
		}
		else if (newGameChoice3 == 2)
		{
			cout << "Alright, sending you back to the menu..." << endl;
			system("Pause");
			PauseMenu(Name);
		}

	case 4:
		cout << "Are you sure you want to exit the game" << endl;
		cout << "All your progress will be lost!" << endl;
		cout << "1 = YES, 2 = NO" << endl;
		int newGameChoice4;

		cin >> newGameChoice4;

		if (newGameChoice4 == 1)
		{
			exitProgram();
		}
		else if (newGameChoice4 == 2)
		{
			cout << "Alright, sending you back to the menu..." << endl;
			system("Pause");
			PauseMenu(Name);
		}

	case 5:
		cout << "Sending you back to the game!" << endl;
		break;

	default:
		cout << "Please enter a valid command..." << endl;
		system("Pause");
		PauseMenu(Name);
	}

	system("Pause");

	return;
}

void MainMenu() //Main/Pause Menu
{
	system("CLS");
	cout << "-----------------------------=" << endl;
	cout << "|           Dazef            |" << endl;
	cout << "|      A electronic RPG      |" << endl;
	cout << "|----------------------------|" << endl;
	cout << "|        1. New Game         |" << endl;
	cout << "|----------------------------|" << endl;
	cout << "|        2. Load Game        |" << endl;
	cout << "|----------------------------|" << endl;
	cout << "|        3. Exit             |" << endl;
	cout << "------------------------------" << endl;

	int menuChoice;
	cout << "What would you like to do?: ";
	cin >> menuChoice;

	switch (menuChoice)
	{
	case 1:
		cout << "Are you sure you want to start a new game?" << endl;
		cout << "1 = YES, 2 = NO" << endl;
		int newGameChoiceMM;

		cin >> newGameChoiceMM;

		if (newGameChoiceMM == 1)
		{
			cout << "Have fun!" << endl;
			Clearer();
		}
		else if (newGameChoiceMM == 2)
		{
			cout << "Alright, sending you back to the menu..." << endl;
			system("Pause");
			MainMenu();
		}

		break;

	case 2:
		cout << "Are you sure you want to load the save file?" << endl;
		cout << "1 = YES, 2 = NO" << endl;
		int newGameChoiceMM2;

		cin >> newGameChoiceMM2;

		if (newGameChoiceMM2 == 1)
		{
			cout << "Have fun!" << endl;
			system("Pause");
			LoadGame();
			break;
		}
		else if (newGameChoiceMM2 == 2)
		{
			cout << "Alright, sending you back to the menu..." << endl;
			system("Pause");
			MainMenu();
		}

	case 3:
		cout << "Are you sure you want to exit the game" << endl;
		cout << "All your progress will be lost!" << endl;
		cout << "1 = YES, 2 = NO" << endl;
		int newGameChoiceMM3;

		cin >> newGameChoiceMM3;

		if (newGameChoiceMM3 == 1)
		{
			exitProgram();
		}
		else if (newGameChoiceMM3 == 2)
		{
			cout << "Alright, sending you back to the menu..." << endl;
			system("Pause");
			MainMenu();
		}

	default:
		cout << "Please enter a valid command..." << endl;
		system("Pause");
		MainMenu();
	}

	system("Pause");

	return;
}

void Inventory()
{
	Items* Inventory[10];
	int itemLocation = 1, counterNum;
	string name, desc;
	int quantity;

	ifstream inFile;
	inFile.open("Trinkets.txt");
	inFile >> counterNum;

	for (int x = 1; x < counterNum; x++)
	{
		inFile >> name >> desc >> quantity;

		//changes all the _ to a space for the names.
		for (int y = 0; y < name.length(); y++)
		{
			if (name.substr(y, 1) == "_")
			{
				name[y] = ' ';
			}
		}

		//changes all the _ to a space for the descriptions.
		for (int y = 0; y < desc.length(); y++)
		{
			if (desc.substr(y, 1) == "_")
			{
				desc[y] = ' ';
			}
		}

		Inventory[itemLocation] = new Trinket(name, desc, quantity);
		itemLocation++;
	}

	inFile.close();

	system("CLS");
	cout << "-----------------------------=" << endl;
	cout << "|           Dazef            |" << endl;
	cout << "|      A electronic RPG      |" << endl;
	cout << "|----------------------------|" << endl;
	cout << "|      CURRENT INVENTORY     |" << endl;
	cout << "|----------------------------|" << endl;
	cout << "|        1. Inspect Item     |" << endl;
	cout << "|----------------------------|" << endl;
	cout << "|        2. Back to game     |" << endl;
	cout << "------------------------------" << endl;

	//Displays items based on global events

	if (Events[1] == 0)
	{
		cout << " - " << "EMPTY" << " - " << endl << endl;
	}

	if (Events[1] == 1)
	{
		cout << " - " << Inventory[1]->getName() << " - " << endl << endl;
	}

	if (Events[3] == 1)
	{
		cout << " - " << Inventory[2]->getName() << " - " << endl << endl;
	}

	if (Banana == 1)
	{
		cout << " - " << Inventory[3]->getName() << " - " << endl << endl;
	}

	if (Gem == 1)
	{
		cout << " - " << Inventory[4]->getName() << " - " << endl << endl;
	}


	if (Lever == 1)
	{
		cout << " - " << Inventory[5]->getName() << " - " << endl << endl;
	}


	if (Rock == 1)
	{
		cout << " - " << Inventory[6]->getName() << " - " << endl << endl;
	}

	cout << "Current Gold: " << inventoryGold << endl << endl;

	cout << "Would you like to do?" << endl;
	int choice;
	cin >> choice;

	if (choice == 1)
	{
		cout << "Choose the item you wish to inspect: ";
		int choiceInv;
		cin >> choiceInv;

		cout << endl << "You have selected the following item" << endl;
		Inventory[choiceInv]->display();
	}
	if (choice == 2)
	{
		cout << "Sending you back to the game!" << endl;
	}

	system("Pause");
	return;
}

void SaveGame(char Name) //Function to save game
{
	//Saves special states to file
	//Name is for room Name
	//Order of saving is
	//1. RoomName
	//2. Gem
	//3. Banana
	//4. Torch
	//5. Lever
	//6. Rock
	//Events[1], etc.

	for (int x = 0; x < 24; x++)
	{
		system("cls");
		cout << "Checking for savefile." << endl;
		system("cls");
		cout << "Checking for savefile.." << endl;
		system("cls");
		cout << "Checking for savefile..." << endl;
	}

	ifstream inFile;
	inFile.open("SaveFile.txt");

	if (inFile.is_open())
	{
		cout << "Save File found" << endl;
		system("PAUSE");
	}
	else
	{
		cout << "Unable to open file" << endl;
		cout << "Creating SaveFile..." << endl;
		ofstream outFile("SaveFile.txt");
		system("PAUSE");
	}

	ofstream outFile;
	outFile.open("SaveFile.txt");

	char roomName = Name;

	outFile << roomName << endl;
	outFile << Gem << endl;
	outFile << Banana << endl;
	outFile << Torch << endl;
	outFile << Lever << endl;
	outFile << Rock << endl;

	//I started the array at 1
	//So it will start at Events[1]
	for (int x = 1; x < 9; x++)
	{
		outFile << Events[x] << endl;
	}

	outFile.close();

	for (int x = 0; x < 24; x++)
	{
		system("cls");
		cout << "Saving data." << endl;
		system("cls");
		cout << "Saving data.." << endl;
		system("cls");
		cout << "Saving data..." << endl;
	}

	cout << "The game has been saved!" << endl;

	return;
}

void LoadGame()
{
	for (int x = 0; x < 24; x++)
	{
		system("cls");
		cout << "Checking for savefile." << endl;
		system("cls");
		cout << "Checking for savefile.." << endl;
		system("cls");
		cout << "Checking for savefile..." << endl;
	}

	ifstream inFile;
	inFile.open("SaveFile.txt");

	if (inFile.is_open())
	{
		cout << "Save File found" << endl;
		system("PAUSE");
	}
	else
	{
		cout << "Unable to open file" << endl;
		cout << "Creating SaveFile..." << endl;
		ofstream outFile("SaveFile.txt");
		system("PAUSE");
	}

	char roomName;

	inFile >> roomName;
	inFile >> Gem;
	inFile >> Banana;
	inFile >> Torch;
	inFile >> Lever;
	inFile >> Rock;

	//Puts the room name into a global char variable
	loadedRoomName = roomName;

	//I started the array at 1
	//So it will start at Events[1]
	for (int x = 1; x < 9; x++)
	{
		inFile >> Events[x];
	}

	inFile >> inventoryGold;

	inFile.close();

	cout << "Game data has been loaded." << endl;
	return;
}

void Clearer()
{
	//Clears all global events variables for a new game
	Gem = 0;
	Banana = 0;
	Torch = 0;
	Lever = 0;
	Rock = 0;

	for (int x = 0; x < 10; x++)
	{
		Events[x] = 0;
	}

	inventoryGold = 0;
}

void exitProgram()
{
	//Exits the program and thanks the user.
	//Clears screen then displays the
	//exiting message
	system("cls");
	cout << "Thank you for playing! \n";
	cout << "Have a nice day! \n";
	cout << "Now exiting... \n";
	exit(0);
}