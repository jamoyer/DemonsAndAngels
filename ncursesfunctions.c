#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "GenerationFunctions.c"
#include "mapstructs.c"

//maximum length the name and path of a file can be including extension EX:"Maps/0map.txt"
#define MAX_MAPNAME_LENGTH 30
//maximum height a map can be
#define MAX_MAP_HEIGHT 300
//maximum width a map can be
#define MAX_MAP_WIDTH 300
//what the player looks like on the screen
#define AVATAR '@'
//the maximum number of steps a player may take in a dangerous map before being attack by a random spirit
#define MAX_PEACEFUL_STEPS_TAKEN 75
//the minimum number of steps a player may take in a dangerous map before being attack by a random spirit
#define MIN_PEACEFUL_STEPS_TAKEN 20

//An array filled with the current map the player is on or using.
char mapArray[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];

//the name of the previous map the player was on.
char *previousmapname;
//the width of the currentmap
int mapWidth=0;
//the height of the currentmap
int mapHeight=0;
//1 if it is a new game, 0 if it is not a new game
int newGameboolean=0;

//the difference between playerWidth and w (the player's width on the screen)
int dif_PW_w;
//the difference between playerHeight and h (the player's height on the screen)
int dif_PH_h;
//whatever the player is standing on
char terrain=' ';
//the player's height in mapArray
int playerHeight=0;
//the player's width in mapArray
int playerWidth=0;
//the direction the player last moved to or is trying to move to
char direction;

//random integer that determines how often the player is attack during a map
int randomAttackCount;
//timer based on how many steps have passed
int stepCounter=0;
//is zero if an attack was just called. I put this here to solve a glitch where the player would overwrite the land.
int attackcalled=0;


//load and save stuff
void loadgame(char *GameSettingsFile);
void savegame(char *GameSettingsFile);

//drawing functions
void attackcall();
void simplemove(int tempHeight, int tempWidth);
void printmap();
void color_and_draw_character(int x, int y, char character, int refresh);
void draw_character(int x, int y, char use);

//game loop functions
void manageInput();
void startgame();
void manageMain();
void Titlemenu();

//in game menu stuff
void menuMovement();
void characterMenuInput();
void startMenu();

//changing map functions
void getplayercoords();
void getMapInfo();
void fillMapArray();
void mapchange(int idoorHeight, int idoorWidth);

//map struct functions
void clearcurrentmap();
void create0map();
void createHmap();
void createbattlemap();
void create1map();
void createCavemap1();
void createMaze1map();

//attackfunctions
void printattackoptions(spirit main, spirit npc);
void printattacks(spirit temp);
int randomAttack(spirit temp);
void attackSequence(character npc);
void Attack(spirit *a,spirit *b,int attack);
void printspirits();
void goodmvprintw(int x, int y, char* line);
void managespirits();
void printstats(int spiritnumber);

//generationfunctions
int checkforlevel(int i);

//-------------------------------------------------------------------------------------------------------------------------
//=========================================================================================================================
//-------------------------------------------------------------------------------------------------------------------------
//functions that run the in-game menu.

/**
 *
 */
void startMenu()
{
	fillMapArray();
	printmap();
	newGameboolean=0;
	menuMovement();

}

/**
 *
 */
void menuMovement(){
char input;
int menuheight = 17;
int menuwidth = 62;
fillMapArray();
printmap();

int position = 1;
int heightSelection1=2;
int heightSelection2=5;
int heightSelection3=8;
int heightSelection4=11;
int heightSelection5=14;

draw_character(12,2,'>');
draw_character(11,2,'-');
draw_character(10,2,'-');
draw_character(9,2,'-');


int currentWidth=12;
int currentHeight=2;

while(1){
		scanf("%c",&input);
		switch(input){
			case 'w':
				if(currentHeight>heightSelection1){
				color_and_draw_character(currentWidth,currentHeight,' ',0);
				color_and_draw_character(currentWidth-1,currentHeight,' ',0);
				color_and_draw_character(currentWidth-2,currentHeight,' ',0);
				color_and_draw_character(currentWidth-3,currentHeight,' ',0);
				color_and_draw_character(currentWidth-4,currentHeight,' ',0);
				currentHeight -= 3;
				position -= 2;
				color_and_draw_character(currentWidth,currentHeight,'>',0);
				color_and_draw_character(currentWidth-1,currentHeight,'-',0);
				color_and_draw_character(currentWidth-2,currentHeight,'-',0);
				color_and_draw_character(currentWidth-3,currentHeight,'-',0);
				color_and_draw_character(currentWidth-4,currentHeight,'-',0);
				refresh();
				}
				break;

			case 's':
				if(currentHeight<heightSelection5){

				color_and_draw_character(currentWidth,currentHeight,' ',0);
				color_and_draw_character(currentWidth-1,currentHeight,' ',0);
				color_and_draw_character(currentWidth-2,currentHeight,' ',0);
				color_and_draw_character(currentWidth-3,currentHeight,' ',0);
				color_and_draw_character(currentWidth-4,currentHeight,' ',0);
				currentHeight += 3;
				position -= 2;
				color_and_draw_character(currentWidth,currentHeight,'>',0);
				color_and_draw_character(currentWidth-1,currentHeight,'-',0);
				color_and_draw_character(currentWidth-2,currentHeight,'-',0);
				color_and_draw_character(currentWidth-3,currentHeight,'-',0);
				color_and_draw_character(currentWidth-4,currentHeight,' ',0);
				refresh();
				}
				break;

			case 'e':
				if(currentHeight==heightSelection1)
				{
					currentmap.mapname=previousmapname;
					startgame();
				/*currentmap.mapname=previousmapname;
				previousmapname="Maps/MainMenuMap.txt";
				startgame();
				*/
				return;
				}

				/*if(currentHeight==heightSelection2)
				{

				}*/

				if(currentHeight==heightSelection3)
				{
					//previousscreenname=currentmap.mapname;
					currentmap.mapname="Maps/CharacterStats.txt";
					characterMenuInput();

				}

				if(currentHeight==heightSelection4)
				{
					savegame("GameSettings1.txt");
				}

				if(currentHeight==heightSelection5)
				{
					Titlemenu();
				}

				break;
	}
}
}

/**
 *
 */
void characterMenuInput(){
	char input;
	fillMapArray();
	printmap();

	while(1){
		scanf("%c",&input);
		switch(input){

		case'q':
			//previousscreenname="Maps/MainMenuMap.txt";
			currentmap.mapname="Maps/MainMenuMap.txt";
				//menuMovement(previousmapname);
				//currentmap.mapname=previousmapname;
				//previousmapname="Maps/MainMenuMap.txt";
				menuMovement();

				break;

		}
	}
}

//-------------------------------------------------------------------------------------------------------------------------
//=========================================================================================================================
//-------------------------------------------------------------------------------------------------------------------------
//functions that run the game: input management loops, menu's ....


/**
 *Starts up the game, bringing up the main menu.
 */
void Titlemenu(){
	srand(time(0));
	currentmap.mapname="Maps/Title.txt";
	fillMapArray();

	//starts ncurses
	initscr();
	printmap();
	manageMain();
}

/**
 *Manages input when the main menu is loaded.
 */
void manageMain(){
	char input;
	int menuheight = 19;
	int menuwidth = 27;
	int position = 1;
	color_and_draw_character(menuwidth,menuheight,'-',0);
	color_and_draw_character(menuwidth+1,menuheight,'>',0);
	refresh();
	while(1){
		scanf("%c",&input);
		switch(input){
			case 'w':
				if(position!=1){
					color_and_draw_character(menuwidth,menuheight,' ',0);
					color_and_draw_character(menuwidth+1,menuheight,' ',0);
					menuheight--;
					position--;
					color_and_draw_character(menuwidth,menuheight,'-',0);
					color_and_draw_character(menuwidth+1,menuheight,'>',0);
					refresh();
				}
				break;
			case 's':
				if(position!=4){
					color_and_draw_character(menuwidth,menuheight,' ',0);
					color_and_draw_character(menuwidth+1,menuheight,' ',0);
					menuheight++;
					position++;
					color_and_draw_character(menuwidth,menuheight,'-',0);
					color_and_draw_character(menuwidth+1,menuheight,'>',0);
					refresh();
				}
				break;
			case 'e':
				//Selects New Game
				if(position == 1){
					newGameboolean=1;
					startgame();
				}
				//Selects Load Game
				if(position == 2){
					char *gamesettings = "GameSettings1.txt";

					/*char gamesettings[30];
					goodmvprintw(0,mapHeight,"Please type the path of the Save File. Then hit enter. (return)");

					scanf(" %s ", gamesettings);

					//loads the settings from the GameSettings file
					*/loadgame(gamesettings);

					//takes the char pointers and points them to real memory locations
					char mapname[MAX_NAME_LENGTH];
					strcpy(mapname,currentmap.mapname);
					currentmap.mapname=mapname;

					int i=0;
					char attack1k[MAX_NAME_LENGTH];
					strcpy(attack1k,mainchar.spirits[i].attacks.attack1name);
					mainchar.spirits[i].attacks.attack1name=attack1k;

					char attack2k[MAX_NAME_LENGTH];
					strcpy(attack2k,mainchar.spirits[i].attacks.attack2name);
					mainchar.spirits[i].attacks.attack2name=attack2k;

					char attack3k[MAX_NAME_LENGTH];
					strcpy(attack3k,mainchar.spirits[i].attacks.attack3name);
					mainchar.spirits[i].attacks.attack3name=attack3k;

					char attack4k[MAX_NAME_LENGTH];
					strcpy(attack4k,mainchar.spirits[i].attacks.attack4name);
					mainchar.spirits[i].attacks.attack4name=attack4k;

					startgame();

				}
				//Selects About
				if(position == 3){
					previousmapname=currentmap.mapname;
					currentmap.mapname="Maps/About.txt";
					fillMapArray();
					printmap();
					char input='\0';
					while(input!='q'){
						scanf("%c",&input);
					}
					Titlemenu();
				}
				//Exits
				if(position == 4){
					endwin();
					exit(1);
				}
				break;
		}

	}
}

/**
 *The loop that runs the game.
 *It creates the map, prints it to the screen, then begins to manage further input from the user.
 */
void startgame(){
	fillMapArray();
	printmap();
	newGameboolean=0;
	manageInput();
}

/**
 *Constantly scans for input and acts accordingly.
 */
void manageInput(){
	char input;
	int tempHeight = playerHeight;
	int tempWidth = playerWidth;
	while(1){
		scanf("%c",&input);
		int tempHeight = playerHeight;
		int tempWidth = playerWidth;
		switch (input){
			case 'w':
				stepCounter++;
				if((stepCounter>=randomAttackCount)&&(currentmap.difficulty!=0)){
					attackcall();
				}
				direction=input;
				tempHeight--;
				break;
			case 'a':
				stepCounter++;
				if((stepCounter>=randomAttackCount)&&(currentmap.difficulty!=0)){
					attackcall();
				}
				direction=input;
				tempWidth--;
				break;
			case 's':
				stepCounter++;
				if((stepCounter>=randomAttackCount)&&(currentmap.difficulty!=0)){
					attackcall();
				}
				direction=input;
				tempHeight++;
				break;
			case 'd':
				stepCounter++;
				if((stepCounter>=randomAttackCount)&&(currentmap.difficulty!=0)){
					attackcall();
				}
				direction=input;
				tempWidth++;
				break;
			case 'W':
				tempHeight--;
				break;
			case 'A':
				tempWidth--;
				break;
			case 'S':
				tempHeight++;
				break;
			case 'D':
				tempWidth++;
				break;
			case'm':
				previousmapname=currentmap.mapname;
				currentmap.mapname="Maps/MainMenuMap.txt";
		 		menuMovement();
				break;
		}

		char target=mapArray[tempHeight][tempWidth];
		switch (target){
			//if the player has moved towards an NPC with any WASD, it begins attacksequence;
			case '&':
				if((input=='W')||(input=='A')||(input=='S')||(input=='D')){
					attackcall();
				}
				break;
			case '$':
				if((input=='W')||(input=='A')||(input=='S')||(input=='D')){
					attackcall();
				}
				break;
			case ' ':
				simplemove(tempHeight, tempWidth);
				break;
			case '=':
				simplemove(tempHeight, tempWidth);
				break;
			//if the player move into a door (%), the map changes.
			case '%':
				mapchange(tempHeight, tempWidth);
				break;

			}
	}
}

//---------------------------------------------------------------------------------------------------------------------
//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
//Loading and Saving functions

/**
 *Call this to save the game.
 *Saves everything (needed to pick up right where the player left off) to a file given in the parameters.
 */
void savegame(char *GameSettingsFile){
	goodmvprintw(0,mapHeight,"Saving...");
	FILE *mapFile= fopen(GameSettingsFile, "w");

	fprintf(mapFile,"%s\n%d\n%d\n%d\n%d\n%d\n%d\n\n",
			previousmapname,terrain,dif_PW_w,dif_PH_h,playerHeight
			,playerWidth,randomAttackCount);

	int i=0;
	fprintf(mapFile,"%s\n%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n\n%s\n%s\n%s\n%s",
			mainchar.spirits[i].name, mainchar.spirits[i].type, mainchar.spirits[i].maxhealth,
			mainchar.spirits[i].health, mainchar.spirits[i].energy, mainchar.spirits[i].maxenergy,
			mainchar.spirits[i].experience, mainchar.spirits[i].level, mainchar.spirits[i].attackpower,
			mainchar.spirits[i].speed, mainchar.spirits[i].armor, mainchar.spirits[i].attacks.attack1,
			mainchar.spirits[i].attacks.attack2, mainchar.spirits[i].attacks.attack3, mainchar.spirits[i].attacks.attack4,
			mainchar.spirits[i].attacks.attack1name, mainchar.spirits[i].attacks.attack2name,
			mainchar.spirits[i].attacks.attack3name, mainchar.spirits[i].attacks.attack4name);
	fclose(mapFile);
	goodmvprintw(0,mapHeight,"                        ");
}


/**
 *Takes a filename as an argument, reads the contents of the file and fills the globals variables with them.
 */
void loadgame(char *GameSettingsFile){
	//opens file
	FILE *mapFile = fopen(GameSettingsFile,"r");

	while(!feof(mapFile)){
		char temp[MAX_NAME_LENGTH];
		fscanf(mapFile," %s ", temp);
		currentmap.mapname=temp;

		//gets regular globals for player position and movement
		fscanf(mapFile," %d %d %d %d %d %d ", &terrain, &dif_PW_w, &dif_PH_h, &playerHeight, &playerWidth, &randomAttackCount/*, &mainchar.numberofspirits*/);

		char *name;
		char *type;
		int maxhealth;
		int health;
		int experience;
		int level;
		int alignment;
		int energy;
		int maxenergy;
		int living;
		int attackpower;
		int speed;
		int armor;
		int bodyhealth;
		int maxbodyhealth;
		int body;
		int attack1;
		int attack2;
		int attack3;
		int attack4;

		//get mainchar struct and spirit array
		int i=0;

			//fgets(temp,MAX_NAME_LENGTH, mapFile);
			char namep[MAX_NAME_LENGTH];
			fscanf(mapFile," %s ", namep);
			name=namep;

			char typep[MAX_NAME_LENGTH];
			fscanf(mapFile," %s ", typep);
			type=typep;

			fscanf(mapFile," %d %d %d %d %d %d %d %d %d %d %d %d %d ", &maxhealth, &health, &energy, &maxenergy, &experience, &level, &attackpower, &speed, &armor, &attack1, &attack2, &attack3, &attack4);

			mainchar.spirits[i].name=name;
			mainchar.spirits[i].type=type;
			mainchar.spirits[i].maxhealth=maxhealth;
			mainchar.spirits[i].health=health;
			mainchar.spirits[i].experience=experience;
			mainchar.spirits[i].level=level;
			mainchar.spirits[i].energy=energy;
			mainchar.spirits[i].maxenergy=maxenergy;
			mainchar.spirits[i].attackpower=attackpower;
			mainchar.spirits[i].speed=speed;
			mainchar.spirits[i].armor=armor;
			mainchar.spirits[i].attacks.attack1 = attack1;
			mainchar.spirits[i].attacks.attack2 = attack2;
			mainchar.spirits[i].attacks.attack3 = attack3;
			mainchar.spirits[i].attacks.attack4 = attack4;

			char attack1p[MAX_NAME_LENGTH];
			fscanf(mapFile," %s ", attack1p);
			mainchar.spirits[i].attacks.attack1name=attack1p;

			char attack2p[MAX_NAME_LENGTH];
			fscanf(mapFile," %s ", attack2p);
			mainchar.spirits[i].attacks.attack2name=attack2p;

			char attack3p[MAX_NAME_LENGTH];
			fscanf(mapFile," %s ", attack3p);
			mainchar.spirits[i].attacks.attack3name=attack3p;

			char attack4p[MAX_NAME_LENGTH];
			fscanf(mapFile," %s ", attack4p);
			mainchar.spirits[i].attacks.attack4name=attack4p;
	}
	fclose(mapFile);
}

//---------------------------------------------------------------------------------------------------------------------
//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
//functions that handle reading in and changing maps

/**
 *Fills mapArray with file mapName's contents.
 *Sets the values of mapWidth, mapHeight to the current map's width and height.
 *If the map is playable (the character roams around on it) it gets playable-map-info.
 *Files should be no larger than 300x300 characters.
 */
void fillMapArray(){
	if(newGameboolean){
		create0map();
		playerHeight = 8;
		playerWidth = 13;

	}

	//opens file
	FILE *mapFile = fopen(currentmap.mapname,"r");

	//reads file and stores it into mapArray
	//also gets the height of the file
	mapWidth=0;
	mapHeight=0;
	while(!feof(mapFile)){
		fgets(mapArray[mapHeight],MAX_MAP_WIDTH, mapFile);
		mapHeight++;
	}
	fclose(mapFile);

	//gets the width of the file
	for(mapWidth;mapArray[0][mapWidth]!='\0';mapWidth++){}

	getMapInfo();
}
/**
 *Based on mapName, it rebuilds the struct currentmap.
 *It then gets the player's new coordinates and puts them into mapArray.
 */
void getMapInfo(){

	//changes currentmap accordingly to match the map
	if(!strcmp(currentmap.mapname,"Maps/0map.txt")){
		create0map();
	}
	else if(!strcmp(currentmap.mapname,"Maps/1map.txt")){
		create1map();
	}
	else if(!strcmp(currentmap.mapname,"Maps/Hmap.txt")){
		createHmap();
	}
	else if(!strcmp(currentmap.mapname,"Maps/BattleScene.txt")){
		createbattlemap();
	}
	else if(!strcmp(currentmap.mapname,"Maps/Cavemap1.txt")){
		createCavemap1();
	}
	else if(!strcmp(currentmap.mapname,"Maps/Maze1undermap1.txt")){
		createMaze1map();
	}
	else if(!strcmp(currentmap.mapname,"Maps/Title.txt")){
		createTitleMenu();
	}
	else if(!strcmp(currentmap.mapname,"Maps/About.txt")){
		createAbout();
	}
	else if(!strcmp(currentmap.mapname,"Maps/2map.txt")){
		create2map();
	}
	else if(!strcmp(currentmap.mapname,"Maps/3map.txt")){
		create3map();
	}
	else if(!strcmp(currentmap.mapname,"Maps/4map.txt")){
		create4map();
	}
	else if(!strcmp(currentmap.mapname,"Maps/5map.txt")){
		create5map();
	}
	else if(!strcmp(currentmap.mapname,"Maps/MainMenuMap.txt")){
		createMainMenu();
	}
	else if(!strcmp(currentmap.mapname,"Maps/CharacterStats.txt")){
		createCharacterStats();
	}

	if(currentmap.type=='p'){
		stepCounter=0;
		while(randomAttackCount<MIN_PEACEFUL_STEPS_TAKEN){
			randomAttackCount=rand()%MAX_PEACEFUL_STEPS_TAKEN;
		}
		//if it isnt a completely new game, it changes the player's coordinates acoording to the new map
		//and where the player came from and puts them into mapArray.
		if((!newGameboolean) && (previousmapname!="Maps/BattleScene.txt")&&
					(previousmapname!="Maps/About.txt")&&
					(previousmapname!="Maps/Title.txt")&&
					(previousmapname!="Maps/MainMenuMap.txt")){
			getplayercoords();
		}
		mapArray[playerHeight][playerWidth]=AVATAR;
	}
}

/**
 *After going through a door, this returns the new player's coordinates on the new map.
 */
void getplayercoords(){
	//checks through to see which door the player came through.
	int x=playerWidth;
	int y=playerHeight;
	if(currentmap.door0_map==previousmapname){
		x = currentmap.door0_width;
		y = currentmap.door0_height;
	}
	else if(currentmap.door1_map==previousmapname){
		x = currentmap.door1_width;
		y = currentmap.door1_height;
	}
	else if(currentmap.door2_map==previousmapname){
		x = currentmap.door2_width;
		y = currentmap.door2_height;
	}
	else if(currentmap.door3_map==previousmapname){
		x = currentmap.door3_width;
		y = currentmap.door3_height;
	}
	else if(currentmap.door4_map==previousmapname){
		x = currentmap.door4_width;
		y = currentmap.door4_height;
	}
	else if(currentmap.door5_map==previousmapname){
		x = currentmap.door5_width;
		y = currentmap.door5_height;
	}
	else if(currentmap.door6_map==previousmapname){
		x = currentmap.door6_width;
		y = currentmap.door6_height;
	}
	else if(currentmap.door7_map==previousmapname){
		x = currentmap.door7_width;
		y = currentmap.door7_height;
	}
	else if(currentmap.door8_map==previousmapname){
		x = currentmap.door8_width;
		y = currentmap.door8_height;
	}
	else if(currentmap.door9_map==previousmapname){
		x = currentmap.door9_width;
		y = currentmap.door9_height;
	}

	//then it places the player one space in the direction entered the door, from the door.
	if(!attackcalled){
		switch (direction){
			case 'w':
				y--;
				break;
			case 'a':
				x--;
				break;
			case 's':
				y++;
				break;
			case 'd':
				x++;
				break;
		}
	}
	attackcalled=0;
	playerHeight=y;
	playerWidth=x;
}



/**
 *Handles when the player attacks another being by calling attacksequence.
 */
void attackcall(){
	attackcalled=1;
	previousmapname=currentmap.mapname;
	currentmap.mapname="Maps/BattleScene.txt";

	attackSequence(generatenpc(currentmap.difficulty));

	//resets the stepCounter and rerandomizes the time it takes to be attacked by a spirit.
	stepCounter=0;
	do{
		randomAttackCount=rand()%MAX_PEACEFUL_STEPS_TAKEN;
	}while(randomAttackCount<MIN_PEACEFUL_STEPS_TAKEN);

	currentmap.mapname=previousmapname;
	startgame();
}

/**
 *Used to simply move a character from one spot on a map to the next.
 */
void simplemove(int tempHeight, int tempWidth){
	mapArray[playerHeight][playerWidth]=terrain;
	color_and_draw_character((playerWidth-dif_PW_w), (playerHeight-dif_PH_h),mapArray[playerHeight][playerWidth], 1);
	playerHeight=tempHeight;
	playerWidth=tempWidth;
	terrain=mapArray[playerHeight][playerWidth];
	mapArray[playerHeight][playerWidth]=AVATAR;

	int row;
	int col;
	getmaxyx(stdscr,row,col);
	//if the player has moved to the boundary of the screen, it reprints the map around the player.
	if((playerWidth-dif_PW_w>col-2)||(playerWidth-dif_PW_w<1)||(playerHeight-dif_PH_h>row-2)||(playerHeight-dif_PH_h<1)){
		printmap();
	}
	else{
		draw_character((playerWidth-dif_PW_w), (playerHeight-dif_PH_h),mapArray[playerHeight][playerWidth]);
	}
}

/**
 *Changes the name of the mapFile based on which door they walked through.
 *Then it restarts the startgame sequence.
 */
void mapchange(int idoorHeight, int idoorWidth){
	previousmapname=currentmap.mapname;
	if((idoorHeight==currentmap.door0_height)&(idoorWidth==currentmap.door0_width)){
			currentmap.mapname=currentmap.door0_map;
	}
	else if((idoorHeight==currentmap.door1_height)&(idoorWidth==currentmap.door1_width)){
			currentmap.mapname=currentmap.door1_map;
	}
	else if((idoorHeight==currentmap.door2_height)&(idoorWidth==currentmap.door2_width)){
			currentmap.mapname=currentmap.door2_map;
	}
	else if((idoorHeight==currentmap.door3_height)&(idoorWidth==currentmap.door3_width)){
			currentmap.mapname=currentmap.door3_map;
	}
	else if((idoorHeight==currentmap.door4_height)&(idoorWidth==currentmap.door4_width)){
			currentmap.mapname=currentmap.door4_map;
	}
	else if((idoorHeight==currentmap.door5_height)&(idoorWidth==currentmap.door5_width)){
			currentmap.mapname=currentmap.door5_map;
	}
	else if((idoorHeight==currentmap.door6_height)&(idoorWidth==currentmap.door6_width)){
			currentmap.mapname=currentmap.door6_map;
	}
	else if((idoorHeight==currentmap.door7_height)&(idoorWidth==currentmap.door7_width)){
			currentmap.mapname=currentmap.door7_map;
	}
	else if((idoorHeight==currentmap.door8_height)&(idoorWidth==currentmap.door8_width)){
			currentmap.mapname=currentmap.door8_map;
	}
	else if((idoorHeight==currentmap.door9_height)&(idoorWidth==currentmap.door9_width)){
			currentmap.mapname=currentmap.door9_map;
	}

	startgame();
}

//---------------------------------------------------------------------------------------------------------------------
//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
//COLORING AND DRAWING FUNCTIONS

/**
 *Clears the old map with spaces, then
 *prints mapArray to the screen.
 */
void printmap(){
	//gets the size of the screen
	int row;
	int col;
	getmaxyx(stdscr,row,col);

	//determines if the terminal can handle colors
	if(has_colors()==false){
		endwin();
		printf("Your terminal does not support color.\n");
		exit(1);
	}

	//makes the cursor invisible
	curs_set(0);

	//activates the colors to be used
	start_color();

	//clears the old map off screen
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			color_and_draw_character(j,i,' ',0);
		}
	}
	refresh();

	int refresh=0;		//set this to 1 to refresh after every character is written, otherwise it does not
				//refresh while writing characters to the screen and that will need to be done manually afterwards.
				//setting it to zero increases the efficiency of loading the screen.

	if(currentmap.type!='p'){
		for(int h=0;((h<row)&&(h<mapHeight));h++){
			for(int w=0;((w<col)&&(w<mapWidth-1));w++){
				color_and_draw_character(w,h,mapArray[h][w],refresh);
			}
		}
		refresh();
	}

	else{
		//prints only what will fit on the screen with the player at the center
		int tempheight;
		int tempwidth;

		if(playerHeight-row/2<=0){
			tempheight=row/2;
		}
		else if(playerHeight+row/2>=mapHeight){
			tempheight=mapHeight-row/2;
		}
		else{
			tempheight=playerHeight;
		}

		if(playerWidth-col/2<=0){
			tempwidth=col/2;
		}
		else if(playerWidth+col/2>=mapWidth){
			tempwidth=mapWidth-col/2;
		}
		else{
			tempwidth=playerWidth;
		}

		//coordinates of where its printing on the screen
		int h=0;
		int w=0;

		//players coordinates on the screen, not the mapArray
		int playerHeightonscreen;
		int playerWidthonscreen;

		int j;
		if(tempheight-row/2<0){
			j=0;
		}
		else{
			j=tempheight-row/2;
		}
		for(;((j<row+tempheight)&&(j<mapHeight)&&(h<row));j++){
			w=0;

			int k;
			if(tempwidth-col/2<0){
				k=0;
			}
			else{
				k=tempwidth-col/2;
			}
			for(int k=(tempwidth-col/2);((k<col+tempwidth)&&(k<mapWidth-1)&&(w<col));k++){
				color_and_draw_character(w,h,mapArray[j][k],refresh);
				if(mapArray[j][k]==AVATAR){
						playerHeightonscreen=h;
						playerWidthonscreen=w;
				}

				w++;
			}
			h++;
		}
		//difference of playerWidth and the players width on the screen. This helps keep the player's
		//position on the screen coordinated with the mapArray[][]
		dif_PW_w=playerWidth-playerWidthonscreen;
		dif_PH_h=playerHeight-playerHeightonscreen;
		refresh();
	}
}

/**
 *Draws character use to the screen and position x,y
 */
void draw_character(int x, int y, char use){
	mvaddch(y,x,use);
	refresh();
}

/**
 *takes in the x,y coordinates and a character and prints them in their respective colors
 *setting refresh to 0 means it will not refresh the screen after it has printed.
 */
void color_and_draw_character(int x, int y, char character, int refresh){
	init_pair(1, COLOR_BLACK, COLOR_BLACK);		//(space)
	init_pair(2, COLOR_WHITE, COLOR_BLACK);		//@,$,&
	init_pair(3, COLOR_GREEN, COLOR_BLACK);		//X,x
	init_pair(4, COLOR_BLUE, COLOR_BLACK);		//~
	init_pair(5, COLOR_CYAN, COLOR_BLACK);		//=
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);	//#
	init_pair(7, COLOR_YELLOW, COLOR_BLACK);	//%
	init_pair(8, COLOR_RED, COLOR_BLACK);

	//coloring for playable maps
	if(currentmap.type=='p'){
		switch(character){
			case '@':
				attron(COLOR_PAIR(2));
				break;
			case '$':
				attron(COLOR_PAIR(2));
				break;
			case '&':
				attron(COLOR_PAIR(2));
				break;
			case 'X':
				attron(COLOR_PAIR(3));
				break;
			case 'x':
				attron(COLOR_PAIR(3));
				break;
			case '#':
				attron(COLOR_PAIR(5));
				break;
			case '%':
				attron(COLOR_PAIR(7));
				break;
			case ' ':
				attron(COLOR_PAIR(1));
				break;
			case '~':
				attron(COLOR_PAIR(4));
				break;
			case '=':
				attron(COLOR_PAIR(5));
				break;
		}
	}
	//coloring for Menus
	else if(currentmap.type=='M'){
		switch(character){
			case 'X':
				attron(COLOR_PAIR(3));
				break;
			case ' ':
				attron(COLOR_PAIR(1));
				break;
		}
	}
	//system to catch that pesky null at the end of the map.
	if(character!='\0'){
		mvaddch(y,x,character);
	}

	//doesn't refresh if refresh is 0. Speeds up screen loading.
	if(refresh){
		refresh();
	}
	standend();
}

//------------------------------------------------------------------------------------------------------------------------------------
//====================================================================================================================================
//------------------------------------------------------------------------------------------------------------------------------------
//attackfunctions begins


/**
 *
 */

void Attack(spirit *a,spirit *b,int attack){
//check if attacker is the main character
//set a temp structure for a and another for b
spirit tempA;
spirit tempB;
tempA = *a;
tempB = *b;
//decide who attacks first based off of attack stat
if(tempA.speed > tempB.speed){
tempB.health = tempB.health - attack + tempB.armor - tempA.attackpower;
	if(tempB.health <= 0){
	*a = tempA;
	*b = tempB;
	return;
	}
tempA.health = tempA.health - randomAttack(tempB) + tempA.armor;
	if(tempA.health <= 0){
	*a = tempA;
	*b = tempB;
	return;
	}
}
else{
tempA.health = tempA.health - randomAttack(tempB) + tempA.armor;
	if(tempA.health <= 0){
	*a = tempA;
	*b = tempB;
	return;
	}
tempB.health = tempB.health - attack + tempB.armor - tempA.attackpower;
	if(tempB.health <= 0){
	*a = tempA;
	*b = tempB;
	return;
	}
}
*a = tempA;
*b = tempB;
return;
}

/**
 *
 */
void attackSequence(character npc){
int attacking = 1;
int attackmenu = 0;
int spiritmenu = 0;
char input;
int menuheight = 17;
int menuwidth = 37;
character temp = mainchar;
spirit enemy = npc.spirits[0];
int count = 0;
int spiritnumber;
for(int v = 0; mainchar.spirits[v].name!="  ";v++){
	if((count==0)&&(mainchar.spirits[v].health>0)){
	spiritnumber = v;
	count = 1;
	}
}
fillMapArray();
printattackoptions(mainchar.spirits[spiritnumber],enemy);
int position = 1;
	while(attacking){
		scanf("%c",&input);
		switch(input){
			case 'w':
				if((position == 3) || (position == 4)){
				draw_character(menuwidth,menuheight,' ');
				draw_character(menuwidth+1,menuheight,' ');
				menuheight -= 2;
				position -= 2;
				draw_character(menuwidth,menuheight,'-');
				draw_character(menuwidth+1,menuheight,'>');
				}
				break;
			case 'a':
				if((position == 2) || (position == 4)){
				draw_character(menuwidth,menuheight,' ');
				draw_character(menuwidth+1,menuheight,' ');
				menuwidth -= 17;
				position -= 1;
				draw_character(menuwidth,menuheight,'-');
				draw_character(menuwidth+1,menuheight,'>');
				}
				break;
			case 's':
				if((position == 1) || (position == 2)){
				draw_character(menuwidth,menuheight,' ');
				draw_character(menuwidth+1,menuheight,' ');
				menuheight += 2;
				position += 2;
				draw_character(menuwidth,menuheight,'-');
				draw_character(menuwidth+1,menuheight,'>');
				}
				break;
			case 'd':
				if((position == 1) || (position == 3)){
				draw_character(menuwidth,menuheight,' ');
				draw_character(menuwidth+1,menuheight,' ');
				menuwidth += 17;
				position += 1;
				draw_character(menuwidth,menuheight,'-');
				draw_character(menuwidth+1,menuheight,'>');
				}
				break;
			case 'e':
				if(position == 1){
					printattacks(mainchar.spirits[spiritnumber]);
					attackmenu = 1;
					char input3;
					while(attackmenu){
						scanf("%c",&input3);
						switch(input3){
							case 'w':
								if((position == 3) || (position == 4)){
								draw_character(menuwidth,menuheight,' ');
								draw_character(menuwidth+1,menuheight,' ');
								menuheight -= 2;
								position -= 2;
								draw_character(menuwidth,menuheight,'-');
								draw_character(menuwidth+1,menuheight,'>');
								}
								break;
							case 'a':
								if((position == 2) || (position == 4)){
								draw_character(menuwidth,menuheight,' ');
								draw_character(menuwidth+1,menuheight,' ');
								menuwidth -= 17;
								position -= 1;
								draw_character(menuwidth,menuheight,'-');
								draw_character(menuwidth+1,menuheight,'>');
								}
								break;
							case 's':
								if((position == 1) || (position == 2)){
								draw_character(menuwidth,menuheight,' ');
								draw_character(menuwidth+1,menuheight,' ');
								menuheight += 2;
								position += 2;
								draw_character(menuwidth,menuheight,'-');
								draw_character(menuwidth+1,menuheight,'>');
								}
								break;
							case 'd':
								if((position == 1) || (position == 3)){
								draw_character(menuwidth,menuheight,' ');
								draw_character(menuwidth+1,menuheight,' ');
								menuwidth += 17;
								position +=1;
								draw_character(menuwidth,menuheight,'-');
								draw_character(menuwidth+1,menuheight,'>');
								}
								break;
							case 'e':
								if(position == 1){
									Attack(&(temp.spirits[spiritnumber]),&enemy,mainchar.spirits[spiritnumber].attacks.attack1);
								}
								if(position == 2){
									Attack(&(temp.spirits[spiritnumber]),&enemy,mainchar.spirits[spiritnumber].attacks.attack2);
								}
								if(position == 3){
									Attack(&(temp.spirits[spiritnumber]),&enemy,mainchar.spirits[spiritnumber].attacks.attack3);
								}
								if(position == 4){
									Attack(&(temp.spirits[spiritnumber]),&enemy,mainchar.spirits[spiritnumber].attacks.attack4);
								}
								for(int v = 0; mainchar.spirits[v].name!="  ";v++){
									if((count==0)&&(mainchar.spirits[v].health>0)){
									count = 1;
									}
								}
								if(count == 0){
									//endgame();
								}
								if(enemy.health<=0){
								attacking=0;
								attackmenu=0;
								temp.spirits[spiritnumber].experience += enemy.experience;
								}
								position = 1;
								menuheight = 17;
								menuwidth = 37;
								attackmenu = 0;
								count = 0;
								break;
							case 'q':
								attackmenu = 0;
								input = ' ';
								input3 = ' ';
								break;
						}
					}
					printattackoptions(temp.spirits[spiritnumber],enemy);
				}
				if(position == 2){
					mainchar = temp;
					printspirits();
					attackmenu=1;
					position=1;
					int i;
					draw_character(6,1+position*2,'-');
					draw_character(7,1+position*2,'>');
					for(i = 0; mainchar.spirits[i].name!="  ";i++){
					}
					char input2;
					while(attackmenu){
						scanf("%c",&input2);
						switch(input2){
							case 'w':
								if(position>1){
								draw_character(6,1+position*2,' ');
								draw_character(7,1+position*2,' ');
								position--;
								draw_character(6,1+position*2,'-');
								draw_character(7,1+position*2,'>');
								}
								input = ' ';
								input2 = ' ';
								break;
							case 's':
								if(position<i){
								draw_character(6,1+position*2,' ');
								draw_character(7,1+position*2,' ');
								position++;
								draw_character(6,1+position*2,'-');
								draw_character(7,1+position*2,'>');
								}
								input = ' ';
								input2 = ' ';
								break;
							case 'e':
								draw_character(9,17,'-');
								draw_character(10,17,'>');
								goodmvprintw(12,17,"Switch");
								goodmvprintw(24,17,"Stats");
								spiritmenu=1;
								char input1;
								while(spiritmenu){
									scanf("%c",&input1);
									switch(input1){
										case 'a':
											if(spiritmenu==2){
												draw_character(21,17,' ');
												draw_character(22,17,' ');
												draw_character(9,17,'-');
												draw_character(10,17,'>');
												spiritmenu--;
											}
											input = ' ';
											input1 = ' ';
											input2 = ' ';
											break;
										case 'd':
											if(spiritmenu==1){
												draw_character(21,17,'-');
												draw_character(22,17,'>');
												draw_character(9,17,' ');
												draw_character(10,17,' ');
												spiritmenu++;
											}
											input = ' ';
											input1 = ' ';
											input2 = ' ';
											break;
										case 'e':
											if(spiritmenu==1){
											spiritnumber=position-1;
											}
											if(spiritmenu==2){
											mainchar = temp;
											printstats(position-1);
											printspirits();
											draw_character(9,17,'-');
											draw_character(10,17,'>');
											goodmvprintw(12,17,"Switch");
											goodmvprintw(24,17,"Stats");
											draw_character(6,1+position*2,'-');
											draw_character(7,1+position*2,'>');
											spiritmenu=1;
											}
											input = ' ';
											input1 = ' ';
											input2 = ' ';
											break;
										case 'q':
											spiritmenu=0;
											goodmvprintw(9,17,"                    ");
											input = ' ';
											input1 = ' ';
											input2 = ' ';
											break;
										}
								}
								input = ' ';
								input2 = ' ';
								break;
							case 'q':
								attackmenu = 0;
								currentmap.mapname="Maps/BattleScene.txt";
								fillMapArray();
								printmap();
								printattackoptions(temp.spirits[spiritnumber],enemy);
								menuheight = 17;
								menuwidth = 37;
								position = 1;
								input = ' ';
								input2 = ' ';
								break;
						}
					}
				}
				if(position == 3){
				printstats(spiritnumber);
				currentmap.mapname = "Maps/BattleScene.txt";
				fillMapArray();
				printattackoptions(mainchar.spirits[spiritnumber],enemy);
				attacking = 1;
				position = 1;
				attackmenu = 0;
				spiritmenu = 0;
				menuheight = 17;
				menuwidth = 37;
				}
				if(position == 4){
				attacking = 0;
				}
				break;
		}
	}
	mainchar = temp;
	for(int v = 0; mainchar.spirits[v].name!="  ";v++){
		if(mainchar.spirits[v].health>0){
		checkforlevel(v);
		}
	}
}

int randomAttack(spirit temp){
srand(time(NULL));
int randomattack = rand()%4;
	if(randomattack==0){
		return temp.attackpower + temp.attacks.attack1;
	}
	if(randomattack==1){
		return temp.attackpower + temp.attacks.attack2;
	}
	if(randomattack==2){
		return temp.attackpower + temp.attacks.attack3;
	}
	if(randomattack==3){
		return temp.attackpower + temp.attacks.attack4;
	}
}

/**
 *
 */
void printattackoptions(spirit main, spirit npc){
	printmap();
	char* line;
	line = (char*) malloc(sizeof(char)*30);
	goodmvprintw(40,12,main.name);
	sprintf(line,"%d\0",main.health);
	goodmvprintw(48,14,line);
	sprintf(line,"%d\0",main.energy);
	goodmvprintw(65,14,line);
	sprintf(line,"%d\0",npc.health);
	goodmvprintw(8,3,line);
	sprintf(line,"%d\0",npc.level);
	goodmvprintw(32,3,line);
	goodmvprintw(8,2,npc.type);
	goodmvprintw(57,12,"Lv. ");
	sprintf(line,"%d\0",main.level);
	goodmvprintw(61,12,line);
	refresh();
}

/**
 *
 */
void printattacks(spirit temp){
	for(int i=40;i<74;i++){
		for(int j = 17; j<20;j+=2){
			draw_character(i,j,' ');
		}
	}
	goodmvprintw(40,17,temp.attacks.attack1name);
	goodmvprintw(57,17,temp.attacks.attack2name);
	goodmvprintw(40,19,temp.attacks.attack3name);
	goodmvprintw(57,19,temp.attacks.attack4name);
	refresh();
}

/**
 *
 */
void printspirits(){
	currentmap.mapname="Maps/SpiritSelection.txt";
	fillMapArray();
	printmap();
	char* line;
	line = (char*) malloc(sizeof(char)*15);
	goodmvprintw(9,3,mainchar.spirits[0].name);
	sprintf(line,"%d\0",mainchar.spirits[0].health);
	goodmvprintw(42,3,line);
	sprintf(line,"%d\0",mainchar.spirits[0].energy);
	goodmvprintw(56,3,line);
	sprintf(line,"%d\0",mainchar.spirits[0].level);
	goodmvprintw(31,3,line);
	if(mainchar.spirits[1].name!="  "){
		sprintf(line,"%d\0",mainchar.spirits[1].level);
		goodmvprintw(31,5,line);
		goodmvprintw(25,5,"Level");
		goodmvprintw(35,5,"Health");
		goodmvprintw(49,5,"Energy");
		goodmvprintw(9,5,mainchar.spirits[1].name);
		sprintf(line,"%d\0",mainchar.spirits[1].health);
		goodmvprintw(42,5,line);
		sprintf(line,"%d\0",mainchar.spirits[1].energy);
		goodmvprintw(56,5,line);
	}
	if(mainchar.spirits[2].name!="  "){
		sprintf(line,"%d\0",mainchar.spirits[2].level);
		goodmvprintw(31,7,line);
		goodmvprintw(25,7,"Level");
		goodmvprintw(35,7,"Health");
		goodmvprintw(49,7,"Energy");
		goodmvprintw(9,7,mainchar.spirits[2].name);
		sprintf(line,"%d\0",mainchar.spirits[2].health);
		goodmvprintw(42,7,line);
		sprintf(line,"%d\0",mainchar.spirits[2].energy);
		goodmvprintw(56,7,line);
	}
	if(mainchar.spirits[3].name!="  "){
		sprintf(line,"%d\0",mainchar.spirits[3].level);
		goodmvprintw(31,9,line);
		goodmvprintw(25,9,"Level");
		goodmvprintw(35,9,"Health");
		goodmvprintw(49,9,"Energy");
		goodmvprintw(9,9,mainchar.spirits[3].name);
		sprintf(line,"%d\0",mainchar.spirits[3].health);
		goodmvprintw(42,9,line);
		sprintf(line,"%d\0",mainchar.spirits[3].energy);
		goodmvprintw(56,9,line);
	}
	if(mainchar.spirits[4].name!="  "){
		goodmvprintw(25,11,"Level");
		sprintf(line,"%d\0",mainchar.spirits[4].level);
		goodmvprintw(31,11,line);
		goodmvprintw(35,11,"Health");
		goodmvprintw(49,11,"Energy");
		goodmvprintw(9,11,mainchar.spirits[4].name);
		sprintf(line,"%d\0",mainchar.spirits[4].health);
		goodmvprintw(42,11,line);
		sprintf(line,"%d\0",mainchar.spirits[4].energy);
		goodmvprintw(56,11,line);
	}
	if(mainchar.spirits[5].name!="  "){
		goodmvprintw(25,13,"Level");
		sprintf(line,"%d\0",mainchar.spirits[4].level);
		goodmvprintw(31,13,line);
		goodmvprintw(35,13,"Health");
		goodmvprintw(49,13,"Energy");
		goodmvprintw(9,13,mainchar.spirits[5].name);
		sprintf(line,"%d\0",mainchar.spirits[5].health);
		goodmvprintw(42,13,line);
		sprintf(line,"%d\0",mainchar.spirits[5].energy);
		goodmvprintw(56,13,line);
	}
	refresh();
}

/**
 *
 */
void goodmvprintw(int x, int y, char* line){
	int i = 0;
	while(line[i]!='\0'){
		draw_character(x,y,line[i]);
		i++;
		x++;
	}
	refresh();
}

void managespirits(){
	int attacking = 1;
	char input;
	int spiritnumber;
	int count;
	int spiritmenu = 1;
	printspirits();
	int attackmenu=1;
	int position=1;
	int spiritnumber1 = 0;
	int i;
	for(i = 0; mainchar.spirits[i].name!='\0';i++){
	}
	while(attackmenu){
		scanf("%c",&input);
			switch(input){
				case 'w':
					if(position>1){
					draw_character(6,1+position*2,' ');
					draw_character(7,1+position*2,' ');
					position--;
					draw_character(6,1+position*2,'-');
					draw_character(7,1+position*2,'>');
					}
					break;
				case 's':
					if(position<i){
					draw_character(6,1+position*2,' ');
					draw_character(7,1+position*2,' ');
					position++;
					draw_character(6,1+position*2,'-');
					draw_character(7,1+position*2,'>');
					}
					break;
				case 'e':
					draw_character(9,17,'-');
					draw_character(10,17,'>');
					goodmvprintw(12,17,"Switch");
					goodmvprintw(24,17,"Stats");
					while(spiritmenu){
						scanf("%c",&input);
						switch(input){
							case 'a':
								if(spiritmenu==2){
								draw_character(21,17,' ');
								draw_character(22,17,' ');
								draw_character(9,17,'-');
								draw_character(10,17,'>');
								spiritmenu--;
								}
								break;
							case 'd':
								if(spiritmenu==1){
								draw_character(21,17,'-');
								draw_character(22,17,'>');
								draw_character(9,17,' ');
								draw_character(10,17,' ');
								spiritmenu++;
								}
								break;
							case 'e':
								if(spiritmenu==1){
									printspirits();
									int attackmenu1 = 1;
									int spiritmenu1 = 0;
									int newspiritnumber = position;
									int position1 = 0;
									while(attackmenu1){
										scanf("%c",&input);
										switch(input){
											case 'w':
												if(position1>1){
												draw_character(6,1+position*2,' ');
												draw_character(7,1+position*2,' ');
												position--;
												draw_character(6,1+position*2,'-');
												draw_character(7,1+position*2,'>');
												}
												break;
											case 's':
												if(position1<i){
												draw_character(6,1+position*2,' ');
												draw_character(7,1+position*2,' ');
												position++;
												draw_character(6,1+position*2,'-');
												draw_character(7,1+position*2,'>');
												}
												break;
											case 'e':
												draw_character(9,17,'-');
												draw_character(10,17,'>');
												goodmvprintw(12,17,"Switch");
												goodmvprintw(24,17,"Stats");
												spiritmenu1 = 1;
												while(spiritmenu1){
													scanf("%c",&input);
													switch(input){
														case 'a':
															if(spiritmenu1==2){
															draw_character(21,17,' ');
															draw_character(22,17,' ');
															draw_character(9,17,'-');
															draw_character(10,17,'>');
															spiritmenu1--;
															}
															break;
														case 'd':
															if(spiritmenu1==1){
															draw_character(21,17,'-');
															draw_character(22,17,'>');
															draw_character(9,17,' ');
															draw_character(10,17,' ');
															spiritmenu1++;
															}
															break;
														case 'e':
															if(spiritmenu1==1){
																spirit temp = mainchar.spirits[newspiritnumber];
																mainchar.spirits[newspiritnumber] = mainchar.spirits[position1];
																mainchar.spirits[position1] = temp;
															}
															if(spiritmenu1==2){
															printstats(spiritnumber1);
															currentmap.mapname = "Maps/SpiritSelection.txt";
															fillMapArray();
															printmap();
															}
															break;
														case 'q':
															spiritmenu1=0;
															goodmvprintw(9,17,"                    ");
															break;
													}
												}
												break;
											case 'q':
												printspirits();
												draw_character(6,1+position*2,'-');
												draw_character(7,1+position*2,'>');
												break;
											}

										}
								if(spiritmenu==2){
								printstats(spiritnumber);
								currentmap.mapname="Maps/SpiritSelection.txt";
								fillMapArray();
								printmap();
								}
								break;
							case 'q':
								spiritmenu=0;
								goodmvprintw(9,17,"                    ");
								break;
							}
						}
					}
					break;
				case 'q':
					attackmenu = 0;
					currentmap.mapname = previousmapname;
					fillMapArray();
					printmap();
					break;
				}
			}
}

void printstats(int spiritnumber){
	currentmap.mapname = "Maps/CharacterStats.txt";
	fillMapArray();
	int x = 1;
	printmap();
	for(int i = 0; i<13; i++){
		if(mainchar.item[i].name!="  "){
		goodmvprintw(4,10+i,mainchar.item[i].name);
		}
	}
	char* line;
	line = (char*) malloc(sizeof(char)*15);
	sprintf(line,"%d\0",mainchar.spirits[spiritnumber].health);
	goodmvprintw(32,10,line);
	sprintf(line,"%d\0",mainchar.spirits[spiritnumber].maxhealth);
	goodmvprintw(32,11,line);
	sprintf(line,"%d\0",mainchar.spirits[spiritnumber].energy);
	goodmvprintw(32,12,line);
	sprintf(line,"%d\0",mainchar.spirits[spiritnumber].maxenergy);
	goodmvprintw(32,13,line);
	sprintf(line,"%d\0",mainchar.spirits[spiritnumber].alignment);
	goodmvprintw(32,14,line);
	sprintf(line,"%d\0",mainchar.spirits[spiritnumber].attackpower);
	goodmvprintw(32,16,line);
	sprintf(line,"%d\0",mainchar.spirits[spiritnumber].defense);
	goodmvprintw(32,17,line);
	sprintf(line,"%d\0",mainchar.spirits[spiritnumber].armor);
	goodmvprintw(32,18,line);
	sprintf(line,"%d\0",mainchar.spirits[spiritnumber].speed);
	goodmvprintw(32,19,line);
	goodmvprintw(32,21,mainchar.spirits[spiritnumber].name);
	sprintf(line,"%d\0",mainchar.spirits[spiritnumber].level);
	goodmvprintw(32,22,line);
	char input;
	while(x){
		scanf("%c",&input);
		if(input == 'q'){
		x=0;
		}
	}
}