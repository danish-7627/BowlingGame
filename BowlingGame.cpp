// BowlingGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include "Frames.h"
#include "Constants.h"
/*
    This Program is made to calculate the Score from Bowling Board
    I have used Singleton Design Pattern, Factory Pattern to solve the Problem
    This can further be optimised if I implement the complete Factory Design Pattern within the class ScoreBoard.
*/


class ScoreBoard {
public:
   static ScoreBoard* getInstance() {
        if (hInstance == NULL) {
            return hInstance = new ScoreBoard();
        }
        return hInstance;
   }
   void addFrames(std::unique_ptr<Frame> frame) {
       allFrame.push_back(std::move(frame));
   }
   int calculateTotalScore() {
       int TotalScore = 0;
       for (const auto &it : allFrame) {
           //std::cout << "Individual Score: " << it->returnscore() << "\n";
           TotalScore += it->returnscore();
       }
       return TotalScore;
   }
   void modifyPreviousFrameValue(int score1) {
       if (!allFrame.empty()) { // Ensure the list is not empty
           auto it = --allFrame.end(); // Correct way to get the last element in the list
           (*it)->addextrascore(score1);  // Modify the last frame
           //std::cout << "Previous SPARE VALUE Updated to : " << (*it)->returnscore()<<"\n";
       }
   }
   void modifyPreviousFrameValue(int score1,int score2) {
       if (!allFrame.empty()) { // Ensure the list is not empty
           auto it = --allFrame.end(); // Correct way to get the last element in the list
           (*it)->addextrascore(score1,score2);  // Modify the last frame
           //std::cout << "Previous STRIKE VALUE Updated to : " << (*it)->returnscore() << "\n";
       }
   }
private:
    ScoreBoard() {}
    ~ScoreBoard() {
    }
    std::list<std::unique_ptr<Frame>> allFrame;
    static ScoreBoard* hInstance;
};

ScoreBoard* ScoreBoard::hInstance = NULL;
int main()
{
    ScoreBoard* score = ScoreBoard::getInstance();
    int score1 = 0, score2 = 0;
    for (int i = 0; i < 10; ++i) {
        enterScore(&score1, &score2);

        // FIX: update previous frame BEFORE adding new frame
        if (prevScoreType == SPARE) {
            score->modifyPreviousFrameValue(score1);
        }
        else if (prevScoreType == STRIKE) {
            score->modifyPreviousFrameValue(score1, score2);
        }

        auto frame = FrameType::decideFrameType(score1, score2);
        score->addFrames(std::move(frame));

        //std::cout << "Current Total Score = " << score->calculateTotalScore() << "\n";

        prevScoreType = currScoreType;
    }

    // In case of 10th frame spare/strike extra roll
    if (currScoreType == SPARE || currScoreType == STRIKE) {
        int extraScore = 0;
        std::cout << "Enter extra score for 10th frame: ";
        std::cin >> extraScore;

        if (currScoreType == SPARE) {
            score->modifyPreviousFrameValue(extraScore);
        }
        else if (currScoreType == STRIKE) {
            int extraScore2 = 0;
            std::cout << "Enter second extra score for 10th frame: ";
            std::cin >> extraScore2;
            score->modifyPreviousFrameValue(extraScore, extraScore2);
        }
    }

    std::cout << "\n\nFINAL TOTAL SCORE = " << score->calculateTotalScore() << "\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
