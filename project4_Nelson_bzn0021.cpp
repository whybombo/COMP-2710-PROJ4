/*
*
* FILE NAME: project4_Nelson_bzn0021
* AUTHOR: Blake Nelson
*
* This C++ code implements a trivia quiz game where players can answer predefined or custom trivia questions and earn points based on correct answers. 
* It allows users to add new questions, play the quiz, accumulate points, and includes unit tests to verify the functionality of the game.
*
* COMPILE: g++ project4_Nelson_bzn0021.cpp -o p4.out
* COMPILE: ./p4.out
* scp studentID@scp.eng.auburn.edu:/home/u3/studentID/project5_lantname_rdb0044.tar.gz /mnt/c/Users/robbi/Downloads
* I followed the instructions provided to understand the code structure.
* Additionally, I used resources like Stack Overflow and asked ChatGPT for assistance
* to figure out how to display multiple questions, tally scores, and grasp the overall code setup.
* 
*/
#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>

using namespace std;

struct TriviaNode {
    string question;
    string answer;
    int points;
    TriviaNode* next;
};
// Function to set up initial predefined trivia questions
void initializeHardcodedQuestions(TriviaNode*& head) {
    head = new TriviaNode {
        "How long was the shortest war on record? (Hint: how many minutes)",
        "38",
        100,
        nullptr
    };

    head->next = new TriviaNode {
        "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)",
        "Bank of Italy",
        50,
        nullptr
    };

    head->next->next = new TriviaNode {
        "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)",
        "Wii Sports",
        20,
        nullptr
    };
}
// Function to add a new trivia question to the list
void addNewTriviaNode(TriviaNode*& head, const string& question, const string& answer, int points) {
    TriviaNode* newNode = new TriviaNode { question, answer, points, nullptr };
    if (head == nullptr) {
        head = newNode;
    } else {
        TriviaNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}
// Function to ask trivia questions and evaluate answers
bool ask_question(TriviaNode* head, int num_ask) {
    int num_of_questions = 0;
    TriviaNode* current = head;

    while (current != nullptr) {
        num_of_questions++;
        current = current->next;
    }

    if (num_ask <= 0) {
        cout << "Warning - the number of trivia to be asked must equal to or be larger than 1." << endl;
        return false;
    } else if (num_of_questions < num_ask) {
        cout << "Warning - There is only " << num_of_questions << " trivia in the list." << endl;
        return false;
    }

    int totalPoints = 0;
    for (int i = 0; i < num_ask; ++i) {
        cout << "\nQuestion: " << head->question << endl;
        string userAnswer;
        cout << "Answer: ";
        getline(cin, userAnswer);

        if (userAnswer == head->answer) {
            cout << "Your answer is correct! You receive " << head->points << " points." << endl;
            totalPoints += head->points;
        } else {
            cout << "Your answer is wrong. The correct answer is: " << head->answer << endl;
        }
        cout << "Your total points: " << totalPoints << endl;
        head = head->next;
    }

    return true;
}
// Function to run various test cases if UNIT_TESTING is defined
void runUnitTests() {
    #ifdef UNIT_TESTING
    cout << "***This is a debugging version ***" << endl;

    // Test Case 1: Ask no question
    cout << "Unit Test Case 1: Ask no question. The program should give a warning message." << endl;
    assert(ask_question(nullptr, 0) == false);
    cout << "Case 1 Passed" << endl;

    // Test Case 2.1: Ask 1 question with an incorrect answer
    TriviaNode* testList1 = new TriviaNode {"How long was the shortest war on record?", "38", 100, nullptr};
    cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
    assert(ask_question(testList1, 1) == true);
    cout << "Case 2.1 passed" << endl;

    // Test Case 2.2: Ask 1 question with a correct answer
    TriviaNode* testList2 = new TriviaNode {"How long was the shortest war on record?", "38", 100, nullptr};
    cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
    assert(ask_question(testList2, 1) == true);
    cout << "Case 2.2 passed" << endl;

    // Test Case 3: Ask all questions of the last trivia in the linked list
    TriviaNode* testList3 = new TriviaNode {"How long was the shortest war on record?", "38", 100, nullptr};
    addNewTriviaNode(testList3, "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)", "Bank of Italy", 50);
    addNewTriviaNode(testList3, "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)", "Wii Sports", 20);
    cout << "Unit Test Case 3: Ask all the questions of the last trivia in the linked list." << endl;
    assert(ask_question(testList3, 3) == true);
    cout << "Case 3 passed" << endl;

    // Test Case 4: Ask 5 questions in the linked list
    TriviaNode* testList4 = new TriviaNode {"How long was the shortest war on record?", "38", 100, nullptr};
    addNewTriviaNode(testList4, "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)", "Bank of Italy", 50);
    addNewTriviaNode(testList4, "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)", "Wii Sports", 20);
    cout << "Unit Test Case 4: Ask 5 questions in the linked list." << endl;
    assert(ask_question(testList4, 5) == false);
    cout << "Case 4 passed" << endl;

    cout << "*** End of the Debugging Version ***" << endl;
    #endif
}

int main() {
    // Runs unit tests if defined
    runUnitTests();

    TriviaNode* triviaList = nullptr;
    initializeHardcodedQuestions(triviaList);

    cout << "*** Welcome to Blake's trivia quiz g  ame ***" << endl;
    int numberOfQuestions = 3;

    while (true) {
        string continueInput;

        if (numberOfQuestions < 6) {
            string question, answer;
            int points;

            cout << "Enter a question: ";
            getline(cin, question);
            cout << "Enter an answer: ";
            getline(cin, answer);
            cout << "Enter award points: ";
            cin >> points;
            cin.ignore();

            addNewTriviaNode(triviaList, question, answer, points);
            ++numberOfQuestions;
        } else {
            cout << "You've reached the maximum number of questions allowed." << endl;
            break;
        }

        cout << "Continue? (Yes/No): ";
        getline(cin, continueInput);
        transform(continueInput.begin(), continueInput.end(), continueInput.begin(), ::tolower);

        if (continueInput != "yes") {
            break;
        }
    }

    if (!ask_question(triviaList, numberOfQuestions)) {
        cout << "Unable to ask questions." << endl;
    }

    cout << "*** Thank you for playing the trivia quiz game. Goodbye! ***" << endl;

    return 0;
}