#include "Riddle.hpp"
# include <iostream>
#include <string>
#include <map>
#include <ctime>


Riddle:: Riddle(std:: string q, std:: string a){
    question = q;
    answer = a;
    
}

RiddleManager::RiddleManager() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void RiddleManager::initializeRiddles() {
    std::cout <<"Initialize Riddles called" << std:: endl;
    locationRiddles[1] = {Riddle("I organize data in a structured way, Tables, rows, and columns, they all sway. Relationships I manage with great precision, Which course am I?", "Gem 1"), 
                        Riddle("In me, keys are not just for doors,They help identify and open data stores. Normal, primary, foreign, all play a role, In this system, they're key to the whole. Which course am I? ", "Gem 1"),
                        Riddle("Queries run through me, like a database maze, Selecting, updating, I handle them with grace. ACID properties guide my transactions, Which course am I?", "Gem 1"), 
                        Riddle("As data grows, I keep it neat, Indexing, optimizing, a task that's sweet. No SQL command is beyond my reach, In the world of databases, I teach. Which course am I?", "Gem 1")};
    
    locationRiddles[2] = {Riddle("Clock pulses ticking, circuits in sync, I process data in a systematic link. Multiplexers, decoders, a language I speak, Can you decipher the course I seek ?", "Gem 2"), 
                        Riddle("In ones and zeros, I find my delight, Boolean algebra, simplifying the fight. With truth tables and circuits, I play, Which course in your studies do I convey?", "Gem 2"),
                        Riddle("I'm composed of gates, from AND to XOR, Binary world, where logic I explore. Flip-flops, registers, in circuits so grand, Guess my course, where digital rules the land.", "Gem 2"),
                        Riddle("From gates to circuits, I design the flow, State machines, counters, in patterns they grow. Karnaugh maps and binary trees, In which course do you find these keys?", "Gem 2")};
    
    locationRiddles[3] = {Riddle("In bytes and bits, I weave a tale, Memory's guardian, where pointers set sail. Dynamic or static, I manage the space, Guess the course, in the coder's embrace?", "Gem 3"), 
                        Riddle("Through memory's veil, pointers take flight, In arrays and structures, their power is in sight. Abstract or virtual, functions unfold, Pillars of code, in which course am I told?", "Gem 3"),
                        Riddle("In classes and objects, I find my way, Encapsulation and inheritance, my forte they say. Polymorphism, with methods to bind, Guess my course, in the programming kind.", "Gem 3"),
                        Riddle("I speak of objects and the things they do, Attributes and methods, in a class or two. Instances created, from a blueprint so fine, Unravel my name, in the world of design.", "Gem 3")};
    
    locationRiddles[4] = {Riddle("I analyze data, draw conclusions with might, Standard deviations, I calculate right. Bell curves and p-values, I unfold, Which statistical course do I hold?", "Gem 4"), 
                        Riddle("Random variables and distributions I explore, Confidence intervals, I help you score. From sampling methods to hypothesis tests, Name my course amidst statistical quests?", "Gem 4"),
                        Riddle("In distributions and outcomes, I hold the key, Measures of central tendency, revealed through me. Odds and chances, events I quantify, Which course am I, where probabilities lie?", "Gem 4"),
                        Riddle("With permutations and combinations, I play, A branch of math where uncertainties sway. Toss a coin or roll a die, Can you guess the course, as chances multiply?", "Gem 4")};
    
    locationRiddles[5] = {Riddle("Integration and derivatives, my terrain, Limits and series, I do not disdain. In the realm of calculus, I find my stance, Guess the course, where functions enhance?", "Gem 5"), 
                        Riddle("Differential equations, I solve the flow, Transforms and solutions, watch them grow. From Laplace to Fourier, I navigate, In which math course do these topics resonate?", "Gem 5"),
                        Riddle("Matrices and vectors, my tools in hand, Linear equations dance at my command. Eigenvalues, determinants, in my scope, Which math course am I, where linear structures elope?", "Gem 5"),
                        Riddle("Complex numbers and their intricate play, Convergence and divergence guide my way. Analytic functions, a complex delight, Name my course, where mathematical insights unite.", "Gem 5")};
}


void RiddleManager::prepareRandomRiddle() {
    std:: cout <<" Display called" << std:: endl;

        //getting a random integer between the value 1 and 5
        int locationID = (rand() % 5) + 1;
        // Get the riddles for the current location
        std::vector<Riddle>& riddles = locationRiddles[locationID];

        // Select a random index for getting a riddle from the vector
        int randomIndex = rand() % riddles.size();

        Riddle& selectedRiddle = riddles[randomIndex];

        correctAnswer = selectedRiddle.answer;
        question = selectedRiddle.question;

}

//checking whether the collided gem is correct or not by comparing the id and correct answer
bool RiddleManager::checkAnswer(std::string userAnswer) {
    std:: cout << "Check Answer called" << std:: endl;
    if (userAnswer == correctAnswer){
        std::cout << correctAnswer << std::endl;
        return true;
    }
    return false;
}

//returning the riddle which will be displayed on the screen
std::string RiddleManager::getQuestion(){
    return question;
}