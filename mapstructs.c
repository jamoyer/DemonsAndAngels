#define MAX_MAPNAME_LENGTH 30
#define MAX_MAP_HEIGHT 300
#define MAX_MAP_WIDTH 300

struct map{
	char *mapname;		//the path of the map file.

	char type;		//whether or not the map is a playable(character moves around in it) or some other screen
	int difficulty;		//the difficulty of spirits on the map from 1-100

	int door0_height;
	int door0_width;
	char *door0_map;

	int door1_height;
	int door1_width;
	char *door1_map;

	int door2_height;
	int door2_width;
	char *door2_map;

	int door3_height;
	int door3_width;
	char *door3_map;

	int door4_height;
	int door4_width;
	char *door4_map;

	int door5_height;
	int door5_width;
	char *door5_map;

	int door6_height;
	int door6_width;
	char *door6_map;

	int door7_height;
	int door7_width;
	char *door7_map;

	int door8_height;
	int door8_width;
	char *door8_map;

	int door9_height;
	int door9_width;
	char *door9_map;
};

//Begin playable map struct functions-----------------------------------------------------------------------------------------------------
struct map currentmap;

/**
 *Clears all the currentmap data out.
 */
void clearcurrentmap(){
	currentmap.mapname="";

	currentmap.type='\0';
	currentmap.difficulty=0;

	currentmap.door0_height=MAX_MAP_HEIGHT+1;
	currentmap.door0_width=MAX_MAP_WIDTH+1;
	currentmap.door0_map="";

	currentmap.door1_height=MAX_MAP_HEIGHT+1;
	currentmap.door1_width=MAX_MAP_WIDTH+1;
	currentmap.door1_map="";

	currentmap.door2_height=MAX_MAP_HEIGHT+1;
	currentmap.door2_width=MAX_MAP_WIDTH+1;
	currentmap.door2_map="";

	currentmap.door3_height=MAX_MAP_HEIGHT+1;
	currentmap.door3_width=MAX_MAP_WIDTH+1;
	currentmap.door3_map="";

	currentmap.door4_height=MAX_MAP_HEIGHT+1;
	currentmap.door4_width=MAX_MAP_WIDTH+1;
	currentmap.door4_map="";

	currentmap.door5_height=MAX_MAP_HEIGHT+1;
	currentmap.door5_width=MAX_MAP_WIDTH+1;
	currentmap.door5_map="";

	currentmap.door6_height=MAX_MAP_HEIGHT+1;
	currentmap.door6_width=MAX_MAP_WIDTH+1;
	currentmap.door6_map="";

	currentmap.door7_height=MAX_MAP_HEIGHT+1;
	currentmap.door7_width=MAX_MAP_WIDTH+1;
	currentmap.door7_map="";

	currentmap.door8_height=MAX_MAP_HEIGHT+1;
	currentmap.door8_width=MAX_MAP_WIDTH+1;
	currentmap.door8_map="";

	currentmap.door9_height=MAX_MAP_HEIGHT+1;
	currentmap.door9_width=MAX_MAP_WIDTH+1;
	currentmap.door9_map="";
}

/**
 *Builds all the data for the maps that are loaded onto the screen.
 */

void createbattlemap(){
	clearcurrentmap();
	currentmap.mapname = "Maps/BattleScene.txt";

	currentmap.type='M';
}

void createMaze1map(){
	clearcurrentmap();
	currentmap.mapname="Maps/Maze1undermap1.txt";

	currentmap.type='p';
	currentmap.difficulty=8;

	currentmap.door0_height=0;
	currentmap.door0_width=7;
	currentmap.door0_map="Maps/Cavemap1.txt";

	currentmap.door1_height=26;
	currentmap.door1_width=57;
	currentmap.door1_map="Maps/1map.txt";
}

void createCavemap1(){
	clearcurrentmap();
	currentmap.mapname="Maps/Cavemap1.txt";

	currentmap.type='p';
	currentmap.difficulty=10;

	currentmap.door0_height=0;
	currentmap.door0_width=7;
	currentmap.door0_map="Maps/1map.txt";

	currentmap.door1_height=37;
	currentmap.door1_width=57;
	currentmap.door1_map="Maps/Maze1undermap1.txt";
}

void createTitleMenu(){
	clearcurrentmap();
	currentmap.mapname="Maps/Title.txt";

	currentmap.type='M';
}

void createAbout(){
	clearcurrentmap();
	currentmap.mapname="Maps/About.txt";

	currentmap.type='M';
}

void create0map(){
	clearcurrentmap();
	currentmap.mapname="Maps/0map.txt";

	currentmap.type='p';
	currentmap.difficulty =0;

	currentmap.door0_height=7;
	currentmap.door0_width=13;
	currentmap.door0_map="Maps/Hmap.txt";

	currentmap.door1_height=13;
	currentmap.door1_width=13;
	currentmap.door1_map="";

	currentmap.door2_height=6;
	currentmap.door2_width=24;
	currentmap.door2_map="";

	currentmap.door3_height=8;
	currentmap.door3_width=46;
	currentmap.door3_map="";

	currentmap.door4_height=18;
	currentmap.door4_width=47;
	currentmap.door4_map="";

	currentmap.door5_height=11;
	currentmap.door5_width=66;
	currentmap.door5_map="Maps/1map.txt";
}

void createHmap(){
	clearcurrentmap();
	currentmap.mapname="Maps/Hmap.txt";

	currentmap.type='p';
	currentmap.difficulty=0;

	currentmap.door0_height=7;
	currentmap.door0_width=11;
	currentmap.door0_map="Maps/0map.txt";
}

void create1map(){
	clearcurrentmap();
	currentmap.mapname="Maps/1map.txt";

	currentmap.type='p';
	currentmap.difficulty=5;

	currentmap.door0_height=37;
	currentmap.door0_width=0;
	currentmap.door0_map="Maps/0map.txt";

	currentmap.door1_height=20;
	currentmap.door1_width=9;
	currentmap.door1_map="";

	currentmap.door2_height=72;
	currentmap.door2_width=79;
	currentmap.door2_map="Maps/Maze1undermap1.txt";

	currentmap.door3_height=2;
	currentmap.door3_width=22;
	currentmap.door3_map="Maps/Cavemap1.txt";

	currentmap.door4_height=70;
	currentmap.door4_width=120;
	currentmap.door4_map="";

	currentmap.door5_height=72;
	currentmap.door5_width=123;
	currentmap.door5_map="";

	currentmap.door6_height=75;
	currentmap.door6_width=141;
	currentmap.door6_map="Maps/2map.txt";
}

void create2map(){
	clearcurrentmap();
	currentmap.mapname="Maps/2map.txt";

	currentmap.type='p';
	currentmap.difficulty=20;

	currentmap.door0_height=5;
	currentmap.door0_width=0;
	currentmap.door0_map="Maps/1map.txt";

	currentmap.door1_height=42;
	currentmap.door1_width=87;
	currentmap.door1_map="Maps/3map.txt";

	}

void create3map(){
	clearcurrentmap();
	currentmap.mapname="Maps/3map.txt";

	currentmap.type='p';
	currentmap.difficulty=30;

	currentmap.door0_height=39;
	currentmap.door0_width=1;
	currentmap.door0_map="Maps/4map.txt";

	currentmap.door1_height=0;
	currentmap.door1_width=35;
	currentmap.door1_map="Maps/2map.txt";

	}

void create4map(){
	clearcurrentmap();
	currentmap.mapname="Maps/4map.txt";

	currentmap.type='p';
	currentmap.difficulty=40;

	currentmap.door0_height=42;
	currentmap.door0_width=51;
	currentmap.door0_map="Maps/3map.txt";

	currentmap.door1_height=3;
	currentmap.door1_width=50;
	currentmap.door1_map="Maps/5map.txt";

	}

void create5map(){
	clearcurrentmap();
	currentmap.mapname="Maps/5map.txt";

	currentmap.type='p';
	currentmap.difficulty=70;

	currentmap.door0_height=46;
	currentmap.door0_width=66;
	currentmap.door0_map="Maps/4map.txt";

	}

void createMainMenu(){
	clearcurrentmap();
	currentmap.mapname = "Maps/MainMenuMap.txt";

	currentmap.type='M';
}

void createCharacterStats(){
	clearcurrentmap();
	currentmap.mapname = "Maps/CharacterStats.txt";
	currentmap.type='M';
}