#pragma once
#include <iostream>

#include "raylib.h"
#include "Trainer.h"
#include "allPokemons.h"
#include "Battle.h"

bool isInSendPokemon = false;
bool pokemonImageIsLoad = false;

Rectangle changePokemonBox { 0 , 55, 1600, 800 / 2 };
//Rectangle abilityBox{ 20 , 20, 1600 / 2 , 1200 / 2 };

vector<Texture2D> allPokemonsTexture;

Trainer::Trainer()
{
	mFirstName = "Arthur";
	mLastName = "Cathelain";
	mCatchPhrase = "Nothing in life is equivalent to the beauty of splines";
	mPokemonTeam = { Diglett };
}

Trainer::Trainer(string firstName, string lastName, string CatchPhrase, vector<Pokemon> PokemonTeam)
{
	mFirstName = firstName;
	mLastName = lastName;
	mCatchPhrase = CatchPhrase;
	mPokemonTeam = PokemonTeam;
}

void Trainer::UpdateTrainer()
{
	//
}

void Trainer::DrawTrainer()
{
	if (isInSendPokemon) 
	{
		DrawRectangleRec(changePokemonBox, WHITE);
		DrawText("You have this pokemon team :", 70, 775, 70, BLACK);
		DrawText("Which Pokemon do you want to use ? ", 70, 950, 50, BLACK);
		DrawText("Write the corresponding number :", 70, 1050, 50, RED);

		float pokemonPosition = 50;
		float pokemonNamePosition = 70;

		if (!pokemonImageIsLoad) 
		{
			int spacing = 0;
			for (int i = 0; i < mPokemonTeam.size(); i++)
			{
				ImageFormat(mPokemonTeam[i].GetPokemonImage(), PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
				Texture2D onePokemonTexture = LoadTextureFromImage(*(mPokemonTeam[i].GetPokemonImage()));
				
				allPokemonsTexture.push_back(onePokemonTexture);
			}
			pokemonImageIsLoad = true;
		}

		for (int i = 0; i < mPokemonTeam.size(); i++)
		{
			DrawTextureEx(allPokemonsTexture[i], {pokemonPosition, 100}, 0, 0.6f, WHITE);
			pokemonPosition += GetScreenWidth() / mPokemonTeam.size();
		}

		for (int i = 0; i < mPokemonTeam.size(); i++)
		{
			DrawText(TextFormat("%i. %s ", i + 1, mPokemonTeam[i].GetPokemonName().c_str()), pokemonNamePosition, 870, 35, BLACK);
			pokemonNamePosition += 250;
		}
	}
}

const char* Trainer::Introduction()
{
	return (char*) TextFormat("%s %s said : %s", mFirstName.c_str(), mLastName.c_str(), mCatchPhrase.c_str());
}

const char* Trainer::ChallengeTrainer()
{
	return (char*) TextFormat("You are challenging %s %s !!!", mFirstName.c_str(), mLastName.c_str());
}

//*************** TO REFACTOR ***************************************
// 
// JUST PRINT the wild pokemon found in the main
// 
//const char* Trainer::ChallengePokemon()
//{
//	(char*) TextFormat("You are challenging %s %s !!!", mFirstName.c_str(), mLastName.c_str());
//	//*************** TO REFACTOR ***************************************
//	cout << "\nYou just found a wild pokemon !!" << endl;
//
//	//Battle theBattle = Battle(thePlayer);
//	//theBattle.BattleAgainstPokemon(true);
//}

bool Trainer::IsPokemonCaptured(Pokemon& pokemon)
{
	if (mPokemonTeam.size() < 6 && mPokeballs > 0)
	{
		//*************** TO REFACTOR ***************************************
		//cout << "\nYou are trying to capture " << pokemon.GetPokemonName() << endl;

		float captureRate = (((1.0f + (((pokemon.GetPokemonMaxLife() * 3.0f) - (pokemon.GetPokemonLife() * 2.0f)) * 256.0f)) 
			/ (pokemon.GetPokemonMaxLife() * 3.0f)) / 334.0f) * 100.0f;

		if (captureRate <= 50)
		{
			//*************** TO REFACTOR ***************************************
			cout << "You have failed to capture the pokemon" << endl;
			return false;
		}

		//*************** TO REFACTOR ***************************************
		//cout << "You have managed to capture " << pokemon.GetPokemonName() << " !!!!" << endl;

		mPokemonTeam.push_back(pokemon);
		mPokeballs -= 1;
		return true;
	}
	else if (mPokeballs <= 0)
	{
		//*************** TO REFACTOR ***************************************
		cout << "\nYou don't have enough Pokeballs, try an other time." << endl;

		return false;
	}
	//*************** TO REFACTOR ***************************************
	cout << "\nYou already have 6 pokemon and can't capture one anymore" << endl;

	return false;
}

bool Trainer::CheckIfTeamDead()
{
	for (int i = 0; i < mPokemonTeam.size(); i++)
	{
		if (mPokemonTeam[i].GetPokemonLife() > 0)
		{
			return false;
		}
	}

	mMoney -= 10;

	//*************** TO REFACTOR ***************************************
	cout << "\nAll your Pokemon are dead, you have lost the fight " << endl;
	//cout << "You have lost 10 gold, you now have " << mMoney << " gold" << endl;

	return true;
}

Pokemon& Trainer::SendOrChangePokemon()
{
	isInSendPokemon = true;
	int pokemonIndex = 0;

	Pokemon& pokemonWantingToBeUse = mPokemonTeam[0];
	return  pokemonWantingToBeUse;
	//int answer;

	//*************** TO REFACTOR ***************************************
	//cout << "\nYou have this Pokemon team, please choose one to use" << endl;
	//for (int i = 1; i < mPokemonTeam.size() + 1; i++)
	//{
	//	//add type ?
	//	cout << i << ". " << mPokemonTeam[i - 1].GetPokemonName() << endl;
	//}

	//cout << "Which Pokemon do you want to use ? (write the corresponding number) : " << endl;
	//cin >> pokemonIndex;
	//*************** TO REFACTOR ***************************************

	//Pokemon& pokemonWantingToBeUse = mPokemonTeam[pokemonIndex - 1];

	mCurrentPokemonIndex = pokemonIndex - 1;
	return pokemonWantingToBeUse;
}

void Trainer::WinFight()
{
	//*************** TO REFACTOR ***************************************
	cout << "You have won the Battle !!!!! " << endl;
	int random = rand() % 101;
	if (random <= 50)
	{
		mMoney += 10;
		cout << "You won 10 gold, you now have " << mMoney << " gold" << endl;
		return;
	}
	else if (random > 50)
	{
		mPokeballs += 2;
		cout << "You won 2 new Pokeballs, you now have " << mPokeballs << " Pokeballs" << endl;
		return;
	}
	//*************** TO REFACTOR ***************************************
}

vector<Pokemon>& Trainer::GetPokemonTeam()
{
	return mPokemonTeam;
}