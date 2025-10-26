/*
Problem Statement:
------------------
You have been tasked with writing a program for a popular bank that will automate all its incoming transactions (transfer, deposit, and withdraw). 
The bank has n accounts numbered from 1 to n. 
The initial balance of each account is stored in a 0-indexed integer array `balance`, with the (i + 1)th account having an initial balance of balance[i].

Execute all the valid transactions. A transaction is valid if:
  1. The given account number(s) are between 1 and n, and
  2. The amount of money withdrawn or transferred from is less than or equal to the balance of the account.

Implement the Bank class:
  - Bank(long[] balance)
        Initializes the object with the 0-indexed integer array balance.
  - bool transfer(int account1, int account2, long long money)
        Transfers money dollars from the account numbered account1 to account2.
        Return true if the transaction was successful, false otherwise.
  - bool deposit(int account, long long money)
        Deposits money dollars into the given account.
        Return true if the transaction was successful, false otherwise.
  - bool withdraw(int account, long long money)
        Withdraws money dollars from the given account.
        Return true if the transaction was successful, false otherwise.

  Approach:
  ---------
    - The class directly stores all account balances in a `vector<long long>` for constant-time access.
    - Each operation checks account validity (index bounds) and sufficient funds when needed.
    - If valid, updates are done in O(1) per operation.

  Time Complexity:
  ----------------
    - transfer(): O(1)
    - deposit():  O(1)
    - withdraw(): O(1)

  Space Complexity:
  -----------------
    - O(n), where n is the number of accounts, due to storing the balances.
*/
class Bank {
    const int NumAccounts_;
    vector<long long> balance_;

public:
    Bank(vector<long long>& balance):balance_(balance), NumAccounts_(balance.size()) {
        
    }
    
    bool transfer(int account1, int account2, long long money) {
        bool result = false;
        if(account1 - 1 < NumAccounts_ && account2 - 1 < NumAccounts_ && balance_[account1 - 1] >= money){
            balance_[account1 - 1] -= money;
            balance_[account2 - 1] += money;
            result =  true; 
        }
        return result;
    }
    
    bool deposit(int account, long long money) {
        bool result = false;
        if(account - 1 < NumAccounts_ ){
            balance_[account - 1] += money;
            result = true;
        }
        return result;
    }
    
    bool withdraw(int account, long long money) {
        bool result = false;
        if(account - 1 < NumAccounts_  && balance_[account - 1] >= money){
            balance_[account - 1] -= money;
            result =  true; 
        }
        return result;
    }
};

