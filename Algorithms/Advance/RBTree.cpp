// Delete element
// Insert without recursion
// maxDepth
// get iter count for search

#include <iostream>
#include <windows.h>
#include <string>

#define LEFT	1
#define RIGHT	2
#define NIL		NULL
enum Color { RED, BLACK };
using namespace std;

struct RBNode {
	Color color;
	int key;
	RBNode *right, *left, *parent;
};


// Needs windows.h
template <typename T>
class TreePrint {
public:
	T root;
	TreePrint(T r) {
		root = r;
	}

	void gotoXY(int x, int y) {
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	int whereX() {
		CONSOLE_SCREEN_BUFFER_INFO consoleinfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleinfo);
		return consoleinfo.dwCursorPosition.X;
	}

	int whereY() {
		CONSOLE_SCREEN_BUFFER_INFO consoleinfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleinfo);
		return consoleinfo.dwCursorPosition.Y;
	}

	int maxDepth(T root) {
		if (root == NULL) return 0;
		int left = maxDepth(root->left);
		int right = maxDepth(root->right);
		return (left > right) ? left + 1 : right + 1;
	}

	void _print(T n, int x = 40, int y = 0, int isRight = -1) {
		int tmpY = whereY();

		if (y == 0) y = tmpY;

		if (n == NULL) {
			gotoXY(x, y);
			cout << "Empty";
			return;
		}

		if (isRight == 1) {
			gotoXY(x + 2, y - 1);
			cout << "/";
		}

		if (isRight == 0) {
			gotoXY(x - 2, y - 1);
			cout << "\\";
		}

		gotoXY(x, y);
		if (n->color == RED) {
			SetConsoleTextAttribute(
				GetStdHandle(STD_OUTPUT_HANDLE), 
				FOREGROUND_RED
			);
		}
		else {
			SetConsoleTextAttribute(
				GetStdHandle(STD_OUTPUT_HANDLE),
				FOREGROUND_BLUE
			);
		}
		cout << n->key << endl;

		SetConsoleTextAttribute(
			GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN
		);

		Sleep(100);

		if (n->left != NULL) {
			_print(n->left, x - 5, y + 2, 1);
		}

		if (n->right != NULL) {
			_print(n->right, x + 5, y + 2, 0);
		}

		gotoXY(0, tmpY + maxDepth(this->root) + 4);
	}

	void print() {
		_print(root, 40, 0);
	}
};

class RBTree {
public:
	RBNode *root = NIL;
	
	void LeftRotate(RBNode* x) {
		RBNode* y = x->right;
		x->right = y->left;
		if (y->left != NIL)
			y->left->parent = x;
		y->parent = x->parent;
		if (x->parent == NIL) {
			root = y;
		}
		else {
			if (x == x->parent->left) {
				x->parent->left = y;
			}
			else {
				x->parent->right = y;
			}
		}
		y->left = x;
		x->parent = y;
	}

	void RightRotate(RBNode* x) {
		RBNode* y = x->left;
		x->left = y->right;
		if (y->right != NIL)
			y->right->parent = x;
		y->parent = x->parent;
		if (x->parent == NIL) {
			root = y;
		}
		else {
			if (x == x->parent->left) {
				x->parent->left = y;
			}
			else {
				x->parent->right = y;
			}
		}
		y->right = x;
		x->parent = y;
	}

	void RBInsertFixup(RBNode* z) {
		RBNode* y;
		cout << "Parent: " << z->parent << endl;
		while (z->parent != NIL && z->parent->color == RED) {
			
			if (z->parent == z->parent->parent->left) {
				cout << "Here#1";
				y = z->parent->parent->right;
				if (y && y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->right) {
						z = z->parent;
						LeftRotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					RightRotate(z->parent->parent);
				}
			}
			else {
				cout << "Here#2";
				y = z->parent->parent->left;
				if (y && y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->left) {
						z = z->parent;
						RightRotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					LeftRotate(z->parent->parent);
				}
			}
		}
		root->color = BLACK;
	}

	void Insert(int data) {
		RBNode* z = new RBNode;
		z->key = data;
		RBNode* y = NIL;
		RBNode* x = root;
		while (x != NIL) {
			y = x;
			if (z->key < x->key) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}
		z->parent = y; // Set Parent
		// If no parent then it is root		
		if (y == NIL) {
			root = z;
		}
		else {
			if (z->key < y->key)
				y->left = z;
			else 
				y->right = z;
		}
		z->left = NIL;
		z->right = NIL;
		z->color = RED;
		RBInsertFixup(z);
	}
	
	void inOrder(RBNode *root) {
		if (root == NULL) return;
		else {
			inOrder(root->left);
			cout << root->key << " ";
			inOrder(root->right);
		}
	}
};

int main() {
	RBTree t;

	t.Insert(10);
	t.Insert(12);

	t.Insert(5);
	t.Insert(15);
	t.Insert(25);
	t.Insert(13);
	t.Insert(30);
	t.Insert(1);
	t.Insert(-1);
	t.Insert(2);
	
	
	
	TreePrint<RBNode*> printer(t.root);
	printer.print();

	t.inOrder(t.root);

	return 0;
}