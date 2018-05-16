#include "FBullCowGame.h"
#include "globals.h"
#include <iostream>
#include <map>
#include <locale>

#define TMap std::map

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

FBullCowGame::FBullCowGame()
{
	this->Reset();
}

void FBullCowGame::Reset()
{
	this->MyMaxTries = MAX_TRIES;
	this->MyCurrentTry = 1;
	this->MyHiddenWord = "planet";
	this->bGameWon = false;

	return;
}

bool FBullCowGame::IsGameWon() const
{
	return bGameWon;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

EGuessValidity FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (Guess.length() != GetHiddenWordLength())
		return EGuessValidity::WRONG_LENGTH;
	else if (!IsIsogram(Guess))
		return EGuessValidity::NOT_ISOGRAM;
	else
		return EGuessValidity::OK;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	TMap<char, bool> Characters;

	for (const auto c : Guess) {
		char lowerC = toLowerCase(c);

		if (Characters[lowerC])
			return false;
		else
			Characters[lowerC] = true;
	}

	return true;
}

char FBullCowGame::toLowerCase(char c) const
{
	return std::tolower(c, std::locale());
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	this->MyCurrentTry++;
	FBullCowCount count = FBullCowCount();

	int32 length = this->MyHiddenWord.length();

	for (int32 i = 0; i < length; i++) {
		char c = toLowerCase(MyHiddenWord.at(i));

		for (int32 j = 0; j < length; j++) {
			char c2 = toLowerCase(Guess.at(j));

			if (c == c2 && i == j)
				count.Bulls++;
			else if (c == c2)
				count.Cows++;
		}
	}

	this->bGameWon = count.Bulls == length && count.Cows == 0;

	return count;
}