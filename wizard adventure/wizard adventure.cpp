#include <iostream>
using namespace std;
class Character
{
private:
	string name;
	int maxHealth;
	int health;
	int damagePoint;
	int defence;
	int healing;
public:
	Character(string name, int health, int damagePoint, int defence, int healing)
	{
		this->name = name;
		this->maxHealth = health;
		this->health = health;
		this->damagePoint = damagePoint;
		this->defence = defence;
		this->healing = healing;
	}
	virtual string GetName()
	{
		return name;
	}
	int GetHealth()
	{
		return health;
	}
	int GetDamage()
	{
		return damagePoint;
	}
	virtual void TakeDamage(int _damage)
	{
		int damage = (_damage - defence);
		health = health - damage;
		cout << "\nCause damage : " << _damage << endl;
	}
	void MainStatus()
	{
		cout << "NAME : " << name << endl;
		cout << "HEALTH : " << maxHealth << endl;
		cout << "DAMAGE POINT : " << damagePoint << endl;
		cout << "DEFENCE POWER : " << defence << endl;
		cout << "HEALING POINT : " << healing << endl;

	}
	void Status()
	{
		cout << endl << name << "'s health : " << health;
	}
	virtual void Heal()
	{
		if (maxHealth == health)
			cout << endl << name << "'s health is already full\n";
		else if (health + healing > maxHealth)
		{
			int tempheal;
			tempheal = (maxHealth - health);
			health += tempheal;
			cout << "/n" << name << "'s health is added by " << tempheal;
		}
		else
		{
			health += healing;
			cout << "\n" << name << "'s health is added by " << healing;
		}
	}
	virtual int Run()
	{
		srand(time(0));
		int chance = 0;
		chance = rand() % 2;
		if (chance == 0)
		{
			cout << name << " TRY'S TO RAN AWAY SORRY BUT CAN'T RAN AWAY \n";
			return chance;
		}
		else
		{
			cout << name << " RUN AWAY\n";
			return chance;
		}
	}
};

class Wizard : public Character
{
public:
	Wizard(string name) :Character(name, 100, 35, 10, 50)
	{}
	~Wizard() {}
};

class Enemy : public Character
{
public:
	Enemy(string name, int health, int damagePoint, int defence, int healing) :Character(name, health, damagePoint, defence, healing)
	{}
	~Enemy() {}
};

class GamePlay
{
private:
	//variables
	int round;
	int damage;
	Character* player;
	Character* enemy;
	string name;
	//function
	void GameTitle()
	{
		cout << "\n				    	WIZARD ADVENTURE\n\n";
	}
	void CharacterCreation()
	{
		cout << "ENTER YOUR NAME : ";
		cin >> name;
		player = new Wizard(name);
	}
	void MainStatus()
	{
		cout << "\nPLAYER\n";
		player->MainStatus();
		cout << "\nENEMY\n";
		enemy->MainStatus();
	}
	void Status()
	{
		player->Status();
		enemy->Status();
	}
	void EnemyGameRound()
	{
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
			damage = enemy->GetDamage();
			player->TakeDamage(damage);
		}
		else if (enemy->GetHealth() < health10Percentage)
		{
			int run = enemy->Run();
			if (run == 0)
			{
			}
			else if (run == 1)
			{
				cout << player->GetName() << " wins";
			}
		}
	}

	void PlayerGameRound()
	{
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
			int run = player->Run();
			if (run == 0)
				break;
			else if (run == 1)
			{
				cout << player->GetName() << " lose";
				exit(0);
			}
		}
		default:
			cout << "\nENTERED OPTION IS NOT AVAILABLE SO CHOOSING DEFAULT OPTION ATTACK";
			damage = player->GetDamage();
			enemy->TakeDamage(damage);
		}
	}
	void PlayGame()
	{
		//enemy created
		enemy = new Enemy("Dragon", 100, 25, 10, 40);
		MainStatus();
		round = 1;
		while (player->GetHealth() > 0 && enemy->GetHealth() > 0)
		{
			cout << "\n\nROUND : " << round << endl;
			cout << endl << player->GetName() << "'s Turn choose your option\n";
			PlayerGameRound();
			Status();
			cout << endl << endl << enemy->GetName() << "'s Turn\n";
			EnemyGameRound();
			Status();
			round++;
		}
	}
public:
	void Play()
	{
		//display game title
		GameTitle();
		//character selection
		CharacterCreation();
		PlayGame();
	}
};

int main()
{
	//gameplay
	GamePlay game;
	game.Play();
	return 0;
}