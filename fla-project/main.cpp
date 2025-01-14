#include <bits/stdc++.h>
#include "pda.h"
#include "utils.h"
#include "message.h"
#include "TM.h"
using namespace std;

string filename;
bool verbose = false;
int main(int argc, char* argv[]){
    if(argc == 1){
        return 1;
    }
    bool help = false, err = false;
    string input;
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == "-h"s || argv[i] == "--help"s) {
        help = true;
        } else if (argv[i] == "-v"s || argv[i] == "--verbose"s) {
        verbose = true;
        } else if (filename.empty()) {
        filename = argv[i];
        } else if (input.empty()) {
        input = argv[i];
        } else {
        err = true;
        }
    }
    if (filename.empty()) {
        err = true;
    }
    if (help) {
        cout << "usage: fla [-v|--verbose] [-h|--help] <pda> <input>" << endl
             << "       fla [-v|--verbose] [-h|--help] <tm> <input>" << endl;
        return 0;
    } 
    else if (err) {
        cerr << "usage: fla [-v|--verbose] [-h|--help] <pda> <input>" << endl
             << "       fla [-v|--verbose] [-h|--help] <tm> <input>" << endl;
        return 1;
    }
    if(!verbose){
        if(filename.find("pda") != string::npos){
            bool read_right = read_pda(filename);
            if(!read_right){
                return 1;
            }
            int flag = simulate_pda(input);
            if(flag == 1){
                cout<<"true"<<endl;
            }
            else if(flag == 2){
                cout<<"false"<<endl;
            }
        }
        else if(filename.find("tm") != string::npos){
                parser(filename);
                simulator(input);
        }
        else{
            cerr << "usage: fla [-v|--verbose] [-h|--help] <pda> <input>" << endl
                << "        fla [-v|--verbose] [-h|--help] <tm> <input>" << endl;
        }
    }
    else{
        if(filename.find("pda") != string::npos){
            bool read_right = read_pda(filename);
            if(!read_right){
                return 1;
            }
            int flag = simulate_pda(input);
            if(flag == 1){
                cerr<<"Result: true"<<endl;
                PrintEnd();
                return 0;
            }
            else if(flag == 2){
                cerr<<"Result: false"<<endl;
                PrintEnd();
                return 1;
            }
        }
        else if(filename.find("tm") != string::npos){
            parser(filename);
            simulator(input);
        }
        else{
            cerr << "usage: fla [-v|--verbose] [-h|--help] <pda> <input>" << endl
                << "        fla [-v|--verbose] [-h|--help] <tm> <input>" << endl;
        }
    }
    return 0;
}
