#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Movie
{
    int rating;
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
    }
    Movie(){

    }
};

class Heap{
    public:
        void createHeap(vector<Movie> movies);
        void heapify_down(Movie heapArr[], int size, int root);
        bool sortCond(Movie a, Movie b);
        void finder(Movie heap[], string type, double ratinghelp, string helper);
        void printer(Movie movie);   
};

void Heap::createHeap(vector<Movie> movies){
    Movie heapArr[movies.size()];
    for(int i = 0; i<movies.size(); i++){
        heapArr[i] = movies[i];
    }
    int size = sizeof(heapArr)/sizeof(heapArr[0]);
    heapify_down(heapArr, size, 0);
}

void Heap::heapify_down(Movie heapArr[], int size, int root) {
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

bool Heap::sortCond(Movie a, Movie b){
    return (a.rating<b.rating);
}

void Heap::finder(Movie heap[], string type, double ratinghelp, string helper){
    vector<Movie> movies;
    int size = sizeof(heap)/sizeof(heap[0]);
    if(type == "rating"){
        for(int i = 0; i<size; i++){
            if(heap[i].rating>ratinghelp){
                movies.push_back(heap[i]);
            }
        }
        sort(movies.begin(), movies.end(),sortCond);
        for(int i = 0; i<movies.size(); i++){
            cout<<i<<": "<<heap[i].name<<" Rating:"<<heap[i].rating<<endl;
        }
    }
    else if(type == "genre"){
        for(int i = 0; i<size; i++){
            if(heap[i].genre==helper){
                movies.push_back(heap[i]);
            }
        }
        sort(movies.begin(), movies.end(),sortCond);
        for(int i = 0; i<movies.size(); i++){
            cout<<i<<": "<<heap[i].name<<" Rating:"<<heap[i].rating<<endl;
        }
    }
    else if(type == "movie"){
        for(int i = 0; i<size; i++){
            if(helper == heap[i].name){
                printer(heap[i]);
            }
        }
    }
}
void Heap::printer(Movie movie){
    cout << "Name: " << movie.name << endl;
    cout << "Genre: " << movie.genre << endl;
	cout << "Release Date: " << movie.releaseDate << endl;
	cout << "Overview: " << movie.overview << endl;
	cout << "Runtime: " << movie.runtime << endl;
	cout << "Rating: " << movie.rating << endl;
	cout << "Rating Count: " << movie.ratingCount << endl;
	cout << "Language: " << movie.language << endl;
}

int main(){
    Heap heap;

    vector<Movie> movies;
    Movie movie(3.0, 1, 1, "today", "English", "Fun", "Capturew", "Adventure");
    movies.push_back(movie);
    Movie movie1(1.0, 1, 1, "today", "English", "Fun", "CaptureS", "Adventure");
    movies.push_back(movie1);
    Movie movie2(5.0, 1, 1, "today", "English", "Fun", "CaptureT", "Adventure");
    movies.push_back(movie2);
    Movie movie3(7.0, 1, 1, "today", "English", "Fun", "CaptureF", "Adventure");
    movies.push_back(movie3);
    Movie movie4(6.0, 1, 1, "today", "English", "Fun", "Captureg", "Adventure");
    movies.push_back(movie4);
    Movie movie5(8.0, 1, 1, "today", "English", "Fun", "Capturej", "Adventure");
    movies.push_back(movie5);
    Movie movie6(9.0, 1, 1, "today", "English", "Fun", "Capturenm", "Adventure");
    movies.push_back(movie6);
    Movie movie7(10.0, 1, 1, "today", "English", "Fun", "Capturel", "Adventure");
    movies.push_back(movie7);

    
    heap.createHeap(movies);
}