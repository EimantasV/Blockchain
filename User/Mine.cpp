#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include<cmath>
#include "../HashNew.h"

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
    int transactionsCount = 0; // for validation
};

struct User
{
    string name;
    string id;
    string memes;
};

void ReadChain(vector<Block> &Chain)
{
    ifstream blockchain("../Blockchain.txt");
    if (!blockchain.is_open())
    {
        cerr << "couldn't open file.";
        system("pause");
    }

    Block temp;
    string read;
    bool isBlock = false;
    bool isTransaction = false;
    while (!blockchain.eof())
    {
        blockchain >> read;
        if (read == "{" && !isBlock)
        {
            isBlock = true;
            continue;
        }
        else if (read == "}" && !isTransaction)
        {
            isBlock = false;
            Chain.push_back(temp);
            continue;
        }
        else if (read == "{" && isBlock)
        {
            isTransaction = true;
            continue;
        }
        else if (read == "}" && isTransaction)
        {
            isTransaction = false;
            continue;
        }

        if (!isTransaction) // then it's block header
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
            temp.transactionsCount++;
        }
    }
    blockchain.close();
}

void ReadTransactionPool(vector<Transaction> &Pool)
{
    ifstream readTransactions("../TransactionPool.txt");
    if (!readTransactions.is_open())
    {
        cerr << "couldn't open file.";
        system("pause");
    }

    Transaction temp;
    string read;
    bool isTransaction = false;
    while (!readTransactions.eof())
    {
        readTransactions >> read;
        if (read == "{" && !isTransaction)
        {
            isTransaction = true;
            continue;
        }
        else if (read == "}" && isTransaction)
        {
            isTransaction = false;
            Pool.push_back(temp);
            continue;
        }

        if (isTransaction) // then it's block header
        {
            temp.id = read;
            readTransactions >> temp.timestamp;
            readTransactions >> temp.sender;
            readTransactions >> temp.reciever;
            readTransactions >> temp.amount;
            //temp.transactionsCount++;
        }
    }
    readTransactions.close();
}
string GetMerkleHash(Transaction transactions[], int n)
{
    if (n == 0)
        return HashHex("");

    string hashes1[128];
    string hashes2[64];
    string hashes3[32];
    string hashes4[16];
    string hashes5[8];
    string hashes6[4];
    string hashes7[2];
    string hashes8[1];
    for (int i = 0; i < n; i++)
    {
        hashes1[i] = HashHex(transactions[i].id + transactions[i].timestamp + transactions[i].sender + transactions[i].reciever + transactions[i].amount);
    }
    if(n%2==1)
    {
        hashes1[n] = hashes1[n-1];
        n+=1;
    }
    n/=2;
    for(int i=0;i< n ;i++)
    {
        hashes2[i] = HashHex(hashes1[i*2]+hashes1[i*2+1]);
    }
    if(n%2==1)
    {
        hashes2[n] = hashes2[n-1];
        n+=1;
    }
    n/=2;
    for(int i=0;i< n ;i++)
    {
        hashes3[i] = HashHex(hashes2[i*2]+hashes2[i*2+1]);
    }
    if(n%2==1)
    {
        hashes3[n] = hashes3[n-1];
        n+=1;
    }
    n/=2;
    for(int i=0;i< n ;i++)
    {
        hashes4[i] = HashHex(hashes3[i*2]+hashes3[i*2+1]);
    }
    if(n%2==1)
    {
        hashes4[n] = hashes4[n-1];
        n+=1;
    }
    n/=2;
    for(int i=0;i< n ;i++)
    {
        hashes5[i] = HashHex(hashes4[i*2]+hashes4[i*2+1]);
    }
    if(n%2==1)
    {
        hashes5[n] = hashes5[n-1];
        n+=1;
    }
    n/=2;
    for(int i=0;i< n ;i++)
    {
        hashes6[i] = HashHex(hashes5[i*2]+hashes5[i*2+1]);
    }
    if(n%2==1)
    {
        hashes6[n] = hashes6[n-1];
        n+=1;
    }
    n/=2;
        for(int i=0;i< n ;i++)
    {
        hashes7[i] = HashHex(hashes6[i*2]+hashes6[i*2+1]);
    }
    if(n%2==1)
    {
        hashes7[n] = hashes7[n-1];
        n+=1;
    }
    n/=2;
    for(int i=0;i< n ;i++)
    {
        hashes8[i] = HashHex(hashes7[i*2]+hashes7[i*2+1]);
    }
    return hashes8[0];

}

string CalculateDifficulty(vector<Block> &Chain)
{
    return "5";
}

int main()
{
    string login;
    cout << "Memes mine login: ";
    cin >> login;
    ifstream userWallet(login + ".txt");
    if (!userWallet.is_open())
        return 1;

    User user;
    userWallet >> user.name;
    userWallet >> user.id;
    userWallet >> user.memes;
    userWallet.close();

    vector<Block> Chain;

    ReadChain(Chain);

    // MINING ===================================================

    auto it = Chain.end() - 1; // latest block

    //read TransactionPool.txt
    //add to newBlock

    vector<Transaction> transactionPool;

    ReadTransactionPool(transactionPool);

    //NOW VALIDATE transactionPool
    
    




    //

    Transaction chosenOnes[128];
    int chosenOnesC = 1;
    chosenOnes[0].id = "Memes";
    chosenOnes[0].timestamp = (*it).timestamp;
    chosenOnes[0].sender = "Universe_itself";
    chosenOnes[0].reciever = user.id;
    chosenOnes[0].amount = to_string(1000 / pow(2, (5 - stoi((*it).difficultyTarget))));
    for (auto it = transactionPool.begin(); it != transactionPool.end(); it++)
    {
        chosenOnes[chosenOnesC] = (*it);
        //cout << chosenOnes[chosenOnesC].id << " ";
        chosenOnesC++;
        if (chosenOnesC == 128)
            break;
    }
    cout << endl;

    //do merkle hash with transactions
    //update difficulty

    Block newBlock; //new block
    newBlock.prevHash = HashHex((*it).prevHash + (*it).timestamp + (*it).version + (*it).merkleRootHash + (*it).difficultyTarget + (*it).nonce);
    newBlock.timestamp = to_string(time(0));
    newBlock.version = "1";
    newBlock.merkleRootHash = GetMerkleHash(chosenOnes, chosenOnesC);
    newBlock.difficultyTarget = CalculateDifficulty(Chain);

    //newBlock = (*it).prevHash + to_string(time(0)) + "1" + (*it).merkleRootHash + (*it).difficultyTarget;

    //cout << newBlock.prevHash << endl;
    //cout << newBlock.difficultyTarget << endl;

    // for (auto it = Chain.begin(); it != Chain.end(); it++)
    //     cout << (*it).difficultyTarget << " ";

    string block = newBlock.prevHash + newBlock.timestamp + newBlock.version + newBlock.merkleRootHash + newBlock.difficultyTarget;

    for (int i = 0; i < 100000000; i++)
    {
        uint8_t *hash = HashRaw(block + to_string(i));
        bool solved = true;
        for (int a = 0; a < stoi(newBlock.difficultyTarget) / 2; a++)
        {
            if (hash[a] != 0)
            {
                solved = false;
            }
        }
        if (stoi(newBlock.difficultyTarget) % 2 == 1)
        {
            if ((hash[stoi(newBlock.difficultyTarget) / 2] >> 4) != 0)
            {
                solved = false;
            }
        }
        if (solved)
        {
            newBlock.nonce = to_string(i);
            cout << "\ncode: " << i << endl;
            cout << HashHex(block + to_string(i)) << endl;
            break;
        }
        delete[] hash;
        if (i % 10000 == 0)
            cout << ".";
    }

    if (newBlock.nonce != "")
    {
        ofstream write("../Blockchain.txt", std::ios_base::app);
        write << "{\n";
        write << "\t" << newBlock.prevHash << endl;
        write << "\t" << newBlock.timestamp << endl;
        write << "\t" << newBlock.version << endl;
        write << "\t" << newBlock.merkleRootHash << endl;
        write << "\t" << newBlock.difficultyTarget << endl;
        write << "\t" << newBlock.nonce << endl;
        for(int ch =0;ch<chosenOnesC;ch++)
        {
            write << "\t{\n";
            write << "\t\t" << chosenOnes[ch].id << endl;
            write << "\t\t" << chosenOnes[ch].timestamp << endl;
            write << "\t\t" << chosenOnes[ch].sender << endl;
            write << "\t\t" << chosenOnes[ch].reciever << endl;
            write << "\t\t" << chosenOnes[ch].amount << endl;
            write << "\t}\n";
        }
        write << "}\n\n";
        write.close();
    }

    system("pause");
    return 0;
}