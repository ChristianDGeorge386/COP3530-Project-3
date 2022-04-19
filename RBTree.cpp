#include <iostream>
using namespace std;

//Movie struct that will act as nodes in red-black tree
struct Movie
{
	double rating;
	int ratingCount;
	int runtime;
	string releaseDate;
	string language;
	string overview;
	string name;
	string genre;
	Movie* parent;
	Movie* left;
	Movie* right;
	bool red;

	//Default constructor
	Movie() {};

	//Defined constructor
	Movie(double _rating, int _ratingCount, int _runtime, string _releaseDate, string _language, string _overview, string _name, string _genre)
	{
		rating = _rating;
		ratingCount = _ratingCount;
		runtime = _runtime;
		releaseDate = _releaseDate;
		language = _language;
		overview = _overview;
		name = _name;
		genre = _genre;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		red = true;
	}
};

//RBTree class
class RBTree 
{
private:
	Movie* root;
	Movie* blank;

public:
	RBTree() 
	{
		blank = new Movie;
		blank->left = nullptr;
		blank->right = nullptr;
		blank->red = false;
		root = blank;
	}
	void insert(double rating, int ratingCount, int runtime, string releaseDate, string language, string overview, string name, string genre);
	void replaceChild(Movie* parent, Movie* oldChild, Movie* newChild);
	void rotateRight(Movie* movie);
	void rotateLeft(Movie* movie);
	void balance(Movie* movie);
	void find(string name);
	void findAll(double rating, string genre);
};

//Find helper
void findHelper(Movie* node, string name)
{
	if (node != nullptr)
	{
		if (node->name == name)
		{
			cout << "Name: " << node->name << endl;
			cout << "Genre: " << node->genre << endl;
			cout << "Release Date: " << node->releaseDate << endl;
			cout << "Overview: " << node->overview << endl;
			cout << "Runtime: " << node->runtime << endl;
			cout << "Rating: " << node->rating << endl;
			cout << "Rating Count: " << node->ratingCount << endl;
			cout << "Language: " << node->language << endl;
		}
		if (node->left)
		{
			findHelper(node->left, name);
		}
		if (node->right)
		{
			findHelper(node->right, name);
		}
	}
}

//Find all movies helper
void findAllHelper(Movie* node, double rating, string genre)
{
	if (node != nullptr)
	{
		if (node->rating >= rating && node->genre == genre)
		{
			cout << "Name: " << node->name << endl;
		}
		if (node->left && node->left->rating >= rating)
		{
			findAllHelper(node->left, rating, genre);
		}
		if (node->right && node->right->rating >= rating)
		{
			findAllHelper(node->right, rating, genre);
		}
	}
}

//Find movie based on name
void RBTree::find(string name)
{
	findHelper(root, name);
}

//Find all movies based on genre and rating
void RBTree::findAll(double rating, string name)
{
	findAllHelper(root, rating, name);
}

//Replace child in rotation
void RBTree::replaceChild(Movie* parent, Movie* oldChild, Movie* newChild)
{
	if (parent == nullptr) 
		root = newChild;
	else if (parent->right == oldChild)
		parent->right = newChild;
	else if (parent->left == oldChild) 
		parent->left = newChild;

	if (newChild != nullptr)
		newChild->parent = parent;
}

//Rotate right
void RBTree::rotateRight(Movie* movie)
{
	//Create poiners to parent and child
	Movie* parent = movie->parent;
	Movie* left = movie->left;

	//Reassign movie's left to left's right node
	movie->left = left->right;
	if (left->right != nullptr)
		left->right->parent = movie;

	left->right = movie;
	movie->parent = left;
	replaceChild(parent, movie, left);
}

//Rotate left
void RBTree::rotateLeft(Movie* movie)
{
	//Create pointers to parent and child
	Movie* parent = movie->parent;
	Movie* right = movie->right;

	//Reassign movie's right to right's left node
	movie->right = right->left;
	if (right->left != nullptr) 
		right->left->parent = movie;

	right->left = movie;
	movie->parent = right;
	replaceChild(parent, movie, right);
}

//Balance newly inserted node
void RBTree::balance(Movie* movie)
{
	//If movie is root, color it black
	if (movie->parent == nullptr)
	{
		movie->red = false;
		return;
	}

	//If movie is directly under root, keep it red
	else if (movie->parent->parent == nullptr)
		return;

	Movie* tempPtr;

	//While the parent's color is red, balance tree
	while (movie->parent->red == true) 
	{
		//Find appropriate uncle to current node
		if (movie->parent == movie->parent->parent->right) 
		{
			tempPtr = movie->parent->parent->left;

			//If uncle is red, perform color flip. Repoint movie to grandparent to check if more balancing is needed.
			if (tempPtr->red == true) 
			{
				tempPtr->red = false;
				movie->parent->red = false;
				movie->parent->parent->red = true;
				movie = movie->parent->parent;
			}
			//If uncle is black, perform appropriate rotations
			else 
			{
				if (movie == movie->parent->left) 
				{
					movie = movie->parent;
					rotateRight(movie);
				}
				movie->parent->red = false;
				movie->parent->parent->red = true;
				rotateLeft(movie->parent->parent);
			}
		}
		else {
			tempPtr = movie->parent->parent->right;

			//If uncle is red, perform color flip. Repoint movie to grandparent to check if more balancing is needed.
			if (tempPtr->red == true) 
			{
				tempPtr->red = false;
				movie->parent->red = false;
				movie->parent->parent->red = true;
				movie = movie->parent->parent;
			}
			//If uncle is black, perform appropriate rotations
			else 
			{
				if (movie == movie->parent->right) 
				{
					movie = movie->parent;
					rotateLeft(movie);
				}
				movie->parent->red = false;
				movie->parent->parent->red = true;
				rotateRight(movie->parent->parent);
			}
		}
		if (movie == root)
			break;
	}
	//Keep root node black
	root->red = false;
}

//RBTree insert function
void RBTree::insert(double rating, int ratingCount, int runtime, string releaseDate, string language, string overview, string name, string genre)
{
	Movie* movie = new Movie(rating, ratingCount, runtime, releaseDate, language, overview, name, genre);
	movie->left = blank;
	movie->right = blank;

	Movie* tempPtr = nullptr;
	Movie* rootPtr = root;

	//Find parent node of new movie
	while (rootPtr != blank)
	{
		tempPtr = rootPtr;
		//If movie rating is less, move to left of current node. Otherwise, move to right
		if (movie->rating < rootPtr->rating)
			rootPtr = rootPtr->left;
		else
			rootPtr = rootPtr->right;
	}

	//Place movie at left or right of parent
	movie->parent = tempPtr;
	if (tempPtr == nullptr)
		root = movie;
	else if (movie->rating < tempPtr->rating)
		tempPtr->left = movie;
	else
		tempPtr->right = movie;
	
	balance(movie);
}

int main() {
	RBTree tree;
	tree.insert(3.0, 1, 1, "today", "English", "Fun", "Capturew", "Adventure");
	tree.insert(1.0, 1, 1, "today", "English", "Fun", "CaptureS", "Adventure");
	tree.insert(5.0, 1, 1, "today", "English", "Fun", "CaptureT", "Adventure");
	tree.insert(7.0, 1, 1, "today", "English", "Fun", "CaptureF", "Adventure");
	tree.insert(6.0, 1, 1, "today", "English", "Fun", "Captureg", "Adventure");
	tree.insert(8.0, 1, 1, "today", "English", "Fun", "Capturej", "Adventure");
	tree.insert(9.0, 1, 1, "today", "English", "Fun", "Capturenm", "Adventure");
	tree.insert(10.0, 1, 1, "today", "English", "Fun", "Capturel", "Adventure");
	tree.findAll(1.0, "Adventure");
	return 0;
}