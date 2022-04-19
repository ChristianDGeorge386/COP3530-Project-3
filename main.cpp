#include <iostream>
#include <iosfwd>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Movie{
public:
    vector<string> genres;
    string language, overview, releaseDate, runtime, title, voteCount;
    double rating;

    Movie(vector<string> genres, string language, string overview, string releaseDate, string runtime, string title, double rating, string voteCount){
        this->genres = genres;
        this->language = language;
        this->overview = overview;
        this->releaseDate = releaseDate;
        this->runtime = runtime;
        this->title = title;
        this->rating = rating;
        this->voteCount = voteCount;
        Movie* parent;
        Movie* left;
        Movie* right;
        bool red;
    }

    Movie(){

    }
    
    Movie printer(Movie movie){
        cout << "Title: " << movie.title << endl;
        cout << "Genres: ";
        for(int i = 0; i < movie.genres.size(); i++){
            if(i == movie.genres.size() - 1){
                cout << movie.genres[i] << ", ";
            }
            cout << movie.genres[i];
        }
        cout << "Release Date: " << movie.releaseDate << endl;
        cout << "Overview: " << movie.overview << endl;
        cout << "Runtime: " << movie.runtime << endl;
        cout << "Rating: " << movie.rating << endl;
        cout << "Rating Count: " << movie.voteCount << endl;
        cout << "Language: " << movie.language << endl;
    }
};


class Heap{
public:
    void createHeap(vector<Movie> movies);
    void heapify_down(Movie heapArr[], int size, int root);
    static bool sortCond(Movie a, Movie b);
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
            cout<<i<<": "<< heap[i].title <<" Rating:" << heap[i].rating << endl;
        }
    }
    else if(type == "genre"){
        for(int i = 0; i<size; i++){
            for(string genre: heap[i].genres){
                if(genre==helper){
                    movies.push_back(heap[i]);
                }
            }
        }
        sort(movies.begin(), movies.end(),sortCond);
        for(int i = 0; i<movies.size(); i++){
            cout<<i<<": "<<heap[i].title<<" Rating:"<<heap[i].rating<<endl;
        }
    }
    else if(type == "movie"){
        for(int i = 0; i<size; i++){
            if(helper == heap[i].title){
                printer(heap[i]);
            }
        }
    }
}

int main() {

    ifstream movieFile(("moviedata.csv"));

    string line;
    getline(movieFile, line);
    string word;

    vector<string> row;
    vector<Movie> allMovies;
    vector<string> genres;

    while(getline(movieFile, line)){
        istringstream split(line);
        int wordCount = 0;
        string overviewStr = "";
        while(getline(split, word, ',')) {
            wordCount++;
            string genre = "";
            int singleQuoteCount = 0;
            for (int j = 0; j < word.size(); j++) {
                if(word[j] == 39) {
                    singleQuoteCount++;
                    continue;
                }
                if(singleQuoteCount == 3) {
                    genre += word[j];
                }
            }
            if(genre == ""){
                row.push_back(word);
            }
            else{
                genres.push_back(genre);
            }

        }
        overviewStr = "";
        for(int i = genres.size() + 1; i < row.size() - 5; i++){
            overviewStr += row[i];
        }

        Movie m(genres,row[genres.size()],overviewStr,row[row.size() - 5],row[row.size() - 4],row[row.size() - 3],stod(row[row.size() - 2]),row[row.size() - 1]);
        allMovies.push_back(m);
        row.clear();
        genres.clear();
    }
    Heap heap;
    heap.createHeap(allMovies);

}