

#include"game.h"


void Game::initialize() {

    aggregate = 0;
    round = 0;


    //    Open the file - words.txt.
    wordslist = new ifstream("words.txt");

    //To check whether the file is opened successfully or not.
    if (!(*wordslist)) {
        cout << "Error opening the file words.txt" << endl;
        cout << "Game Exiting..." << endl;
        exit(1);
    }


    //    Declare a variable{word} to hold the word read from the file.
    char word[20];

    //    Declare a variable{i} to serve the purpose
    //    of counting the number of words read.
    int i;

    //    for loop to read the words in the wordslist file and store them
    //    in the vector words.
    for (i = 0; (wordslist->getline(word, 18)); i++) {
        words.push_back(word);
    }

    //    number of words in the file are found by the i value
    //    remaining after reading the file completely.
    numberOfWords = i;

    time_t seconds;

    //    Get value from system clock and place in seconds variable.
    time(&seconds);

    //    Provide the time as seed for the randome number generation.
    srand((unsigned int) seconds);

    randomize();

    cout << endl << endl;

    cout << "Welcome to the game \"Word Play\" " << endl;

    cout << endl << endl;



    cout << "Here the computer bot will select a word at random from its database." << endl;
    cout << "Guess the word, letter-by-letter and gain score." << endl;
    cout << "Wish you Good Luck!!" << endl << endl;

    cout << "To quit the game at any time press '0' " << endl << endl;

}

void Game::randomize() {

    //    Declare variable to hold seconds on clock.

    //    Random number is generated by rand() function and is obtained to be in the
    //    range of 0 to numberOfWords - 1 by obtaining the mod by numberOfWords.
    random_number = rand() % numberOfWords;

}

void Game::play() {


    int blanks, chances = 10;
    int score = 0;

    round++;

    char g;
    vector<char> guesses, wrongGuesses;
    string guessedword;

    string secretword = words.at(random_number);


    //To be removed at the end of the project.
    //    cout << secretword << endl;
    //To be removed at the end of the project.

    int length = secretword.length() - 1;

    blanks = length;


    //To be removed at the end of the project.
    //    cout << length << endl;
    //To be removed at the end of the project.

    cout << "The round " << round << " begins" << endl;


    cout << "Guess the secret word   ";

    for (int i = 0; i < length; i++) {
        guessedword += "_ ";
    }



    cout << guessedword << endl << endl << endl;
    while (blanks > 0 && chances > 0) {


        cout << chances << " chance(s) left" << endl << endl;
        cout << "Guess a letter  ";
        cin >> g;

        if (g == '0') {
            cout << "Are you sure you want to quit?(y/n)  ";
            cin >> g;
            if (g == 'y') {
                cout << "Aggregate Score is " << aggregate << endl;
            } else continue;
        }

        cout << endl;

        if (!isalpha(g)) {
            //            If entered character does not belong to the english alphabet
            cout << "Enter an English alphabet" << endl;
            continue;
        }

        bool con = false;

        for (int i = 0; i < guesses.size(); i++) {
            if (guesses.at(i) == g) {
                con = true;
                break;
            }
        }
        if (con) {
            //            If entered character is already entered previously.
            cout << "You have already tried the letter '" << g << "'" << endl << endl;

            printGuessedWord(guessedword, wrongGuesses);

            continue;
        }


        guesses.push_back(g);

        bool rightGuess = false;

        for (int i = 0; i < secretword.size(); i++) {
            if (secretword.at(i) == g) {
                rightGuess = true;
                guessedword[2 * i] = g;
                blanks--;
            }
        }

        if (!rightGuess) {
            chances--;
            wrongGuesses.push_back(g);
            cout << "Oops, " << g << " is Wrong Guess" << endl << endl;
        } else {
            cout << g << " is Good Guess, Keep it up!" << endl << endl;
        }


        printGuessedWord(guessedword, wrongGuesses);

    }


    if (blanks == 0) {
        cout << chances << " chance(s) left" << endl << endl;
        cout << endl << "Congrats!! You have found out the word " << secretword << endl;
    } else {
        cout << "No chance(s) left" << endl << endl;
        cout << endl << "Sorry, you could not find the right word. " << endl
                << "The correct word is " << secretword << endl;
    }

    score = chances * 10;

    cout << endl << "Score of round " << round << " is " << score << endl << endl;

    int oldaggregate = aggregate;

    aggregate = ((aggregate * (round - 1)) + score * 10) / round;

    cout << endl << "Aggregate Score is " << aggregate << endl << endl;

    if (aggregate - oldaggregate > 50 && round != 1) {

        cout << "Kudos.... YOUR Aggregate Score is growing. "
                "The computer bot suggests you to play again" << endl
                << endl;

    }

}

void Game::printGuessedWord(string guessedword, vector<char> wrongGuesses) {
    cout << guessedword << "  ";
    cout << "[ Wrong guesses:   ";
    for (int i = 0; i < wrongGuesses.size(); i++) {
        cout << wrongGuesses.at(i);
    }
    cout << " ]   ";
}

bool Game::callPlayAgain() {

    char choice;

    cout << "Do you want to play again?(y/n) ";
    cin >> choice;


    if (choice == 'y') {
        playAgain = true;
    } else {
        playAgain = false;
    }

    if (playAgain) {
        randomize();
    }

    return playAgain;

}

void Game::shutdown() {

    //    Close the wordslist file.
    wordslist->close();
    cout << endl << "Thanks for playing..." << endl << endl << "Bye." << endl << endl;
    cout << "Credits: Sai Manoj Kumar Yadlapati" << endl;

}
