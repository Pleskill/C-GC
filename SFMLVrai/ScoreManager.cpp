#include "ScoreManager.h"

ScoreManager::ScoreManager(){
    score = 0;
}

void ScoreManager::addScore(int newScore) {
    score = score + newScore;

}