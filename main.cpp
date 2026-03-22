#include <fstream>
#include <cstring>
#include <iostream>
#include <ctime>
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
    char* meaningReversed;
public:
    Card();
    Card( char* name,char arcana, float energy, char* meaning, char* meaningReversed);
    Card(const Card& obj);
    Card& operator=(const Card& obj);
    ~Card();

    friend ostream& operator<<(ostream& os, const Card& obj);
    friend istream& operator>>(istream& is, Card& obj);

    void setName(const char* name);
    void setMeaning(const char* meaning);
    void setMeaningReversed(const char* meaningReversed);
    void setReversed(bool random);
    void revealCards();
    float getEnergy();

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

    void loadCards(const char* filename);

    static int getTotalDecks();

    void setScoresAndHope(Deck& deck);
    void setScores(int C, int L, int S);
    void setHope(int hope);
    void setRandomScores();
    void setRandomHope();
    void calculatePrice();
    double getPrice();
    Card* getCards();
    int getHope();
    double setPrice(double);
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

    void initClient();
    bool playerIsActive();
    double getPlayerMoney();
    long getConfusionLevel();
    void setConfusionLevel(long confusionLevel);
    void setActive(bool);
    void setMoney(double);

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
    void startSession(Player& client, Deck* decks);
    void drawCards();
    float calculateEnergy();
    void applySessionResult(Player& client, float totalEnergy, Deck* decks) ;
    void handleConfusedPlayer(Player& client, Deck* decks);
};

class Menu {
private:
    Deck decks[3];
    Player client;
    double minPrice;
    bool running;

public:
    Menu();

    void run();
};




///============STATICS==============

int Card::totalCards=0;
int Deck::totalDecks=0;
int Player::totalPlayers=0;
int Session::totalSessions=0;


///============CONSTRUCTORS============

//====CARD

Card::Card() :id(++totalCards-1){
    name=strcpy(new char[4], "N/A");
    arcana='?';
    reversed= false;
    energy=0.0;
    meaning=strcpy(new char[4], "N/A");
    meaningReversed=strcpy(new char[4], "N/A");
}

Card::Card(char* name, char arcana, float energy, char* meaning, char*meaningReversed):id(++totalCards-1) {
    this->name=strcpy(new char[strlen(name)+1],name);
    this->arcana=arcana;
    this->energy=energy;
    this->meaning=strcpy(new char[strlen(meaning)+1],meaning);
    this->reversed=false;
    this->meaningReversed=strcpy(new char[strlen(meaningReversed)+1], meaningReversed);
}

Card::Card(const Card& obj):id(obj.id){
    this->name=strcpy(new char[strlen(obj.name)+1], obj.name);
    this->arcana=obj.arcana;
    this->energy=obj.energy;
    this->meaning=strcpy(new char[strlen(obj.meaning)+1], obj.meaning);
    this->reversed=obj.reversed;
    this->meaningReversed=strcpy(new char[strlen(obj.meaningReversed)+1], obj.meaningReversed);
}

Card& Card::operator=(const Card& obj){
    if (this==&obj) return *this;

    delete[] name;
    delete[] meaning;
    delete[] meaningReversed;

    this->name=strcpy(new char[strlen(obj.name)+1], obj.name);
    this->arcana=obj.arcana;
    this->energy=obj.energy;
    this->meaning=strcpy(new char[strlen(obj.meaning)+1], obj.meaning);
    this->reversed=obj.reversed;
    this->meaningReversed=strcpy(new char[strlen(obj.meaningReversed)+1], obj.meaningReversed);

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

    if (meaningReversed!=nullptr) {
        delete[] meaningReversed;
        meaningReversed=nullptr;
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

//===MENU

Menu::Menu() {
    decks[0].loadCards("cards.txt");
    decks[1].loadCards("cards.txt");
    decks[2].loadCards("cards.txt");

    decks[0].setHope(7);
    decks[0].setScores(8, 1, 2);
    decks[0].calculatePrice();

    for (int i=1; i<3;i++) {
        decks[i].setScoresAndHope(decks[i]);
        decks[i].calculatePrice();
    }

    minPrice = decks[0].getPrice();
    for (int i=0;i<3;i++)
        if (minPrice>decks[i].getPrice()) minPrice=decks[i].getPrice();

    client.initClient();
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
    os<<"Reversed meaning: "              << obj.meaningReversed               << "\n";
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
    is.getline(bufMeaning, 256);
    obj.setMeaning(bufMeaning);

    char bufMeaningReversed[256];
    cout<<"Reversed meaning: ";
    is.getline(bufMeaningReversed,256);
    obj.setMeaningReversed(bufMeaningReversed);

    return is;
}

//====DECK

ostream& operator<<(ostream& os, const Deck& obj) {

    // for (int i=0;i<78;i++) {
    //     os <<"Card " << i+1 << ": " << '\n' << obj.cards[i] << '\n';
    // }

    os<<"Deck "<< obj.id << ":\n";
    os<<"Price: " << obj.price << '\n';
    os<<"Hope: " << obj.hope << '\n';

    os<<"Scores:"<<'\n';
    os<< "-Career: " << obj.scores[0] << '\n';
    os<< "-Love: " << obj.scores[1] << '\n';
    os<< "-Self: " << obj.scores[2] << '\n';

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

//==MENU



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

void Card::setMeaningReversed(const char* meaningReversed) {
    delete[] this->meaningReversed;
    this->meaningReversed = strcpy(new char[strlen(meaningReversed)+1], meaningReversed);
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

///=====FUNCTIONS===========

//===CARD

void Card::setReversed(bool random) {
    this->reversed=random;
}

void Card::revealCards() {
    cout<<this->name<<(reversed? " reversed: " : ": ")<<(reversed? this->meaningReversed: this->meaning)<<'\n';
}

float Card::getEnergy() {
    if (this->reversed) return -(this->energy);
    else return this->energy;
}
//====DECK


void Deck::loadCards(const char* filename) {
    ifstream file(filename);
    char line[512];
    int i=0;

    while (file.getline(line,512) && i<78) {
        char* name=strtok(line, ",");
        char* arcana=strtok(nullptr, ",");
        char* energy=strtok(nullptr, ",");
        char* meaning=strtok(nullptr, ",");
        char* meaningReversed=strtok(nullptr, ",");

        cards[i]=Card(name, arcana[0], atof(energy), meaning, meaningReversed );
        i++;
    }

    file.close();
}

void Deck::setScoresAndHope(Deck& deck) {
    deck.setRandomHope();
    deck.setRandomScores();
}

void Deck::setScores(int C, int L, int S) {
    this->scores[0]=C;
    this->scores[1]=L;
    this->scores[2]=S;
}

void Deck::setHope(int hope) {
    this->hope=hope;
}

void Deck::setRandomScores() {
    this->scores[0]= rand() %10 +1;
    this->scores[1]= rand() %10 +1;
    this->scores[2]= rand() %10 +1;

}

void Deck::setRandomHope() {
    this->hope=rand()%10+1;

}

int Deck::getTotalDecks() {
    return totalDecks;
}

void Deck::calculatePrice() {
    this->price=100+(this->scores[0]+this->scores[1]+this->scores[2])*5+(this->hope)*3;
}

double Deck::getPrice() {
    return this->price;
}

Card* Deck::getCards() {
    return this->cards;
}

int Deck::getHope() {
    return this->hope;
}

double Deck::setPrice(double price) {
    this->price=price;
}

//===Player

void Player::initClient() {

    char clientName[256], clientJob[256];
    cout<<"Welcome!\nWhat's your name?";
    cin>>clientName;
    cout<<"Hi "<<clientName<<"!\n"<<"Please enter your job.\n";
    cin>>clientJob;
    cout<<"Since you are at the beginning, your minimum net wage is 500 pentacles.\nTherefore, "
          "you'll recieve 500 pentacles right now.\n"
          "Don't worry! You can recieve promotions after a good reading!\n"
            "However, should the fates be upset with you, you'll recieve a bad reading.\n"
            "This means that your confusion level will rise. If your confusion level is very high you won't want readings anymore.";

    this->name=strcpy(new char[strlen(clientName)+1], clientName);
    this->job=strcpy(new char[strlen(clientJob)+1], clientJob);
    this->money=500;
    this->active=true;
    this->confusionLevel=0;

}

bool Player::playerIsActive() {
    return this->active;
}

double Player::getPlayerMoney() {
    return this->money;
}

long Player::getConfusionLevel() {
    return this->confusionLevel;
}

void Player::setConfusionLevel(long confusionLevel) {
    this->confusionLevel=confusionLevel;
}

void Player::setActive(bool active) {
    this->active=active;
}

void Player::setMoney(double money) {
    this->money=money;
}

//===SESSION


    void Session::startSession(Player& client, Deck* decks) {
        cout<<"Please choose your deck by typing the deck number."<<'\n';
        for (int i=0;i<Deck::getTotalDecks();i++) {
            cout<<decks[i]<<'\n';
        }
        int choiceDeck;
        cin>>choiceDeck;
        if (decks[choiceDeck-1].getPrice()>client.getPlayerMoney())
            cout<<"You can't afford this deck. Please choose another one.\n";
        else {
            if (choiceDeck>=1 && choiceDeck<=Deck::getTotalDecks()) this->deckUsed=&decks[choiceDeck-1];
            else {
                cout<<"This is not a valid option. Defaulting to the cheapest deck.\n";
                int minIdx = 0;
                for (int i = 1; i < Deck::getTotalDecks(); i++) {
                    if (decks[i].getPrice() < decks[minIdx].getPrice())
                        minIdx = i;
                }
                this->deckUsed = &decks[minIdx];
            }
        }
    client.setMoney(client.getPlayerMoney() - deckUsed->getPrice());
        cout<<"Now please choose what do you want your reading to be about.\n"
              "Select one of the following domains by typing the corresponding number.\n"
              "1. Career\n"
              "2. Love\n"
              "3. Self\n";
        int choiceDomain;
        cin>>choiceDomain;
        switch (choiceDomain) {
            case 1: this->domain='C'; break;
            case 2: this->domain='L'; break;
            case 3: this->domain='S'; break;
            default: {
                cout<<"No valid option chosen. Defaulting to Career.";
                this->domain='C';
            }
        }
        if (type!=nullptr)delete[] type;
        cout<<"What type of reading do you want?\n"
              "Select one of the following options by typing the corresponding number.\n"
              "1. Yes or No question\n"
              "2. Open reading\n";
        int choiceType;
        cin>>choiceType;
        if (choiceType==2) {
            this->type=strcpy(new char[5], "Open");
            cout<<"Please choose what spread do you want by entering the corresponding number.\n"
                  "1. General\n"
                  "2. Specific question\n";
            int choiceSpread;
            cin>>choiceSpread;
            if (spread!=nullptr)delete[] spread;

            if (choiceSpread==2) {

                this->spread=strcpy(new char[9], "Specific");
                cout<<"What is your question?\n";
                cin.ignore();
                char question[512];
                cin.getline(question, 512);
                cout<<"How many cards do you want drawn out?\n";
                cin>>this->nrDrawnCards;
                drawCards();
                float totalEnergy=calculateEnergy();
                if (totalEnergy > 0)
                    cout << "The reading was successful!\n";
                else
                    cout << "The reading was unclear...\n";
                this->applySessionResult(client, totalEnergy, decks);

            }

            else { if (choiceSpread!=1)cout<<"Invalid option. Defaulting to General.";
                this->spread = strcpy(new char[8], "General");
                cout<<"How many cards do you want drawn?\n";
                cin>>this->nrDrawnCards;
                drawCards();
                float spreadEnergy=calculateEnergy();
                if (spreadEnergy > 30)
                    cout << "The reading was successful!\n";
                else
                    cout << "The reading was unclear...\n";
                this->applySessionResult(client, spreadEnergy, decks);
            }
        }
        else { if (choiceType!=1)cout<<"This is not a valid option. Defaulting to Yes or No.";
            this->type=strcpy(new char[10], "Yes or No");
            this->spread=nullptr;
            this->nrDrawnCards=1;
            cout<<"What is your question?\n";
            char question[512];
            cin.getline(question, 512);
            drawCards();
            float spreadEnergy=drawnCards[0].getEnergy();
            if (spreadEnergy>25)cout<<"Answer: Yes.";
            else if (spreadEnergy<0)cout<<"Answer: No.";
            else cout<< "Answer: Maybe.";
        }
    }

    void Session::drawCards(){
        delete[] drawnCards;
        drawnCards=new Card[nrDrawnCards];
        bool drawn[78]={false};

        for (int i=0;i<nrDrawnCards;i++) {
            int randomIndx;
            do {
                randomIndx = rand() % 78;
            } while (drawn[randomIndx]);
            drawn[randomIndx]=true;
            drawnCards[i]=deckUsed->getCards()[randomIndx];
            drawnCards[i].setReversed(rand() % 2 == 0);
            cout<<"Card "<<i+1<<" has been drawn...\n";
        }

        cout << "\nAll cards have been drawn. Press Enter to reveal them...\n";
        cin.ignore();
        cin.get();

        for (int i=0;i<nrDrawnCards;i++) {
            cout <<"\nCard "<< i+1 <<":\n";
            drawnCards[i].revealCards();
        }
    }

    float Session::calculateEnergy() {
        float sumEnergy=0.0;
        for (int i=0;i<nrDrawnCards;i++) {
            sumEnergy+=drawnCards[i].getEnergy();
        }
        float avg = sumEnergy/ nrDrawnCards;
        avg += deckUsed->getHope() * 2.0f; // hope boost
        return avg;
    }

    void Session::applySessionResult(Player& client, float totalEnergy, Deck* decks) {
        if (totalEnergy > 30) {
            client.setConfusionLevel(client.getConfusionLevel()-75);
            if (client.getConfusionLevel() < 0) client.setConfusionLevel(0) ;
            if (domain == 'C') {
                client.setMoney(client.getPlayerMoney()+1000);
                cout << "You got a promotion! +1000 pentacles!\n";
            }
            if (domain == 'L') {
                client.setMoney(client.getPlayerMoney()+500);
                cout << "You found a wealthy partner! +250 pentacles!\n";
            }
            if (domain=='S') {
                client.setMoney(client.getPlayerMoney()+300);
                cout<<"You gather strength and enter a new chapter of your life. Creativity and confidence brings money. +300 pentacles!\n";
            }
        } else {
            client.setConfusionLevel(client.getConfusionLevel()+50);
            if (client.getConfusionLevel()>= 100) {
                client.setActive(false);
                handleConfusedPlayer(client, decks);

            }
        }
    }

void Session::handleConfusedPlayer(Player& client, Deck* decks) {
    cout << "You are too confused...\n";
    cout << "However, we have a special offer! A hope-boosted deck for only 50 pentacles!\n";
    cout << "Would you like to try again? (1=Yes, 0=No)\n";
    int offerChoice;
    cin.ignore();
    cin >> offerChoice;
    if (offerChoice==1 && client.getPlayerMoney()>=50) {
        client.setActive(true);
        client.setConfusionLevel(0);
        client.setMoney(client.getPlayerMoney() - 50);

        Deck* hopefulDeck = new Deck;
        hopefulDeck->loadCards("cards.txt");
        hopefulDeck->setHope(10);
        hopefulDeck->setScores(9,10, 9);
        hopefulDeck->setPrice(50);


        startSession(client, hopefulDeck);

        delete hopefulDeck;
    }
    else if (client.getPlayerMoney()<=50) cout<< "You don't have enough money.";
}

//===MENU



void Menu::run() {
    int choice;

    do {
        cout << "\n===== TAROT READING SIMULATOR =====\n";
        cout << "1. Start new session\n";
        cout << "2. View decks\n";
        cout << "3. View player info\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;


        switch (choice) {
            case 1: {
                if (!client.playerIsActive()) {
                    Session sC;
                    sC.handleConfusedPlayer(client, decks);
                }
                else if (client.getPlayerMoney() < minPrice)
                    cout << "You don't have enough money";
                else {
                    Session s;
                    s.startSession(client, decks);
                }
                break;
            }
            case 2: {
                for (int i = 0; i<3; i++)
                    cout << decks[i] << '\n';
                break;
            }
            case 3: {
                cout << client;
                break;
            }
        };
    }while (choice!=0);

}


int main() {
    srand(time(nullptr));
    Menu menu;
    menu.run();
    return 0;
}