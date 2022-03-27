#ifndef BARLEYBREAK_H
#define BARLEYBREAK_H

class BarleyBreak {
    public:
        BarleyBreak();
        void startGame();
        bool isFinished() const;
        int getVoidY() const;
        int getVoidX() const;
        void restartGame();
        void MoveWhenClicked(int a, int b);
        int getMovesCount() const;
        int getNumber(int i, int j) const;
    private:
        int moves;
        int table [4][4];
        int cpyTable[4][4];
        int RightTable[4][4];
        int emptyX;
        int emptyY;
    };
#endif // BARLEYBREAK_H
