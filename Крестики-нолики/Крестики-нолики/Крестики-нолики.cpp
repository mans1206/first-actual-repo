#include <iostream>
#include <cmath>
#include <random>
#include <stdlib.h>
#include <chrono>

using namespace std;
// Я, конечно, не продвинутый и не опытный ваш ученик)) 
//но решил попытать счастья в выполнении дополнительного условия: увеличил размер поля, теперь оно 4х4.
//Однако для победы необходимо собрать только 3 одинаковых значения.
//По-моему все работает, хотя я не ожидал, что с увеличением количества полей, настолько придется все переписывать, а главное - менять стратегию бота.
//Теперь в игре хоть и нет бесконечной ничьи, побеждает тот игрок, который ходит первым. Это обусловливается только размерами поля, как мне кажется.

enum TCell : char {
	CROSS = 'X',
	ZERO = '0',
	EMPTY = '_'
};

enum TProgress {
	IN_PROGRESS,
	WON_HUMAN,
	WON_AI,
	DRAW
};

struct TCoord {
	size_t y{ 0U };
	size_t x{ 0U };
};

struct TGame {
	TCell** ppField{ nullptr };
	const size_t SIZE{ 4U };
	TCell human;
	TCell ai;
	TProgress progress{ IN_PROGRESS };
size_t turn{ 0U }; // chetnie chisla - hod cheloveka, nechetniye - kompa
};
inline void clearScr()
{
	//system.cls
	std::cout << "\x1B[2J\x1B[H";
}

int32_t __fastcall getRandomNum(int32_t min, int32_t max)
{
	const static auto seed = chrono::system_clock::now().time_since_epoch().count();
	static mt19937_64 generator(seed);
	uniform_int_distribution<int32_t> dis(min, max);
	return dis(generator);
}

void __fastcall initGame(TGame& g)
{
	g.ppField = new TCell * [g.SIZE];
	for (size_t i = 0; i < g.SIZE; i++)
	{
		g.ppField[i] = new TCell[g.SIZE];
	}
	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			g.ppField[y][x] = EMPTY;

		}
	}

	if (getRandomNum(0, 1000) > 500)
	{
		g.human = CROSS;
		g.ai = ZERO;
		g.turn = 0;
	}
	else
	{
		g.human = ZERO;
		g.ai = CROSS;
		g.turn = 1;
	}
}

void __fastcall deinitGame(TGame& g)
{
	for (size_t i = 0; i < g.SIZE; i++)
	{
		g.ppField[i] = new TCell[g.SIZE];
	}
	delete[] g.ppField;
	g.ppField = nullptr;

}

void __fastcall drawGame(const TGame& g)
{
	cout << "    ";
	for (size_t x = 0; x < g.SIZE; x++)
	{
		cout << x + 1 << " ";
	}
	cout << endl;
	for (size_t y = 0; y < g.SIZE; y++)
	{
		cout << " " << y + 1 << " |";
		for (size_t x = 0; x < g.SIZE; x++)
		{
			cout << g.ppField[y][x] << "|";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Human: " << g.human << endl << "Computer: " << g.ai << endl << endl;
}

void __fastcall congrats(const TGame& g)
{
	if (g.progress == WON_HUMAN)
		cout << "Human won! =)" << endl;
	else if (g.progress == WON_AI)
		cout << "Computer won! =(" << endl;
	else if (g.progress == DRAW)
		cout << "Draw! =/" << endl;
}

TProgress getWon(const TGame& g)
{
	//proverka pobedi v strokah
	for (size_t y = 0; y < g.SIZE; y++)
	{
		if (g.ppField[y][0] == g.ppField[y][1] && g.ppField[y][0] == g.ppField[y][2]) 
		{
			if (g.ppField[y][0] == g.human)
				return WON_HUMAN;
			if (g.ppField[y][0] == g.ai)
				return WON_AI;
		}
		if (g.ppField[y][1] == g.ppField[y][2] && g.ppField[y][1] == g.ppField[y][3]) 
		{
			if (g.ppField[y][1] == g.human)
				return WON_HUMAN;
			if (g.ppField[y][1] == g.ai)
				return WON_AI;
		}
	}
	//proverka pobedi v stolbcah	
	for (size_t x = 0; x < g.SIZE; x++)
	{
		if (g.ppField[0][x] == g.ppField[1][x] && g.ppField[0][x] == g.ppField[2][x]) 
		{
			if (g.ppField[0][x] == g.human)
				return WON_HUMAN;
			if (g.ppField[0][x] == g.ai)
				return WON_AI;
		}
		if (g.ppField[1][x] == g.ppField[2][x] && g.ppField[1][x] == g.ppField[3][x]) 
		{
			if (g.ppField[1][x] == g.human)
				return WON_HUMAN;
			if (g.ppField[1][x] == g.ai)
				return WON_AI;
		}
	}

	// proverka diagonaley
	if (g.ppField[0][0] == g.ppField[1][1] && g.ppField[0][0] == g.ppField[2][2])  
	{
		if (g.ppField[1][1] == g.human) 
			return WON_HUMAN;
		if (g.ppField[1][1] == g.ai) 
			return WON_AI;
	}

	if (g.ppField[1][1] == g.ppField[2][2] && g.ppField[1][1] == g.ppField[3][3]) 
	{
		if (g.ppField[2][2] == g.human)
			return WON_HUMAN;
		if (g.ppField[2][2] == g.ai)
			return WON_AI;
	}

	if (g.ppField[0][1] == g.ppField[1][2] && g.ppField[0][1] == g.ppField[2][3]) 
	{
		if (g.ppField[1][2] == g.human) 
			return WON_HUMAN;
		if (g.ppField[1][2] == g.ai) 
			return WON_AI;
	}

	if (g.ppField[1][0] == g.ppField[2][1] && g.ppField[1][0] == g.ppField[3][2])
	{
		if (g.ppField[2][1] == g.human)
			return WON_HUMAN;
		if (g.ppField[2][1] == g.ai)
				return WON_AI;
	}
	if (g.ppField[2][0] == g.ppField[1][1] && g.ppField[2][0] == g.ppField[0][2])
	{
		if (g.ppField[1][1] == g.human) 
			return WON_HUMAN;
		if (g.ppField[1][1] == g.ai) 
			return WON_AI;
	}
	if (g.ppField[3][1] == g.ppField[2][2] && g.ppField[3][1] == g.ppField[1][3]) 
	{
		if (g.ppField[2][2] == g.human)
			return WON_HUMAN;
		if (g.ppField[2][2] == g.ai)
			return WON_AI;
	}

	if (g.ppField[3][0] == g.ppField[2][1] && g.ppField[3][0] == g.ppField[1][2]) 
	{
		if (g.ppField[2][1] == g.human)
			return WON_HUMAN;
		if (g.ppField[2][1] == g.ai)
			return WON_AI;
	}

	if (g.ppField[2][1] == g.ppField[1][2] && g.ppField[2][1] == g.ppField[0][3]) 
	{
		if (g.ppField[1][2] == g.human)
			return WON_HUMAN;
		if (g.ppField[1][2] == g.ai)
			return WON_AI;
	}

	//mozhet nichya?
	bool draw = true;
	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			if (g.ppField[y][x] == EMPTY)
			{
				draw = false;
				break;
			}
		}
		if (!draw)
			break;

	}
	if (draw)
		return DRAW;

	return IN_PROGRESS;

}

TCoord getHumanCoord(const TGame& g)
{
	TCoord c;
	do {
		cout << "Enter X (1..4): ";
		cin >> c.x;
		cout << "Enter Y (1..4): ";
		cin >> c.y;

		c.x--;//0..2
		c.y--;//0..2
	} while (c.x > 3 || c.y > 3 || g.ppField[c.y][c.x] != EMPTY);

	return c;
}

TCoord getAICoord(TGame& g)
{
	//1. PRE WIN SITUATION
	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			if (g.ppField[y][x] == EMPTY)
			{
				g.ppField[y][x] = g.ai;
				if (getWon(g) == WON_AI)
				{
					g.ppField[y][x] = EMPTY;
					return { y, x };//komp viigrivaet sam
				}
				g.ppField[y][x] = EMPTY;
			}
		}

	}
	//2. PRE FAIL SITUATION
	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			if (g.ppField[y][x] == EMPTY)
			{
				g.ppField[y][x] = g.human;
				if (getWon(g) == WON_HUMAN)
				{
					g.ppField[y][x] = EMPTY;
					return { y, x }; // meshaem cheloveku vigrat
				}
				g.ppField[y][x] = EMPTY;
			}
		}

	}
	
	//3.1 Заполнение центра
	if (g.ppField[1][1] == EMPTY)
	{
		return { 1,1 };
	}
	if (g.ppField[1][2] == EMPTY)
	{
		return { 1,2 };
	}
	if (g.ppField[2][1] == EMPTY)
	{
		return { 2,1 };
	}
	if (g.ppField[2][2] == EMPTY)
	{
		return { 2,2 };
	}
	//3. po prioritetam + rand
	// proverka uglov
	TCoord buf[10];
	size_t num{ 0 };
	if (g.ppField[0][0] == EMPTY)
	{
		buf[num++] = { 0,0 };
	}
	if (g.ppField[3][3] == EMPTY)
	{
		buf[num++] = { 3,3 };
	}
	if (g.ppField[0][3] == EMPTY)
	{
		buf[num++] = { 0,3 };
	}
	if (g.ppField[3][0] == EMPTY)
	{
		buf[num++] = { 3,0 };
	}
	if (num > 0)
	{
		const size_t index = getRandomNum(0, 1000) % num;
		return buf[index]; // voavrasheniye sluch ugla iz naydennih svob uglov
	}

	//proverka neuglov
	num = 0;
	if (g.ppField[0][1] == EMPTY)
	{
		buf[num++] = { 0,1 };
	}
	if (g.ppField[0][2] == EMPTY)
	{
		buf[num++] = { 0,2 };
	}
	if (g.ppField[3][1] == EMPTY)
	{
		buf[num++] = { 3,1 };
	}
	if (g.ppField[3][2] == EMPTY)
	{
		buf[num++] = { 3,2 };
	}
	if (g.ppField[1][0] == EMPTY)
	{
		buf[num++] = { 1,0 };
	}
	if (g.ppField[1][3] == EMPTY)
	{
		buf[num++] = { 1,3 };
	}
	if (g.ppField[2][0] == EMPTY)
	{
		buf[num++] = { 2,0 };
	}
	if (g.ppField[2][3] == EMPTY)
	{
		buf[num++] = { 2,3 };
	}
	
	if (num > 0)
	{
		const size_t index = getRandomNum(0, 1000) % num;
		return buf[index]; // voavrasheniye sluch neugla iz naydennih svob uglov
	}
}

//======================================================================
int main()

{
	TGame g;
	initGame(g);
	clearScr();
	drawGame(g);

	do {
		if (g.turn % 2 == 0)
		{
			//hod cheloveka
			TCoord c = getHumanCoord(g);
			g.ppField[c.y][c.x] = g.human;

		}
		else
		{
			// hod kompa
			TCoord c = getAICoord(g);
			g.ppField[c.y][c.x] = g.ai;
		}


		g.turn++;
		clearScr();
		drawGame(g);
		g.progress = getWon(g);

	} while (g.progress == IN_PROGRESS);


	congrats(g);
	deinitGame(g);
	return 0;
}