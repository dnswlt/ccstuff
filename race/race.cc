// Simple program to demonstrate race conditions. 
// Two threads add and subtract an amount from an account.
// In the end, the balance is != 0 if there was a data race.

#include <iostream>
#include <thread>
#include <mutex>

std::mutex account_mutex;

using Lock = std::lock_guard<std::mutex>;

class Account {
public:
  int balance;
  Account(int initial_balance) : balance(initial_balance) { }
};

void run(Account *account) {
  for (int i=0; i<100000; i++) {
    Lock lock(account_mutex); // comment this line to obtain a data race
    account->balance += 1;
    account->balance -= 1;
  }
}

int main() {
  Account acc(0);
  std::thread t1(run, &acc);
  std::thread t2(run, &acc);
  t1.join();
  t2.join();
  std::cout << "Final balance is " << acc.balance << "\n";
  return 0;
}


