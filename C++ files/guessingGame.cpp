/*
	Program name:GuessingGame
	Problem: create a guessing game with the computer
	so that people cannot cheat at it.
	purpose:Practice in anticipating user input and making
	games.
	author: Karl Bigley-Bodlak
*/
//program start
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include<time.h>
using namespace std;


void guessReverse(int guesses);//prototype
/*
	guess is the user's guess, secret is the computer's
	chosen random number, guesses is how many times the user
	has guessed the computer's number.
*/
void guessingGame()
{	
	int  guess, guesses=0;
	//secret number is chosen from 0-100
	int secret =(int)(100*(double(rand())/RAND_MAX));
	//since range is 1-100, have to handle exception.
	if(secret==0) secret=1;
	cout<<"I have picked"
	<<" an integer from 1 to 100.  I will count how many "
	<<"guesses it takes for you to get to it, and then we will"
	<<" switch roles. whoever has the fewest guesses wins!\n"
	<<"To exit, enter 0.\n Guess your first number\n";
	
	while (guess!=secret)
	{
		cin>>guess;
		guesses++;
		//sentinel value zero.
		if(guess==0) return;
		if(guess<secret) cout<<"too small\n";
		if(guess>secret) cout<<"too big\n";
		if(guess==secret)
		{
		//switches to other half of game when user is correct.
			cout<<"correct!\n";
			cout<<"it took you "<<guesses<<" guesses.\n\n";
			guessReverse(guesses);
			return;
		}
	}	
	return;
}
/*
	compguesses is how many guesses the computer has made.
	guess is the computer's current guess.
	max and min define range of possible numbers.
	signal is the user input.
*/
void guessReverse(int guesses)
{
	int compguesses=0, guess, max=100, min=0;
	char signal;
	cout<<"Now I will try to guess your secret number.\n"
	<<"Pick a number between 1 and 100, but don't tell me.\n"
	<<"For each guess I make, let me know if I am too low by"
	<<" typing \"<\", too high with \">\".  If I am correct, "
	<<"type \"=\".\nA zero will terminate the program.\n";
	while (signal!='0')
	{
		//binary search algorithm to find secret number.
		guess = (max+min)/2;
		cout<<"is it "<<guess<<"?\n";
		compguesses++;
		cin>>signal;
		if(signal=='>')
		{
			max=guess-1;
			//exception handling restarts second part.
			if(max<min || max==0) 
			{
			cout<<"your number is invalid. try a "
			<<"new number.\n";
			max=100;
			min=0;
			compguesses=0;
			continue;
			}
		} 
		if(signal=='<') 
		{
			min=guess+1;
			//exception handling.
			if(min>max)
			{
			cout<<"your number is invalid. try a "
			<<"new number.\n";
			max=100;
			min=0;
			compguesses=0;
			continue;
			}
		}
		if(signal=='=')
		{
			cout<<"I guessed your number in "<<compguesses
			<<" guesses.\n";
			//determining winner of game
			if(compguesses<guesses) cout<<"i win!\n\n";
			if(compguesses>guesses) cout<<"you win!\n\n";
			if(compguesses==guesses) cout<<"it's a tie!\n\n";
			guessingGame();
			return;
		}
	}
	return;
}

int main(void)
{
	//randomize seed
	srand( (unsigned) time( NULL ) );
	guessingGame();
	return 0;
}
