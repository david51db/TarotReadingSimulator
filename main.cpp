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
    Card(const Card& obj);
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
    Deck(const Deck& obj);
    Deck& operator=(const Deck& obj);
    ~Deck();
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
    Player(const Player& obj);
    Player& operator=(const Player& obj);
    ~Player();
};

class Session {
private:
    Player* client;
    char domain; // Love-Career-Self
    double price;
    char* type; //Open or Yes/No
    Deck* deckUsed;

    //if open:
    char* spread; //general, specific

    //if specific:
    int nrDrawnCards; //choice: 2,3,5,7,.... CARDS
    Card* drawnCards;

    //if yes or no:
    bool answer;

public:
    Session();
    Session(Player* client, Deck* deckUsed,char domain, char* type, double price);
    Session(const Session& obj);
    Session& operator=(const Session& obj);
    ~Session();
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

//=======DECK

Deck::Deck():id(++totalDecks) {
    cards= new Card[78]; //calls parameterless Card constructor
    price=0.0;
    scores= new int[3]{0,0,0};
    hope=0;
}

Deck::Deck(Card *cards, float price, int *scores, int hope):id(++totalDecks){
    this->cards= new Card[78];
    for(int i=0; i<78; i++) {
        this->cards[i]=cards[i]; //operator= din Card
    }
    this->price=price;
    this->scores=new int[3];
    for(int i=0;i<3;i++) {
        this->scores[i]=scores[i];
    }
    this->hope=hope;
}

Deck::Deck(const Deck& obj):id(obj.id) {
    this->cards= new Card[78];
    for(int i=0; i<78; i++) {
        this->cards[i]=obj.cards[i]; //operator= din Card
    }
    this->price=obj.price;
    this->scores=new int[3];
    for(int i=0;i<3;i++) {
        this->scores[i]=obj.scores[i];
    }
    this->hope=obj.hope;
}

Deck& Deck::operator=(const Deck& obj) {
    if (this==&obj) return *this;

    delete[] cards;
    delete[] scores;

    this->cards= new Card[78];
    for (int i=0;i<78;i++) {
        this->cards[i]=obj.cards[i];
    }
    this->price=obj.price;
    this->scores= new int[3];
    for (int i=0;i<3;i++) {
        this->scores[i]=obj.scores[i];
    }
    this->hope=obj.hope;

    return *this;
}

Deck::~Deck() {
    if (cards!=nullptr) {
        delete[] cards;
        cards=nullptr;
    }
    if (scores!=nullptr) {
        delete[] scores;
        scores=nullptr;
    }

}

//======PLAYER


Player::Player() {
    name=strcpy(new char[4], "N/A");
    job=strcpy(new char[4], "N/A");
    money=0.0;
    confusionLevel=0;
    active=true;
}

Player::Player(char *name, char *job, double money, long confusionLevel, bool active) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->job=strcpy(new char[strlen(job)+1], job);
    this->money=money;
    this->confusionLevel=confusionLevel;
    this->active=active;
}

Player::Player(const Player &obj) {
    this->name=strcpy(new char[strlen(obj.name)+1], obj.name);
    this->job=strcpy(new char[strlen(obj.job)+1], obj.job);
    this->money=obj.money;
    this->confusionLevel=obj.confusionLevel;
    this->active=obj.active;
}

Player& Player::operator=(const Player &obj) {
    if (this==&obj) return *this;
    else {
        delete[] name;
        delete[] job;

        this->name=strcpy(new char[strlen(obj.name)+1], obj.name);
        this->job=strcpy(new char[strlen(obj.job)+1], obj.job);
        this->money=obj.money;
        this->confusionLevel=obj.confusionLevel;
        this->active=obj.active;

        return *this;
    }
}

Player::~Player() {
    if (name!=nullptr) {
        delete[] name;
        name=nullptr;
    }
    if (job!=nullptr) {
        delete[] job;
        job=nullptr;
    }
};

//===SESSION

Session::Session() {
    domain='?';
    price=0.0;
    client=nullptr;
    type=strcpy(new char[4], "N/A");
    spread=nullptr;
    nrDrawnCards=0;
    drawnCards=nullptr;
    deckUsed= nullptr;
    answer=false;
}

Session::Session(Player *client, Deck *deckUsed, char domain, char *type, double price) {
    this->client=client;
    this->deckUsed=deckUsed;
    this->domain=domain;
    this->type=strcpy(new char[strlen(type)+1], type);
    this->price=price;
    this->spread=nullptr;
    this->nrDrawnCards=0;
    this->drawnCards=nullptr;
    this->answer=false;
}

Session::Session(const Session &obj) {
    this->client=obj.client;
    this->deckUsed=obj.deckUsed;
    this->domain=obj.domain;
    this->type=strcpy(new char[strlen(obj.type)+1], obj.type);
    this->price=obj.price;

    if (obj.spread!=nullptr)
        this->spread=strcpy(new char[strlen(obj.spread)+1],obj.spread);
    else this->spread=nullptr;

    this->nrDrawnCards=obj.nrDrawnCards;

    if (obj.drawnCards!=nullptr) {
        this->drawnCards=new Card[obj.nrDrawnCards];
        for (int i=0;i<nrDrawnCards;i++) {
            this->drawnCards[i]=obj.drawnCards[i];
        }
    }
    else drawnCards=nullptr;
    this->answer=obj.answer;
}

Session& Session::operator=(const Session& obj) {
    if (this==&obj) return *this;
    else {
        delete[] type;
        if (spread!=nullptr) delete[] spread;
        if (drawnCards!=nullptr) delete[] drawnCards;

        this->client=obj.client;
        this->deckUsed=obj.deckUsed;
        this->domain=obj.domain;
        this->type=strcpy(new char[strlen(obj.type)+1], obj.type);
        this->price=obj.price;

        if (obj.spread!=nullptr)
            this->spread=strcpy(new char[strlen(obj.spread)+1],obj.spread);
        else this->spread=nullptr;

        this->nrDrawnCards=obj.nrDrawnCards;

        if (obj.drawnCards!=nullptr) {
            this->drawnCards=new Card[obj.nrDrawnCards];
            for (int i=0;i<nrDrawnCards;i++) {
                this->drawnCards[i]=obj.drawnCards[i];
            }
        }
        else drawnCards=nullptr;
        this->answer=obj.answer;

        return *this;
    }
}

Session::~Session() {
    delete[] type;
    if (spread!=nullptr) delete[] spread;
    if (drawnCards!=nullptr) delete[] drawnCards;
}

int main() {
    return 0;
}