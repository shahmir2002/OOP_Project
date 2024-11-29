
#include <string>
#include <vector>
#include <map>
#include <iostream>


struct Riddle{
    std::string question;
    std::string answer;

    Riddle(std::string q, std::string a);
};

class RiddleManager {
public:
    RiddleManager(); // Default constructor
    void initializeRiddles(); // Function to initialize riddles for each location
    void prepareRandomRiddle() ; // Function to display a random riddle for a specific location
    bool checkAnswer(std::string userAnswer) ; // Function to check the answer for a specific location
    std::string getQuestion(); //returns the selected riddle
private:
    std::map<int, std::vector<Riddle>> locationRiddles; // Map to associate location IDs with riddles
    std:: string correctAnswer;
    std:: string question;
};

