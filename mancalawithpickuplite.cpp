// Mancala with PickupLite
// designed for eclipse
//Rules: If you final piece lands on another of your holes (not your oppenents) and that hole has pieces, then you pick up all the pieces and continue.
//Another rule: If your piece lands on another of your holes and that hole is empty, you take your pieces and all pieces above into your own mancala.
//Otherwise, the rules are mostly regular intuitive. Please report any bugs that may exist.

#include <iostream>
using namespace std;

int top[7];
int bottom[7];
int left_store = 0;
int right_store = 0;
int hole;
bool free_turn;
int speed;

void printBoard() {
	cout << " ";
	for (int i = 0; i < 8; i++) {
		cout << " _____      ";
	}
	cout << endl;
	cout << " ";
	for (int i = 0; i < 8; i++) {
		cout << "/     \\     ";
	}
	cout << endl;
	cout << "|       |   ";
	for (int i = 0; i < 6; i++) {
		if (top[i + 1] < 10) {
			cout << "|   " << top[i + 1] << "   |   ";
		}
		else {
			cout << "|  " << top[i + 1] << "   |   ";
		}
	}
	cout << "|       |   ";
	cout << endl;
	cout << "|       |   ";
	cout << " ";
	for (int i = 0; i < 6; i++) {
		cout << "\\_____/    ";
		if (i != 5) {
			cout << " ";
		}
	}
	cout << "|       |";
	cout << endl;
	cout << "|       |                                                                           |       |" << endl;
	if (left_store < 10) {
		cout << "|   " << left_store;
	}
	else {
		cout << "|  " << left_store;
	}
	cout << "   |                                                                           |   " << right_store << "   |" << endl;
	cout << "|       |    ";
	for (int i = 0; i < 6; i++) {
		cout << " _____     ";
		if (i != 5) {
			cout << " ";
		}
	}
	cout << "|       |    ";
	cout << endl;
	cout << "|       |    ";
	for (int i = 0; i < 6; i++) {
		cout << "/     \\    ";
		if (i != 5) {
			cout << " ";
		}
	}
	cout << "|       |   ";
	cout << endl;
	cout << "|       |   ";
	for (int i = 0; i < 6; i++) {
		if (bottom[i + 1] < 10) {
			cout << "|   " << bottom[i + 1] << "   |   ";
		}
		else {
			cout << "|  " << bottom[i + 1] << "   |   ";
		}
	}
	cout << "|       |   ";
	cout << endl;
	cout << " \\_____/     ";
	for (int i = 0; i < 7; i++) {
		cout << "\\_____/     ";
	}
	cout << endl;
	cout << endl;
}

int nextHole(int x, int turn) {
	if (turn == 0) {
		if (x > 1 && x < 7) {
			return x - 1;
		}
		else if (x > 6 && x < 12) {
			return x + 1;
		}
		else if (x == 1) {
			return 13;
		}
		else if (x == 13) {
			return 7;
		}
		else if (x == 12) {
			return 6;
		}
	}
	if (turn == 1) {
		if (x > 1 && x < 7) {
			return x - 1;
		}
		else if (x > 6 && x < 12) {
			return x + 1;
		}
		else if (x == 12) {
			return 14;
		}
		else if (x == 14) {
			return 6;
		}
		else if (x == 1) {
			return 7;
		}
	}
	return -1;
}

void snatch(int marbles_in_hand, int current, int turn) {
	//	cout << marbles_in_hand << " " << top[current] << " " << current << endl;
	//	cout << "condition2: " << (marbles_in_hand == 1 && top[current] == 1) << endl;
	if (marbles_in_hand == 1 && top[current] == 1 && turn == 0 && current > 0 && current < 7) {
		//		cout << "here8" << endl;
		left_store += 1 + bottom[current];
		top[current] = 0;
		bottom[current] = 0;
		printBoard();
	}
	if (marbles_in_hand == 1 && bottom[current - 6] == 1 && turn == 1 && current > 6 && current < 13) {
		//		cout << "here9" << endl;
		right_store += 1 + top[current - 6];
		top[current - 6] = 0;
		bottom[current - 6] = 0;
		printBoard();
	}
}

bool freeTurn(int turn, int marbles_in_hand) {
	// unnecessary but aesthetically minimizing
	if (marbles_in_hand == 1) {
		return true;
	}
	return false;
}

void move(int current, int turn, int marbles_in_hand, bool first) {
	if (turn == 0) {
		bool print = false;
		//		cout << current << " " << marbles_in_hand << endl;
		int delay = 0;
		for (int i = 0; i < speed; i++) {
			delay++;
		}
		if (first) {
			marbles_in_hand = top[current];
			top[current] = 0;
			printBoard();
			print = true;
			//			cout << "here1" << endl;
			move(nextHole(current, turn), turn, marbles_in_hand, false);
		}
		if (!first && marbles_in_hand != 0) {
			if (current > 1 && current < 7) {
				top[current]++;
				printBoard();
				print = true;
				//				cout << "here2 " << endl;
				snatch(marbles_in_hand, current, turn);
				move(nextHole(current, turn), turn, marbles_in_hand - 1, false);
			}
			else if (current > 6 && current < 13) {
				bottom[current - 6]++;
				printBoard();
				print = true;
				//				cout << "here3" << endl;
				move(nextHole(current, turn), turn, marbles_in_hand - 1, false);
			}
			else if (current == 1) {
				top[1]++;
				printBoard();
				print = true;
				//				cout << "here4" << endl;
				snatch(marbles_in_hand, current, turn);
				move(nextHole(current, turn), turn, marbles_in_hand - 1, false);
			}
			else if (current == 13) {
				left_store++;
				printBoard();
				print = true;
				//				cout << "here5" << endl;
				if (freeTurn(turn, marbles_in_hand)) {
					free_turn = true;
				}
				move(nextHole(current, turn), turn, marbles_in_hand - 1, false);
			}
			else if (current == 12) {
				bottom[6]++;
				printBoard();
				print = true;
				//				cout << "here6" << endl;
				move(nextHole(current, turn), turn, marbles_in_hand - 1, false);
			}
		}
		if (!first && marbles_in_hand == 1 && current > 0 && current < 7 && top[current] > 1) {
			if (!print) {
				printBoard();
			}
			//			cout << "here7" << endl;
			//			cout << marbles_in_hand << endl;
			move(current, turn, marbles_in_hand, true);
		}
	}
	if (turn == 1) {
		bool print = false;
		//		cout << current << " " << marbles_in_hand << endl;
		int delay = 0;
		for (int i = 0; i < speed; i++) {
			delay++;
		}
		if (first) {
			marbles_in_hand = bottom[current - 6];
			bottom[current - 6] = 0;
			printBoard();
			print = true;
			//			cout << "here1" << endl;
			move(nextHole(current, turn), turn, marbles_in_hand, false);
		}
		if (!first && marbles_in_hand != 0) {
			if (current > 0 && current < 7) {
				top[current]++;
				printBoard();
				print = true;
				//				cout << "here2 " << endl;
				snatch(marbles_in_hand, current, turn);
				move(nextHole(current, turn), turn, marbles_in_hand - 1, false);
			}
			else if (current > 6 && current < 12) {
				bottom[current - 6]++;
				printBoard();
				print = true;
				//				cout << "here3" << endl;
				move(nextHole(current, turn), turn, marbles_in_hand - 1, false);
			}
			else if (current == 12) {
				bottom[6]++;
				printBoard();
				print = true;
				//				cout << "here4" << endl;
				snatch(marbles_in_hand, current, turn);
				move(nextHole(current, turn), turn, marbles_in_hand - 1, false);
			}
			else if (current == 14) {
				right_store++;
				printBoard();
				print = true;
				//				cout << "here5" << endl;
				if (freeTurn(turn, marbles_in_hand)) {
					free_turn = true;
				}
				move(nextHole(current, turn), turn, marbles_in_hand - 1, false);
			}
			else if (current == 1) {
				top[1]++;
				printBoard();
				print = true;
				//				cout << "here6" << endl;
				move(nextHole(current, turn), turn, marbles_in_hand - 1, false);
			}
		}
		if (!first && marbles_in_hand == 1 && current > 6 && current < 13 && top[current] > 1) {
			if (!print) {
				printBoard();
			}
			//			cout << "here7" << endl;
			//			cout << marbles_in_hand << endl;
			move(current, turn, marbles_in_hand, true);
		}
	}
}

int main() {
	for (int i = 0; i < 6; i++) {
		top[i + 1] = 4;
		bottom[i + 1] = 4;
	}
	int turn;
	cout << "Mancala (with PickupLite)" << endl;
	cout << "Player one's mancala (store) is on the left and player two's mancala is to the left." << endl;
	cout << "Please read the (modified) rules (at beginning of code) before playing." << endl;
	do {
		cout << "Who is first player? Top (0) or bottom (1)?" << endl;
		cin >> turn;
	} while (turn != 0 && turn != 1);
	do {
		cout << "What speed would you like to play the game at? (For reference: (1) slow (2) medium (3) fast (4) instantaneous)" << endl;
		cin >> speed;
	} while (speed < 1 || speed > 4);
	if (speed == 1) {
		speed = 500000000;
	}
	else if (speed == 2) {
		speed = 300000000;
	}
	else if (speed == 3) {
		speed = 100000000;
	}
	else if (speed == 4) {
		speed = 0;
	}
	bool done = false;
	printBoard();
	while (!done) {
		if (turn == 0) {
			do {
				int count_inputs = 0;
				do {
					if (count_inputs == 0) {
						cout << "Player 1 (top), it's your turn. Please select a start hole." << endl;
					}
					else {
						cout << "Player 1 (top), please select a *valid* nonempty hole." << endl;
					}
					cin >> hole;
					count_inputs++;
				} while (top[hole] == 0);
				free_turn = false;
				move(hole, turn, 0, true);
			} while (free_turn);
			turn = 1;
		}
		else if (turn == 1) {
			int count_turns = 0;
			do {
				int count_inputs = 0;
				do {
					if (count_inputs == 0 && count_turns == 0) {
						cout << "Player 2 (bottom), it's your turn. Please select a start hole." << endl;
					}
					else if (count_inputs == 0 && count_turns != 0) {
						cout << "Player 2 (bottom), it's your turn again. Please select a start hole." << endl;
					}
					else {
						cout << "Player 2 (bottom), please select a *valid* nonempty hole." << endl;
					}
					cin >> hole;
					count_inputs++;
				} while (bottom[hole] == 0);
				free_turn = false;
				move(hole + 6, turn, 0, true);
				count_turns++;
			} while (free_turn);
			turn = 0;
		}
		bool top_empty = true;
		for (int i = 1; i <= 6; i++) {
			if (top[i] != 0) {
				top_empty = false;
			}
		}
		if (top_empty) {
			for (int i = 1; i <= 6; i++) {
				right_store += bottom[i];
			}
			done = true;
			break;
		}
		bool bottom_empty = true;
		for (int i = 1; i <= 6; i++) {
			if (bottom[i] != 0) {
				bottom_empty = false;
			}
		}
		if (bottom_empty) {
			for (int i = 1; i <= 6; i++) {
				left_store += top[i];
			}
			done = true;
			break;
		}
	}
	if (left_store > right_store) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 5; j++) {
				cout << "Player 1 wins!!! The score is " << left_store << " to " << right_store << "! ";
			}
			cout << endl;
		}
	}
	if (right_store > left_store) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 5; j++) {
				cout << "Player 2 wins!!! The score is " << right_store << " to " << left_store << "! ";
			}
			cout << endl;
		}
	}
}


