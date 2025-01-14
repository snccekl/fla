#include <bits/stdc++.h>
#include "utils.h"
#include "message.h"

extern bool verbose;
string Trim(const string &str, const char &ch) {
  if (str.empty())
    return str;
  string res = str;
  res.erase(0, res.find_first_not_of(ch));
  res.erase(res.find_last_not_of(ch) + 1);
  return res;
}
void Help() {
  cout << "usage: turing [-v|--verbosee] [-h|--help] <tm> <input>";
}

void SyntaxError(const string &error, const string &sentence, int error_pos) {
  if (verbose) {
    PrintErr();
    cerr << "error: " << error << endl;
    if (not sentence.empty())
      cerr << "Input: " << sentence << endl;
    if (not sentence.empty() and error_pos >= 0 and error_pos < sentence.size()) {
      cerr << "       ";
      for (int i = 0; i < error_pos; i++) { cerr << " "; }
      cerr << "^" << endl;
    }
    PrintEnd();
  } else {
    cerr << "syntax error" << endl;
  }
  exit(1);
}

void IllegalInput(const string &input, int error_pos) {
  if (verbose) {
    cerr << "Input: " << input << endl;
    PrintErr();

    char illegal_char = input.at(error_pos);
    cerr << "\'" << illegal_char << "\' was not declared in the set of input symbols" << endl;
    cerr << "Input: " << input << endl;

    if (error_pos >= 0 and error_pos < input.size()) {
      cerr << "       ";
      for (int i = 0; i < error_pos; i++) { cerr << " "; }
      cerr << "^" << endl;
    }

    PrintEnd();
  } else { 
    cout << "illegal input" << endl;
  }
  exit(1);
}

vector<string> Split(const string &str, const string &delim) {
  vector<string> res;
  string::size_type lastPos = str.find_first_not_of(delim, 0);
  string::size_type pos = str.find_first_of(delim, lastPos);
  while (string::npos != pos || string::npos != lastPos) {
    res.emplace_back(str.substr(lastPos, pos - lastPos));
    lastPos = str.find_first_not_of(delim, pos);
    pos = str.find_first_of(delim, lastPos);
  }
  return res;
}

int NumLen(long long int num) {
  stringstream ss;
  ss << num;
  return ss.str().size();
}

string Space(int num_space) {
  stringstream ss;
  for (int i = 0; i < num_space; i++) {
    ss << " ";
  }
  return ss.str();
}

