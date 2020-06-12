#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<io.h>
#include<time.h>
#include<fstream>
#include<cstdlib>
#include<stack>
#include<queue>
#include<iomanip>
#include<memory>
#include<string.h>
#include<string>
#include<malloc.h>
#include<direct.h>
#include<filesystem>
#include<vector>
#include<array>
#include<deque>
using namespace std;

/*�������� ���� "�����"*/
string koz;
short beat = 2;

class Card {
public:
	string suit;
	string num;
	short power = 0;
	short compare = 0;
};

vector<Card> koloda;

class Player {
	vector<Card> fan;
	vector<Card> comp;
	vector<Card> fight;
	short const val = 6;
public:
	Player();
	void rest(short);
	void computermove(short);
	void computermove2(short);
	void playermove(short, short);
	void playermove2(short);
	void game();
	void game2();
	void is_choise(short);
	void attack(short, short);
	void attack2(short, short);
	void is_move(short&, short);
	void takeitback();
	void win(short);
	void beat_it();
	void takeback(short);
	void fan_func(); 
	void comp_func();
	void inspacer(string, string&);
	void outspacer(string&);
	

};

void Player::inspacer(string a, string& b) { //���������������
	short len1 = a.length();
	short len2 = b.length();
	short need = 20 - len1 - len2;
	b.append(need, ' ');
}

void Player::outspacer(string& b) { //��������������������
	short place = b.find(" ", 0);
	string temp = b.erase(place);
	b = temp;
}


void Player::is_move(short& a, short check) { // �������� ������ ���� ������� �� ����� ����� ����
	if (check == 0) {
		if (a < 1 || a > fan.size()) {
			cout << "\n\n\t\t\tIncorrect Choise! Choose again: ";
			cin >> a;
			is_move(a, check);
		}
	}
	else {
		if (a == 0) beat_it();
		else if (a < 0 || a > fan.size()) {
			cout << "\n\n\t\t\tIncorrect Choise! Choose again: ";
			cin >> a;
			is_move(a, check);
		}
		short ind = 0;
		for (short x = 0; x < check * 2; x++) {
			if (fan[a - 1].compare == fight[x].compare) {
				ind++;
				break;
			}
		}
		if (ind == 0) { cout << "\n\n\t\t\tCan't take this card on this replace! Choose again: "; cin >> a; is_move(a, check); }
	}
}

void Player::playermove(short x, short check) { //��������� ����� ������ ��� ��� ������ �� ���������
	if (koloda.size() == 0 && fan.size() == 0 && comp.size() > 1) win(1);
	if (check == 0) cout << "\nChoose a card to move: ";
	else cout << "Choose a card to move, or press 0 to BEAT IT! : ";
	short move;
	cin >> move;
	is_move(move, check); // ������� ������ ����
	move -= 1;
	short ab = x * 2;
	fight.resize(fight.size()+1);
	fight[ab] = fan[move];
	auto iter = fan.cbegin();
	cout<<"\nPlayer takes "<<fight.at(ab).num << " " << fight.at(ab).suit << "\n";
	fan.erase(iter + move);
	if (koloda.size() == 0 && fan.size() == 0) win(1); // ������� ������
}

void Player::win(short a) { // ������������ � ������
	if (a == 1) cout << "\n\n\n\t\t\t!!!!!!!!!!YOU WIN!!!!!!!!!\n\n\n";
	else cout << "\n\n\n\t\t\t!!!!!!!!!!COMPUTER WINS!!!!!!!!!\n\n\n";
	exit(0);
}

void Player::computermove2(short age) { // �������� �� ���������� ��� ������ �� �������
	if (koloda.size() == 0 && comp.size() == 0 && fan.size() > 1) win(0);
	short mini = 100, cur = -1, lakmus = 0;
	for (short x = 0; x < comp.size(); x++) {
		if (comp.at(x).power < mini) { // �������� ���������� �� ���� �����
			if (!age) {
				lakmus++;
				mini = comp.at(x).power;
				cur = x;
			}
			else{
				for (short y = 0; y < fight.size(); y++) {
					if (comp.at(x).num == fight.at(y).num) { // �������� ���������� ������� ��� ������������ ����� ����
						lakmus++;
						mini = comp.at(x).power;
						cur = x;
					}
				}
			}
		}
	}
	if (lakmus == 0) { cout << "\nCOMPUTER SAYS BEAT ON!\n";  beat_it(); } // ���������� ����� �����
	short ab = age * 2;
	fight.resize(fight.size() + 1);
	fight[ab] = comp[cur];
	auto iter = comp.cbegin();
	comp.erase(iter + cur);
	if (koloda.size() == 0 && comp.size() == 0) win(0); // ������� ������
}

void Player::takeitback() { // ��������� �� ������� � ������� �����
	cout << "\n\n!!!!!!!COMPUTER TAKES IT BACK!!!!!!!";
	if (fan.size() == 0) win(1); // ������� ������
	cout << " com = " << comp.size();
	for (short x = 0; x < fight.size(); x++) {
		comp.push_back(fight.at(x));
	}
	cout << " com = " << comp.size();
	if (fan.size() < val) { // ����� �������� ����������� �����
		while (fan.size() < val && koloda.size()) {
			short ran = rand() % koloda.size();
			fan.resize(fan.size() + 1);
			fan[fan.size() - 1] = koloda[ran];
			auto iter = koloda.cbegin();
			koloda.erase(iter + ran);
		}
	}
	fight.clear(); // ������� �������� �����
	rest(0); // ����� �� ����� ����� ���� � ������
}

void Player::fan_func() { // ����� ���� ��� ������
	while (fan.size() < val && koloda.size()) {
		short ran = rand() % koloda.size();
		fan.resize(fan.size() + 1);
		fan[fan.size() - 1] = koloda[ran];
		auto iter = koloda.cbegin();
		koloda.erase(iter + ran);
	}
}

void Player::comp_func() { // ����� ���� ��� ����������
	while (comp.size() < val && koloda.size()) {
		short ran = rand() % koloda.size();
		comp.resize(comp.size() + 1);
		comp[comp.size() - 1] = koloda[ran];
		auto iter = koloda.cbegin();
		koloda.erase(iter + ran);
	}
}

void Player::beat_it() { // ������� ����!! ��� ��������� � ���������
	cout << "\n\n!!!!!!!BEAT IT!!!!!!!\n";
	fight.clear();
	for (short x = 0; x < 2; x++) {
		if (beat % 2 == 0) { fan_func(); comp_func(); }
		else { comp_func(); fan_func(); }
	}
	if (beat % 2 == 1) { beat++; rest(0); }
	if (beat % 2 == 0) { beat++; rest(2); }
}


void Player::computermove(short y) { // ���� ��������� ���������� ����� ����� ������
	if (comp.size() == 0 && koloda.size() == 0) win(0);
	short mini = 100, card = 0, cur = -1;
	for (short x = 0; x < comp.size(); x++) { // �� ���������� ����� �� ���������:
		if (comp[x].power > fight[y * 2].power) { // ���� ���� ����� ������
			if (comp[x].power < mini) {           // ���� ����� ���������� �� ���, ������� ����� ��������� ����� ������
				if (fight[y * 2].suit == comp[x].suit || comp[x].suit == koz) {  // ���� � ����� ��������� ����� ��� ��� ��������
					card++;
					mini = comp[x].power;
					cur = x;
				}
			}
		}
	}
	if (cur < 0) { takeitback(); // ���� �� ����������� �� ���� �������, ��������� ����� ����� � ���� ���� 
	}
	else { // � �������� ������ �� ������� ����� ���������� ����� �����
		fight.resize(fight.size() + 1);
		fight[y * 2 + 1] = comp[cur];
		auto ptr = comp.cbegin();
		cout << "<== Computer attack's with " << comp[cur].num << " " << comp[cur].suit << "\n";
		comp.erase(ptr + cur);
	}
}

void Player::is_choise(short a) { // ������ ��� ������ ���� �������, �� ����� ���� ����������
	if (a < 0 || a > fan.size()) {
		cout << "\n\n\t\t\tIncorrect choise. Write again: ";
		cin >> a;
		is_choise(a); // �������� ���� ���� ���� ��������� ����� �� ������������� ���� ���������
	}
	if (a == 0) takeback(a); //player takes off
	if(fan.at(a - 1).power < fight.at(fight.size() - 1).power ||
		fan.at(a - 1).suit != fight.at(fight.size() - 1).suit && fan.at(a - 1).suit != koz){
		cout << "\n\n\t\t\tCan't take this card. Choose again: ";
		cin >> a;
		is_choise(a); // �������� ���� ���� ���� ��������� ����� �� ������������� ���� ���������
	}
}

void Player::takeback(short a) { // ���������, ����������� ��������, ��� ����� ����� �����, �� ����� ��������
	cout << "\n\n!!!!!!!YOU TOOK IT BACK!!!!!!!"; //
	if (comp.size() == 0) win(0);
	for (short x = 0; x < fight.size(); x++) {
		fan.push_back(fight.at(x));
	}
	fight.clear();

	while (comp.size() < val && koloda.size()) { // ��������� �������� ����������� �����
		short ran = rand() % koloda.size();
		comp.resize(comp.size() + 1);
		comp[comp.size() - 1] = koloda[ran];
		auto iter = koloda.cbegin();
		koloda.erase(iter + ran);
	}

	rest(2);
}

void Player::playermove2(short age) { //���������, ��� ����� ���������� �� ���� ����������
	if (fan.size() == 0 && koloda.size() == 0) win(1);
	short choise;
	cout << "\nChoose a card to beat " << fight.at(fight.size() - 1).num << " " << fight.at(fight.size() - 1).suit << ". Press from 1 to " << fan.size() << "\n";
	cout << "if you want to TAKE IT BACK press 0! : ";
	cin >> choise;
	is_choise(choise);
	choise -= 1;
	fight.resize(fight.size() + 1); 
	fight.at(age * 2 + 1) = fan.at(choise); 
	auto iter = fan.cbegin();
	fan.erase(iter + choise);
}


void Player::attack2(short z, short end) { // ������������ ���� ����������� ���� - ������� (����� ���������, ���������� �����)
	cout << "\nMoves in fight:\n";
	short x = 0;
	for (short x = 0; x < fight.size(); x++) {
		if (x == 0 || x % 2 == 0)
			cout << "Computer move: " << fight.at(x).num << " " << fight.at(x).suit << " ==>\n";
		else
			cout << "\t\t\t<== Your move: " << fight.at(x).num << " " << fight.at(x).suit << " \n\n";
	}
}

void Player::attack(short z, short end) { // ������������ ���� ����������� ���� - ������� (����� �����, ���������� ���������)
	cout << "\nMoves in fight:\n";
	short x = 0;
	for (short x = 0; x < z*2+2; x++) {
		if (x == 0 || x % 2 == 0)
			cout << "\nYour move: " << fight.at(x).num << " " << fight.at(x).suit << " ==>\n";
		else
			cout << "\t\t\t<== Computer move: " << fight.at(x).num << " " << fight.at(x).suit << "\n";
	}
}


void Player::game() { //�������, ��� ����� �����. ��������� ����������
	short balance = 6;
	for (short x = 0, check = 0; x < balance; x++) {
		playermove(x, check);        // ����� � ����
		computermove(x);             //�� ����������
		rest(1);                            //����� �� �����
		attack(x, 0);                //������� �� ���� ���� �� ��������� �����
		check++;
	}
}

void Player::game2() { //�������, ��� ������ �������� ����� ����������. ����� ����������
	short balance = 6;
	for (short x = 0, check = 0; x < balance; x++) {
		computermove2(x);                       // �� ����������
		rest(1);                                // ����� �� �����
		attack2(x, 0);                   //������� �� ���� ���� �� ��������� �����
		playermove2(x);                         //����� ����������
		check++;
	}
}

void Player::rest(short off) { // ����� �� �����. �������� � ������� ����. ��� �������� ��������� ������������ �������� � ����� ����������
	cout << "TRUMP CARDS IS: " << koz << "\n";
	cout << "\n\t\t\t\t---------CARDS IN KOLODA = " << koloda.size() << "--------\n\n"; //�������� ���� � ������
	/*cout << "\n\t\t\t\t---------COMP CARDS = " << comp.size() << "--------\n\n"; // ����� ����������
	for (short x = 0; x <= comp.size(); x++) {
		if (x == 0) cout << "Number\tSuit\t\t\t\t\tPower\tIs Trump?\n\n";
		else {
			inspacer(comp[x - 1].num, comp[x - 1].suit); // ��������� �������, ����� �������� ����� ���������
			cout << x << "\t" << comp.at(x - 1).num << " " << comp.at(x - 1).suit << "\t\t\t" << comp.at(x - 1).power << "\t";
			if (comp.at(x - 1).power > 9) cout << "TRUMP\n"; // ���������� ���������� �����
			else cout << "vulgar\n";
			outspacer(comp[x - 1].suit); // ������� �������, ������ �� �����
		}
	}*/
	cout << "\n\t\t\t\t---------YOUR CARDS--------\n\n"; // ����� ������
	for (short x = 0; x <= fan.size(); x++) {
		if (x == 0) cout << "Number\tSuit\t\t\t\t\tPower\tIs Trump?\n\n";
		else {
			inspacer(fan[x - 1].num, fan[x - 1].suit); // ��������� �������, ����� �������� ����� ���������
			cout << x << "\t" << fan.at(x-1).num << " " << fan.at(x-1).suit << "\t\t\t" << fan.at(x-1).power << "\t";
			if (fan.at(x-1).power > 9) cout << "TRUMP\n"; // ���������� ���������� �����
			else cout << "vulgar\n";
			outspacer(fan[x - 1].suit); // ������� �������, ������ �� �����
		}
		
	}

	if(!off) game(); // ���� � �������, ��� ����� �����
	if (off == 2) game2(); //���� � �������, ��� ����� ���������
	
}

Player::Player() { //����������� ������. ������������� ������ ���� � ������ � ����������

	for (short x = 0; x < val; x++) {
		short ran = rand() % koloda.size();
		comp.resize(x + 1);
		comp[x] = koloda[ran];
		auto iter = koloda.cbegin();
		koloda.erase(iter + ran);
	}

	for (short x = 0; x < val; x++) {
		short ran = rand() % koloda.size();
		fan.resize(x + 1);
		fan[x] = koloda[ran];
		auto iter = koloda.cbegin();
		koloda.erase(iter + ran);
	}
	rest(0);
}

void gettaNum(Card& neo, short x) { // �������������� ������� ����
	if (x % 9 == 0) { neo.power += 1; neo.compare += 1; neo.num = "Six of"; }
	else if (x % 9 == 1) { neo.power += 2; neo.compare += 2; neo.num = "Seven of"; }
	else if (x % 9 == 2) { neo.power += 3; neo.compare += 3; neo.num = "Eight of"; }
	else if (x % 9 == 3) { neo.power += 4; neo.compare += 4; neo.num = "Nine of"; }
	else if (x % 9 == 4) { neo.power += 5; neo.compare += 5; neo.num = "Ten of"; }
	else if (x % 9 == 5) { neo.power += 6; neo.compare += 6; neo.num = "Jack of"; }
	else if (x % 9 == 6) { neo.power += 7; neo.compare += 7; neo.num = "Queen of"; }
	else if (x % 9 == 7) { neo.power += 8; neo.compare += 8; neo.num = "King of"; }
	else { neo.power += 9; neo.compare += 9; neo.num = "Ace of"; }
}




void gettaSuit(Card& neo, short x) { // �������������� ������
	if (x < 9) neo.suit = "Hearts";                                  // �����
	else if (x > 8 && x < 18) neo.suit = "Spades";                   // ����
	else if (x > 17 && x < 27) neo.suit = "Diamonds";                // �����
	else neo.suit = "Clubs";                                         // �����

}

void gettaKoz(Card& neo, short x) {// ������� ��������� ��������� ���� �������� �����
	if (neo.suit == koz)
		neo.power += 9;
}


void make_koloda() { // ������ ������� ������ ���� �� ���� ������� �������, ������������ � ���������� ����
	short ran = rand() % 4;
	if (ran == 0) koz = "Spades";
	if (ran == 1) koz = "Clubs";
	if (ran == 2) koz = "Diamonds";
	if(ran == 3) koz = "Hearts";


	for (short x = 0; x < 36; x++) {
		Card neo;
		gettaSuit(neo, x);
		gettaKoz(neo, x);
		gettaNum(neo, x);
		koloda.push_back(neo);
	}
	
}

int main() {
	srand(time(NULL));
	cout << "\t\t\t\tI V A N - D U R A K / J O H N   F O O L\n\n\n";
	make_koloda();
	Player player;
}

