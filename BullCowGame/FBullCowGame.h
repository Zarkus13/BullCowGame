#pragma once

#include <string>
#include "globals.h"

constexpr int32 MAX_TRIES = 5;

class FBullCowGame {
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	int32 GetHiddenWordLength() const;

	void Reset();
	EGuessValidity CheckGuessValidity(FString) const;
	bool IsIsogram(FString) const;
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameWon;

	char toLowerCase(char c) const;
};