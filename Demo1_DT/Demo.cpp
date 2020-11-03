#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <ctime>
#include <conio.h>
using namespace std;
class Admin {
	string sUser;
	string sPass;
public:
	string getUser() { return sUser; }
	void setUser(string value) { sUser = value; }
	string getPass() { return sPass; }
	void setPass(string value) { sPass = value; }
	Admin() {
		sUser = "Admin";
		sPass = "";
	}
	Admin(string _u, string _p) {
		sUser = _u;
		sPass = _p;
	}
	~Admin() {}
	friend istream& operator >> (istream& is, Admin& ad) {
		is >> ad.sUser;
		is >> ad.sPass;
		return is;
	}
	friend ostream& operator << (ostream& os, Admin ad) {
		os << ad.sUser << endl;
		os << ad.sPass << endl;
		return os;
	}
};
class User {
	string sID;
	string sPin;
	string sName;
	long long lSoDuTK;
	string sLoaiTienTe;
	string sLock;
public:
	string getID() { return sID; }
	void setID(string value) { sID = value; }
	string getPin() { return sPin; }
	void setPin(string value) { sPin = value; }
	string getName() { return sName; }
	void setName(string value) { sName = value; }
	string getLoaiTien() { return sLoaiTienTe; }
	void setLoaiTien(string value) { sLoaiTienTe = value; }
	long long getSoDuTK() { return lSoDuTK; }
	void setSoDuTK(long long value) { lSoDuTK = value; }
	string getLock() { return sLock; }
	void setLock(string value) { sLock = value; };
	User() {
		sID = "00000000000000";
		sPin = "123456";
		sName = "";
		lSoDuTK = 50000;
		sLoaiTienTe = "VND";
		sLock = "Dang hoat dong";
	}
	User(string _id, string _name, long long _sodu, string _loaiTien) {
		sID = _id;
		sName = _name;
		sPin = "123456";
		lSoDuTK = _sodu;
		sLoaiTienTe = _loaiTien;
		sLock = "Dang hoat dong";
	}
	~User() {}
	friend istream& operator >> (istream& is, User& us) {
		is >> us.sID;
		is.ignore();
		getline(is, us.sName);
		is >> us.lSoDuTK;
		is >> us.sLoaiTienTe;
		is.ignore();
		getline(is, us.sLock);
		return is;
	}
	friend ostream& operator << (ostream& os, User us) {
		os << us.sID << endl;
		os << us.sName << endl;
		os << us.lSoDuTK << endl;
		os << us.sLoaiTienTe << endl;
		os << us.sLock << endl;
		return os;
	}
	void createAndUpdateFileID();
	void createAndUpdateFileHistory(string note, long long mon, string _id = "") {
		string fileHistory = "LichsuID/Lichsu" + sID + ".txt";
		ofstream file(fileHistory, ios::app);
		time_t now = time(0);
		const char* dt = ctime(&now);
		file << "TOPbank: " << dt;
		file << "So tai khoan: " << sID << endl;
		file << "So tien GD: " << mon << endl;
		file << "So du cuoi: " << lSoDuTK << endl;
		file << "Noi dung: ";
		if (note == "Chuyen tien") { file << "Chuyen tien cho [" << _id << "]"; }
		else if (note == "Nhan tien") { file << "Nhan tien tu [" << _id << "]"; }
		else { file << note; }
		file << endl;
		file << "*************************\n";
		file.close();
	}
	void getInformationAccount();
	void withDrawal();
	void transfers();
	void getHistoryAccount();
	void changePin();
};

//Tinh nang Admin
void menuOptionAdmin();
void getListAccountUser();
void addAccountUser();
void removeAccountUser();
void unlockAccountUser();

//Tinh nang User
void menuOptionUser(User us);

//Ham bo tro
void mauNenVaChu(int text, int background);
bool checkFileID(string id);
int checkLock(string id);
User loadFile(string id);
bool CheckLogin(string tk, string mk, string filename);
void inputPass(string& pas);
void lockAccountUser(string id);
string toupperArr(char arr[]);
void stringToChar(string str, char c_arr[]);



int main() {
	while (true) {
		mauNenVaChu(14, 0);
		system("cls");
		cout << "\n\n\n";
		cout << setw(80) << "*********************************\n";
		cout << setw(80) << "*          * 1. Admin           *\n";
		cout << setw(80) << "*          * 2. User            *\n";
		cout << setw(80) << "*********************************\n";
		int counterObject;
		cout << setw(65) << "       Doi tuong:  "; cin >> counterObject;
		if (counterObject == 1) {
			while (true) {
				system("cls");
				cout << "\n\n\n";
				cout << setw(80) << "*********************************\n";
				cout << setw(80) << "*                               *\n";
				cout << setw(80) << "*        DANG NHAP ADMIN        *\n";
				cout << setw(80) << "*                               *\n";
				cout << setw(80) << "*********************************\n";
				string user, pass = "", filename = "Admin.txt";
				char ch;
				cout << setw(64) << "User:    "; cin >> user;
				cout << setw(64) << "Pass:    ";
				inputPass(pass);
				if (CheckLogin(user, pass, filename) == true) {
					mauNenVaChu(10, 0);
					menuOptionAdmin();
					break;
				}
				else {
					cout << "\n\n";
					cout << setw(79) << "SAI TAI KHOAN HOAC MAT KHAU !!!";
					system("pause>nul");
				}
			}
			break;
		}
		else if (counterObject == 2) {
			string check;
			int dem = 0;
			while (true) {
				system("cls");
				cout << "\n\n\n";
				cout << setw(80) << "*********************************\n";
				cout << setw(80) << "*                               *\n";
				cout << setw(80) << "*        DANG NHAP USER         *\n";
				cout << setw(80) << "*                               *\n";
				cout << setw(80) << "*********************************\n";
				string id, pin = "", filename = "TheTu.txt";
				char ch;
				cout << setw(59) << "ID:     "; cin >> id;
				cout << setw(59) << "Pin:    ";
				inputPass(pin);
				if (CheckLogin(id, pin, filename) == true) {
					User us = loadFile(id);
					if (us.getLock() == "Da khoa")
						cout << "\n\n" << setw(73) << "TAI KHOAN DA BI KHOA!";
					else {
						mauNenVaChu(15, 0);
						menuOptionUser(us);
					}
					break;
				}
				else {
					cout << "\n\n";
					cout << setw(79) << "SAI TAI KHOAN HOAC MAT KHAU !!!";
					if (checkFileID(id)) {
						if (check != id) { dem = 0; check = id; dem++; }
						else {
							dem++;
							if (dem == 3) {
								cout << "\n" << setw(85) << "TAI KHOAN DA BI KHOA DO NHAP SAI NHIEU LAN!!!" << endl;
								lockAccountUser(check);
								break;
							}
						} 
					}
					system("pause>nul");
				}
			} break;
		}
		else continue;
	}
	system("pause>nul");
	return 0;
}

//Tinh nang cua Admin
void menuOptionAdmin() {
	while (true) {
		system("cls");
		cout << setw(80) << "*************MENU****************\n";
		cout << setw(83) << "1. Xem danh sach tai khoan       \n";
		cout << setw(83) << "2. Them tai khoan                \n";
		cout << setw(83) << "3. Xoa tai khoan                 \n";
		cout << setw(83) << "4. Mo khoa tai khoan             \n";
		cout << setw(83) << "5. Thoat                         \n";
		cout << setw(80) << "*********************************\n";
		int iOption;
		cout << setw(69) << "Chon chuc nang: "; cin >> iOption;
		system("cls");
		if (iOption == 1) { getListAccountUser(); }
		else if (iOption == 2) { addAccountUser(); }
		else if (iOption == 3) { removeAccountUser(); }
		else if (iOption == 4) { unlockAccountUser(); }
		else if (iOption == 5) { cout << "\n\n\n" << setw(78) << "CAM ON DA SU DUNG DICH VU ^_^"; break; }
		else { cout << setw(73) << "Vui long chon lai!!!"; }
		system("pause>nul");
	}
}
void getListAccountUser() {
	cout << "\n\n\n";
	cout << setw(80) << "*********************************\n"
		 << setw(80) << "*      DANH SACH TAI KHOAN      *\n"
		 << setw(80) << "*********************************\n";
	ifstream fileAccountUser("TheTu.txt", ios::in);
	cout << setw(53) << "ID" << setw(14) << "Pin" << setw(14) << "Trang thai" << endl;
	while (!fileAccountUser.eof()) {
		string acc = "";
		string pas = "";
		fileAccountUser >> acc;
		fileAccountUser >> pas;
		if (acc != "") {
			if (checkLock(acc) == 0) { cout << setw(58) << acc << setw(9) << pas << setw(10) << "Da khoa" << endl; }
			else if (checkLock(acc) == 1) { cout << setw(58) << acc << setw(9) << pas << setw(15) << "Dang hoat dong" << endl; }
		}
	}
	fileAccountUser.close();
}
void addAccountUser() {
	cout << "\n\n\n";
	cout << setw(80) << "*********************************\n";
	cout << setw(80) << "*         THEM TAI KHOAN        *\n";
	cout << setw(80) << "*********************************\n";
	ifstream readFileAccountUser("TheTu.txt", ios::in);
	vector<string> listAccountUser;
	while (!readFileAccountUser.eof()) {
		string acc;
		readFileAccountUser >> acc;
		listAccountUser.push_back(acc);
	}
	readFileAccountUser.close();
	//tao account moi
	long long numID = stoll(listAccountUser[listAccountUser.size() - 3]) + 1;
	string newID = to_string(numID);
	string newName; cout << setw(63) << "Nhap ten tai khoan: ";
	cin.ignore();
	getline(cin, newName);
	long long newSodu; cout << setw(63) << "So tien cap nap:    "; cin >> newSodu;
	while (true) {
		if (newSodu >= 50000) { break; }
		else { 
			cout << setw(69) << "So du toi thieu 50.000 VND" << endl; 
			cout << setw(63) << "So tien can nap:    "; cin >> newSodu;
		}
	}
	string newLoaitien; cout << setw(63) << "Loai tien:          "; cin >> newLoaitien;
	char arr_newName[100], arr_newLoaiTien[100];
	stringToChar(newName, arr_newName);
	stringToChar(newLoaitien, arr_newLoaiTien);
	User newAccount = User(newID, toupperArr(arr_newName), newSodu, toupperArr(arr_newLoaiTien));
	//them thong tin vao file TheTu.txt
	ofstream writeFileAccountUser("TheTu.txt", ios::app);
	writeFileAccountUser << newAccount.getID() << endl << newAccount.getPin() << endl;
	writeFileAccountUser.close();
	//tạo file [ID].txt và file Lichsu[ID].txt tương ứng
	newAccount.createAndUpdateFileID();
	newAccount.createAndUpdateFileHistory("Nap tien", newSodu);
	if (checkFileID(newID)) {
		system("cls");
		cout << "\n\n\n\n";
		cout << setw(75) << "TAO TAI KHOAN THANH CONG";
	}
	else {
		system("cls");
		cout << "\n\n\n\n";
		cout << setw(78) << "TAO TAI KHOAN KHONG THANH CONG";
	}
}
void removeAccountUser() {
	cout << "\n\n\n";
	cout << setw(80) << "*********************************\n";
	cout << setw(80) << "*          XOA TAI KHOAN        *\n";
	cout << setw(80) << "*********************************\n";
	string sFileName;
	cout << setw(65) << "ID tai khoan can xoa: "; cin >> sFileName;
	Sleep(100);
	if (checkFileID(sFileName)) {
		User us = loadFile(sFileName);
		cout << endl;
		cout << setw(61) << "Ten tai khoan: " << us.getName() << endl;
		cout << setw(53) << "So du: " << us.getSoDuTK() << " " << us.getLoaiTien() << endl;
		cout << endl;
		char key;
		cout << setw(90) << "Nhan phim Y de XAC NHAN hoac phim bat ki de HUY: ";	cin >> key;
		if (key == 'Y') {
			char c_arFileName[50], c_arFileHistory[50];
			stringToChar("ID/" + sFileName + ".txt", c_arFileName);
			stringToChar("LichsuID/Lichsu" + sFileName + ".txt", c_arFileHistory);
			if (remove(c_arFileName) == 0 && remove(c_arFileHistory) == 0) {
				cout << setw(60) << "THANH CONG";
				//remove information user in file TheTu
				ifstream readFileAccountUser("TheTu.txt", ios::in);
				vector<string> listAccountUser;
				while (!readFileAccountUser.eof()) {
					string sIfUser;
					readFileAccountUser >> sIfUser;
					listAccountUser.push_back(sIfUser);
				}
				ofstream writeFileAccountUser("TheTu.txt", ios::out);
				for (int i = 0; i < listAccountUser.size() - 1; i += 2) {
					if (listAccountUser[i] != sFileName) {
						writeFileAccountUser << listAccountUser[i] << endl;
						writeFileAccountUser << listAccountUser[i + 1] << endl;
					}
				}
			}
			else cout << setw(73) << "XOA KHONG THANH CONG";
		}
		else { cout << setw(67) << "HUY XOA"; }
	}
	else { cout << setw(75) << "TAI KHOAN KHONG TON TAI"; }
}
void unlockAccountUser() {
	cout << "\n\n\n";
	cout << setw(80) << "*********************************\n"
		 << setw(80) << "*        MO KHOA TAI KHOAN      *\n"
		 << setw(80) << "*********************************\n"; 
	string id;
	cout << setw(66) << "ID user can mo khoa: "; cin >> id;
	if (checkFileID(id)) {
		User us = loadFile(id);
		us.setLock("Dang hoat dong");
		us.createAndUpdateFileID();
		cout << "\n\n" << setw(69) << "MO KHOA THANH CONG";
	}
	else cout << "\n\n" << setw(75) << "KHONG TIM THAY TAI KHOAN";
}

//Tinh nang cua User
void menuOptionUser(User us) {
	while (true) {
		system("cls");
		cout << "\n\n\n";
		cout << setw(80) << "**************MENU***************\n";
		cout << setw(83) << "1. Xem thong tin tai khoan       \n";
		cout << setw(83) << "2. Rut tien                      \n";
		cout << setw(83) << "3. Chuyen tien                   \n";
		cout << setw(83) << "4. Xem noi dung giao dich        \n";
		cout << setw(83) << "5. Doi mat khau                  \n";
		cout << setw(83) << "6. Thoat                         \n";
		cout << setw(80) << "*********************************\n";
		int iOption;
		cout << setw(69) << "Chon chuc nang: ";
		cin >> iOption;
		system("cls");
		if (iOption == 1) { us.getInformationAccount(); }
		else if (iOption == 2) { us.withDrawal(); }
		else if (iOption == 3) { us.transfers(); }
		else if (iOption == 4) { us.getHistoryAccount(); }
		else if (iOption == 5) { us.changePin(); }
		else if (iOption == 6) { cout << "\n\n\n" << setw(78) << "CAM ON DA SU DUNG DICH VU ^_^"; break; }
		else { cout << setw(73) << "Vui long chon lai!!!" << endl; }
		system("pause>nul");
	}
}
void User::createAndUpdateFileID() {
	string fileIDNew = "ID/" + sID + ".txt";
	User acc = *this;
	ofstream createfileUser(fileIDNew, ios::out);
	createfileUser << acc;
	createfileUser.close();
}
void User::getInformationAccount() {
	cout << "\n\n\n";
	cout << setw(80) << "*********************************\n"
		 << setw(80) << "*      THONG TIN TAI KHOAN      *\n"
		 << setw(80) << "*********************************\n";
	cout << "\n\n";
	cout << setw(62) << "ID:              " << sID << endl;
	cout << setw(62) << "Ten tai khoan:   " << sName << endl;
	cout << setw(62) << "So du tai khoan: " << lSoDuTK << endl;
	cout << setw(62) << "Loai tien:       " << sLoaiTienTe << endl;
	cout << setw(62) << "Tinh trang:      " << sLock;
}
void User::withDrawal() {
	cout << "\n\n\n";
	cout << setw(80) << "*********************************\n"
		 << setw(80) << "*            RUT TIEN           *\n"
		 << setw(80) << "*********************************\n";
	cout << setw(80) << "* 1. 50000            * 2. 100000\n"
		 << setw(80) << "* 3. 200000           * 4. 500000\n"
		 << setw(80) << "* 5. Khac             * 6. Thoat \n";
	int i;
	cout << setw(71) << "Chon menh gia: "; cin >> i;
	if (i == 1) {
		if (lSoDuTK < 100000) { cout << setw(72) << "So du khong du!!!"; }
		else {
			lSoDuTK = lSoDuTK - 50000;
			createAndUpdateFileID();
			createAndUpdateFileHistory("Rut tien", 50000);
			cout << setw(68) << "THANH CONG";
		}
	}
	else if (i == 2) {
		if (lSoDuTK < 150000) { cout << setw(72) << "So du khong du!!!"; }
		else {
			lSoDuTK = lSoDuTK - 100000;
			createAndUpdateFileID();
			createAndUpdateFileHistory("Rut tien", 100000);
			cout << setw(68) << "THANH CONG";
		}
	}
	else if (i == 3) {
		if (lSoDuTK < 2500000) { cout << setw(72) << "So du khong du!!!"; }
		else {
			lSoDuTK = lSoDuTK - 200000;
			createAndUpdateFileID();
			createAndUpdateFileHistory("Rut tien", 200000);
			cout << setw(68) << "THANH CONG";
		}
	}
	else if (i == 4) {
		if (lSoDuTK <= 550000) { cout << setw(72) << "So du khong du!!!"; }
		else {
			lSoDuTK = lSoDuTK - 500000;
			createAndUpdateFileID();
			createAndUpdateFileHistory("Rut tien", 500000);
			cout << setw(68) << "THANH CONG";
		}
    }
	else if (i == 5) {
		long long money;
		cout << setw(68) << "Nhap so tien can rut: "; cin >> money;
		if (money > 3000000) { cout << setw(75) << "So tien khong hop le !!!"; }
		else {
			if (lSoDuTK - money < 50000) { cout << setw(72) << "So du khong du!!!"; }
			else {
				if (money % 50000 == 0) {
					lSoDuTK = lSoDuTK - money;
					createAndUpdateFileID();
					createAndUpdateFileHistory("Rut tien", money);
					cout << setw(68) << "THANH CONG";
				}
				else { cout << setw(75) << "So tien khong hop le!!!"; }
			}
		}
	}
	else if (i == 6) {
		return;
	}
}
void User::transfers() {
	cout << "\n\n\n";
	cout << setw(80) << "*********************************\n"
		 << setw(80) << "*          CHUYEN TIEN          *\n"
		 << setw(80) << "*********************************\n";
	string id;
	cout << setw(65) << "ID user nhan tien: ";	cin >> id;
	if (checkFileID(id)) {
		// check tien
		User userReceive = loadFile(id);
		cout << "ID nguoi nhan: " << userReceive.getID() << endl;
		cout << "Ten nguoi nhan: " << userReceive.getName() << endl;
		long money;
		do {
			cout << setw(71) << "Nhap so tien can chuyen: ";	cin >> money;
			if (money < 50000)	cout << setw(74) << "So tien khong hop le!\n";
		} while (money < 50000 || lSoDuTK - money < 50000);
		char key;
		cout << "Nhan phim " << "Y" << " de xac nhan hoan phim " << "N" << " de huy: ";	cin >> key;
		if (toupper(key) == 'Y') {
			userReceive.setSoDuTK(userReceive.getSoDuTK() + money);
			userReceive.createAndUpdateFileID();
			userReceive.createAndUpdateFileHistory("Nhan tien", money, sID);
			lSoDuTK = lSoDuTK - money;
			createAndUpdateFileID();
			createAndUpdateFileHistory("Chuyen tien", money, userReceive.getID());
			cout << "Da chuyen thanh cong!!\n";
		}
		else return;
	}
	else { cout << setw(75) << "TAI KHOAN KHONG TON TAI"; }
}
void User::getHistoryAccount() {
	cout << "\n\n\n";
	cout << setw(80) << "*********************************\n"
		 << setw(80) << "*        LICH SU TAI KHOAN      *\n"
		 << setw(80) << "*********************************\n";
	ifstream file("LichsuID/Lichsu" + sID + ".txt", ios::in);
	cout << "\n";
	while (!file.eof()) {
		string str;
		getline(file, str);
		cout << setw(46) << "." << str << endl;
	}
	file.close(); //10000000000005
}
void User::changePin() {
	cout << "\n\n\n";
	cout << setw(80) << "*********************************\n"
		 << setw(80) << "*          DOI MAT KHAU         *\n"
		 << setw(80) << "*********************************\n";
	string oldpin = "", pin = "", newpin = "";
	cout << "\n\n\n";
	cout << setw(62) << "Nhap ma pin cu: ";	inputPass(oldpin);
	if (CheckLogin(getID(),oldpin,"TheTu.txt")) {
		cout << endl;
		cout << setw(63) << "Nhap ma pin moi: ";	inputPass(pin);
		cout << endl;
		cout << setw(67) << "Nhap lai ma pin moi: ";	inputPass(newpin);
		if (pin == newpin) {
			//update file TheTu
			vector<Admin> ad;
			ifstream readFileTheTu("TheTu.txt", ios::in);
			while (!readFileTheTu.eof()) {
				Admin tmp;
				readFileTheTu >> tmp;
				if (tmp.getUser() == sID) { tmp = Admin(sID, newpin); }
				ad.push_back(tmp);
			}
			readFileTheTu.close();
			ofstream writeFileTheTu("TheTu.txt", ios::out);
			for (int i = 0; i < ad.size() - 1; i++) {
				writeFileTheTu << ad[i];
			}
			writeFileTheTu.close();
			cout << endl << setw(68) << "THANH CONG";
		}
		else cout << endl << setw(73) << "MAT KHAU KHONG KHOP";
	}
	else cout << endl << setw(69) << "SAI MAT KHAU";
}

// Ham bo tro
void mauNenVaChu(int text, int background) {
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	int color = background * 16 + text;
	SetConsoleTextAttribute(hConsoleColor, color);
}
string toupperArr(char arr[]) {
	string str;
	int i = 0;
	while (arr[i]) {
		str += toupper(arr[i]);
		i++;
	}
	return str;
}
void stringToChar(string str, char c_arr[]) {
	str.copy(c_arr, str.size() + 1);
	c_arr[str.size()] = '\0';
}
bool checkFileID(string id) {
	string fileName = "ID/" + id + ".txt";
	ifstream file(fileName, ios::in);
	if (file.is_open())	return true;
	return false;
}
int checkLock(string id) {
	User us = loadFile(id);
	if (us.getLock() == "Da khoa") { return 0; }
	else if (us.getLock() == "Dang hoat dong") { return 1; }
	return -1;
}
User loadFile(string id) {
	string fileName = "ID/" + id + ".txt";
	ifstream file(fileName, ios::in);
	User acc;
	file >> acc;
	file.close();
	return acc;
}
bool CheckLogin(string tk, string mk, string filename) {
	ifstream fileAccount(filename, ios::in);
	while (!fileAccount.eof()) {
		string acc, pas;
		fileAccount >> acc;
		fileAccount >> pas;
		if (acc == tk && mk == pas)
			return true;
	}
	fileAccount.close();
	return false;
}
void inputPass(string& pas) {
	char pass[32];
	int i = 0;
	char a;
	for (i = 0;;) {
		a = _getch();
		if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9')) {
			pass[i] = a;
			++i;
			cout << "*";
		}
		if (a == '\b' && i >= 1) {
			cout << "\b \b";
			--i;
		}
		if (a == '\r') {
			pass[i] = '\0';
			break;
		}
	}
	for (int z = 0; z < i; z++) {
		pas.push_back(pass[z]);
	}
}
void lockAccountUser(string id) {
	User us = loadFile(id);
	us.setLock("Da khoa");
	us.createAndUpdateFileID();
}