/**
 * HOMEWORK 1
 * Aim: Solve the 8-Puzzle using Breadth-First Search algorithm
 *
 * Author: Sukrucan Taylan Isikoglu
 **/
#include <vector>
#include <deque>
#include <set>
#include <iostream>
#include <algorithm>

//Initial state
std::vector<int> state{2, 8, 3, 1, 6, 4, 7, -1, 5};
//The state we are aiming for
std::vector<int> endState{1, 2, 3, 8, -1, 4, 7, 6, 5};

//Holds the states we will discover
//We use a double ended queue as a FIFO by pushing from front of the queue and popping at the back of the queue 
std::deque<std::vector<int>> searchQueue;
//Holds the states that are already discovered
//We use a set since searching existing elements is a O(logn) operation
std::set<std::vector<int>> discoveredSet;

//Prints the vector in 3x3 form on console
void printVector(std::vector<int>& vec);

int main() {
	std::cout << "Starting..." << std::endl;

	std::vector<int> tmp(state.size());
	searchQueue.push_front(state);
	
	int step = 0;

	while(!searchQueue.empty()) {
		step++;
		
		tmp = searchQueue.front();
		searchQueue.pop_front();
		discoveredSet.insert(tmp);

		//Index of the -1, which represents the empty tile
		int empty_index = std::distance(tmp.begin(), std::find(tmp.begin(), tmp.end(), -1));

		//We reached our goal
		if (tmp == endState) {
			std::cout << "Program reached its goal in " << step << " steps!" << std::endl;
			printVector(tmp);
			return 0;
		}
		
		/**
		 * We need to visit every neighbor in state space
		 * To do that we need to move empty space in current state(tmp) up, down, left, right
		 * up = -3
		 * down = +3
		 * left = -1
		 * right = +1
		 **/
		
		/**
		 * Check the validity of the moves first, then do the move
		 * If this state has not been discovered yet or is not in the queue already, push it into the queue
		 * Then restore back the move for next trial.
		 **/
		//UP
		if (empty_index-3 >= 0) {
			std::swap(tmp.at(empty_index), tmp.at(empty_index-3));
			if (discoveredSet.count(tmp) != 1 &&
					std::find(searchQueue.begin(), searchQueue.end(), tmp) == searchQueue.end()) {
				searchQueue.push_back(tmp);	
			}		
			std::swap(tmp.at(empty_index), tmp.at(empty_index-3));
		}
		//DOWN
		if (empty_index+3 <= tmp.size()-1) {
			std::swap(tmp.at(empty_index), tmp.at(empty_index+3));
			if (discoveredSet.count(tmp) != 1 &&
					std::find(searchQueue.begin(), searchQueue.end(), tmp) == searchQueue.end()) {
				searchQueue.push_back(tmp);	
			}		
			std::swap(tmp.at(empty_index), tmp.at(empty_index+3));	
		}
		//LEFT
		if (empty_index % 3 != 0) {
			std::swap(tmp.at(empty_index), tmp.at(empty_index-1));
			if (discoveredSet.count(tmp) != 1 &&
					std::find(searchQueue.begin(), searchQueue.end(), tmp) == searchQueue.end()) {
				searchQueue.push_back(tmp);	
			}		
			std::swap(tmp.at(empty_index), tmp.at(empty_index-1));
		}
		//RIGHT
		if ((empty_index+1) % 3 != 0) {
			std::swap(tmp.at(empty_index), tmp.at(empty_index+1));
			if (discoveredSet.count(tmp) != 1 &&
					std::find(searchQueue.begin(), searchQueue.end(), tmp) == searchQueue.end()) {
				searchQueue.push_back(tmp);	
			}		
			std::swap(tmp.at(empty_index), tmp.at(empty_index+1));
		}
		//printVector(tmp);
	}
	std::cout << "Could not find solution in " << step << " steps..." << std::endl;

	return 0;
}

void printVector(std::vector<int>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
		if ((i+1)%3 == 0 && i != 0) {
			std::cout << std::endl;
		}
	}
}
