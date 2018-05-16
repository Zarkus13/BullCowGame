#include <iostream>
#include <string>
#include <chrono>
#include "globals.h"
#include "FBullCowGame.h"

void displayIntroduction(int32 wordLength, int32 maxTries);
FString askUserForValidGuess(int32 wordLength);
void displayCountOrEndGame(FBullCowCount count);
bool askToPlayAgain();
bool isTrue(char character);


FBullCowGame cowGame = FBullCowGame();

int32 main(FString** args) {
	int32 maxTries = cowGame.GetMaxTries();
	int32 wordLength = cowGame.GetHiddenWordLength();

	displayIntroduction(wordLength, maxTries);

	do {
		cowGame.Reset();

		while (!cowGame.IsGameWon() && cowGame.GetCurrentTry() <= cowGame.GetMaxTries()) {
			FString UserGuess = askUserForValidGuess(wordLength);
			FBullCowCount count = cowGame.SubmitValidGuess(UserGuess);

			displayCountOrEndGame(count);
		}
	} while (askToPlayAgain());

	std::cout << "\nGood bye !" << std::endl;

	system("pause");
	return 0;
}

void displayIntroduction(int32 wordLength, int32 maxTries) {
	std::cout << "Welcome to Bulls and Cows, a fun word game" << std::endl << std::endl;
	std::cout << "Can you guess the " << wordLength << " letter isogram I'm thinking of ? You have " << maxTries << " tries." << std::endl;
	return;
}

FString askUserForValidGuess(int32 wordLength) {
	FString UserGuess = "";
	
	EGuessValidity guessValidity;

	do {
		std::cout << "\nTry " << cowGame.GetCurrentTry() << ") Enter something : ";
		std::getline(std::cin, UserGuess);
		guessValidity = cowGame.CheckGuessValidity(UserGuess);

		switch (guessValidity) {
			case EGuessValidity::WRONG_LENGTH:
				std::cout << "Please enter a word of " << wordLength << " characters length" << std::endl;
				break;
			case EGuessValidity::NOT_ISOGRAM:
				std::cout << "Please enter a word without repeating letters." << std::endl;
				break;
		}
	} while (guessValidity != EGuessValidity::OK);

	return UserGuess;
}

void displayCountOrEndGame(FBullCowCount count) {
	if (cowGame.IsGameWon())
		std::cout << "\nCongratulations ! You have found the word to guess !\n" << std::endl;
	else if (!cowGame.IsGameWon() && cowGame.GetCurrentTry() > cowGame.GetMaxTries())
		std::cout << "\nOH NO ! YOU LOSE ! Try again !\n" << std::endl;
	else
		std::cout << "Bulls : " << count.Bulls << " - Cows : " << count.Cows << std::endl;

	return;
}

bool askToPlayAgain() {
	FString UserResponse = "";
	
	std::cout << "\nDo you want to play again ? (Y/n)";
	std::getline(std::cin, UserResponse);

	return isTrue(UserResponse[0]);
}

bool isTrue(char Character) {
	return Character == 'y' || Character == 'Y';
}