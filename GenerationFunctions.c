// Formula for the structures of all non-player-characters.
#include <time.h>
#include <stdlib.h>

//the maximum length a character's name can be
#define MAX_NAME_LENGTH 20

struct character mainchar;

typedef struct attacklist {
	int attack1;
	int attack2;
	int attack3;
	int attack4;
	char *attack1name;
	char *attack2name;
	char *attack3name;
	char *attack4name;
	} attacklist;

typedef struct spirit{
	char *name;
	char *type;
	int defense;
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
	attacklist attacks;
} spirit;

typedef struct items {
	char* name;
	int healthregen;
	int energyregen;
	int armor;
	int equipped;
	int canbeequipped;
	} items;

typedef struct character {
	struct spirit spirits[6];
	struct items item[13];
	} character;

void createattacks(spirit *f);

void levelup(int i){
	spirit temp = mainchar;
	srand(time(NULL));
	int modifier = rand()%3;
	temp.experience = 0;
	temp.level = mainchar.spirits[i].level + 1;
	temp.alignment = mainchar.spirits[i].alignment;
	temp.maxenergy = mainchar.spirits[i].maxenergy + (mainchar.spirits[i].level) * (mainchar.spirits[i].level) + 5 + modifier;
	temp.energy = temp.maxenergy;
	temp.attackpower = mainchar.spirits[i].attackpower + 3 + (modifier+1)/2;
	temp.armor = mainchar.spirits[i].armor;
	temp.speed = mainchar.spirits[i].speed + 5 + (mainchar.spirits[i].level) + (2-modifier);
	mainchar.spirits[i] = temp;
	}

int checkforlevel(int i){
	if(mainchar.spirits[i].experience >= 50*mainchar.spirits[i].level){
		levelup(i);
	}
}

character generatenpc(int level){
	srand(time(NULL));
	int selection = rand()% 2;
	int healthmodifier;
	int energymodifier;
	int speedmodifier;
	int levelmodifier;
	int i;
	spirit randomchar = { .maxhealth = 100, .health = 100, .experience = 0, .level = 1, .alignment = 0, .energy = 50, .maxenergy = 50, .living = 1, .bodyhealth = 100, .maxbodyhealth = 100, .armor = 0, .attackpower = 0, .speed = 10};
		switch(selection){

			case 0:
				healthmodifier = rand()% 3;
				energymodifier = rand()% 5;
				speedmodifier = rand()% 3;
				levelmodifier = rand()% 5;
				randomchar.type = "spirit";
				for(i=0;i<level-2+levelmodifier;i++){
					randomchar.maxhealth = randomchar.maxhealth + 3*(randomchar.level) + healthmodifier;
					randomchar.health = randomchar.maxhealth;
					randomchar.maxenergy = randomchar.maxenergy + 5*(randomchar.level) + energymodifier;
					randomchar.energy = randomchar.maxenergy;
					randomchar.speed = randomchar.speed + randomchar.level + 3 + speedmodifier;
					randomchar.level ++;
				}
				break;
			case 1:
				healthmodifier = rand()% 2;
				energymodifier = rand()% 3;
				speedmodifier = rand()% 4;
				levelmodifier = rand()% 5;
				randomchar.type = "townsman";
				for(i=0;i<level-2+levelmodifier;i++){
					randomchar.maxhealth = randomchar.maxhealth + 2*(randomchar.level) + healthmodifier;
					randomchar.health = randomchar.maxhealth;
					randomchar.maxenergy = randomchar.maxenergy + 3*(randomchar.level) + energymodifier;
					randomchar.energy = randomchar.maxenergy;
					randomchar.speed = randomchar.speed + randomchar.level + 4 + speedmodifier;
					randomchar.level ++;
				}
				break;

		}
	randomchar.experience = randomchar.level*5;
	randomchar.armor = 0;
	createattacks(&randomchar);
	character x;
	x.spirits[0] = randomchar;
return x;
}


void createattacks(spirit *f){
	spirit temp = *f;
	int level = temp.level;
	srand(time(NULL));
	int attackmod = rand()%level;
	//if(level<15){
	temp.attacks.attack1name = "Cut";
	temp.attacks.attack1 = 5;
	temp.attacks.attack2name = "Lunge";
	temp.attacks.attack2 = 10;
	if(level>7){
		temp.attacks.attack3name = "Mangle";
		temp.attacks.attack3 = 15;
	}
	if(level>12){
		temp.attacks.attack4name = "Freighten";
		temp.attacks.attack4 = 8;
	}
	//}
	//else{
	//}
	*f = temp;
}

/* list of all attacks corresponding to integers
struct attacks{

}
*/

/*struct character {
	char *name;
	char *type;
	int maxhealth = 100;
	int health = 100;
	int experience = 0;
	int level = 1;
	int alignment = 0;
	int energy = 50;
	int maxenergy = 50;
	int living = 1;
	int bodyhealth = 100;
	int maxbodyhealth = 100;
	int armor = 0;
	int attackpower = 0;
	int speed = 10;
	struct attacklist attacks;
	} ;*/
