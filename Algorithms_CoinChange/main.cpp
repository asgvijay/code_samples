#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <iterator>
#include <typeinfo>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::stringstream;
using std::ofstream;

void coinChangeDP(int, vector<int> *, vector<int>);
void coinChangeGreedy(int, vector<int> *, vector<int>);
void printVector(vector<int>, ofstream&);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("You must specify a file in the command line.\n");
		return 1;
	}
	const string fileName(argv[1]);

	ifstream file(fileName);
	ofstream outputFile;
	string outFileName;
	std::size_t pos = fileName.find(".");
	outFileName = fileName.substr(0, pos);
	outFileName += "change.txt";
	outputFile.open(outFileName.c_str());



	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			string valstr;
			vector<int> coins;
			getline(file, valstr);
			int value = atoi(valstr.c_str());

			int i = 0;
			line.erase(0, 1);
			stringstream ssin(line);
			string s;
			int j = 0;
			while (ssin.good()) {
				ssin >> s;
				j = atoi(s.c_str());
				coins.push_back(j);
				i++;
			}
			coins.pop_back();
			i--;
			if (i == 0) {
				break;
			}
			vector<int> DPCoins (i);
			vector<int> greedyCoins (i);
			outputFile << "Algorithm changeGreedy:\n";
			coinChangeGreedy(value, &greedyCoins, coins);
			printVector(greedyCoins, outputFile);
			outputFile << "Algorithm changeDP:\n";
			coinChangeDP(value, &DPCoins, coins);
			printVector(DPCoins, outputFile);
			outputFile << endl;
		}
	} else {
		printf("File failed to open. Please make sure file exists in the same directory as the program.\n");
	}
	file.close();
	outputFile.close();
    return 0;
}

void printVector(vector<int> v,  ofstream& readfile)
{
	int numOfCoins = 0;
	readfile << "[";
    for (int i = 0; i < v.size(); i++)
    {
    	if (i == 0) {
    		readfile << v[i];
    	} else {
    		readfile << ", " << v[i];
    	}
    	numOfCoins += v[i];
    }
    readfile << "]" << endl;
    readfile << numOfCoins << endl;
}

void coinChangeDP(int v, vector<int> *c, vector<int> coins)
{
    int opt[v + 1];
    int coinCh[v + 1];
    int pos;
    opt[0] = 0;                                     //total change of zero is zero
    coinCh[0] = -1;
    for (int i = 1; i < v + 1; i++)
    {
        opt[i] = std::numeric_limits<int>::max();
        coinCh[i] = -1;
    }
    for (int j = 0; j < coins.size(); j++)
    {
        for (int i = 1; i < v + 1; i++)
        {
            if (i >= coins[j])                     //if current coin is greater than V_i
            {
                if(opt[i - coins[j]] + 1 < opt[i])       //if adding current coin reduces total coins to make change
                {
                    opt[i] = opt[i - coins[j]] + 1;
                    coinCh[i] = j;                  //keep track of last coin to be used to make total
                }
            }
        }
    }
    int i = 1;
    while (v > 0)
    {
        (*c)[coinCh[v]]++;
        v -= coins[coinCh[v]];
    }
}

void coinChangeGreedy(int v, vector<int> *c, vector<int> coins)
{
    int i = coins.size();
    i--;
    while(v > 0)
    {
        if(v >= coins[i])
        {
            v = v - coins[i];
            (*c)[i]++;
        }
        else
            i--;
    }
}
