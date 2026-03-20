#include <chrono>
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

    friend ostream& operator<<(ostream& os, const Card& obj);
    friend istream& operator>>(istream& is, Card& obj);

    void setName(const char* name);
    void setMeaning(const char* meaning);
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

    friend ostream& operator<<(ostream& os,const Deck& obj);
    friend istream& operator>>(istream& is, Deck& obj);
};

class Player {
private:
    char* name;
    char* job;
    const int id;
    static int totalPlayers;
    double money;
    long confusionLevel;
    bool active; //if confusion level=max>>>>>bye
public:
    Player();
    Player(char* name, char* job, double money,long confusionLevel, bool active );
    Player(const Player& obj);
    Player& operator=(const Player& obj);
    ~Player();

    friend ostream& operator<<(ostream& os, const Player& obj );
    friend istream& operator>>(istream& is, Player& obj);

    void setName(const char* name);
    void setJob(const char* job);
};

class Session {
private:
    Player* client;
    const int id;
    static int totalSessions;
    char domain; // Love(L)-Career(C)-Self(S)
    double price;
    char* type; //Open or Yes/No
    Deck* deckUsed;

    //if open:
    char* spread; //specific(What does someone think about you, do they have feelings? How do i get a promotion?
    // OR general for domain

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

    friend ostream& operator<<(ostream& os, const Session& obj);
    friend istream& operator>>(istream& is, Session& obj);

    void setType(int chooseType);
    void setSpread(int chooseSpread);
};

///============STATICS==============

int Card::totalCards=0;
int Deck::totalDecks=0;
int Player::totalPlayers=0;
int Session::totalSessions=0;


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


Player::Player():id(++totalPlayers) {
    name=strcpy(new char[4], "N/A");
    job=strcpy(new char[4], "N/A");
    money=0.0;
    confusionLevel=0;
    active=true;
}

Player::Player(char *name, char *job, double money, long confusionLevel, bool active):id(++totalPlayers) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->job=strcpy(new char[strlen(job)+1], job);
    this->money=money;
    this->confusionLevel=confusionLevel;
    this->active=active;
}

Player::Player(const Player &obj):id(obj.id) {
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

Session::Session():id(++totalSessions) {
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

Session::Session(Player *client, Deck *deckUsed, char domain, char *type, double price):id(totalSessions) {
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

Session::Session(const Session &obj) :id(obj.id){
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


///======OVERLOADING >> AND << OPERATORS=========

//=====CARD

ostream& operator<<(ostream& os, const Card& obj) {
    os<<"Name: "            << obj.name             << "\n";
    os<<"Id: "              << obj.id               << "\n";

    if (obj.arcana=='m')
        os<<"Arcana: "          << "Minor"               << "\n";
    else if (obj.arcana=='M')
        os <<"Arcana: "         << "Major"               << "\n";
    else
        os<<"Arcana: "          << obj.arcana               << "\n";

    os<<"Reversed: "        << (obj.reversed ? "Yes" : "No") << "\n";
    os<<"Energy: "              << obj.energy               << "\n";
    os<<"Meaning: "              << obj.meaning               << "\n";

    return os;
}

istream& operator>>(istream& is, Card& obj) {

    char bufName[256];
    cout<<"Name: ";
    is>>bufName;
    obj.setName(bufName);

    cout<<"Arcana(m/M): ";
    is>>obj.arcana;

    obj.reversed=false;

    cout<<"Energy: ";
    is>>obj.energy;

    char bufMeaning[256];
    cout<<"Meaning: ";
    is>>bufMeaning;
    obj.setMeaning(bufMeaning);

    return is;
}

//====DECK

ostream& operator<<(ostream& os, const Deck& obj) {

    for (int i=0;i<78;i++) {
        os <<"Card" << i+1 << ": " << '\n' << obj.cards[i] << '\n';
    }

    os<<"Id: "<< obj.id << '\n';
    os<<"Price: " << obj.price << '\n';
    os<<"Hope: " << obj.hope << '\n';

    os<<"Scores:"<<'\n';
    os<< "Career: " << obj.scores[0] << '\n';
    os<< "Love: " << obj.scores[1] << '\n';
    os<< "Self: " << obj.scores[2] << '\n';

    return os;
}

istream& operator>>(istream& is, Deck& obj) {

    for (int i=0;i<78;i++) {
        cout << "Card" << i+1 << ": " << '\n';
        is >> obj.cards[i] ;
        cout <<'\n';
    } //in practice no one will fill up 78 fields lol

    cout<<"Price: " ;
    is>> obj.price;
    cout<<'\n';

    cout<<"Hope: ";
    is>>obj.hope;
    cout<<'\n';

    cout<<"Career Score: " ;
    is>> obj.scores[0];
    cout<<'\n';

    cout<<"Love Score: " ;
    is>> obj.scores[1];
    cout<<'\n';

    cout<<"Self Score: " ;
    is>> obj.scores[2];
    cout<<'\n';

    return is;
}

//===PLAYER


ostream& operator<<(ostream& os, const Player& obj) {

    os<<"Name: "<<obj.name<<'\n';
    os<<"Job: "<<obj.job<<'\n';
    os<<"Id: "<<obj.id<<'\n';
    os<<"Money: "<<obj.money<<'\n';
    os<<"Confusion Level: "<<obj.confusionLevel<<'\n';
    os<<"Active: "<< (obj.active ? "Yes" : "No") <<'\n';

    return os;
}

istream& operator>>(istream& is, Player& obj) {

    char bufName[256];
    cout<<"Name: ";
    is>>bufName;
    obj.setName(bufName);

    char bufJob[256];
    cout<<"Job: ";
    is>>bufJob;
    obj.setJob(bufJob);

    cout<<"Money: ";
    is>>obj.money;
    cout<<'\n';

    obj.confusionLevel=0;
    obj.active=true;

    return is;
}

//===SESSION

ostream& operator<<(ostream& os, const Session& obj) {

    os<<"Client: "<<'\n';
    if (obj.client!=nullptr)
        os<<*obj.client<<'\n';

    os<<"Id: "<< obj.id<<'\n';
    os<<"Domain: "<<obj.domain<<'\n';
    os<<"Price: "<<obj.price<<'\n';
    os<<"Type: "<<obj.type<<'\n';
    if (strcmp(obj.type,"Yes or No")==0) { ///ATENTIE COMPAR POINTERI. DE REZ!
        os<<"Answer: "<<(obj.answer?"Yes":"No")<<'\n';
    }
    else if (strcmp(obj.type,"Open")==0) {
        os<<"Spread: "<<obj.spread<<'\n';
        os<<"Number of drawn cards: "<<obj.nrDrawnCards<<'\n';
        os<<"Drawn cards: "<<'\n';
        for (int i=0;i<obj.nrDrawnCards;i++) {
            os<<"Card "<< i+1<<": "<<'\n';
            os<<obj.drawnCards[i]<<'\n';
        }
    }

    os<<"Deck used: "<<obj.deckUsed<<'\n';
    return os;
}

istream& operator>>(istream& is, Session& obj) {

    cout<<"Client: "<<'\n';
    if (obj.client==nullptr) obj.client= new Player;
    is >> *obj.client;
    cout<<'\n';

    cout<<"Domain(C for Career, L for Love, S for Self): "<<'\n';
    is >> obj.domain;
    cout<<'\n';

    cout<<"Price: "<<'\n';
    is>>obj.price;
    cout<<'\n';

    cout<<"Type of reading. Press 1 for 'Yes/No' reading or Press 2 for open reading: "<<'\n';
    int chooseType;
    is>>chooseType;
    obj.setType(chooseType);

    if (strcmp(obj.type,"Yes or No")==0) {
        cout<<"Answer(true for Yes, false for No): ";
        is>>obj.answer;
        cout<<'\n';
    }
    else {
        cout<<"Type of spread. Press 1 for 'General' reading or Press 2 for 'Specific' reading: "<<'\n';
        int chooseSpread;
        is>>chooseSpread;
        obj.setSpread(chooseSpread);
    }

    cout<<"Deck: ";
    if (obj.deckUsed==nullptr) obj.deckUsed=new Deck;
    is>>*obj.deckUsed;
    cout<<'\n';

    return is;

}



///==========SETTERS=========

//===CARD

void Card::setName(const char* name) {
    delete[] this->name;
    this->name=strcpy(new char[strlen(name)+1], name);
}

void Card::setMeaning(const char *meaning) {
    delete[] this->meaning;
    this->meaning=strcpy(new char[strlen(meaning)+1], meaning);
}

//===DECK

//-------

//===PLAYER

void Player::setName(const char *name) {
    delete[] this->name;
    this->name=strcpy(new char[strlen(name)+1], name);
}

void Player::setJob(const char *job) {
    delete[] this->job;
    this->job=strcpy(new char[strlen(job)+1], job);
}

//==SESSION

void Session::setType(int chooseType) {

    delete[] this->type;
    if (chooseType==1)this->type=strcpy(new char[10], "Yes or No");
    else if (chooseType==2) this->type=strcpy(new char[5], "Open");
    else {
        cout<<"Invalid type. Defaulting to Open";
        this->type=strcpy(new char[5], "Open");
    }


}

void Session::setSpread(int chooseSpread) {

    delete[] this->spread;
    if (chooseSpread==1)this->spread=strcpy(new char[8], "General");
    else if (chooseSpread==2) this->spread=strcpy(new char[9], "Specific");
    else {
        cout<<"Invalid type. Defaulting to General";
        this->spread=strcpy(new char[8], "General");
    }
}


int main() {
    return 0;
}