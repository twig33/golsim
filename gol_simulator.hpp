#ifndef GOL_SIMULATOR_HPP_
#define GOL_SIMULATOR_HPP_

#include <vector>

/*
Argument: 2d matrix representing game of life state
1 means a live cell and 0 means a dead cell
Return value: 2d matrix of the next state
*/
std::vector<std::vector<int>> NextState(std::vector<std::vector<int>> &state);

//Returns a randomly generated game of life state of a given width and height
std::vector<std::vector<int>> RandomState(const int width, const int height);

#endif // GOL_SIMULATOR_HPP_