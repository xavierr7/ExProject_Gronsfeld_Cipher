//  ��������������� ������ "���� �����������"
//  �������� ���� ������
//  06/23/2022
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
using std::string;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::cin;
using std::endl;

string alphabet;
/// <summary>
/// ������� ��� ���������� ������
/// </summary>
/// <param name="">����������� ������ �� ������(�����/��������� ������� ����� �����������)</param>
/// <param name="">����������� ������ �� ������-���� ��� ��������</param>
/// <returns>���������� ������������� �����</returns>
string encryption(const string&, const string&);

/// <summary>
/// ������� ��� ������������ ������
/// </summary>
/// <param name="">����������� ������ �� ������(�����/��������� ������� ����� ������������)</param>
/// <param name="">����������� ������ �� ������-���� ��� ����������</param>
/// <returns>���������� �������������� �����</returns>
string decryption(const string&, const string&);

/// <summary>
/// ������� ��� �������� ������������ �������� �� ����� ���������(�����������, �����, ��������, ���������)
/// </summary>
/// <returns>���������� ������ �������� � ���� �������</returns>
string MakeAlphabet();

/// <summary>
/// ������� ��� �������� �� �� ���������� �� ��� ���� ������������
/// </summary>
/// <param name="str">������ �� ������-����</param>
/// <returns>���������� ���� ���� ���� ������������ � ������ ���� ����������</returns>
bool CheckNum(string& str);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	MakeAlphabet();

	string filename1 = "sourceFile.txt";
	string filename2 = "encryption.txt";
	string filename3 = "decryption.txt";

	ifstream fileIn;
	ofstream fileOut;
	fileIn.open(filename1);

	if (fileIn.fail())
	{
		cout << "Error opening file!\a";
		return 404;
	}

	string textFromSourceFile;

	while (!fileIn.eof())
	{
		string line;
		getline(fileIn, line);
		if (line == "")
		{
			textFromSourceFile += "\n";
		}
		textFromSourceFile += line + "\n";
	}
	textFromSourceFile[textFromSourceFile.length() - 1] = '\0';

	cout << "�������� ����� ������ �� ����� ��� ���������: " << filename1 << endl;
	system("pause");
	system("cls");

	fileIn.close();

	fileOut.open(filename2);

	cout << "������� ����: ";
	string key;
	while (!CheckNum(key))
	{
		cout << "������! ���� �� ����� ���� ������ ��� ������������, ������� �����." << endl;
		system("pause");
		system("cls");
	}

	fileOut << encryption(textFromSourceFile, key);

	cout << "��� ����� ���������� � ������� � ���� ��� ���������: " << filename2 << endl;
	system("pause");
	system("cls");

	fileOut.close();

	fileIn.open(filename2);

	string encryptText;
	while (!fileIn.eof())
	{
		string line;
		getline(fileIn, line);
		if (line == "")
		{
			encryptText += "\n";
		}
		encryptText += line + "\n";
	}
	encryptText[encryptText.length() - 1] = '\0';
	fileIn.close();

	fileOut.open(filename3);

	fileOut << decryption(encryptText, key);

	cout << "������������� ����� ��� ������ � ������� � ���� ��� ���������: " << filename3 << endl;
	system("pause");
	system("cls");

	fileOut.close();

	return 0;
	system("pause");
}

string encryption(const string& str, const string& keyInString)
{
	int temp;
	string encryptText;
	string eachKeyNumberToInt;
	for (int i = 0, k = 0; i < str.length(); i++, k++)
	{
		if (str[i] == '\n')
		{
			encryptText += "\n";
			++i;
		}
		if (str[i] == '\t')
		{
			encryptText += "\t";
			++i;
		}

		if (k == (keyInString.length()))
		{
			k = 0;
		}

		eachKeyNumberToInt = keyInString[k];

		for (int j = 0; j < alphabet.length(); j++)
		{
			if (str[i] == alphabet[j])
			{
				temp = (static_cast<unsigned long long>(j) + stoi(eachKeyNumberToInt)) % alphabet.length();
				encryptText += alphabet[temp];
				break;
			}
		}
	}
	return encryptText;
}
string decryption(const string& str, const string& keyInString)
{
	int temp;
	string decryptText;
	string eachKeyNumberToInt;
	for (int i = 0, k = 0; i < str.length(); i++, k++)
	{
		if (str[i] == '\n')
		{
			decryptText += "\n";
			++i;
		}
		if (str[i] == '\t')
		{
			decryptText += "\t";
			++i;
		}

		if (k == (keyInString.length()))
		{
			k = 0;
		}

		eachKeyNumberToInt = keyInString[k];

		for (int j = 0; j < alphabet.length(); j++)
		{
			if (str[i] == alphabet[j])
			{
				temp = j - stoi(eachKeyNumberToInt);
				if (temp < 0)
				{
					temp += alphabet.length();
				}
				else
				{
					temp = (static_cast<unsigned long long>(j) - stoi(eachKeyNumberToInt)) % alphabet.length();
				}
				decryptText += alphabet[temp];
				break;
			}
		}
	}
	return decryptText;
}

string MakeAlphabet()
{
	for (int i = 192; i <= 255; i++)
	{
		alphabet += i;
	}
	alphabet += "��";
	for (int i = 32; i <= 126; i++)
	{
		alphabet += i;
	}
	return alphabet;
}

bool CheckNum(string& str)
{
	cin >> str;
	for (int i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]))
		{
			return false;
		}
	}
	return true;
}