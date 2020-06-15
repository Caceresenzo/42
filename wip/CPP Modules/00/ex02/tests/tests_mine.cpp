#include "Account.class.hpp"

int main(void)
{
	Account *accounts[8];
	int initials[] = { 42, 54, 957, 432, 1234, 0, 754, 16576 };

	for (int i = 0; i < 8; i++) {
		accounts[i] = new Account(initials[i]);
	}

	Account::displayAccountsInfos();

	for (int i = 0; i < 8; i++) {
		accounts[i]->displayStatus();
	}

	int deposits[] = { 5, 765, 564, 2, 87, 23, 9, 20 };

	for (int i = 0; i < 8; i++) {
		accounts[i]->makeDeposit(deposits[i]);
	}

	Account::displayAccountsInfos();

	for (int i = 0; i < 8; i++) {
		accounts[i]->displayStatus();
	}

	int withdrawals[] = { 10000, 34, 657, 4, 76, 10000, 657, 7654 };

	for (int i = 0; i < 8; i++) {
		accounts[i]->makeWithdrawal(withdrawals[i]);
	}

	Account::displayAccountsInfos();

	for (int i = 0; i < 8; i++) {
		accounts[i]->displayStatus();
	}

	for (int i = 0; i < 8; i++) {
		delete accounts[i];
	}
}
