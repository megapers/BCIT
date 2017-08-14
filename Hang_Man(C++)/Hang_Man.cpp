// Assignment 8: Assign07.cpp
// July 02, 2015
// Author: Tim Makimov

#include <iostream>
#include <ctime>
#include <random> 
#include <vector>  
#include <algorithm>
#include <array>
#include <string>
#include <iterator>
#include <unordered_set>

using namespace std;

const size_t random_ten = 9;
const int A = 65;
const int Z = 90;
const int a = 97;
const int z = 122;
bool play = true;

void playGame();
void hangManDraw(int);
int comparator(const string&, string&, unordered_set<char>&, const char&);
void playOrNot();

int main()
{
	do
	{
		playGame();
	} while (play);	
} // end main


void playGame()
{
	default_random_engine engine(static_cast<unsigned int>(time(0)));
	uniform_int_distribution<size_t> randomInt(0, 9);
	int counter = 0;
	char input;
	bool play = true;
	
	vector <string> words = { "INTEGER", "BOOLEAN", "CHARACTER", "VARIABLE", "STRING", "ARRAY", "MEMBER", "SOLUTION", "PROGRAM", "OBJECT" };
	string guess = words[randomInt(engine)];
	string word(guess);
	unordered_set<char> container;
	
	fill(word.begin(), word.end(), '?');

	cout << "Guess the word: ";
	for (int i = 0; i < guess.size(); i++)
	{
		cout << "X";
	}
	cout << endl;

	while (play)
	{
		cout << "\n\nGuess a letter: " << word << "\n?";
		cin >> input;

		if (comparator(guess, word, container, input) == 0)
		{
			hangManDraw(++counter);
			
			if (counter == 7)
			{
				play = false;
				cout << "\n\n\nSorry - you have run out of guesses ;("
					<< "\nThe correct answer was: " << guess
					<< "\n\n ...GAME OVER...\n\n" << endl;
				playOrNot();
			}	
		}
		else if (word == guess)
		{
			cout << "\n\nWord: " << word << "\n" << endl;
			cout << "\nCongratulations!!! You guessed my word.\n\n" << endl;
			play = false;
			playOrNot();
		}	
	}
}


int comparator(const string &guess, string &word, unordered_set<char> &container, const char &input)
{
	int matches = 0;
	
	string::iterator itr1 = word.begin();
	string::const_iterator itr2 = guess.cbegin();

	if (!(input >= A && input <= Z || input >= a && input <= z))
	{
		cout << "Letters only please" << endl;
		return 1;
	}

	auto p = container.insert(toupper(input));

	if (p.second == false)
	{
		cout << '\'' << static_cast<char>(toupper(input)) << '\'' << " Was already guessed. Try another letter.";
		return 1;
	}
	else
	{
		cout << "\n\nYour guesses: " << "\n" << " ";
		ostream_iterator<char> output(cout, " ");
		copy(container.begin(), container.end(), output);
	}
			
	while (itr1 != word.end())
	{	
		if (*itr2 == toupper(input))
		{
			*itr1 = toupper(input);	
			++matches;
		}
		++itr1;
		++itr2;
	}
		return matches;
}


void hangManDraw(int counter)
{
	char hangman[] = { 'o', '/', '|', '\\' };

	switch (counter)
	{
	case 1: cout << "\n\n " << hangman[0] << endl;
		break;
	case 2: cout << "\n\n " << hangman[0] << "\n" << hangman[1] << endl;
		break;
	case 3: cout << "\n\n " << hangman[0] << "\n" << hangman[1] << hangman[2] << endl;
		break;
	case 4: cout << "\n\n " << hangman[0] << "\n" << hangman[1] << hangman[2] << hangman[3] << endl;
		break;
	case 5: cout << "\n\n " << hangman[0] << "\n" << hangman[1] << hangman[2] << hangman[3] << "\n" << " " << hangman[2] << endl;
		break;
	case 6: cout << "\n\n " << hangman[0] << "\n" << hangman[1] << hangman[2] << hangman[3] << "\n" << " " << hangman[2] << "\n" << hangman[1] << endl;
		break;
	case 7:	cout << "\n\n " << hangman[0] << "\n" << hangman[1] << hangman[2] << hangman[3] << "\n" << " " << hangman[2] << "\n" << hangman[1] << " " << hangman[3] << endl;
		break;
	default:
		break;
	}
}


void playOrNot()
{
	char yesNo;
	cout << "Play again? (y/n) ";
	cin >> yesNo;
	if (yesNo == 'y')
	{
		play = true;
	}
	else
	{
		play = false;
	}
}