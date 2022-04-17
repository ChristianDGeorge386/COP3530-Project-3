#include <iostream>
#include <iosfwd>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Movie{
public:
    vector<string> genres;
    string originalLanguage, overview, releaseDate, runtime, title, voteCount;
    double rating;

    Movie(vector<string> genres, string originalLanguage, string overview, string releaseDate, string runtime, string title, double rating, string voteCount){
        this->genres = genres;
        this->originalLanguage = originalLanguage;
        this->overview = overview;
        this->releaseDate = releaseDate;
        this->runtime = runtime;
        this->title = title;
        this->rating = rating;
        this->voteCount = voteCount;
    }
};

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

}