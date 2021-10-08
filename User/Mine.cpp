#include<iostream>
#include<fstream>
#include<vector>
#include"../HashNew.h"

using namespace std;

struct Transaction
{
    string id;
    string sender;
    string reciever;
    string amount;
};

struct Block
{
    string prevHash;
    string timestamp;
    string version;
    string merkelRootHash;
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

int main()
{
    string block; //latest

    ifstream blockchain("Blockchain.txt");

    vector<Block> Chain;
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
            blockchain >> temp.merkelRootHash;
            blockchain >> temp.difficultyTarget;
            blockchain >> temp.nonce;
        }
        else // transactions
        {
            temp.transactions[temp.transactionsCount].id = read;
            blockchain >> temp.transactions[temp.transactionsCount].sender;
            blockchain >> temp.transactions[temp.transactionsCount].reciever;
            blockchain >> temp.transactions[temp.transactionsCount].amount;
            temp.transactionsCount++;
        }
    }
    block = temp.prevHash + temp.timestamp + temp.version + temp.merkelRootHash + temp.difficultyTarget;

    cout << block << endl;

    for(int i=0;i<100000000;i++)
    {
        uint8_t * hash = HashRaw(block+to_string(i));
        bool solved=true;
        for(int a=0;a<stoi(temp.difficultyTarget)/2;a++)
        {
            if(hash[a]!=0)
            {
                solved=false;
            }
        }
        if(stoi(temp.difficultyTarget)%2==1)
        {
            if((hash[stoi(temp.difficultyTarget)/2]>>4)!=0)
            {
                solved=false;
            }
        }
        if(solved)
        {
            cout << "code: " << i <<endl;
            cout << HashHex(block+to_string(i)) << endl;
            break;
        }
        delete[] hash;
        if(i%10000==0)cout<<i<<endl;
    }
    system("pause");
    return 0;
}