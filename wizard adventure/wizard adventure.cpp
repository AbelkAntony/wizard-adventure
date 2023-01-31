#include <iostream>
using namespace std;

class Character
{
private:
	int agility;
	int baseDefence;
	int baseDamagePoint;
protected:
	int defence;
	int damagePoint;
	int experiencePoint;
	int level;
	string name;
	int maxHealth;
	int currentHealth;
public:
	Character(string name, int health, int damagePoint, int defence, int agility)
	{
		this->name = name;
		this->maxHealth = health;
		this->currentHealth = health;
		this->damagePoint = damagePoint;
		baseDamagePoint = damagePoint;
		this->defence = defence;
		baseDefence = defence;
		this->agility = agility;
	}


	void SetDamage() { damagePoint = damagePoint + (baseDamagePoint * (level / 100)); }
	void SetDefence() { defence = defence + (baseDefence * (level / 100)); }

	virtual string GetName() { return name; }
	int GetHealth() { return currentHealth; }
	int GetDamage() { return damagePoint; }
	int GetAgility() { return agility; }
	int GetLevel() { return level; }

	virtual void TakeDamage(int _damage)
	{
		int damage = (_damage - defence);
		currentHealth = currentHealth - damage;
		cout << "\nCause damage : " << _damage << endl;
	}
	virtual	void DisplayAllStatus()
	{
		cout << "NAME : " << name << endl;
		cout << "HEALTH : " << maxHealth << endl;
		cout << "DAMAGE POINT : " << damagePoint << endl;
		cout << "DEFENCE POWER : " << defence << endl;
		cout << "LEVEL : " << level << endl;
	}



	void DisplayHealthStatus() { cout << endl << name << "'s health : " << currentHealth; }

	virtual void Heal() {}

	virtual int RunAwayFromAttack(Character* character1, Character* character2)
	{
		int totalAgility = character1->GetAgility() + character2->GetAgility();
		int percentageOfAgility = (character1->GetAgility() * 100) / totalAgility;
		int chance;
		srand(time(0));
		chance = rand() % 100;
		if (chance <= percentageOfAgility)
		{
			cout << name << " RUN AWAY\n";
			return 1;
		}
		else
		{
			cout << name << " TRY'S TO RAN AWAY SORRY BUT CAN'T RAN AWAY \n";
			return 0;
		}
	}
};

class Wizard : public Character
{
private:
	int baseCoin;
	int coin;
	int healthPortion = 0;
	int healingLowerLimit = maxHealth * .2;
	int healingUpperlimit = maxHealth * .4;
	int randomHealing;
	int xpLimit = 5;
public:
	Wizard(string name) :Character(name, 100, 35, 10, 10)
	{
		level = 1;
		experiencePoint = 0;
		baseCoin = 100;
		coin = 100;
	}

	void DisplayAllStatus()
	{
		cout << "NAME : " << name << endl;
		cout << "HEALTH : " << maxHealth << endl;
		cout << "DAMAGE POINT : " << damagePoint << endl;
		cout << "DEFENCE POWER : " << defence << endl;
		cout << "LEVEL : " << level << endl;
		cout << "XP : " << experiencePoint << "/" << xpLimit << endl;
		cout << "HEALING PORTION :" << healthPortion << endl;
		cout << "COINS : " << coin;
	}

	int GetCoin() { return coin; }
	int GetPortion() { return healthPortion; }

	void SetCoin(int value) { coin = coin - value; }
	void SetHealthPortion() { healthPortion++; }

	void TakeCoins(int _level)
	{
		coin = coin + baseCoin * ((_level * 10) / 100);
	}

	void Heal()
	{
		srand(time(0));
		randomHealing = (rand() % (healingUpperlimit - healingLowerLimit + 1)) + healingLowerLimit;
		if (healthPortion != 0)
		{
			if (maxHealth == currentHealth)
				cout << endl << name << "'s health is already full\n";
			else if (currentHealth + randomHealing > maxHealth)
			{
				int tempHeal;
				tempHeal = (maxHealth - currentHealth);
				currentHealth += tempHeal;
				cout << "/n" << name << "'s health is added by " << tempHeal;
				healthPortion--;
			}
			else
			{
				currentHealth += randomHealing;
				cout << "\n" << name << "'s health is added by " << randomHealing;
				healthPortion--;
			}

		}
		else
		{
			cout << "YOU DO NOT HAVE ANY HEALTH PORTION TO HEAL";
		}
	}


	void SetLevel()
	{
		while (experiencePoint >= xpLimit)
		{
			level++;
			cout << "Your Level up to" << level << endl;
			experiencePoint = experiencePoint - xpLimit;
			xpLimit = xpLimit + (xpLimit * .3);
			cout << "current XP" << experiencePoint << endl;
			SetDamage();
			SetDefence();
		}
	}
	void SetXp(int enemylevel)
	{
		int tempXp;
		int tempLevel = level - enemylevel;
		if (tempLevel == -3)
		{
			srand(time(0));
			tempXp = (rand() % (5 - 1 + 1)) + 1;
			experiencePoint = tempXp;
			cout << "Your XP increase by :" << tempXp;
			SetLevel();
		}
	}
	void SetXp(int xp, int _xp)
	{
		experiencePoint += xp;
		cout << "Your XP increase by :" << xp;
		SetLevel();
	}
	~Wizard() {}
};

class Dragon : public Character
{
private:
	int healthPortionDropPercentage;
	int healing;
public:
	Dragon(string name, int health, int damagePoint, int defence, int agility) :Character(name, health, damagePoint, defence, agility)
	{
		srand(time(0));
		healthPortionDropPercentage = 25;
		healing = 30;
	}
	void Heal()
	{
		currentHealth += healing;
		cout << "\n" << name << "'s health is added by " << healing;
	}

	void SetLevel(int _level, int area)
	{
		int tempLevel;
		int maxLowLevel = _level - 3;
		int maxHighLevel = _level + 3;
		srand(time(0));
		tempLevel = (rand() % (maxHighLevel - maxLowLevel + 1)) + maxLowLevel;
		if (tempLevel <= 0)
		{
			level = 1;
			SetDamage();
			SetDefence();
		}
		else
		{
			level = tempLevel;
			SetDamage();
			SetDefence();
		}
	}
	void SetLevel(int _level)
	{
		level = _level;
		SetDamage();
		SetDefence();
	}

	int GetHealthPortionDropPercentage() { return healthPortionDropPercentage; }

	~Dragon() {}
};

class GamePlay
{
private:
	//variables
	int run = 0;
	int reviveValue = 70;
	int round;
	int damage;
	Wizard* player;
	Dragon* enemy;
	string name;
	//function
	void healthPortionDropingByEnemy()
	{
		int option;
		srand(time(0));
		int chance;
		chance = rand() % 100;
		if (chance <= enemy->GetHealthPortionDropPercentage())
		{
			player->SetHealthPortion();
			cout << "\nYOU GAINED A HEALTH PORTION";
			cout << "\nDo you want to heal ? \n1. Yes\n2. No";
			cin >> option;
			if (option == 1)
			{
				player->Heal();
			}
		}
	}
	void DisplayGameTitle()
	{
		cout << "\n				    	WIZARD ADVENTURE\n\n";
	}

	void EnemyCharacterCreation(int levelOfPlayer, int area)
	{
		switch (area)
		{
		case 1:
			enemy = new Dragon("Adelaid", 100, 15, 10, 5);
			break;
		case 2:
			enemy = new Dragon("Smite", 125, 30, 15, 5);
			area = 21;
			break;
		case 3:
			enemy = new Dragon("Arman", 150, 40, 20, 5);
			area = 41;
			break;
		case 4:
			enemy = new Dragon("Darksmoke", 200, 45, 25, 5);
			area = 61;
			break;
		}
		if (levelOfPlayer <= area)
			enemy->SetLevel(area);
		else if (levelOfPlayer > area)
			enemy->SetLevel(levelOfPlayer, area);
	}

	void PlayerCharacterCreation()
	{
		cout << "ENTER YOUR NAME : ";
		cin >> name;
		player = new Wizard(name);
	}

	void DisplayAllDetailsOfCharacters()
	{
		cout << "\nPLAYER\n";
		player->DisplayAllStatus();
		cout << "\nENEMY\n";
		enemy->DisplayAllStatus();
	}
	void HealthStatus()
	{
		player->DisplayHealthStatus();
		enemy->DisplayHealthStatus();
	}
	int EnemyGameRound()
	{
		cout << endl << endl << enemy->GetName() << "'s Turn\n";
		int health20Percentage = (enemy->GetHealth()) * .2;
		int health10Percentage = (enemy->GetHealth()) * .1;
		if (enemy->GetHealth() > health20Percentage)
		{
			damage = enemy->GetDamage();
			player->TakeDamage(damage);
		}
		else if (enemy->GetHealth() < health20Percentage && enemy->GetHealth() > health10Percentage)
		{
			enemy->Heal();
		}
		else if (enemy->GetHealth() < health10Percentage)
		{
			run = enemy->RunAwayFromAttack(enemy, player);
			if (run == 0)
			{
			}
			else if (run == 1)
			{
				cout << player->GetName() << " wins";
				return run;
			}
		}
		HealthStatus();
		return run;
	}

	int PlayerGameRound()
	{
		cout << endl << player->GetName() << "'s Turn choose your option\n";
		int option;
		cout << "\n1. Attack\n2. Heal\n3. Run\nEnter your option : ";
		cin >> option;
		switch (option)
		{
		case 1:
			damage = player->GetDamage();
			enemy->TakeDamage(damage);
			break;
		case 2:
			player->Heal();
			break;
		case 3:
		{
			run = player->RunAwayFromAttack(player, enemy);
			if (run == 0)
				break;
			else if (run == 1)
			{
				cout << player->GetName() << " lose";
				return run;
			}
		}
		default:
			cout << "\nENTERED OPTION IS NOT AVAILABLE SO CHOOSING DEFAULT OPTION ATTACK";
			damage = player->GetDamage();
			enemy->TakeDamage(damage);
		}
		HealthStatus();
		return run;
	}
	int CharacterTurnDecider()
	{
		if (enemy->GetAgility() < player->GetAgility())
		{
			run = PlayerGameRound();
			if (run == 1)
				return run;
			run = EnemyGameRound();
			if (run == 1)
				return run;
		}
		else
		{
			run = EnemyGameRound();
			if (run == 1)
				return run;
			run = PlayerGameRound();
			if (run == 1)
				return run;
		}
		return run;
	}
	void DisplayWinner()
	{
		int option;
		if (player->GetHealth() <= 0)
		{
			int choise;
			cout << "\nYOU LOSE THE BATTLE";
			cout << endl << reviveValue << " Points to Revive \n1. Yes\n2. No\nEnter your choise";
			cin >> choise;
			if (choise == 1)
			{
				reviveValue += 30;
				if (player->GetCoin() > reviveValue)
					player->SetCoin(reviveValue);
				WizardAdventureMainMenu();
			}
			else
				exit(0);
		}
		else if (enemy->GetHealth() <= 0)
		{
			cout << "\nYOU WIN THE BATTLE";
			player->TakeCoins(enemy->GetLevel());
			player->SetXp(enemy->GetLevel());
			if (player->GetPortion() > 0)
			{
				cout << "\nDo you want to heal?\n1. Yes\n2. No\n";
				cin >> option;
				if (option == 1)
					player->Heal();
			}
		}
	}
	int PlayGame()
	{
		DisplayAllDetailsOfCharacters();
		round = 1;
		while (player->GetHealth() > 0 && enemy->GetHealth() > 0)
		{
			cout << "\n\nROUND : " << round << endl;
			run = CharacterTurnDecider();
			if (run == 1)
				return run;
			round++;
		}
		DisplayWinner();
		return run;
	}

	void ShopPurchase(int option)
	{
		switch (option)
		{
		case 1:
			player->SetXp(100, 1);
			player->SetCoin(50);
			break;
		case 2:
			player->SetHealthPortion();
			player->SetCoin(50);
			break;
		default:
			break;
		}
	}

	int DisplayItemsInShop()
	{
		int option;
		cout << "\n1. XP potions (100xp) \n Price = 50 coins";
		cout << "\n\n2. HP portion (1 Portion) Price = 10 coins";
		cout << "\n\n3. Exit shop\n";
		cin >> option;
		return option;
	}

	void Shop()
	{
		int option = 0;
		while (option != 3)
		{
			cout << "\nYou discover a Shop\n";
			option = DisplayItemsInShop();
			ShopPurchase(option);
		}
	}

	void Chest()
	{
		cout << "\nYou found a chest\n";
		player->TakeCoins(player->GetLevel());
		srand(time(0));
		int numberOfItems = 1 + rand() % (4 - 1 + 1);
		for (int x = 0; x < numberOfItems; x++)
		{
			int item = rand() % 2;
			switch (item)
			{
			case 0:
				cout << "You get XP" << endl;
				player->SetXp(player->GetLevel());
				break;
			case 1:
				cout << "You got Healing Portion" << endl;
				player->SetHealthPortion();
				break;
			}
		}
	}
	int Explore()
	{
		srand(time(0));
		int option = rand() % 3;
		switch (option)
		{
		case 0:
			run = PlayGame();
			return run;
			break;
		case 1:
			Chest();
			return 1;
			break;
		case 2:
			Shop();
			return 1;
			break;
		default:
			return 1;
		}
	}
	int AreaWiseGame(int area)
	{
		EnemyCharacterCreation(player->GetLevel(), area);
		int secondoption;
		int option;
		while (true)
		{
			cout << "\nDO YOU WANT TO EXPLORE NEW AREA IN WORLD OF DRAGONS\n1. YES\n2. NO\nENTER YOUR CHOISE: ";
			cin >> option;
			switch (option)
			{
			case 1:
				run = Explore();
				break;
			case 2:
				cout << "\nARE YOU SURE WANT TO GO BACK\n1. YES\n2. NO\nENTER YOUR CHOISE : ";
				cin >> secondoption;
				if (secondoption == 2)
				{
					run = Explore();
					break;
				}
				else if (secondoption == 1)
				{
					return 1;
				}
			default:
				cout << "ENTERED OPTION IS NOT AVAILABLE SO CHOOSING DEFAULT OPTION NO\n";
				return 1;
				break;
			}
		}
	}

	void DisplayArea()
	{
		cout << "\nAvailable Area\n";
		cout << "1. Forest\n2. Beach \n3. Volcano \n4. GraveYard \n5. Exit Game\n";
		cout << "Which area do you want to explore\n";
	}

	int AreaSelection()
	{

		int area;
		DisplayArea();
		cin >> area;
		return area;
	}
	void WizardAdventureMainMenu()
	{
		while (true)
		{
			int area = AreaSelection();
			if (area == 5)
				exit(0);
			AreaWiseGame(area);
		}

	}
	void DisplayStoryOfWizardAdventure()
	{
		cout << "Hi Chef,\nYou are a king in your world.\nThe last war was with the God of DRAGON's\nUnfortunatly you lose your battle. \nSad part is that they kidnap your QUEEN \nYou decided to go to the God of DRAGON's world.  \nFind your QUEEN and bring her back to your MANISON\nBe a warrior and figth till you find your QUEEN\n\nGOOD LUCK CHEF";
	}
public:
	void WizardAdventure()
	{
		//display game title
		DisplayGameTitle();
		//character selection
		PlayerCharacterCreation();
		DisplayStoryOfWizardAdventure();
		WizardAdventureMainMenu();
		delete player;
		delete enemy;
	}
};

int main()
{
	//gameplay
	GamePlay game;
	game.WizardAdventure();
	return 0;
}
