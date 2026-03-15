#include <iostream>
using namespace std;



///=========CLASSES==============


class Card {
private:
    char* name;
    const int id; //max=78
    static int totalCards;
    char* arcana;
    bool reversed;
    float energy;
    const char* meaning;
public:
    Card(char* name, int id, char* arcana, float energy, const char* meaning);

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

};

class Session {
    char domain; // Love-Career-Self
    char* type; //Open or Yes/No

    //if open:
    char* spread; //general, specific

    //if specific:
    int nrDrawnCard;
    Card* drawnCards;

    //if yes or no:
    bool answer;
    double price;
};

///============CONSTRUCTORS============

//====CARD





int main() {
    return 0;

}