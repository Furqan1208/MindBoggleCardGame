#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include<windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include<time.h>
#include<ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>
using namespace std;

class Card {
public:
    int rank;
    string suit;
};

class Memory{
public:
    int rank, cond, position;                   // store rank, condition (known, less than, unknown) and position of own and opponents card
    Memory() {
        rank = 14;                       //default rank = 14 means unknown
        cond = 0;                       // default condition = 0 means unknown
        position = 3;                   //3 means unknown
    }
};

class Player {
public:
    Card hand[3];

    void printHand() {                      //prints card on hand
        for (int i = 0;i < 3;i++) {
            switch (hand[i].rank) {
            case 1:
                cout << "Ace";
                break;
            case 11:
                cout << "Jack";
                break;
            case 12:
                cout << "Queen";
                break;
            case 13:
                cout << "King";
                break;
            default:
                cout << hand[i].rank;
            }
            cout << " of " << hand[i].suit << endl;
        }
    }
    void shuffle() {                            //shuffles card of a hand
        int y = rand() % 3;
        int z = rand() % 3;
        int tempr;
        string temps;
        for (int i = 0;i < 10;i++) {
            tempr = hand[y].rank;
            temps = hand[y].suit;
            hand[y].rank = hand[z].rank;
            hand[y].suit = hand[z].suit;
            hand[z].rank = tempr;
            hand[z].suit = temps;
            y = rand() % 3;
            z = rand() % 3;
        }
    }
};

class Human :public Player {
 };

class Bot:public Player {
public:
    Memory pmem[3], bmem[3][3];

    void printmem() {                               //prints memory of a bot... func for test only
        cout << "Player cards: " << endl;
        for (int i = 0;i < 3;i++) {
            cout << "Position: " << pmem[i].position << endl << "Rank: " << pmem[i].rank << endl << "Condition: " << pmem[i].cond << endl;
        }
        cout << "Bot Cards:" << endl << endl ;
        for (int i = 0;i < 3;i++) {
            cout << "Bot " << i << endl;
            for (int j = 0;j < 3;j++) {
                cout << "Position: " << bmem[i][j].position << endl << "Rank: " << bmem[i][j].rank << endl << "Condition: " << bmem[i][j].cond << endl << endl;
            }
        }

    }
};

class Game {
public:
    Card deck[52];  // create 52 cards
    Card bank[40];  // those cards which will remain for us after distribution
    Human p;
    Bot b[3];
    int dr;                     //discarded rank
    string ds;                  //discarded suit
    void initializeDeck() {                 //intializes deck in sorted order
        int k = 0;
        string s[4] = {"spades","clubs","hearts","diamonds"};
        for (int i = 0;i < 4;i++) {     //as there are 4 suits
            for (int j = 1;j < 14;j++) {   // as there are 13 cards of every suit
                deck[k].rank = j;
                deck[k].suit = s[i];
                k++;
            }
        }
    }

    void distributeCards() {
        
        int y = rand() % 52;
        for (int i = 0;i < 3;i++) {             //dist card to player
            while (deck[y].rank == 0) {
                y = rand() % 52;                //random num to get card randomly from the deck
            }
            p.hand[i].rank = deck[y].rank;
            p.hand[i].suit = deck[y].suit;
            deck[y].rank = 0;                   //setting value for the rank to 0, since this card is already distributed... 
        }
        for (int i = 0;i < 3;i++) {             //dist card to bots... i is for bot whos recieving card
            for (int j = 0;j < 3;j++) {         // j is for posiiton of card
                while (deck[y].rank == 0) {
                    y = rand() % 52;
                }
                b[i].hand[j].rank = deck[y].rank;
                b[i].hand[j].suit = deck[y].suit;
                b[i].bmem[i][j].rank = deck[y].rank;       // bot memorizes its cards here
                b[i].bmem[i][j].position = j;         //3 means unknown
                b[i].bmem[i][j].cond = 2;               //  0 unknown, 1 less than=, 2 known
                deck[y].rank = 0;
            }
        }
        
        for (int i = 0;i < 40;i++) {            //distributing remaining cards to bank randomly
            while (deck[y].rank == 0) {
                y = rand() % 52;
            }
            bank[i].rank = deck[y].rank;
            bank[i].suit = deck[y].suit;
            deck[y].rank = 0;
        }
    }

    void printAllHands() {                              //prints all hands in game... use in end
        cout << endl << "Player Hand" << endl; 
        p.printHand();
        for (int i = 0;i < 3;i++) {
            cout << endl << "Bot " << i + 1 << " Hand" << endl;
            b[i].printHand();
        }
    }

    void pmove(int r, string s) {                   //players move
        int m;
        cout << "You picked ";
        switch (r)
        {
        case 1:
            cout << "Ace";
            break;
        case 11:
            cout << "Jack";
            break;
        case 12:
            cout << "Queen";
            break;
        case 13:
            cout << "King";
            break;
        default:
            cout << r;
        }
        cout << " of " << s << endl;
        cout << "Enter -1 to discard or Enter position of your card (0/1/2) to replace it" << endl;
        cin >> m;
        while (m > 2 || m < -1) {
            cout << "Invalid number, enter again" << endl;
            cin >> m;
        }
        switch (m) {
        case -1:
            dr = r;
            ds = s;
            for (int i = 0;i < 3;i++) {
                for (int j = 0;j < 3;j++) {
                    if (b[i].pmem[j].rank > dr) {
                        b[i].pmem[j].rank = dr;
                        b[i].pmem[j].cond = 1;
                    }
                }
            }
            break;
        default:
            dr = p.hand[m].rank;
            ds = p.hand[m].suit;
            p.hand[m].rank = r;
            p.hand[m].suit = s;
            
            for (int i = 0;i < 3;i++) {
                b[i].pmem[m].cond = 1;
                b[i].pmem[m].position = m;
                b[i].pmem[m].rank = dr;
           }
        }
        cout << "You Discarded ";
        switch (dr) {
        case 1:
            cout << "Ace";
            break;
        case 11:
            cout << "Jack";
            break;
        case 12:
            cout << "Queen";
            break;
        case 13:
            cout << "King";
            break;
        default:
            cout << dr;
        }
        cout << " of " << ds << endl;
        switch (dr) {   //special cards
        case 13:                //King thrown.. see your card
        {
            p.shuffle();
            cout << "Your cards are in following order now" << endl;
            p.printHand();
            for (int i = 0;i < 3;i++) {
                for (int j = 0;j < 3;j++) {
                    b[i].pmem[j].position = 3;
                }
            }
            break;
        }
        case 10:            //10 ...shuffle oppponent's card
        {
            int x;
            cout << "Enter a number to shuffle bot's cards and view them" << endl;
            cin >> x;
            while (x < 0 || x>2) {
                cout << "Invalid input, enter the bot number again" << endl;
                cin >> x;
            }
            b[x].shuffle();
            cout << "Bot " << x << "'s cards are in this order now" << endl;
            b[x].printHand();
            for (int i = 0;i < 3;i++) {
                for (int j = 0;j < 3;j++) {
                    b[i].bmem[x][j].position = 3;
                }
            }
            break;
        }
        case 7:             //7... exchange card w/o looking
        {
            int x, y, z;
            cout << "Enter a bot number to exchnage card with" << endl;
            cin >> x;
            while (x < 0 || x>2) {
                cout << "Invalid input, enter the bot number again" << endl;
                cin >> x;
            }
            cout << "Enter a card number/positon to exchnage card" << endl;
            cin >> y;
            while (y < 0 || y>2) {
                cout << "Invalid input, enter the card number again" << endl;
                cin >> y;
            }
            cout << "Enter your card number/positon to exchnage card" << endl;
            cin >> z;
            while (z < 0 || z>2) {
                cout << "Invalid input, enter the card number again" << endl;
                cin >> z;
            }
            int tempr, tempmr, tempmc, tempmp;      //tempmr is for memory rank... 
            string temps;   //card replacing algorithmS
            tempr = p.hand[z].rank;
            temps = p.hand[z].suit;
            p.hand[z].rank = b[x].hand[y].rank;
            p.hand[z].suit = b[x].hand[y].suit;
            b[x].hand[y].rank=tempr;
            b[x].hand[y].suit=temps;
            for (int i = 0;i < 3;i++) {
                tempmr = b[i].pmem[z].rank;
                tempmc = b[i].pmem[z].cond;
                tempmp = b[i].pmem[z].position;
                b[i].pmem[z].rank=b[i].bmem[x][y].rank;
                b[i].pmem[z].cond = b[i].bmem[x][y].position;
                b[i].pmem[z].position = b[i].bmem[x][y].position;
                b[i].bmem[x][y].rank=tempmr;
                b[i].bmem[x][y].cond = tempmc;
                b[i].bmem[x][y].position = tempmp;
            }
            break;
        }
        }
    }

    void bmove(int r, string s, int bn) {
        int pos = 4;  /*. Iterate over the bot's memory (bmem) for a particular bot (bn) and find the highest-ranked card (myHighR) that satisfies certain conditions (rank, condition, and position).*/
        bool discard_flag = 0;
        int z = rand() % 5;
        int myHighR = 0;
        int myHighC=4;
        if (r <= 6) {
            for (int i = 0;i < 3;i++) {
                if (b[bn].bmem[bn][i].rank > myHighR && b[bn].bmem[bn][i].cond > 0 && b[bn].bmem[bn][i].position == i) {
                    myHighR = b[bn].bmem[bn][i].rank;
                    myHighC = i;
                    discard_flag = 1; // Set discard_flag to 1 if a suitable card is found.
                }
            }
            if (discard_flag == 0) {  /* If discard_flag is still 0, randomly choose a position (3) and check the bot's memory again for the highest-ranked card.*/
                if (z == 0) {
                    goto l1;
                }
                for (int i = 0;i < 3;i++) {
                    if (b[bn].bmem[bn][i].rank > myHighR && b[bn].bmem[bn][i].cond > 0 && b[bn].bmem[bn][i].position == 3) {
                        myHighR = b[bn].bmem[bn][i].rank;
                        myHighC = i;
                        discard_flag = 1;
                    }
                }
            }
            l1:
            if (discard_flag == 1) {
                if (myHighR < r) {
                    discard_flag = 0;
                }
            }
            if (discard_flag == 1) {
                b[bn].hand[myHighC].rank = r;
                b[bn].hand[myHighC].suit = s;
                dr = b[bn].hand[myHighC].rank;
                ds = b[bn].hand[myHighC].suit;
                b[bn].bmem[bn][myHighC].cond = 2;
                b[bn].bmem[bn][myHighC].position = myHighC;
                b[bn].bmem[bn][myHighC].rank = r;
                pos = myHighC;
                for (int i = 0;i < 3;i++) {
                    if (i == bn) {
                        continue;
                    }
                    b[i].bmem[bn][myHighC].cond = 1;
                    b[i].bmem[bn][myHighC].position = myHighC;
                    b[i].bmem[bn][myHighC].rank = dr;
                }
            }
        }
        if (discard_flag == 0) {
            dr = r;
            ds = s;
            for (int i = 0;i < 3;i++) {
                if (i == bn) {
                    continue;
                }
                for (int j = 0;j < 3;j++) {
                    if (b[i].bmem[bn][j].cond == 0) {
                        b[i].bmem[bn][j].cond = 1;
                        b[i].bmem[bn][j].position = j;
                        b[i].bmem[bn][j].rank = dr;
                    }
                }
            }
        }
    
        cout << "Bot " << bn << " discarded ";
        switch (dr) {
        case 1:
            cout << "Ace";
            break;
        case 11:
            cout << "Jack";
            break;
        case 12:
            cout << "Queen";
            break;
        case 13:
            cout << "King";
            break;
        default:
            cout << dr;
        }
        cout << " of " << ds;
        switch (pos) {
        case 4: {
            cout << " without exchange" << endl;
            break;
        }
        default:
        {
            cout << " from index " << pos << endl;
        }
        }
        switch (dr) {
        case 13:                    //bots move on king
        {
            b[bn].shuffle();
            for (int j = 0;j < 3;j++) {
                b[bn].bmem[bn][j].rank = b[bn].hand[j].rank;
                b[bn].bmem[bn][j].position = j;
                b[bn].bmem[bn][j].cond = 2;
            }
            for (int i = 0;i < 3;i++) {
                if (i == bn) {
                    continue;
                }
                for (int j = 0;j < 3;j++) {
                    b[i].bmem[bn][j].position = 3;
                }
            }
            break;
        }
        case 10:                //bot's move on 10
        {
            int x = 0;
            int z = 0;
            int y = rand() % 4;
            while (x < 6) {
                while (y == bn) {
                    y = rand() % 4;
                }
                switch (y) {
                case 3:
                {
                    if ((b[bn].pmem[0].cond > 0 && b[bn].pmem[1].cond > 0 && b[bn].pmem[2].cond > 0) || (b[bn].pmem[0].cond > 0 && b[bn].pmem[1].cond > 0) || (b[bn].pmem[0].cond > 0 && b[bn].pmem[2].cond > 0) || (b[bn].pmem[1].cond > 0 && b[bn].pmem[2].cond > 0)) {
                        break;
                    }
                    p.shuffle();
                    cout << "Bot shuffled your cards" << endl;
                    z = 1;
                    for (int j = 0;j < 3;j++) {
                        b[bn].pmem[j].rank = p.hand[j].rank;
                        b[bn].pmem[j].position = j;
                        b[bn].pmem[j].cond = 2;
                    }
                    for (int i = 0;i < 3;i++) {
                        if (i == bn) {
                            continue;
                        }
                        for (int j = 0;j < 3;j++) {
                            b[i].pmem[j].position = 3;
                        }
                    }
                    break;
                }
                default:
                {
                    if ((b[bn].bmem[y][0].cond > 0 && b[bn].bmem[y][1].cond > 0 && b[bn].bmem[y][2].cond > 0) || (b[bn].bmem[y][0].cond > 0 && b[bn].bmem[y][1].cond > 0) || (b[bn].bmem[y][0].cond > 0 && b[bn].bmem[y][2].cond > 0) || (b[bn].bmem[y][1].cond > 0 && b[bn].bmem[y][2].cond > 0)) {
                        break;
                    }
                    b[y].shuffle();
                    cout << "Bot shuffled cards of bot " << y << endl;
                    z = 1;
                    for (int j = 0;j < 3;j++) {
                        b[bn].bmem[y][j].rank = p.hand[j].rank;
                        b[bn].bmem[y][j].position = j;
                        b[bn].bmem[y][j].cond = 2;
                    }
                    for (int i = 0;i < 3;i++) {
                        if (i == bn) {
                            continue;
                        }
                        for (int j = 0;j < 3;j++) {
                            b[i].bmem[y][j].position = 3;
                        }
                    }
                    break;
                }
                    
                }
                y = rand() % 4;
                x++;
            }
            if (z== 0) {
                while (y == bn) {
                    y = rand() % 4;
                }
                switch (y) {
                case 3:
                {
                    p.shuffle();
                    cout << "Bot shuffled your cards" << endl;
                    z = 1;
                    for (int j = 0;j < 3;j++) {
                        b[bn].pmem[j].rank = p.hand[j].rank;
                        b[bn].pmem[j].position = j;
                        b[bn].pmem[j].cond = 2;
                    }
                    for (int i = 0;i < 3;i++) {
                        if (i == bn) {
                            continue;
                        }
                        for (int j = 0;j < 3;j++) {
                            b[i].pmem[j].position = 3;
                        }
                    }
                    
                    break;
                }
                default:
                {
                    b[y].shuffle();
                    cout << "Bot shuffled cards of bot " << y << endl;
                    z = 1;
                    for (int j = 0;j < 3;j++) {
                        b[bn].bmem[y][j].rank = p.hand[j].rank;
                        b[bn].bmem[y][j].position = j;
                        b[bn].bmem[y][j].cond = 2;
                    }
                    for (int i = 0;i < 3;i++) {
                        if (i == bn) {
                            continue;
                        }
                        for (int j = 0;j < 3;j++) {
                            b[i].bmem[y][j].position = 3;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 7:
        {
            int plow = 4;
            int clow = 14;
            int cLown;
            int myHighR = 0;
            int myHighC = 4;
            bool found = 0;
            for (int i = 0;i < 3;i++) {
                if (b[bn].pmem[i].rank < clow && b[bn].pmem[i].position == i && b[bn].pmem[i].cond>0) {
                    plow = 3;
                    clow = b[bn].pmem[i].rank;
                    cLown = i;
                    found = 1;
                }
            }
            for (int i = 0;i < 3;i++) {
                if (i == bn) {
                    continue;
                }
                for (int j = 0;j < 3;j++) {
                    if (b[bn].bmem[i][j].rank < clow && b[bn].bmem[i][j].position == j && b[bn].bmem[i][j].cond>0) {
                        plow = i;
                        clow = b[bn].bmem[i][j].rank;
                        found = 1;
                        cLown = j;
                    }
                }
            }
            if (found == 0) {
                for (int i = 0;i < 3;i++) {
                    if (b[bn].pmem[i].rank < clow && b[bn].pmem[i].position == 3 && b[bn].pmem[i].cond>0) {
                        plow = 3;
                        clow = b[bn].pmem[i].rank;
                        found = 1;
                        cLown = i;
                    }
                }
                for (int i = 0;i < 3;i++) {
                    if (i == bn) {
                        continue;
                    }
                    for (int j = 0;j < 3;j++) {
                        if (b[bn].bmem[i][j].rank < clow && b[bn].bmem[i][j].position == 3 && b[bn].bmem[i][j].cond>0) {
                            plow = i;
                            clow = b[bn].bmem[i][j].rank;
                            cLown = j;
                            found = 1;
                        }
                    }
                }
            }
            if (found == 0) {
                plow = rand() % 4;
                while (plow == bn) {
                    plow = rand() % 4;
                }
                cLown = rand() % 4;
            }
            found = 0;
            for (int i = 0;i < 3;i++) {
                if (b[bn].bmem[bn][i].rank > myHighR && b[bn].bmem[bn][i].cond > 0 && b[bn].bmem[bn][i].position == i) {
                    myHighR = b[bn].bmem[bn][i].rank;
                    myHighC = i;
                    found = 1;
                }
            }
            if (found == 0) {
                for (int i = 0;i < 3;i++) {
                    if (b[bn].bmem[bn][i].rank > myHighR && b[bn].bmem[bn][i].cond > 0 && b[bn].bmem[bn][i].position == 3) {
                        myHighR = b[bn].bmem[bn][i].rank;
                        myHighC = i;
                        found = 1;
                    }
                }
            }
            if (found == 0) {
                myHighC = rand() % 4;
            }
            int tempr, tempmr,tempmc,tempmp;
            string temps;
            switch (plow) {
            case 3:
            {
                tempr = p.hand[cLown].rank;
                temps = p.hand[cLown].suit;
                p.hand[cLown].rank=b[bn].hand[myHighC].rank;
                p.hand[cLown].suit = b[bn].hand[myHighC].suit;
                b[bn].hand[myHighC].rank = tempr;
                b[bn].hand[myHighC].suit = temps;
                for (int i = 0;i < 3;i++) {
                    tempmr = b[i].pmem[cLown].rank;
                    tempmc = b[i].pmem[cLown].cond;
                    tempmp = b[i].pmem[cLown].position;
                    b[i].pmem[cLown].rank = b[i].bmem[bn][myHighC].rank;
                    b[i].pmem[cLown].cond = b[i].bmem[bn][myHighC].position;
                    b[i].pmem[cLown].position = b[i].bmem[bn][myHighC].position;
                    b[i].bmem[bn][myHighC].rank = tempmr;
                    b[i].bmem[bn][myHighC].cond = tempmc;
                    b[i].bmem[bn][myHighC].position = tempmp;
                }
                cout << "Bot exchnaged card with you" << endl;
                cout << "Your index: " << cLown << endl;
                cout << "Bot's index: " << myHighC << endl;
                break;
            }
            default:
            {
                tempr = b[plow].hand[cLown].rank;
                temps = b[plow].hand[cLown].suit;
                b[plow].hand[cLown].rank = b[bn].hand[myHighC].rank;
                b[plow].hand[cLown].suit = b[bn].hand[myHighC].suit;
                b[bn].hand[myHighC].rank = tempr;
                b[bn].hand[myHighC].suit = temps;
                for (int i = 0;i < 3;i++) {
                    tempmr = b[i].bmem[plow][cLown].rank;
                    tempmc = b[i].bmem[plow][cLown].cond;
                    tempmp = b[i].bmem[plow][cLown].position;
                    b[i].bmem[plow][cLown].rank = b[i].bmem[bn][myHighC].rank;
                    b[i].bmem[plow][cLown].cond = b[i].bmem[bn][myHighC].position;
                    b[i].bmem[plow][cLown].position = b[i].bmem[bn][myHighC].position;
                    b[i].bmem[bn][myHighC].rank = tempmr;
                    b[i].bmem[bn][myHighC].cond = tempmc;
                    b[i].bmem[bn][myHighC].position = tempmp;
                }
                cout << "Bot exchnaged card with bot "<<plow << endl;
                cout << "Bot "<<plow<< " index: " << cLown << endl;
                cout << "Bot's index: " << myHighC << endl;
                break;
            }
            }
            break;
        }
        }
    }

    void winner() {
        int sum[4];
        for (int i = 0;i < 3;i++) {
            sum[i] = 0;
            for (int j = 0;j < 3;j++) {
                sum[i] += b[i].hand[j].rank;
            }
        }
        sum[3] = 0;
        for (int i = 0;i < 3;i++) {
            sum[3] += p.hand[i].rank;
        }
        cout << endl;
        cout << "Your score: " << sum[3]<<endl;
        for (int i = 0;i < 3;i++) {
            cout << "Bot " << i + 1 << " score: " << sum[i] << endl;
        }
        cout << endl;
        if (sum[0] < sum[1] && sum[0] < sum[2] && sum[0] < sum[3]) {    //0
            cout << "BOT 1 WINS" << endl;
        }
        else if (sum[1] < sum[0] && sum[1] < sum[2] && sum[1] < sum[3]) {   //1
            cout << "BOT 2 WINS" << endl;
        }
        else if (sum[2] < sum[0] && sum[2] < sum[3] && sum[2] < sum[1]) {   //2
            cout << "BOT 3 WINS" << endl;
        }
        else if (sum[3] < sum[0] && sum[3] < sum[1] && sum[3] < sum[2]) {   //3
            cout << "YOU WIN" << endl;
        }
        else if (sum[0] == sum[1] && sum[0] < sum[2] && sum[0] < sum[3]) {  //01
            cout << "DRAW BETWEEN BOT 1 AND BOT 2" << endl;
        }
        else if (sum[0] == sum[2] && sum[0] < sum[3] && sum[0] < sum[1]) {  //02
            cout << "DRAW BETWEEN BOT 1 AND BOT 3" << endl;
        }
        else if (sum[0] == sum[3] && sum[0] < sum[2] && sum[0] < sum[1]) {  //03
            cout << "DRAW BETWEEN YOU AND BOT 1" << endl;
        }
        else if (sum[1] == sum[2] && sum[1] < sum[3] && sum[1] < sum[0]) {    //12
            cout << "DRAW BETWEEN BOT 2 AND BOT 3" << endl;
        }
        else if (sum[1] == sum[3] && sum[1] < sum[0] && sum[1] < sum[2]) {    //13
            cout << "DRAW BETWEEN YOU AND BOT 2" << endl;
        }
        else if (sum[2] == sum[3] && sum[2] < sum[0] && sum[2] < sum[1]) {    //23
            cout << "DRAW BETWEEN YOU AND BOT 3" << endl;
        }
        else if (sum[0] == sum[1] && sum[1] == sum[2] && sum[2] < sum[3]) {    //012
            cout << "DRAW BETWEEN BOT 1, BOT 2 AND BOT 3" << endl;
        }
        else if (sum[0] == sum[1] && sum[1] == sum[3] && sum[1] < sum[2]) {    //013
            cout << "DRAW BETWEEN YOU, BOT 1 AND BOT 2" << endl;
        }
        else if (sum[0] == sum[2] && sum[2] == sum[3] && sum[2] < sum[1]) {    //023
            cout << "DRAW BETWEEN YOU, BOT 1 AND BOT 3" << endl;
        }
        else if (sum[1] == sum[2] && sum[2] == sum[3] && sum[1] < sum[0]) {    //123
            cout << "DRAW BETWEEN YOU, BOT 2 AND BOT 3" << endl;
        }
        else if (sum[1] == sum[2] && sum[2] == sum[3] && sum[3] == sum[0]) {    //123
            cout << "DRAW BETWEEN ALL" << endl;
        }

    }

    
};

void start_program(){
    cout<<" =============================================================================================================\n"  ;  
    cout<<"| |=========================================================================================================| |\n";
    cout<<"| |        $$___$$_ $$$$_ $$___$$_ $$$$$___ __$$$$$$___ __$$$___ __$$$$__ __$$$$__ $$______ $$$$$$$$        | |\n";
    cout<<"| |        $$$_$$$_ _$$__ $$$__$$_ $$__$$__ __$$__$$__  _$$_$$__ _$$__$$_ _$$__$$_ $$______ $$______        | |\n";
    cout<<"| |        $$$$$$$_ _$$__ $$$$_$$_ $$___$$_ __$$$$$___  $$___$$_ $$______ $$______ $$______ $$$$$$$$        | |\n";
    cout<<"| |        $$_$_$$_ _$$__ $$_$$$$_ $$___$$_ __$$___$$_  $$___$$_ $$__$$$_ $$__$$$_ $$______ $$$$$$$$        | |\n";
    cout<<"| |        $$___$$_ _$$__ $$__$$$_ $$__$$__ __$$___$$_  _$$_$$__ _$$__$$_ _$$__$$_ $$______ $$______        | |\n";
    cout<<"| |        $$___$$_ $$$$_ $$___$$_ $$$$$___ __$$$$$$__  __$$$___ __$$$$__ __$$$$__ $$$$$$$_ $$$$$$$$        | |\n";
    cout<<"| |=========================================================================================================| |\n"    ;
    cout<<" =============================================================================================================  \n\n"  ;                                                       
}

void theme(){
    cout<<"==========================================THEME===============================================================\n";
    cout<<"                COLOR                       ||                 CODE                                           \n";
    cout<<"==============================================================================================================\n";
    cout<<"                BLACK                       ||                   0                                            \n";
    cout<<"                BLUE                        ||                   1                                            \n";
    cout<<"                AQUA                        ||                   2                                            \n";
    cout<<"                RED                         ||                   3                                            \n";
    cout<<"                PURPLE                      ||                   4                                            \n";
    cout<<"==============================================================================================================\n";
    while(1)
    {
    cout<<"Select your theme : ";
    int a;
    cin>>a;
    if(a==0){
        system("color 0A");
        break;
    }
    else if(a==1){
        system("color 1A");
        break;
    }
    else if(a==2){
        system("color 3A");
        break;
    }
    else if(a==3){
        system("color 4F");
        break;
    }
    else if(a==4){
        system("color D0");
        break;
    }
    else{
        cout<<"Invalid theme\nChoose again\nPress any number to continue\n\n";
        cin>>a;
        continue;
    }
    }
}
int main()
{
    //load();
    start_program();
    theme();
    srand(time(0));
    cout << "WELCOME TO MIND BOGGLE" << endl << endl;
    cout<<"RULES"<<endl<<"1) 3 cards will be distributed between 4 players, the player will look at those cards once and put them upside down.\n2) Each player can pick one card from deck.Now he can either discard that card or exchange it with one of his three cards(he cannot look his 3 cards again).There would be 40 cards in deck.\n3)  If a player discards card ranked 10, he can pick any opponent’s cards and shuffle them(now opponent doesn’t know which card is where.\n4) If a player discards card ranked 7, he can exchange one of his card with any of opponent’s card without looking at both cards."<<endl;
    cout << "5) If a player discards card ranked ‘King’, he can pick his 3 cards, look at them and shuffle them.\n6) The game will end after all cards from deck are picked up.\n7) Player whose sum of card rank is lowest will win." << endl;
    Game g;
    int x = 0;
    g.initializeDeck();
    g.distributeCards();
    cout << "\nYour cards are:" << endl;
    g.p.printHand();
    for (int i = 0;i < 10;i++) {
        cout << endl;
        g.pmove(g.bank[x].rank, g.bank[x].suit);
        x++;
        for (int j = 0;j < 3;j++) {
            cout << endl;
            g.bmove(g.bank[x].rank, g.bank[x].suit, j);
            x++;
        }
    } 
    g.printAllHands();
    g.winner();

}