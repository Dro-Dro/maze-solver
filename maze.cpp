//
// Created by Yusuf Pisan on 4/18/18.
//

#include "maze.h"
#include <algorithm>
#include <cassert>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// print maze object
ostream &operator<<(ostream &out, const Maze &maze) {
  for (int row = 0; row < maze.height; ++row) {
    for (int col = 0; col < maze.width; ++col) {
      out << maze.field[row][col];
    }
    out << endl;
  }
  out << endl;
  return out;
}

// default constructor
Maze::Maze() = default;

// Load maze file from current directory
bool Maze::load(const string &fileName) {
  ifstream inFile;
  inFile.open(fileName);
  if (!inFile.is_open()) {
    cerr << "Unable to open file: " << fileName << endl;
    // next line is just to satisfy clang-tidy
    // otherwise it complains saying function can be const
    width = height = 0;
    return false;
  }
  inFile >> width >> height;
  inFile >> exitRow >> exitColumn;
  inFile >> startRow >> startColumn;
  // ignore leftover charcaters up to newline
  inFile.ignore(INT_MAX, '\n');
  string line;
  for (int row = 0; row < height; ++row) {
    getline(inFile, line);
    field.push_back(line);
  }
  return true;
}

// // true if maze can be solved
bool Maze::solve() {
  if (startRow == exitRow && startColumn == exitColumn) {
    return true;
  }
  int posX = startRow;
  int posY = startColumn;
  return helpSolve(posX, posY);
}

// helper function for solve function
bool Maze::helpSolve(int &posX, int &posY) {
  if (atExit(posX, posY)) {
    markAsPath(posX, posY);
    return true;
  }
  markAsPath(posX, posY);
  if (isClear(posX, posY + 1) && isInside(posX, posY + 1)) {
    posY++;
    path.push_back('E');
    return helpSolve(posX, posY);
  }
  if (isClear(posX + 1, posY) && isInside(posX + 1, posY)) {
    posX++;
    path.push_back('S');
    return helpSolve(posX, posY);
  }
  if (isClear(posX, posY - 1) && isInside(posX, posY - 1)) {
    posY--;
    path.push_back('W');
    return helpSolve(posX, posY);
  }
  if (isClear(posX - 1, posY) && isInside(posX - 1, posY)) {
    posX--;
    path.push_back('N');
    return helpSolve(posX, posY);
  }
  if (!(checkPath())) {
    markAsVisited(posX, posY);
    backTrack(posX, posY);
    return helpSolve(posX, posY);
  }
  return false;
  // see readme file
}

// backtrack helper function
void Maze::backTrack(int &posX, int &posY) {
  char lastPos = path.back();
  path.pop_back();
  switch (lastPos) {
  case 'E':
    posY--;
    break;
  case 'S':
    posX--;
    break;
  case 'W':
    posY++;
    break;
  case 'N':
    posX++;
    break;
  default:
    break;
  }
}

// check if options have been exhausted
bool Maze::checkPath() const { return path.empty(); }

// path to exit
string Maze::getPath() const { return path; }

// true if row, column is the exit
bool Maze::atExit(int row, int column) const {
  return row == exitRow && column == exitColumn;
}

// true if row, column is inside the maze
bool Maze::isInside(int row, int col) const {
  return row >= 0 && col >= 0 && row < field.size() && col < field[row].size();
}

// true if row, column is clear to move
bool Maze::isClear(int row, int col) const {
  return row >= 0 && col >= 0 && row < field.size() &&
         col < field[row].size() && field[row][col] == CLEAR;
}

// mark location as part of the path to exit
void Maze::markAsPath(int row, int col) {
  assert(row >= 0 && col >= 0 && row < field.size() && col < field[row].size());
  field[row][col] = PATH;
}

// mark location as visited, not part of the path to exit
void Maze::markAsVisited(int row, int col) {
  assert(row >= 0 && col >= 0 && row < field.size() && col < field[row].size());
  field[row][col] = VISITED;
}
