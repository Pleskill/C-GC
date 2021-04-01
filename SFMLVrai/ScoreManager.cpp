#include "ScoreManager.h"

ScoreManager::ScoreManager(){
    score = 0;
}
//int ScoreManager::getScore() {
//    return score;
//
//}

void ScoreManager::addScore(int newScore) {
    score = score + newScore;

}