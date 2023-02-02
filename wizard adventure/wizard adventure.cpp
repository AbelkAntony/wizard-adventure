#include <iostream>
using namespace std;

class Character
{
protected:
	int agility;
	int baseDefence;
	int baseDamagePoint;
	int defence;
	int damagePoint;
	int experiencePoint;
	int level;
	string name;
	int maxHealth;
	int currentHealth;
public:

	Character(string _name, int _health, int _damagePoint, int _defence, int _agility)
	{
		name = _name;
		maxHealth = _health;
		currentHealth = _health;
		damagePoint = _damagePoint;
		baseDamagePoint = _damagePoint;
		defence = _defence;
		agility = _agility;
	}

	void SetDamage() { damagePoint = damagePoint + (baseDamagePoint * (level / 100)); }
	void SetDefence() { defence = defence + (baseDefence * (level / 100)); }

	virtual string GetName() { return name; }
	int GetHealth() { return currentHealth; }
	int GetDamage() { return damagePoint; }
	int GetAgility() { return agility; }
	int GetLevel() { return level; }
	int GetDefence() { return defence; }

	virtual void TakeDamage(int damage)
	{
		currentHealth = currentHealth - damage;
		cout << "\nCause damage : " << damage << endl;
	}
	virtual	void DisplayAllStatus()
	{
		cout << "NAME : " << name << endl;
		cout << "HEALTH : " << maxHealth << endl;
		cout << "DAMAGE POINT : " << damagePoint << endl;
		cout << "DEFENCE POWER : " << defence << endl;
		cout << "LEVEL : " << level << endl;
	}

	void DisplayHealthStatus()
	{
		if (currentHealth <= 0)
			cout << endl << name << "'s health : 0\n";
		else
			cout << endl << name << "'s health : " << currentHealth;
	}

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
			cout << name << " \nRUN AWAY\n";
			return 1;
		}
		else
		{
			cout << name << "\n TRY'S TO RAN AWAY SORRY BUT CAN'T RAN AWAY \n";
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
	Wizard(string _name, int _health, int _damagePoint, int _defence, int _agility) : Character(_name, _health, _damagePoint, _defence, _agility)
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
		cout << "COINS : " << coin << endl;
	}

	int GetCoin() { return coin; }
	int GetPortion() { return healthPortion; }

	void SetCoin(int value) { coin = coin - value; }
	void SetHealthPortion() { healthPortion++; }

	void TakeCoins(int _level)
	{
		int _coin = baseCoin * _level;
		coin += _coin;
		cout << "\nYou got " << _coin << "coins\n";
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
		if (tempLevel <= 0)
		{
			srand(time(0));
			tempXp = (rand() % (5 - 1 + 1)) + 1;
			experiencePoint += tempXp;
			cout << "Your XP increase by :" << tempXp;
			SetLevel();
		}
		else
		{
			experiencePoint += enemylevel;
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
protected:
	int healthPortionDropPercentage;
	int healing;
public:
	Dragon(string _name, int _health, int _damagePoint, int _defence, int _agility, int _healthPortionDropPercentage, int _healing) : Character(_name, _health, _damagePoint, _defence, _agility)
	{
		healthPortionDropPercentage = _healthPortionDropPercentage;
		healing = _healing;
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

class Inferno : public Dragon
{
public:
	Inferno() : Dragon("Adelaid-Inferno", 100, 15, 10, 5, 50, 30) {}

};

class Aqua : public Dragon
{
public:
	Aqua() : Dragon("Smite-Aqua", 125, 30, 15, 5, 30, 40) {}

};

class Terra : public Dragon
{
public:
	Terra() : Dragon("Arman-Terra", 150, 40, 20, 5, 30, 35) {}

};

class Shadow : public Dragon
{
public:
	Shadow() : Dragon("Darksmoke-Shadow", 200, 45, 25, 5, 40, 45) {}

};

class AAttack
{
private:
	int fireball = 0;
	int waterGun = 0;
	int earthquake = 0;
	int rejuvenate = 0;
	int solarBeam = 0;
public:
	//getter
	int	GetSolarBeam() { return solarBeam; }
	int GetRejuvenate() { return rejuvenate; }
	int GetEarthquake() { return earthquake; }
	int GetWaterGun() { return waterGun; }
	int GetFireball() { return fireball; }
	//setter
	void SetSolarBeam() { solarBeam = 1; }
	void SetRejuvenate() { rejuvenate = 1; }
	void SetEarthquake() { earthquake = 1; }
	void SetWaterGun() { waterGun = 1; }
	void SetFireball() { fireball = 1; }

	int Attack(char choise)
	{
		if (solarBeam == 1)
		{
			if (choise == 'S' || choise == 's')
			{
				return 4;
			}
		}
		if (rejuvenate == 1)
		{
			if (choise == 'R' || choise == 'r')
			{
				return 0;
			}
		}
		if (earthquake == 1)
		{
			if (choise == 'E' || choise == 'e')
			{
				return 1;
			}
		}
		if (waterGun == 1)
		{
			if (choise == 'W' || choise == 'w')
			{
				return 2;
			}
		}
		if (fireball == 1)
		{
			if (choise == 'F' || choise == 'f')
			{
				return 4;
			}
		}
		return 1;
	}
	int Attack()
	{
		return 2;
	}

	void DisplayAttack()
	{
		cout << "FOR NORMAL ATTACK  PRESS  N\n";
		if (solarBeam == 1)
			cout << "FOR SOLAR BEAM ATTACK PRESS  S\n";
		if (rejuvenate == 1)
			cout << "FOR REJIVENATE ATTACK PRESS  R\n";
		if (earthquake == 1)
			cout << "FOR EARTHQUAKE ATTACK PRESS  E\n";
		if (waterGun == 1)
			cout << "FOR WATER GUN ATTACK  PRESS  W\n";
		if (fireball == 1)
			cout << "FOR FIRE BALL ATTACK  PRESS  F\n";
	}

};

class GamePlay
{
private:
	//variables
	int run = 0;
	int reviveValue = 70;
	int round;
	int damage;
	AAttack* playerAttack = new AAttack();
	AAttack* enemyAttack = new AAttack();
	Wizard* player;
	Dragon* enemy;
	string name;
	int specialAttack = 1;
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
			enemy = new Inferno();
			enemyAttack->Attack(2);
			break;
		case 2:
			enemy = new Aqua();
			enemyAttack->Attack(2);
			area = 21;
			break;
		case 3:
			enemy = new Terra();
			enemyAttack->Attack(2);
			area = 41;
			break;
		case 4:
			enemy = new Shadow();
			enemyAttack->Attack(2);
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
		player = new Wizard(name, 100, 35, 10, 10);
	}

	void DisplayAllDetailsOfCharacters()
	{
		cout << "\nPLAYER\n";
		player->DisplayAllStatus();
		cout << "\n\nENEMY\n";
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
			specialAttack = enemyAttack->Attack();
			Damage(enemy, player, specialAttack, 'a');
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

	void Damage(Character* character1, Character* character2, int specialAttack, char attack)
	{
		if (enemy->GetName() == "Adelaid-Inferno" && (attack == 'E' || attack == 'e'))
		{
			int damage = (character1->GetDamage()) - character2->GetDefence();
			character2->TakeDamage(damage);
		}
		else if (enemy->GetName() == "Smite-Aqua" && (attack == 'F' || attack == 'f'))
		{
			int damage = (character1->GetDamage()) - character2->GetDefence();
			character2->TakeDamage(damage);
		}
		else if (enemy->GetName() == "Darksmoke-Shadow" && (attack == 'S' || attack == 's'))
		{
			int damage = (character1->GetDamage()) - character2->GetDefence();
			character2->TakeDamage(damage);
		}
		else if (enemy->GetName() == "Arman-Terra" && (attack == 'W' || attack == 'w'))
		{
			int damage = (character1->GetDamage()) - character2->GetDefence();
			character2->TakeDamage(damage);
		}
		else
		{
			int damage = (character1->GetDamage() * specialAttack) - character2->GetDefence();
			character2->TakeDamage(damage);
		}
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
			char choise;
			playerAttack->DisplayAttack();
			cin >> choise;
			if (choise == 'R' || choise == 'r')
				player->Heal();
			specialAttack = playerAttack->Attack(choise);
			Damage(player, enemy, specialAttack, choise);
			if (enemy->GetHealth() <= 0)
				return 0;
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
			run = 0;
		}
		HealthStatus();
		return 0;
	}
	int CharacterTurnDecider()
	{
		if (enemy->GetAgility() < player->GetAgility())
		{
			run = PlayerGameRound();
			if (run == 1)
				return run;
			if (enemy->GetHealth() <= 0)
				return 0;
			run = EnemyGameRound();
			if (run == 1)
				return run;
			if (player->GetHealth() <= 0)
				return 0;
		}
		else
		{
			run = EnemyGameRound();
			if (run == 1)
				return run;
			if (player->GetHealth() <= 0)
				return 0;
			run = PlayerGameRound();
			if (run == 1)
				return run;
			if (enemy->GetHealth() <= 0)
				return 0;
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

	void SpellBook()
	{
		srand(time(0));
		int option = rand() % 5 + 1;
		int spellUnlockValue;


		switch (option)
		{
		case 1:
			cout << "You Learn a attacking Using Fireball";
			playerAttack->SetFireball();
			break;
		case 2:
			cout << "You Learn a attacking Using Water gun";
			spellUnlockValue = 2;
			playerAttack->SetWaterGun();
			break;
		case 3:
			cout << "You Learn a attacking Using Earthquake";
			playerAttack->SetEarthquake();
			break;
		case 4:
			cout << "You Learn a attacking Using Rejuvenate";
			playerAttack->SetRejuvenate();
			break;
		case 5:
			cout << "You Learn a attacking Using Solar beam";
			playerAttack->SetSolarBeam();
			break;
		}
	}

	void ShopPurchase(int option)
	{
		switch (option)
		{
		case 1:
			if ((player->GetCoin() - 50) > 0)
			{
				player->SetXp(100, 1);
				player->SetCoin(50);
			}
			else
			{
				cout << "You don't have enough coin";
			}
			break;
		case 2:
			if ((player->GetCoin() - 10) > 0)
			{
				player->SetHealthPortion();
				player->SetCoin(10);
			}
			else
			{
				cout << "You don't have enough coin";
			}
			break;
		case 3:
			if ((player->GetCoin() - 100) > 0)
			{
				SpellBook();
				player->SetCoin(100);
			}
			else
			{
				cout << "You don't have enough coin";
			}
		default:
			break;
		}
	}

	int DisplayItemsInShop()
	{
		int option;
		cout << "\nAVAILABLE COINS :" << player->GetCoin();
		cout << "\n1. XP potions (100xp)  Price = 50 coins";
		cout << "\n2. HP portion (1 Portion) Price = 10 coins";
		cout << "\n3. Spell Book  Price = 100 coins";
		cout << "\n\n4. Exit shop\n";
		cin >> option;
		return option;
	}

	void Shop()
	{
		int option = 0;
		cout << "\nYou discover a Shop\n";
		while (option != 4)
		{
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
				cout << "\nYou get XP" << endl;
				player->SetXp(player->GetLevel());
				break;
			case 1:
				cout << "\nYou got Healing Portion" << endl;
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
			cout << "\nDO YOU WANT TO EXPLORE NEW AREA \n1. YES\n2. NO\nENTER YOUR CHOISE: ";
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
					return 0;
				}
			default:
				cout << "\nENTERED OPTION IS NOT AVAILABLE SO CHOOSING DEFAULT OPTION NO\n";
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
		cout << "\nHi Chef,\nYou are a king in your world.\nThe last war was with the God of DRAGON's\nUnfortunatly you lose your battle. \nSad part is that they kidnap your QUEEN \nYou decided to go to the God of DRAGON's world.  \nFind your QUEEN and bring her back to your MANISON\nBe a warrior and figth till you find your QUEEN\n\nGOOD LUCK CHEF\n";
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
