#pragma once

#include <iostream>
#include <vector>

#include "Pokemon.h"

using namespace std;


class Trainer
{
private:
	string mFirstName;
	string mLastName;
	string mCatchPhrase;
	int mMoney;
	int mLifePoints = 100;
	vector<Pokemon> mPokemonTeam;
	int mPokeballs = 10;
	int mCurrentPokemonIndex = 0;


public:
	Trainer();
	Trainer(string firstName, string lastName, string CatchPhrase, vector<Pokemon> PokemonTeam);

	void UpdateTrainer();
	void DrawTrainer(float posX, float posY, float fontSize);
	string TextToReturn();

	void Introduction();
	void ChallengeTrainer(Trainer& thePlayer, Trainer& otherTrainer);
	void ChallengePokemon(Trainer& thePlayer);
	bool IsPokemonCaptured(Pokemon& pokemon);
	Pokemon& SendOrChangePokemon();
	void WinFight();
	bool CheckIfTeamDead();
	vector<Pokemon>& GetPokemonTeam();
};

