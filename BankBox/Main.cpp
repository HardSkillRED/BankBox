#include <iostream>
#include <string>
#include <map>

using namespace std;

/*Массив - перечень номиналов валют, при необходимости можно будет заменить на допустим list
и использовать как номинал для допустим разных типов валют*/
const int cashMassCount = 8;
int cashMass[cashMassCount] = { 1 , 5 , 10, 50, 100, 500, 1000, 5000 };

class Cash {
private:
	string name;
	map <int, int> CashType;
public:
	Cash(string name, int* cashMass, int cashMassCount) {
		this->name = name;
		for (int i = 0; i < cashMassCount; i++) {
			CashType[cashMass[i]] = 0;
		}
	}

	string GetCashName() {
		return this->name;
	}

	void ShowCash() {
		for (auto getType : CashType) {
			if (getType.second > 0) {
				cout << this->name << " " << getType.first << " " << getType.second << endl;
			}
		}
	}

	bool AddCash(int nominal, int value) {
		if (CashType.count(nominal)) {
			CashType[nominal] += value;
			return true;
		}
		return false;
	}

	map <int, int> GetCash(int summ) {
		map <int, int> reservedCash;
		int tmp, nominal, count;
		for (auto it = CashType.rbegin(); it != CashType.rend(); it++) {
			count = it->second;
			nominal = it->first;
			if (count > 0 && nominal < summ) {
				tmp = summ / nominal;
				tmp = tmp > count ? count : tmp;
				reservedCash[nominal] = tmp;
				summ -= tmp * nominal;
			}
			if (summ == 0) {
				break;
			}
		}
		if (summ > 0) {
			reservedCash.clear();
		}
		for (auto popCash : reservedCash) {
			CashType[popCash.first] -= popCash.second;
		}
		return reservedCash;
	}
};

map<string, Cash*> AllCash; // map здесь использован исключетельно для упрощения сортировки по наименованию валюты

bool AddCurrencies(string cashName, int* cashMass, int cashMassCount) {
	int nominal, value;
	cin >> nominal >> value;
	for (auto isName : AllCash) {
		if (cashName == isName.second->GetCashName()) {
			return isName.second->AddCash(nominal, value);
		}
	}
	Cash* newCash = new Cash(cashName, cashMass, cashMassCount);
	bool result = newCash->AddCash(nominal, value);
	if (result) {
		AllCash[cashName] = newCash;
	}
	return result;
}

bool GetCurrencies(string cashName) {
	int summ;
	map <int, int> getCash;
	bool res = false;
	cin >> summ;
	for (auto isName : AllCash) {
		if (cashName == isName.second->GetCashName()) {
			getCash = isName.second->GetCash(summ);
		}
	}
	for (auto it = getCash.rbegin(); it != getCash.rend(); it++) {
		cout << it->first << " " << it->second << endl;
		res = true;
	}
	return res;
}

bool ShowBallance() {
	bool res = false;
	for (auto getCash : AllCash) {
		getCash.second->ShowCash();
		res = true;
	}
	return res;
}

int main() {
	char move;
	string CashName;
	cout << "Hi I'm your ||||TEST BANK||||" << endl;
	while (true) {
		cin >> move;
		switch (move) {
		case '+':
			cin >> CashName;
			if (AddCurrencies(CashName, cashMass, cashMassCount))
				cout << "OK" << endl;
			else
				cout << "ERROR" << endl;
			break;
		case '-':
			cin >> CashName;
			if (GetCurrencies(CashName))
				cout << "OK" << endl;
			else
				cout << "ERROR" << endl;
			break;
		case '?':
			if (ShowBallance())
				cout << "OK" << endl;
			else
				cout << "ERROR" << endl;
			break;
		default:
			cout << "ERROR" << endl;
			break;
		}
	}
	getchar();
	return 0;
}