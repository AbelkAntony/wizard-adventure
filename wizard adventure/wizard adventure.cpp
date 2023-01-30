#include <iostream>
using namespace std;

class Character
{
private:
	string name;
	int maxHealth;
	int currentHealth;
	int damagePoint;
	int defence;
	int healing;
	int agility;
public:
	Character(string name, int health, int damagePoint, int defence, int healing, int agility)
	{
		this->name = name;
		this->maxHealth = health;
		this->currentHealth = health;
		this->damagePoint = damagePoint;
		this->defence = defence;
		this->healing = healing;
		this->agility = agility;
	}
	virtual string GetName()
	{
		return name;
	}
	int GetHealth()
	{
		return currentHealth;
	}
	int GetDamage()
	{
		return damagePoint;
	}
	int GetAgility()
	{
		return agility;
	}
	virtual void TakeDamage(int _damage)
	{
		int damage = (_damage - defence);
		currentHealth = currentHealth - damage;
		cout << "\nCause damage : " << _damage << endl;
	}
	void DisplayAllStatus()
	{
		cout << "NAME : " << name << endl;
		cout << "HEALTH : " << maxHealth << endl;
		cout << "DAMAGE POINT : " << damagePoint << endl;
		cout << "DEFENCE POWER : " << defence << endl;
		cout << "HEALING POINT : " << healing << endl;

	}
	void DisplayHealthStatus()
	{
		cout << endl << name << "'s health : " << currentHealth;
	}
	virtual void Heal()
	{
		if (maxHealth == currentHealth)
			cout << endl << name << "'s health is already full\n";
		else if (currentHealth + healing > maxHealth)
		{
			int tempHeal;
			tempHeal = (maxHealth - currentHealth);
			currentHealth += tempHeal;
			cout << "/n" << name << "'s health is added by " << tempHeal;
		}
		else
		{
			currentHealth += healing;
			cout << "\n" << name << "'s health is added by " << healing;
		}
	}
	virtual int RunAwayFromAttack(Character* character1, Character* character2)
	{
		int totalAgility = character1->GetAgility() + character2->GetAgility();
		int percentageOfAgility = (character1->GetAgility() * 100) / totalAgility;
		srand(time(0));
		int chance;
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
public:
	Wizard(string name) :Character(name, 100, 35, 10, 50, 10)
	{}
	~Wizard() {}
};

class Dragon : public Character
{
public:
	Dragon() :Character("Dragon", 100, 25, 10, 40, 15)
	{}
	~Dragon() {}
};

class GamePlay
{
private:
	//variables
	int run = 0;
	int round;
	int damage;
	Character* player;
	Character* enemy;
	string name;
	//function
	void DisplayGameTitle()
	{
		cout << "\n				    	WIZARD ADVENTURE\n\n";
	}
	void EnemyCharacterCreation()
	{
		enemy = new Dragon();
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
		return run;
	}
	int WizardAdventureMainMenu()
	{
		int secondoption;
		int option;
		while (true)
		{
			cout << "\nDO YOU WANT TO EXPLORE NEW WORLD OF FANTACY\n1. YES\n2. NO\nENTER YOUR CHOISE : ";
			cin >> option;
			switch (option)
			{
			case 1:

				EnemyCharacterCreation();
				run = PlayGame();
				break;
			case 2:
				cout << "\nARE YOU SURE WANT TO GO BACK\n1. YES\n2. NO\nENTER YOUR CHOISE : ";
				cin >> secondoption;
				if (secondoption == 2)
				{
					EnemyCharacterCreation();
					run = PlayGame();
					break;
				}
				else if (secondoption == 1)
				{
					exit(0);
				}
				else
				{
					cout << "ENTERED OPTION IS NOT AVAILABLE SO CHOOSING DEFAULT OPTION NO";
					exit(0);
				}
			default:
				cout << "ENTERED OPTION IS NOT AVAILABLE SO CHOOSING DEFAULT OPTION NO";
				break;
			}
		}

	}
public:
	void WizardAdventure()
	{
		//display game title
		DisplayGameTitle();
		//character selection
		PlayerCharacterCreation();
		//DisplayStoryOfWizardAdventure();
		WizardAdventureMainMenu();

	}
};

int main()
{
	//gameplay
	GamePlay game;
	game.WizardAdventure();
	return 0;
}
