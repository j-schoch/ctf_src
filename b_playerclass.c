//js. 
//b_playerclass.c
//This code file consists of functions that relate to classes
//of players in deathmatch mode

#include "g_local.h"
#include "m_player.h"
#include "b_playerclass.h"


// CheckClass - This checks to see if a class has been chosen. If not, a message is printed.
// This function is called in the Client_Think function to keep displaying it every frame.
void CheckClass(edict_t *ent)
{
	if(ent->client->resp.udClass < 1)   //Do we already have a class?
	{       //Nope... Send Message
		gi.centerprintf(ent, "Please choose a class:\n\nB - Bomber - Offensive\nH - Hero - Supportive\n");
		//return NULL;
	}
	/*else if(ent->client->resp.udClass == 1)
	{
		return 1;
	}
	else if(ent->client->resp.udClass == 2)
	{
		return 2;
	}*/
}
// Cmd_Class sets the ent->client->resp.udClass value
void Cmd_Class_f(edict_t *ent, char *cmd)
{
	gitem_t		*item;
	//If the player already has an udClass, tell him what it is and return
	if(ent->client->resp.udClass > 0)
	{
		//Let the player know he can't change udClass, and tell him what he is...
		if(ent->client->resp.udClass == 1)
		{
			gi.centerprintf(ent,"Sorry Bomber.\nYou can't change class now.\n");
		}
		else if(ent->client->resp.udClass == 2)
		{
			gi.centerprintf(ent,"Sorry Hero.\nYou can't change class now.\n");
		}
		//Play a sound for the player.
		gi.sound(ent, CHAN_VOICE, gi.soundindex("items/damage2.wav"), 1, ATTN_NORM, 0);
		//Bail out now. We don't want to execute what's below
		return;
	}
	//Otherwise, assign an udClass now...
	gi.cprintf(ent,PRINT_HIGH,"Got: %s\n",cmd);
		
	// confirm class selection
	if(Q_stricmp (cmd, "bomber") == 0)
	{
		ent->client->resp.udClass = 1;

		item = FindItem("Shotgun");
		ent->client->pers.selected_item = ITEM_INDEX(item);
		ent->client->pers.inventory[ent->client->pers.selected_item] = 1;
		ent->client->pers.weapon = item;
		ent->client->pers.lastweapon = item;
		ent->client->newweapon = ent->client->pers.weapon;
		ChangeWeapon (ent);

		item = FindItem("Rocket Launcher");
		ent->client->pers.selected_item = ITEM_INDEX(item);
		ent->client->pers.inventory[ent->client->pers.selected_item] = 1;
		ent->client->pers.weapon = item;
		ent->client->pers.lastweapon = item;
		ent->client->newweapon = ent->client->pers.weapon;
		ChangeWeapon (ent);

		item = FindItem("Rockets");
		Add_Ammo(ent,item,99);

		item = FindItem("Shells");
		Add_Ammo(ent,item,99);

		gi.centerprintf(ent,"You have chosen the Bomber class.\nPrimary: RocketJumper - 1\nSecondary: Shotgun - 2\nGood Luck!\n");
		
	}
	else if(Q_stricmp (cmd, "hero") == 0)
	{
		//js. vampire gun siphons health on hit
		item = FindItem("Vampire");
		ent->client->pers.selected_item = ITEM_INDEX(item);
		ent->client->pers.inventory[ent->client->pers.selected_item] = 1;
		ent->client->pers.weapon = item;
		ent->client->pers.lastweapon = item;
		ent->client->newweapon = ent->client->pers.weapon;
		ChangeWeapon (ent);

		//js. modded to heal with lasers
		item = FindItem("HealBlaster"); 
		ent->client->pers.selected_item = ITEM_INDEX(item);
		ent->client->pers.inventory[ent->client->pers.selected_item] = 1;
		ent->client->pers.weapon = item;
		ent->client->pers.lastweapon = item;
		ent->client->newweapon = ent->client->pers.weapon;
		ChangeWeapon (ent);

		item = FindItem("Cells");
		Add_Ammo(ent,item,200);

		gi.centerprintf(ent,"You have chosen the Hero class.\nPrimary: HealBlaster - 3\nSecondary: Vampire - 4\nGood Luck!\n");
	}
	else
	{
	//For completeness. We should NEVER get here.
		ent->client->resp.udClass = 0;
		gi.centerprintf(ent,"Invalid class selection!\n");
	}

	//Play a sound
	gi.sound(ent, CHAN_VOICE, gi.soundindex("player/male/jump1.wav"), 1, ATTN_NORM, 0);
}