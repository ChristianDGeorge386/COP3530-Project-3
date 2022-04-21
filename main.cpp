#include <iostream>
#include <iosfwd>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

class Movie{
public:
    vector<string> genres;
    string language, overview, releaseDate, runtime, title, voteCount;
    double rating;
    Movie* parent;
    Movie* left;
    Movie* right;
    bool red;

    //Defined constructor
    Movie(vector<string> genres, string language, string overview, string releaseDate, string runtime, string title, double rating, string voteCount){
        this->genres = genres;
        this->language = language;
        this->overview = overview;
        this->releaseDate = releaseDate;
        this->runtime = runtime;
        this->title = title;
        this->rating = rating;
        this->voteCount = voteCount;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        red = true;
    }

    //Default constructor
    Movie(){

    }

    //Movie stats printer
    void printer(Movie movie){
        cout<<"---------------------------------------------------------------------------------------------"<<endl;
        cout << "Title: " << movie.title << endl;
        cout << "Genres: ";
        for(int i = 0; i < movie.genres.size(); i++){
            cout << movie.genres[i];
            if(i < movie.genres.size() - 1){
                cout << ", ";
            }
        }
        cout<<endl;
        cout << "Release Date: " << movie.releaseDate << endl;
        cout << "Overview: " << movie.overview << endl;
        cout << "Runtime: " << movie.runtime << endl;
        cout << "Rating: " << movie.rating << endl;
        cout << "Number of Votes: " << movie.voteCount << endl;
        cout << "Language: " << movie.language << endl;
        cout<<endl;
    }
};


class Heap{
public:
    void heapify_down(vector<Movie> heapArr, int size, int root);
    static bool sortCond(Movie a, Movie b);
    void finder(vector<Movie> heap, string type, double ratinghelp, string helper);
};


//heapify down to create a max heap
void Heap::heapify_down(vector<Movie> heapArr, int size, int root) {
    int val = root;
    if(heapArr[2*root+1].rating>heapArr[root].rating&&((2*root+1)<size)){
        val = 2*root+1;
    }
    if(heapArr[2*root+2].rating>heapArr[val].rating&&((2*root+2)<size)){
        val = 2*root+2;
    }
    if(val!=root){
        Movie temp;
        temp = heapArr[root];
        heapArr[root] = heapArr[val];
        heapArr[val] = temp;
        heapify_down(heapArr, size, val);
    }
}

//condition for sort
bool Heap::sortCond(Movie a, Movie b){
    return (a.rating>b.rating);
}

void Heap::finder(vector<Movie> heapArr, string type, double ratinghelp, string helper){
    vector<Movie> movies;
    if(type == "rating"){
        for(int i = 0; i<heapArr.size(); i++){
            if(heapArr[i].rating>=ratinghelp){
                movies.push_back(heapArr[i]);
            }
        }
        sort(movies.begin(), movies.end(),sortCond);
        for(int i = 0; i<movies.size(); i++){
            cout<<(i+1)<<": "<<movies[i].title<<" | Rating:"<<movies[i].rating<<endl;
        }
    }
    else if(type == "genre"){
        for(int i = 0; i<heapArr.size(); i++){
            for(string genre: heapArr[i].genres){
                if(genre==helper){
                    movies.push_back(heapArr[i]);
                }
            }
        }
        sort(movies.begin(), movies.end(),sortCond);

        for(int i = 0; i<movies.size(); i++) {
            cout<<(i+1)<<": "<< movies[i].title <<" | Genres: ";
            for (int j = 0; j < movies[i].genres.size(); j++) {
                cout << movies[i].genres[j];
                if (j + 1 <= movies[i].genres.size()) {
                    cout << ", ";
                }
            }
            cout << " | Rating:" << movies[i].rating << endl;
        }

    }
    else if(type == "movie"){
        for(int i = 0; i<heapArr.size(); i++){
            if(helper == heapArr[i].title){
                heapArr[i].printer(heapArr[i]);
            }
        }
    }
}


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
    void insert(vector<string> genres, string language, string overview, string releaseDate, string runtime, string title, double rating, string voteCount);
    void replaceChild(Movie* parent, Movie* oldChild, Movie* newChild);
    void rotateRight(Movie* movie);
    void rotateLeft(Movie* movie);
    void balance(Movie* movie);
    void find(string title);
    void findAll(double rating, string genre);
    void findAllRating(double rating);
};

//Find helper
void findHelper(Movie* node, string title)
{
    if (node != nullptr)
    {
        if (node->title == title)
        {
            cout<<"---------------------------------------------------------------------------------------------"<<endl;
            cout << "Title: " << node->title << endl;
            cout << "Genres: ";
            for(int i = 0; i < node->genres.size(); i++){
                cout << node->genres[i];
                if(i <= node->genres.size() - 1){
                    cout << ", ";
                }
            }
            cout << endl;
            cout << "Release Date: " << node->releaseDate << endl;
            cout << "Overview: " << node->overview << endl;
            cout << "Runtime: " << node->runtime << endl;
            cout << "Rating: " << node->rating << endl;
            cout << "Number of Votes: " << node->voteCount << endl;
            cout << "Language: " << node->language << endl;
        }
        if (node->left)
        {
            findHelper(node->left, title);
        }
        if (node->right)
        {
            findHelper(node->right, title);
        }
    }
}

//Find all movies helper
void findAllHelper(Movie* node, double rating, string genre)
{
    if (node != nullptr)
    {
        for (auto genreV: node->genres) {
            if (node->rating >= rating && genreV == genre) {
                cout << "Title: " << node->title << " | Rating: " << node->rating << endl;
            }
        }
        if(genre == "" && node->rating >= rating) {
            cout << "Title: " <<node->title <<" | Rating: "<<node->rating << endl;
        }
        if (node->left)
        {
            findAllHelper(node->left, rating, genre);
        }
        if (node->right)
        {
            findAllHelper(node->right, rating, genre);
        }
    }
}

//Find movie based on title
void RBTree::find(string title)
{
    findHelper(root, title);
}

//Find all movies based on genre and rating
void RBTree::findAll(double rating, string genre)
{
    findAllHelper(root, rating, genre);
}

void RBTree::findAllRating(double rating)
{
    findAllHelper(root, rating, "");
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
void RBTree::insert(vector<string> genres, string language, string overview, string releaseDate, string runtime, string title, double rating, string voteCount)
{
    Movie* movie = new Movie(genres, language,overview, releaseDate, runtime, title, rating, voteCount);
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

    ifstream movieFile(("moviedata.csv"));

    string line;
    getline(movieFile, line);
    string word;

    vector<string> row;
    vector<Movie> allMovies;
    vector<string> genres;
    RBTree tree;

    while (getline(movieFile, line)) {
        istringstream split(line);
        int wordCount = 0;
        string overviewStr = "";
        while (getline(split, word, ',')) {
            wordCount++;
            string genre = "";
            int singleQuoteCount = 0;
            for (int j = 0; j < word.size(); j++) {
                if (word[j] == 39) {
                    singleQuoteCount++;
                    continue;
                }
                if (singleQuoteCount == 3) {
                    genre += word[j];
                }
            }
            if (genre == "") {
                row.push_back(word);
            } else {
                genres.push_back(genre);
            }

        }
        overviewStr = "";
        for (int i = genres.size() + 1; i < row.size() - 5; i++) {
            overviewStr += row[i];
        }

        Movie m(genres, row[genres.size()], overviewStr, row[row.size() - 5], row[row.size() - 4], row[row.size() - 3],
                stod(row[row.size() - 2]), row[row.size() - 1]);
        allMovies.push_back(m);
        tree.insert(genres, row[genres.size()], overviewStr, row[row.size() - 5], row[row.size() - 4],
                    row[row.size() - 3], stod(row[row.size() - 2]), row[row.size() - 1]);
        row.clear();
        genres.clear();
    }
    Heap heap;
    int s = allMovies.size();
    heap.heapify_down(allMovies, s, 0);

    clock_t startHeap, endHeap, startTree, endTree;

    bool stop = false;
    while(!stop) {
        cout << "Option 1: " << "Search for a Movie" << endl;
        cout << "Option 2: " << "Search for a Genre" << endl;
        cout << "Option 3: " << "Search for Rating" << endl;
        cout << "Option 4: " << "Exit" << endl;
        int option;
        cin >> option;

        if(option == 1){
            string inputTitle = "";
            cout << "Enter movie title: ";
            cin.ignore();
            getline(cin, inputTitle);
            cout << inputTitle << endl;
            startTree = clock();
            tree.find(inputTitle);
            endTree = clock();
            startHeap = clock();
            heap.finder(allMovies, "movie", 0, inputTitle);
            endHeap = clock();

            cout << "Tree time: " << (endTree - startTree) / (float) CLOCKS_PER_SEC << " seconds" << endl;
            cout << "Heap time: " << (endHeap - startHeap) / (float) CLOCKS_PER_SEC << " seconds" << endl;
        }
        else if(option == 2){
            cout << "Enter movie genre: ";
            string inputGenre;
            cin >> inputGenre;
            cout << endl;
            startTree = clock();
            tree.findAll(0, inputGenre);
            endTree = clock();
            startHeap = clock();
            heap.finder(allMovies, "genre", 0, inputGenre);
            endHeap = clock();

            cout << "Tree time: " << (endTree - startTree) / (float) CLOCKS_PER_SEC << " seconds" << endl;
            cout << "Heap time: " << (endHeap - startHeap) / (float) CLOCKS_PER_SEC << " seconds" << endl;
        }
        else if (option == 3){
            cout << "Enter movie rating: ";
            double inputRating;
            cout << endl;
            cin>>inputRating;
            startTree = clock();
            tree.findAllRating(inputRating);
            endTree = clock();
            startHeap = clock();
            heap.finder(allMovies, "rating", inputRating, "");
            endHeap = clock();

            cout << "Tree time: " << (endTree - startTree) / (float) CLOCKS_PER_SEC << " seconds" << endl;
            cout << "Heap time: " << (endHeap - startHeap) / (float) CLOCKS_PER_SEC << " seconds" << endl;
        }
        else if (option == 4){
            cout<<"Thank you for using our Movie List"<<endl;
            cout<<"We hope you enjoy your movie!"<<endl;
            break;
        }
        else {
            cout << "Invalid input" << endl;
        }
        cout << endl;
    }
}
