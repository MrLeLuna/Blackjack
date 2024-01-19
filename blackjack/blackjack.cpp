// Created by jluna on 3/29/2023.
//

#include "blackjack.h"

hand::hand(deck *newdeck,bool d) {
    regulardeck=d;
    carddeck=newdeck;
    handvalue=0;

}

void hand::updatehandvalue(string ch) {
    char l=ch[0];
    int v;
    switch (l) {
        case '2':
        {
            v=2;
            break;
        }
        case '3':
        {
            v=3;
            break;
        }
        case '4':
        {
            v=4;
            break;
        }
        case '5':
        {
            v=5;
            break;
        }
        case '6':
        {
            v=6;
            break;
        }
        case '7':
        {
            v=7;
            break;
        }
        case '8':
        {
            v=8;
            break;
        }
        case'9':
        {
            v=9;
            break;
        }
        case 'A':
        {
            v=11;
            break;
        }
        default:
        {
            v=10;
            break;
        }
    }
    handvalue+=v;
}

bool hand::Iwilldraw(int policy) {

    switch (policy) {
        case 1://always draw if hand is less than 17
        {
            if(handvalue>=17)
                return false;
                //if it is less than draw
            else
                return true;
        }
        case 2: //if we need to draw a card based on policy 2
        {

            if(Policy2::blackjack(cardsinhandgetter(), handvaluegetter()))
            {
                //change the value of the hand to reflect it
                int t=Policy2::newhandvalue(cardsinhandgetter());
                handvaluesetter(t);
                //need to draw a card
                return true;
            }
            else
            {
                //don't need to draw a card
                return false;
            }

        }
        case 3://always stick with the original hand
        {
            return false;
        }
        case 4: //always draw only one card
        {
            if(Policy4::nomorethan3cards(cardsinhandgetter()))
                return true;
            else
                return false;

        }
        default: //Same as policy 2 except we are checking we do not go over 17
        {
            if(handvalue<11)
            {
                return true;
            }
            else
            {
                return false;
            }
            /*if(Policy5::shorterblackjack(cardsinhandgetter(), handvaluegetter()))
            {
                //change the value of the hand from A=11 to A=1
                int t=Policy5::Policy5newhandvalue(cardsinhandgetter());
                handvaluesetter(t);
                //need to draw a card
                return true;
            }
            else
            {
                //don't need to draw a card
                return false;
            }*/
        }
    }
}

void hand::drawcard() {
    if(regulardeck){
        string card=carddeck->d.back();
        carddeck->d.pop_back();
        cardsinhand.push_back(card);
        updatehandvalue(card);
    }
    else
    {
        string card=carddeck->d.back();
        cardsinhand.push_back(card);
        updatehandvalue(card);
        generaldeckfunctions::shuffledeck(carddeck->d);
    }
}

void hand::prindhand() {
   if(cardsinhand.empty())
   {
       cout<<"no cards in hand"<<endl;
   }
   else {
       for (const auto & i : cardsinhand) {
           cout << i << ", ";
       }
       cout << endl << handvalue << endl;
   }
}

void hand::discardhand() {
    if(regulardeck)
    {
        for(const auto & i : cardsinhand)
        {
            carddeck->discard(i);
        }
    }
    cardsinhand.clear();
    handvalue=0;
}

int hand::handvaluegetter() const {
    return handvalue;
}

vector<string> hand::cardsinhandgetter() {
    return cardsinhand;
}

hand::~hand() {
    cardsinhand.clear();

}

void hand::handvaluesetter(int x) {

    handvalue=x;
}

deck::deck() {
    d=generaldeckfunctions::initalizedeck();
}

void deck::discard(const string& card) {
    usedpile.push_back(card);
}

void deck::replacedeck() {
    for(const auto& tmp : usedpile)
    {
        d.push_back(tmp);
    }
    usedpile.clear();
    generaldeckfunctions::shuffledeck(d);
}

deck::~deck() {
    d.clear();
    usedpile.clear();
}

gametable::gametable(int p,bool d) {
    tabledeck = new deck;
    gambler = new hand(tabledeck, d);
    dealer = new hand(tabledeck, d);
    gamblerwins = 0;
    dealerwins = 0;
    totalgames = 0;
    policynumber = p;
}

void gametable::playgame()  {
    //char t; //make seeing games easier;
        //check the size of the deck make sure it doesn't go below 3 cards
        ofstream myfile("myfile.txt");
        myfile<<"Games"<<"\t";
        myfile<<"Wins"<<"\t";
        myfile<<"Winning percent"<<"\n";
        int i=0;
        while(i<100000) {
            dealhands();
                while (gambler->Iwilldraw(policynumber))
                {
                    gamblerdraws();
                }
                while (dealer->Iwilldraw(1))
                {
                    dealer->drawcard();
                }
            //cout << "Gambler's hand: ";
            //gambler->prindhand();
            //cout << "The house's hand: ";
            //dealer->prindhand();*/
            whowonthegame();
            gambler->discardhand();
            dealer->discardhand();
            tabledeck->replacedeck();
            i++;
            float ratio=(float)gamblerwins/(float)totalgames;
            myfile<<totalgames<<"\t";
            myfile<<gamblerwins<<"\t";
            myfile<<ratio<<"\n";
        }
        myfile.close();
    gamestatistics();
}

void gametable::whowonthegame() {
    int gamblerhandvalue=gambler->handvaluegetter();
    int dealerhandvalue=dealer->handvaluegetter();
    totalgames++;
    if(gamblerhandvalue>21 && dealerhandvalue<=21)
    {
        dealerwins++;
    }
    else if(dealerhandvalue>21 && gamblerhandvalue<=21)
    {
        gamblerwins++;
    }
    else if(gamblerhandvalue<dealerhandvalue)
    {
        dealerwins++;
    }
    else if (dealerhandvalue<gamblerhandvalue)
    {
        gamblerwins++;
    }

}

void gametable::gamestatistics() const {
    cout<<"total games played with one deck: "<<totalgames<<endl;
    cout<<"total games gambler won: "<<gamblerwins<<endl;
    //cout<<"total games the house won: "<<dealerwins<<endl;
    double ratio=((double)gamblerwins/(double)totalgames);
    cout<<ratio<<"%"<<endl;
}

void gametable::gamblerdraws() const {
    gambler->drawcard();
}

void gametable::dealhands() const {
    dealer->drawcard();
    gambler->drawcard();
    dealer->drawcard();
    gambler->drawcard();

}

gametable::~gametable() {
    delete tabledeck;
    delete gambler;
    delete dealer;
}

void generaldeckfunctions::shuffledeck(vector<string>& d) {
    random_device r;
    //default_random_engine(r());
    // auto rd = random_device{};
    //auto rng = default_random_engine{ rd() };
    //shuffle(begin(d), end(d), rng);
    shuffle(begin(d), end(d), default_random_engine(r()));

}

vector<string> generaldeckfunctions::initalizedeck() {
    vector<string> newd;
    for(int i=0;i<4;i++)
    {
        newd.emplace_back("2");
        newd.emplace_back("3"); newd.emplace_back("4");
        newd.emplace_back("5"); newd.emplace_back("6");
        newd.emplace_back("7"); newd.emplace_back("8");
        newd.emplace_back("9"); newd.emplace_back("10");
        newd.emplace_back("J"); newd.emplace_back("K");
        newd.emplace_back("Q"); newd.emplace_back("A");
    }
    shuffledeck(newd);
    return (newd);
}

void generaldeckfunctions::printdeck(vector<string>&d) {
    for(const auto & i : d)
    {
        cout<<i<<", ";
    }
}

bool Policy2::blackjack(const vector<string>& cardsinh, int valueofh)
//if the hand is blackjack, do not draw
{
    bool aceinhand=false;
    for(const auto & i : cardsinh) //check if there is an ace in hand
    {
        if (i == "A")
            aceinhand = true;

    }
    if(valueofh>=21) //if the hand value is 21 (blackjack)
        return false;
    if(!aceinhand && valueofh>=17) //if the hand has no ace, and the hand is over 17
        return false;
    else //if the hand value is not 21 and there is an ace
    {
        return true;
    }
}

int Policy2::newhandvalue(const vector<string>& cardsinh) {
    int x=0;
    for(auto a : cardsinh)
    {
        char l=a[0];
        switch (l) {
            case '2':
            {
                x+=2;
                break;
            }
            case '3':
            {
                x+=3;
                break;
            }
            case '4':
            {
                x+=4;
                break;
            }
            case '5':
            {
                x+=5;
                break;
            }
            case '6':
            {
                x+=6;
                break;
            }
            case '7':
            {
                x+=7;
                break;
            }
            case '8':
            {
                x+=8;
                break;
            }
            case'9':
            {
                x+=9;
                break;
            }
            case 'A':
            {
                x+=1;
                break;
            }
            default:
            {
                x+=10;
                break;
            }
        }

    }
    return x;
}

bool Policy4::nomorethan3cards(const vector<string>& cardsinh) {
    if(cardsinh.size()==2)
    {
        return true;
    }
    else
        return false;
}
