/*
* game.cpp
* The first assignment practicing recursion, two computers play against
* eachother using recursive thinking to simulate a human brain
* they try to find the quickest way to 0 through recursive calls
* Alex Testani
* May 27th, 2018
*/

#include <iostream>
#include <vector>

using namespace std;

int countWins = 0;
vector<int> movelist; //global vector to store cached moves

//counts all possible paths to victory
// CRASHES ON BIG INPUTS BE WARY
void countWinnings(int n, bool myTurn) {
  if(n <= 0)
    return;

  if(n == 1 || n == 3 || n == 4) {
    if(myTurn)
      countWins += 1;
    return;
  }
  countWinnings(n - 4, !myTurn);
  countWinnings(n - 3, !myTurn);
  countWinnings(n - 1, !myTurn);
}

// This is also the "efficient" version, it didn't crash on me, but it definitely slows down when its a big load
// pick2Zero_CC_Helper goes through n recursively finding the fastest path to victory
// It alternates turns to "predict" what the players next move will be (not that smart though, always assumes 4)
// uses a global cache to store the moves to victory, then returns true if a path is found, false if there's no path
bool pick2Zero_CC_Helper(int n, bool myTurn, vector<int> pastMoves) {
  if(n <= 0)
    return !myTurn; //if computer makes an illegal move, redo turn

  if(myTurn) {
    vector<int> turnset1 = pastMoves; //caches for all the previous moves made
    vector<int> turnset2 = pastMoves;
    vector<int> turnset3 = pastMoves;

    turnset1.push_back(1); // append 1 to end of turnset1
    turnset2.push_back(3); // append 3 to end of turnset2
    turnset3.push_back(4); // append 4 to end of turnset3

    if(n == 4) { //if n = 4 winning path is found
      movelist = turnset3; //store current moves made into movelist
      return true;
    }
    else if(n == 3) { //if n = 3 winning path is found
      movelist = turnset2; //store current moves made into movelist
      return true;
    }
    else if(n == 1) { //if n = 1 winning path is found
      movelist = turnset1; //store current moves made into movelist
      return true;
    }
    else if(n == 2) //if n = 2, guaranteed loss no hope for computer
      return false;
    else { //recurse until a path to 0 is made and is valid
      return pick2Zero_CC_Helper(n - 4, !myTurn, turnset3) ||
      pick2Zero_CC_Helper(n - 3, !myTurn, turnset2) ||
      pick2Zero_CC_Helper(n - 1, !myTurn, turnset1);
    }
  }
  else { //predict opponents moves recusrively
      return pick2Zero_CC_Helper(n - 4, !myTurn, pastMoves) ||
      pick2Zero_CC_Helper(n - 3, !myTurn, pastMoves) ||
      pick2Zero_CC_Helper(n - 1, !myTurn, pastMoves);
  }
}

//recusrive function to decide computers move
int computerPlays(int n) {
  vector<int> pastMoves;
  bool canWin = pick2Zero_CC_Helper(n, true, pastMoves);

  if(canWin) //if pick2Zero_CC_Helper returns true, returns first move made in cache
    return movelist[0];
  else // if there is no route to victory, return 1 because it's most likely n = 2 on the computers turn
    return 1;
}

// Used to play pick2Zero with two computer players
void pick2Zero_CC_efficient(int n) {
  int vComp1 = 0;
  int vComp2 = 0;

  while(true) {
    cout << "n is currently " << n << endl;
    cout << "COMPUTER1: Please enter your move (4, 3, 1): " << endl;
    vComp1 = computerPlays(n); //get computer input
    cout << "COMPUTER1: " << vComp1 << endl;
    n -= vComp1; //subtract from n
    if(n == 0) { //check win
      cout << "COMPUTER1 WINS!!" << endl;
      break;
    }
    cout << "n is currently " << n << endl;
    cout << "COMPUTER2: Please enter your move (4, 3, 1): " << endl;
    vComp2 = computerPlays(n); //get computer input
    cout << "COMPUTER2: " << vComp2 << endl;
    n -= vComp2; //subtract from n
    if(n == 0) { //check win
      cout << "COMPUTER2 WINS!!" << endl;
      break;
    }
  }
}

//checks if player move is legal
bool checkMove(int n) {
  switch(n) {
    case 4:
      return true;
    case 3:
      return true;
    case 1:
      return true;
    default:
      return false;
  }
}

//Used to play pick2Zero with human vs computer
void pick2Zero_HC(int n) {
  int input = 0; //player move
  int vComp = 0; //computer move

  while(true) {
    while(!checkMove(input)) { //make sure move is legal
      cout << "n is currently " << n << endl;
      cout << "PLAYER1: Please enter your move (4, 3, 1): " << endl;
      cin >> input; //get player input
    }
    n -= input; //subtract from n
    if(n == 0) { //check win
      cout << "PLAYER1 WINS!!" << endl;
      break;
    }
    cout << "n is currently " << n << endl;
    cout << "COMPUTER: Please enter your move (4, 3, 1): " << endl;
    vComp = computerPlays(n); //get computer input
    cout << vComp << endl;
    n -= vComp; //subtract from n
    if(n == 0) { //check win
      cout << "COMPUTER WINS!!" << endl;
      break;
    }
  }
}


// main method
int main() {
  int n = 30; // change to play around
  //pick2Zero_HC(n); uncomment if you want to play
  pick2Zero_CC_efficient(n);
  //countWinnings(n, true);
  cout << countWins << endl;
}
