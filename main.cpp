#include <cstring>
#include <iostream>
using namespace std;

///=========CLASSES==============

class Card {
private:
    char* name;
    const int id; //max=78
    static int totalCards;
    char arcana;
    bool reversed;
    float energy;
    char* meaning;
public:
    Card();
    Card( char* name,char arcana, float energy, char* meaning);
    Card(const Card&);
    Card& operator=(const Card& obj);
    ~Card();
};

class Deck {
private:
    Card *cards;
    static int totalDecks;
    const int id;
    float price;
    int* scores; //1-career 2-love 3-self
    int hope;
public:
    Deck();
    Deck(Card *cards, float price, int* scores, int hope);
};

class Player {
private:
    char* name;
    char* job;
    double money;
    long confusionLevel;
    bool active; //if confusion level=max>>>>>bye
public:
    Player();
    Player(char* name, char* job, double money,long confusionLevel, bool active );
};

class Session {
private:
    char domain; // Love-Career-Self
    double price;
    char* type; //Open or Yes/No

    //if open:
    char* spread; //general, specific

    //if specific:
    int nrDrawnCard;
    Card* drawnCards;

    //if yes or no:
    bool answer;

public:
    Session();
    Session(char domain, char* type, double price);
};

///============STATICS==============

int Card::totalCards=0;
int Deck::totalDecks=0;

///============CONSTRUCTORS============

//====CARD

Card::Card() :id(++totalCards){
    name=strcpy(new char[4], "N/A");
    arcana='?';
    reversed= false;
    energy=0.0;
    meaning=strcpy(new char[4], "N/A");
}

Card::Card(char* name, char arcana, float energy, char* meaning):id(++totalCards) {
    this->name=strcpy(new char[strlen(name)+1],name);
    this->arcana=arcana;
    this->energy=energy;
    this->meaning=strcpy(new char[strlen(meaning)+1],meaning);
    this->reversed=false;
}

Card::Card(const Card& obj):id(obj.id){
    this->name=strcpy(new char[strlen(obj.name)+1], obj.name);
    this->arcana=obj.arcana;
    this->energy=obj.energy;
    this->meaning=strcpy(new char[strlen(obj.meaning)+1], obj.meaning);
    this->reversed=obj.reversed;
}

Card& Card::operator=(const Card& obj){
    if (this==&obj) return *this;

    delete[] name;
    delete[] meaning;

    this->name=strcpy(new char[strlen(obj.name)+1], obj.name);
    this->arcana=obj.arcana;
    this->energy=obj.energy;
    this->meaning=strcpy(new char[strlen(obj.meaning)+1], obj.meaning);
    this->reversed=obj.reversed;

    return *this;
}

Card::~Card() {
    if (name!=nullptr) {
        delete[] name;
        name=nullptr;
    }
    if (meaning!=nullptr) {
        delete[] meaning;
        meaning=nullptr;
    }
}



int main() {
    return 0;

}