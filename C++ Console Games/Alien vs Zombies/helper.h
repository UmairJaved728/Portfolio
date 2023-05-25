//helper.h

#ifndef PF_HELPER_H
#define PF_HELPER_H

#include <iostream>

namespace pf
{
    void PrintGameSettings();
    void ChangeGameSettings();
    void Help();
    int GameOver();
    void DeleteGameBoard();
    void Caps_to_small(std::string &a);
    void ChangeArrow();
    char isCharacter(int r_no, int c_no);
    void reset_cell(int i, int j);
    void SetRandomObject(int i, int j, int nums);
    void CreateGameBoard();
    void ShowGameBoard();
    int GetClosestZombie(int r, int c);
    bool CanAttack(int r, int c, int range);
    void ResetTrail();
    void Turn(int t);
    bool OutOfBound(int rows, int cols);
    void ResetZombieAttributes(int zombie_no);
    void ZombieMove();
    void DetectCell(int i, int j);
    void Rock(int i, int j);
    void AlienTurnEnd();
    void AlienMove(std::string direction);
    void SaveGame();
    void LoadGame();
    int ClearScreen();
    int Pause();
}

#endif