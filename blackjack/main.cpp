#include "blackjack.h"
using namespace  std;

/*Write a Monte Carlo script to evaluate the following Monte Carlo Policies:
• Policy 1: if your hand ≥ 17, stick. Else hit.
• Policy 2: if your hand ≥ 17 and is hard, stick. Else hit unless your hand = 21.
• Policy 3: Always stick.
• Two policies of your choice
 Policy 4: Always draw one card
 Policy 5: if your hand ≥ 17 and is hard, stick. Else hit unless your hand = 18.
        Evaluate all policies for the following versions of the game:
• Infinite deck: On every run a card is drawn with equal probability.
• Single deck: One deck of cards is used. The deck is reshuffled after every
game.
*/

int main() {
    int input;
    cout<<"Please input a value between 1 and 5"<<endl;
    cin>>input;
    cout<<"games with an infinite deck"<<endl;
    cout<<"gambler with policy number "<<input<<": "<<endl;
    gametable letsplayblackjack(input, false);
    letsplayblackjack.playgame();

    cout<<endl<<"games with a regular size deck"<<endl;
    cout<<"gambler with policy number "<<input<<": "<<endl;
    gametable regulardecksize(input, true);
    regulardecksize.playgame();

    return 0;
}
