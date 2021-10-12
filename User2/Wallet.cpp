#include<iostream>
#include<fstream>
#include<vector>
#include <time.h>
#include"../HashNew.h"

using namespace std;

struct Transaction
{
    string id;
    string timestamp;
    string sender;
    string reciever;
    string amount;
};

struct Block
{
    string prevHash;
    string timestamp;
    string version;
    string merkleRootHash;
    string difficultyTarget;
    string nonce;
    Transaction transactions[128];
    int transactionsCount=0;
};

struct User
{
    string name;
    string id;
    string memes;
};

void CountMemes(string userid)
{
    cout << "scrolling transactions..."<<endl;

    double memes=0;
    
    ifstream blockchain("../Blockchain.txt");
    if(!blockchain.is_open())
    {
        cerr<<"bad txt";
        system("pause");
    }
    
    Block temp;
    string read;

    bool isBlock = false;
    bool isTransaction = false;
    while (!blockchain.eof())
    {
        blockchain >> read;
        if(read=="{" && !isBlock)
        {
            isBlock=true;
            continue;
        }
        else if(read=="}" && !isTransaction)
        {
            isBlock=false;
            temp.transactionsCount=0;
            continue;
        }
        else if(read=="{" && isBlock)
        {
            isTransaction=true;
            continue;
        }
        else if(read=="}" && isTransaction)
        {
            isTransaction=false;
            continue;
        }

        if(!isTransaction) // then it's block header
        {
            temp.prevHash = read;
            blockchain >> temp.timestamp;
            blockchain >> temp.version;
            blockchain >> temp.merkleRootHash;
            blockchain >> temp.difficultyTarget;
            blockchain >> temp.nonce;
        }
        else // transactions
        {
            temp.transactions[temp.transactionsCount].id = read;
            blockchain >> temp.transactions[temp.transactionsCount].timestamp;
            blockchain >> temp.transactions[temp.transactionsCount].sender;
            blockchain >> temp.transactions[temp.transactionsCount].reciever;
            blockchain >> temp.transactions[temp.transactionsCount].amount;

            if(temp.transactions[temp.transactionsCount].reciever==userid)
            {
                memes += stod(temp.transactions[temp.transactionsCount].amount);
            }
            if(temp.transactions[temp.transactionsCount].sender==userid)
            {
                memes -= stod(temp.transactions[temp.transactionsCount].amount);
            }
            
            temp.transactionsCount++;
        }
    }

    cout << "You have: " << memes << " memes\n";
   // block = temp.prevHash + temp.timestamp + temp.version + temp.merkleRootHash + temp.difficultyTarget;

    //cout << block << endl;


    blockchain.close();
}


int main()
{
    string login;
    cout << "Memes wallet login: ";
    cin >> login;
    ifstream userWallet(login+".txt");
    if(!userWallet.is_open()){
        cout << "User not found. Registering...\n";
        ofstream reg(login+".txt");
        reg << login<<endl;
        reg << HashHex(login)<<endl;
        reg << 0;
        reg.close();
        userWallet.open(login+".txt");
    };

    User user;
    userWallet >> user.name;
    userWallet >> user.id;
    userWallet >> user.memes;
    userWallet.close();

    cout << "\nWallet of " << user.name << endl<<endl;
    cout << "select action:\n";
    cout << "Memes balance (1)\n";
    cout << "Make transaction (2)\n";
    cout << "Spam transactions (3)\n";

    string input;

    bool onMenu=true;
    while(onMenu)
    {
        cout << "Input: ";
        cin >> input;
        //onMenu=false;

        switch (((int)input[0]-'0'))
        {

        case 1:
            CountMemes(user.id);
        break;

        case 2:
            {
            string reciever;
            string cash;
            string timestamp = to_string(time(0));

            cout << "Transaction ===========\n";
            cout << "Reciever id: ";
            cin >> reciever;
            cout << "Amount egz.:(420.69): ";
            cin >> cash;

            ofstream write("../TransactionPool.txt", std::ios_base::app);
            if(!write.is_open())
            {
                cerr<<"bad txt";
                system("pause");
            }
            
            write << "{\n";
            write << "\t" << HashHex(timestamp+user.id+reciever+cash) << endl;
            write << "\t" << timestamp << endl;
            write << "\t" << user.id << endl;
            write << "\t" << reciever << endl;
            write << "\t" << cash << endl;
            write << "}\n";


            write.close();
            break;
            }
            case 3:
            {
            ofstream write("../TransactionPool.txt", std::ios_base::app);
            if(!write.is_open())
            {
                cerr<<"bad txt";
                system("pause");
            }
            for(int i=0;i<200;i++)
            {

                string reciever = "user"+to_string(i);
                string cash = "1";
                string timestamp = to_string(time(0));
                write << "{\n";
                write << "\t" << HashHex(timestamp+user.id+reciever+cash) << endl;
                write << "\t" << timestamp << endl;
                write << "\t" << user.id << endl;
                write << "\t" << reciever << endl;
                write << "\t" << cash << endl;
                write << "}\n";

            }
            write.close();
                break;
            }
        
        default:
            cout <<"No such command. Type egz.: 1\n";
            onMenu=true;
            break;
        }
    }


    system("pause");
    return 0;
}