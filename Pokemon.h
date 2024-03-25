#pragma once
#include <iostream>
#include <vector>

#include "raylib.h"
#include "PokeType.h"
#include "Ability.h"

using namespace std;

class Pokemon
{
private:
	Image mImagePokemon;
	string mName;
	string mDescription;
	PokeType mType;
	int mLevel;
	float mLife;
	float mMaxLife;
	float mDamageResistance;
	vector<Ability> mAbilities;

	int mAnswerPokemon = NULL;

public:
	Pokemon();
	Pokemon(Image imagePokemon, string name, string description, PokeType type, int life, vector<Ability> abilitie);

	void UpdatePokemon();
	void DrawPokemon();

	void TakeDamage(int damage, Ability abilityAttack);
	void Rest();
	bool CheckIfCanUseAbility();
	void AttackOtherPokemon(Pokemon& pokemon);
	void ChooseAbility();
	void LearnNewAbilities();

	void GetDescription();

	const vector<Ability>& GetAbilities() const;
	string GetPokemonName() const;
	Image* GetPokemonImage();
	float GetPokemonLife() const;
	float GetPokemonMaxLife() const;
	float GetPokemonDamage() const;
	int GetAnswerPokemon() const;
};

