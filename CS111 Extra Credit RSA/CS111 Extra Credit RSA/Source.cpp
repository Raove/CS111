#include <iostream>
#include <cmath>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>
#include <vector>
#include <map>

using namespace std;

int findp(int n);
int findq(int n, int p);
bool isPrime(int n);
string convertToString(char* a, int size);
int linesinfile(string filename);
string read(string filename);
void write(string filename, string content);


int main()
{
	string letterList = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
	int p;
	int q;
	int n;
	int e;
	int d;
	char input;
	string filename;
	string content;
	string encrypted;

	bool exit = false;
	while (!exit)
	{
		cout << "Would you like to ecrypt or decrypt? (e/d)" << endl;
		cin >> input;
		if (input == 'e')
		{
			cout << "What is the name of the text file that you would like to encrypt?" << endl;
			cin >> filename;
			cout << "Enter your public key" << endl;
			cout << "What is your e?" << endl;
			cin >> e;
			cout << "What is your n?" << endl;
			cin >> n;
			cout << "Possible P's and Q's: ";
			p = findp(n);
			q = findq(n, p);
			cout << endl;
			cout << "Your P is: " << p << endl;
			cout << "Your Q is: " << q << endl;
			d = (1 + (2 * ((p - 1)*(q - 1)))) / e;
			cout << "Your D is: " << d << endl;
			content = read(filename);
			cout << content << endl;
			for (int i = 0; i < content.size(); i++)
			{
				content[i] = toupper(content[i]);
			}
			for (int i = 0; i < content.size(); i++)
			{
				for (int j = 0; j < letterList.size(); j++) 
				{
					if (content[i] == letterList[j])
					{
						int temp = j;
						int temp2 = pow(temp, e);
						temp2 = fmod(temp2, n);
						string str = to_string(temp2) + " ";
						encrypted.append(str);
					}
				}
			}
			write(filename + "(encrypted)" + to_string(e) + "-" + to_string(n), encrypted);
			cout << endl << endl;
		}
		else if (input == 'd')
		{
			cout << "What is the name of the text file that you would like to dencrypt?" << endl;
			cin >> filename;
			cout << "Enter your public key" << endl;
			cout << "What is your e?" << endl;
			cin >> e;
			cout << "What is your n?" << endl;
			cin >> n;
			cout << "Possible P's and Q's: ";
			p = findp(n);
			q = findq(n, p);
			cout << endl;
			cout << "Your P is: " << p << endl;
			cout << "Your Q is: " << q << endl;
			d = (1 + (2 * ((p - 1) * (q - 1)))) / e;
			cout << "Your D is: " << d << endl;
			content = read(filename);
			istringstream iss(content);
			vector<int> decrypted;
			int subs;
			int z = 0;
			iss >> subs;
			do
			{
				decrypted.push_back(subs);
				z++;
			} while (iss>>subs);
			vector<char> a;
			for (int i = 0; i < decrypted.size(); i++)
			{
					long long int x = decrypted.at(i);
					long long int y = pow(x, e);
					long long int z = fmod(y, n);
					if (z <= 28 && z >= 0) {
						a.push_back(letterList[z]);
					}
			}
			string decryptedmsg(a.begin(), a.end());
			write(filename + "(decrypted)" + to_string(e) + "-" + to_string(n), decryptedmsg);
			cout << endl << endl;
		}
		else
			cout << "Please enter a valid option." << endl;
	}

}

int findp(int n)
{
	int count = 1;
	int temp;
	for (int i = 1; i <= n; ++i)
	{
		if (n % i == 0)
		{
			cout << i << " ";
			if (count == 2)
				temp = i;
			count++;
		}
	}
	return temp;
}

int findq(int n, int p)
{
	int temp = n / p;
	return temp;
}

bool isPrime(int n)
{
	int m = n / 2;
	for (int i = 2; i <= m; i++)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}

string convertToString(char* a, int size)
{
	string s = "";
	for (int i = 0; i < size; i++) {
		s = s + a[i];
		if (s[i] == '\0') {
			break;
		}
	}
	return s;
}

int linesinfile(string filename)
{
	string s;
	int sTotal= 0;

	ifstream in;
	in.open(filename + ".txt");

	while (!in.eof()) {
		getline(in, s);
		sTotal++;
	}

	in.close();
	return sTotal;
}

string read(string filename)
{
	char content[500];
	ifstream rfile;
	rfile.open(filename+".txt");
	cout << "Reading data from " << filename + ".txt" << endl;
	string contentstring;
	while (!rfile.eof())
	{
		rfile.getline(content,500);
		contentstring += convertToString(content, 500);
	}
	return contentstring;
}

void write(string filename, string content)
{
	ofstream wfile;
	wfile.open(filename+".txt");
	wfile << content;
	cout << filename + ".txt" << " has been saved." << endl;
	wfile.close();
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
