#include "barleybreak.h"
#include <QRandomGenerator>
BarleyBreak::BarleyBreak() {
  startGame();
}

void BarleyBreak::startGame() {
    moves = 0;
    QRandomGenerator *rnd = QRandomGenerator::global();
    QRandomGenerator *rnd2 = QRandomGenerator::global();
    do {
        int place = 1;
        for (auto i = 0; i < 4; i++)
            for(auto j = 0; j < 4; j++) {
                table[i][j] = place;
                RightTable[i][j]=table[i][j];
                place++;
            }
        table[3][3]= 0;
        RightTable[3][3]=0;
        emptyX = 3;
        emptyY = 3;
     while(moves < 250) {
         int posY = rnd->bounded(-1,2);
         int posX = rnd2->bounded(-1,2);
         MoveWhenClicked(emptyY+posY,emptyX+posX);
     }
     for (auto i = 0; i < 4; i++)
         for(auto j = 0; j < 4; j++) {
             cpyTable[i][j]=table[i][j];
        }
    } while(isFinished());
    moves = 0;
}

void BarleyBreak::restartGame() {
            for (auto i = 0; i < 4; i++)
                for(auto j = 0; j < 4; j++) {
                    table[i][j] = cpyTable[i][j];
                    if (cpyTable[i][j] == 0) {
                        emptyY = i;
                        emptyX = j;
                       }
                    }
    moves = 0;
}

bool BarleyBreak::isFinished() const {
    for (auto i = 0; i < 4; i++)
        for(auto j = 0; j < 4; j++) {
           if (table[i][j] != RightTable[i][j])
               return false;
        }
    return true;
}

void BarleyBreak::MoveWhenClicked(int a, int b) {
    if (a >= 4 || b >= 4 || b < 0 || a < 0) return;
    if((getVoidY() - a == 0 && abs(getVoidX() - b) == 1) || (abs(getVoidY() - a) == 1 && getVoidX() - b == 0)) {
        moves++;
        int tmp = table[a][b];
        table[a][b]=table[emptyY][emptyX];
        table[emptyY][emptyX] = tmp;
        emptyX = b;
        emptyY = a;
    }
}

int BarleyBreak::getNumber(int i, int j) const {
    return table[i][j];
}

int BarleyBreak::getVoidX() const {
    return emptyX;
}

int BarleyBreak::getVoidY() const {
    return emptyY;
}

int BarleyBreak::getMovesCount() const {
    return moves;
}
