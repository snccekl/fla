#ifndef PDA_H_
#define PDA_H_

#include <bits/stdc++.h>

using namespace std;

void Stringsplit(const string& str, const string& split, vector<string>& res);

bool isStringRepeatedInFile(const std::string& filename, const std::string& target);

bool read_pda(string filename);

int simulate_pda(const string& input);

void print_pda(int step);

#endif //PDA_H_