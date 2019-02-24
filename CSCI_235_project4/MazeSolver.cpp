/**
@author Karanveer Singh
@project Project 4
@file MazeSolver.cpp
@date 11/6/2018

This file is the implentation of the class MazeSolver
*/

#include "MazeSolver.h"

//constructor
//pre: input file is in correct format with first two values being integers
//      followed by valid maze characters in {'_', '*','$'}
//post: if inuput file cannot be read outputs "Cannot read from input_file"
//      otherwise sets maze_rows_ and maze_columns_ from the first two values in input file
//      and allocates two 2-dimesional array of size maze_rows_ and maze_columns_
//      both maze_ and solution_ are initialized with characters read from input
MazeSolver::MazeSolver(std::string input_file)
{
    std::ifstream in_file(input_file);

    if(in_file.fail())
      std::cout << "Cannot read from " << input_file << std::endl;
    else
    {
      // set the number of rows and columns
      in_file >> maze_rows_ >> maze_columns_;

      initializeMaze(maze_rows_, maze_columns_);

      fillMaze(in_file);

      initializeSolution();

      maze_ready = true;
    }

    in_file.close();
}


//pre: rows and columns are positive integers
//post: allocates maze_ with rows and columns
//called by constructor
void MazeSolver::initializeMaze(int rows, int columns)
{
  maze_ = new char* [rows];

  for(int i = 0; i < rows; i++)
    maze_[i] = new char [columns];
}


//pre: maze_ has been allocated with the correct number of rows and columns read from input file
//post: fills in maze_ with characters read from input file
//called by constructor
void MazeSolver::fillMaze(std::ifstream& input_stream)
{
  while(input_stream)
  {
    for(int i = 0; i < maze_rows_; i++)
    {
      for(int j = 0; j < maze_columns_; j++)
      {
        input_stream >> maze_[i][j];
      }
    }
  }
}


//pre: maze_ has been initialized with valid character values in {'_', '*','$'}
//     start position is always [0][0]
//post: initializes solution_ with a copy of maze_
//      initializes backtrack_stack_  with all viable paths from position [0][0]
//      and mark the current position as visited ( '>' ) on solution_
//called by constructor
void MazeSolver::initializeSolution()
{
  solution_ = new char* [maze_rows_];

  for(int i = 0; i < maze_rows_; i++)
    solution_[i] = new char [maze_columns_];

  copyMazetoSolution();
}


//pre: maze_ has been properly initialized
//post: allocates solution_ to the correct number of rows and columns
//      and copies the contents of maze_ into solution_
//called by initializeSolution()
void MazeSolver::copyMazetoSolution()
{
  for(int i = 0; i < maze_rows_; i++)
  {
    for(int j = 0; j < maze_columns_; j++)
      solution_[i][j] = maze_[i][j];
  }
}


// destructor
//post: deletes maze_ and solution_
MazeSolver::~MazeSolver()
{
  if(maze_rows_ != 0 && maze_columns_ != 0)
  {
    // Deallocate dynamic memory from maze_
    for(int i  = 0; i < maze_rows_; i++)
      delete [] maze_[i];

    delete [] maze_;

    // Deallocate dynamic memory from solution_
    for(int i  = 0; i < maze_rows_; i++)
      delete [] solution_[i];

    delete [] solution_;
  }
}


//return: true if maze has been initialized, false otherwise
bool MazeSolver::mazeIsReady()
{
  return maze_ready;
}


//pre: maze_ has been initialized with valid character values in {'_', '*','$'}
//post: solution_ has been marked with '>' signs along the path to the exit
//      prints "Found the exit!!!" if exit is found
//      or "This maze has no solution." if no exit could be found
//return: true if exit is found, false otherwise
bool MazeSolver::solveMaze()
{
  bool solved = false;

  Position current_position;

  // Initialize current position to [0,0]
  current_position.row = 0;
  current_position.column = 0;

  // Initialize the stack with the current position and its initial extensible positions
  backtrack_stack_.push(current_position);
  extendPath(current_position);

  while(!backtrack_stack_.empty() && !solved)
  {
    if(maze_[current_position.row][current_position.column] == '$')
    {
      std::cout << "Found the exit!!!" << std::endl;

      solved = true;
    }

    else if(extendPath(current_position))
    {
      // Mark current_position on the solution maze as PATH (>)
      solution_[current_position.row][current_position.column] = '>';

      // Set the current_position to the position at the top of the stack to move forward
      current_position = backtrack_stack_.top();
    }

    else
    {
      // Mark current_position as VISITED (X) on maze_
      maze_[current_position.row][current_position.column] = 'X';

      // Mark current_position as BACKTRACKED (@) on solution_
      solution_[current_position.row][current_position.column] = '@';

      // Backtrack
      backtrack_stack_.pop();

      if(!backtrack_stack_.empty())

        // Move the current_position forward
        current_position = backtrack_stack_.top();

      else
      {
        std::cout << "This maze has no solution." << std::endl;

        solved = false;
      }
    }

  } // end while

  return solved;
}


//pre: current_position is a valid position on the maze_
//post: adds all positions extensible from current_position to backtrack_stack_
//return: true if path was extended, false otherwise
//called by solveMaze()
bool MazeSolver::extendPath(Position current_position)
{
  bool extended = false;

  if(isExtensible(current_position, SOUTH))
  {
    backtrack_stack_.push(getNewPosition(current_position, SOUTH));
    extended = true;
  }

  if(isExtensible(current_position, EAST))
  {
    backtrack_stack_.push(getNewPosition(current_position, EAST));
    extended = true;
  }

  return extended;
}


//pre: old_position is a Position initialized with row and column to valid positions in maze_ and it is extensible in direction dir
//return: a new Position on the maze moving in direction dir from old_position
//called by extendPath()
Position MazeSolver::getNewPosition(Position old_position, direction dir)
{
  Position new_position;

  if(dir == SOUTH)
  {
    // the new row is the next one down
    new_position.row = old_position.row + 1;
    new_position.column = old_position.column;
  }
  else if(dir == EAST)
  {
    new_position.row = old_position.row;
    // the new column is the next one over
    new_position.column = old_position.column + 1;
  }

  return new_position;
}


//checks if the path can be extended in maze_ from position current_position in direction dir
//return: true if path can be extended given current_position and dir, false otherwise
//called by extendPath
bool MazeSolver::isExtensible(Position current_position, direction dir)
{
  bool extensible = false;

  // if the direction is SOUTH and the next row will be within the boundaries of the maze
  if(dir == SOUTH && current_position.row + 1 < maze_rows_)
  {
    if(maze_[current_position.row + 1][current_position.column] == '_' ||
    maze_[current_position.row + 1][current_position.column] == '$')

      extensible = true;
  }

  // if the direction is EAST and the next column will be within the boundaries of the maze
  else if(dir == EAST && current_position.column + 1 < maze_columns_)
  {
    if(maze_[current_position.row][current_position.column + 1] == '_' ||
    maze_[current_position.row][current_position.column + 1] == '$')

      extensible = true;
  }

  return extensible;
}


//post: prints the solution to the standard output stream
//      with single space character between each maze character
//      and each maze row on a new line
void MazeSolver::printSolution()
{
  std::cout << "The solution to this maze is:" << std::endl;

  for(int i = 0; i < maze_rows_; i++)
  {
    for(int j = 0; j < maze_columns_; j++)
    {
      std::cout << solution_[i][j] << " ";
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;
}
