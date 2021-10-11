#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <cmath>
#include <unordered_map>
#include <algorithm>
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
            //cout << "count: " << temp.transactionsCount<<endl;
            Chain.push_back(temp);
            temp.transactionsCount=0; // bruh to find this
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
    if (n % 2 == 1)
    {
        hashes1[n] = hashes1[n - 1];
        n += 1;
    }
    n /= 2;
    for (int i = 0; i < n; i++)
    {
        hashes2[i] = HashHex(hashes1[i * 2] + hashes1[i * 2 + 1]);
    }
    if (n % 2 == 1)
    {
        hashes2[n] = hashes2[n - 1];
        n += 1;
    }
    n /= 2;
    for (int i = 0; i < n; i++)
    {
        hashes3[i] = HashHex(hashes2[i * 2] + hashes2[i * 2 + 1]);
    }
    if (n % 2 == 1)
    {
        hashes3[n] = hashes3[n - 1];
        n += 1;
    }
    n /= 2;
    for (int i = 0; i < n; i++)
    {
        hashes4[i] = HashHex(hashes3[i * 2] + hashes3[i * 2 + 1]);
    }
    if (n % 2 == 1)
    {
        hashes4[n] = hashes4[n - 1];
        n += 1;
    }
    n /= 2;
    for (int i = 0; i < n; i++)
    {
        hashes5[i] = HashHex(hashes4[i * 2] + hashes4[i * 2 + 1]);
    }
    if (n % 2 == 1)
    {
        hashes5[n] = hashes5[n - 1];
        n += 1;
    }
    n /= 2;
    for (int i = 0; i < n; i++)
    {
        hashes6[i] = HashHex(hashes5[i * 2] + hashes5[i * 2 + 1]);
    }
    if (n % 2 == 1)
    {
        hashes6[n] = hashes6[n - 1];
        n += 1;
    }
    n /= 2;
    for (int i = 0; i < n; i++)
    {
        hashes7[i] = HashHex(hashes6[i * 2] + hashes6[i * 2 + 1]);
    }
    if (n % 2 == 1)
    {
        hashes7[n] = hashes7[n - 1];
        n += 1;
    }
    n /= 2;
    for (int i = 0; i < n; i++)
    {
        hashes8[i] = HashHex(hashes7[i * 2] + hashes7[i * 2 + 1]);
    }
    return hashes8[0];
}

void ValidateTransactionPool(vector<Block> &chain, vector<Transaction> &pool)
{
    //Validate hash...       (if SSH, then validate signature)
    for (auto poolit = pool.begin(); poolit != pool.end(); poolit++) // looping transaction pool
        if ((*poolit).id != HashHex((*poolit).timestamp + (*poolit).sender + (*poolit).reciever + (*poolit).amount))
        {
            //remove transaction
            pool.erase(poolit);
            poolit--;
        }

    //Check if repeated
    for (auto it = chain.end() - 1; it != chain.begin(); it--)           // first block doesn't matter. Looping blockchain backwards
        for (auto poolit = pool.begin(); poolit != pool.end(); poolit++) // looping transaction pool
            for (int i = 0; i < (*it).transactionsCount; i++)            // looping block transactions
                if ((*it).transactions[i].id == (*poolit).id)            //  checking transaction from pool is already in block
                {
                    //remove transaction
                    pool.erase(poolit);
                    poolit--;
                }

    //check transaction sum validity, overspending protection
    unordered_map<string, double> wallets;
    for (auto poolit = pool.begin(); poolit != pool.end(); poolit++)
    {
        if(wallets.find((*poolit).sender)==wallets.end())
        {
            wallets[(*poolit).sender] = 0;
        }
        wallets[(*poolit).sender] -= stod((*poolit).amount);
    } // looping transaction pool

    // for (auto it = wallets.begin(); it != wallets.end(); it++)
    // {
    //     cout << "1  id:" << (*it).first<<endl;
    //     cout << "1 sum:" << (*it).second << endl;
    // }

    for (auto it = wallets.begin(); it != wallets.end(); it++) // looping each wallet
    {
        for (auto it2 = chain.begin(); it2 != chain.end(); it2++) // checking all transactions
        {
            for (int i = 0; i < (*it2).transactionsCount; i++)
            {
                //cout << "count: " << (*it2).transactionsCount << endl;
                if ((*it2).transactions[i].reciever == (*it).first) //  count recieved memes
                {
                    wallets[(*it).first] += stod((*it2).transactions[i].amount);
                    //cout << i << " Recieved: " << stod((*it2).transactions[i].amount)<<endl;
                }
                if ((*it2).transactions[i].sender == (*it).first) //  count sent memes
                {
                    wallets[(*it).first] -= stod((*it2).transactions[i].amount);
                    //cout << i << " Sent: " << stod((*it2).transactions[i].amount)<<endl;
                }
            }
        }
    }
    // for (auto it = wallets.begin(); it != wallets.end(); it++)
    // {
    //     cout << "2  id:" << (*it).first<<endl;
    //     cout << "2 sum:" <<(*it).second << endl;
    // }

    for (auto poolit = pool.begin(); poolit != pool.end(); poolit++)
    {
        if (wallets[(*poolit).sender] < 0)
        {
            pool.erase(poolit);
            poolit--;
        }
    }

    //rewrite transactionpool.txt
    ofstream poolTxt("../TransactionPool.txt");

    for (auto poolit = pool.begin(); poolit != pool.end(); poolit++)
    {
        poolTxt << "{\n";
        poolTxt << "\t" << (*poolit).id << "\n";
        poolTxt << "\t" << (*poolit).timestamp << "\n";
        poolTxt << "\t" << (*poolit).sender << "\n";
        poolTxt << "\t" << (*poolit).reciever << "\n";
        poolTxt << "\t" << (*poolit).amount << "\n";
        poolTxt << "}\n";
    }
    poolTxt.close();
}

string CalculateDifficulty(vector<Block> &Chain)
{
    vector<int> timestamps;
    int i=0;
    bool applicable = true;
    string diffiulty =(*(Chain.end()-1)).difficultyTarget;
    for(auto it = (Chain.end()-1); it != Chain.begin(); it--)
    {
        if((*it).difficultyTarget!=diffiulty) applicable=false;

        timestamps.push_back(   stoi(  (*it).timestamp)-stoi((*(it-1)).timestamp )    )  ;

        i++;
        if(i==21)break;
    }
    sort(timestamps.begin(),timestamps.end());

    if(!applicable || i!=21) return diffiulty;
    int c=0;
    for(auto it = timestamps.begin(); it != timestamps.end(); it++)
    {
        c++;
        if(c==11)
        {
            cout << "difficulty change, time median:" << (*it) <<endl;
            if((*it)<=10)
            {
                return to_string(stoi(diffiulty)+1);
            }
            if((*it)>=40)
            {
                return to_string(stoi(diffiulty)-1);
            }
            break;
        }
    }

    return "20";
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
    while (true)
    {
        vector<Block> Chain;
        ReadChain(Chain);
        // MINING ===================================================

        auto it = Chain.end() - 1; // latest block

        //read TransactionPool.txt
        //add to newBlock

        vector<Transaction> transactionPool;

        ReadTransactionPool(transactionPool);

        //NOW VALIDATE transactionPool

        ValidateTransactionPool(Chain, transactionPool);

        //update difficulty

        //new potencial block
        Block newBlock; //new block
        newBlock.prevHash = HashBit((*it).prevHash + (*it).timestamp + (*it).version + (*it).merkleRootHash + (*it).difficultyTarget + (*it).nonce);
        newBlock.timestamp = to_string(time(0));
        newBlock.version = "1";

        newBlock.difficultyTarget = CalculateDifficulty(Chain);

        //Choose transactions, first transaction is mining reward

        Transaction chosenOnes[128];
        int chosenOnesC = 1;
        chosenOnes[0].id = "Memes";
        chosenOnes[0].timestamp = newBlock.timestamp;
        chosenOnes[0].sender = "Universe_itself";
        chosenOnes[0].reciever = user.id;
        chosenOnes[0].amount = to_string(1000 / pow(2, (stoi(newBlock.difficultyTarget) - 20)));
        for (auto it = transactionPool.begin(); it != transactionPool.end(); it++)
        {
            chosenOnes[chosenOnesC] = (*it);
            //cout << chosenOnes[chosenOnesC].id << " ";
            chosenOnesC++;
            if (chosenOnesC == 128)
                break;
        }
        //cout << endl;

        newBlock.merkleRootHash = GetMerkleHash(chosenOnes, chosenOnesC);

        // block header to mine
        string block = newBlock.prevHash + newBlock.timestamp + newBlock.version + newBlock.merkleRootHash + newBlock.difficultyTarget;

        time_t start = time(0);

        for (int i = 0; true; i++) // actual mining
        {
            uint8_t *hash = HashRaw(block + to_string(i));
            bool solved = true;
            for (int a = 0; a < stoi(newBlock.difficultyTarget); a++)
            {
                if ((hash[a / 8] >> (7 - (a % 8))) != 0)
                {
                    solved = false;
                    break;
                }
            }

            delete[] hash;


            if (i % 100000 == 0)
            {
                string prevHash = (*(Chain.end() - 1)).prevHash;
                cout << ".";
                Chain.clear();
                ReadChain(Chain);
                if(prevHash!= (*(Chain.end() - 1)).prevHash)
                {
                    cout << "missed\n";
                    break;
                }
            }
            
            if (solved)
            {
                newBlock.nonce = to_string(i);
                cout << "\ncode: " << i << endl;
                cout << HashBit(block + to_string(i)) << endl;
                break;
            }


        }

        if (newBlock.nonce != "") // push to blockchain
        {
            ofstream write("../Blockchain.txt", std::ios_base::app);
            write << "{\n";
            write << "\t" << newBlock.prevHash << endl;
            write << "\t" << newBlock.timestamp << endl;
            write << "\t" << newBlock.version << endl;
            write << "\t" << newBlock.merkleRootHash << endl;
            write << "\t" << newBlock.difficultyTarget << endl;
            write << "\t" << newBlock.nonce << endl;
            for (int ch = 0; ch < chosenOnesC; ch++)
            {
                write << "\t{\n";
                write << "\t\t" << chosenOnes[ch].id << endl;
                write << "\t\t" << chosenOnes[ch].timestamp << endl;
                write << "\t\t" << chosenOnes[ch].sender << endl;
                write << "\t\t" << chosenOnes[ch].reciever << endl;
                write << "\t\t" << chosenOnes[ch].amount << endl;
                write << "\t}\n";
            }
            write << "}\n";
            write.close();
        }
    }
    system("pause");
    return 0;
}