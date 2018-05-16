#pragma once

#include <string>

// type aliases
using FString = std::string;
using FText = std::string;
using int32 = int;


// structs
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};


// enums
enum class EGuessValidity {
	OK,
	NOT_ISOGRAM,
	WRONG_LENGTH
};