#include <iostream>
#include <algorithm>
#include <string>
#include <initializer_list>
#include <vector>
#include <climits>
using namespace std;

class Node {
public:
	int value;
	Node* up;
	Node* down;
	Node* left;
	Node* right;
	Node() {
		value = -1;
		up = nullptr;
		down = nullptr;
		left = nullptr;
		right = nullptr;
	}
};

void traversal(Node* curNode, int sum, string fromWhere, vector<int>& sumArr);

int main() {
	int rows = 0, cols = 0;
	cin >> rows >> cols;
	int startingX = 0, startingY = 0;
	cin >> startingX >> startingY;
	Node*** map = new  Node * *[rows];
	vector<int> sumArr;
	for (int i = 0; i < rows; i++) {
		map[i] = new Node * [cols];
		for (int j = 0; j < cols; j++) {
			map[i][j] = new Node;
		}
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cin >> map[i][j]->value;
		}
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (j > 0 && map[i][j]->value != 0 && map[i][j - 1]->value != 0) {
				map[i][j]->left = map[i][j - 1];
				map[i][j - 1]->right = map[i][j];
			}
			if (i > 0 && map[i][j]->value != 0 && map[i - 1][j]->value != 0) {
				map[i][j]->up = map[i - 1][j];
				map[i - 1][j]->down = map[i][j];
			}
		}
	}
	traversal(map[startingY][startingX], 0, "root", sumArr);
	int min = INT_MAX;
	for (auto it : sumArr) {
		if (it < min) {
			min = it;
		}
	}
	cout << min << endl;
}

void traversal(Node* curNode, int sum, string fromWhere, vector<int>& sumArr) {
	if (curNode->value == -1) {
		return;
	}

	int numOfNullptrs = 0;
	if (curNode->up == nullptr) {
		numOfNullptrs++;
	}
	else {
		if (fromWhere != "up") {
			traversal(curNode->up, sum + curNode->value, "down", sumArr);
		}
	}
	if (curNode->down == nullptr) {
		numOfNullptrs++;
	}
	else {
		if (fromWhere != "down") {
			traversal(curNode->down, sum + curNode->value, "up", sumArr);
		}
	}
	if (curNode->left == nullptr) {
		numOfNullptrs++;
	}
	else {
		if (fromWhere != "left") {
			traversal(curNode->left, sum + curNode->value, "right", sumArr);
		}
	}
	if (curNode->right == nullptr) {
		numOfNullptrs++;
	}
	else {
		if (fromWhere != "right") {
			traversal(curNode->right, sum + curNode->value, "left", sumArr);
		}
	}
	if (numOfNullptrs == 3) {
		sumArr.push_back(sum + curNode->value);
	}
}

// 還是一樣MLE 哭啊!!!