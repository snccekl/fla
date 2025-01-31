#include <bits/stdc++.h>

using namespace std;

extern bool verbose;

struct trasition
{
    string old_state;
    string old_symbol_set;
    string new_symbol_set;
    string direction_set;
    string new_state;
}; 

void parser(string TM);
void parser_Q(string input);
void parser_S(string input);
void parser_G(string input);
void parser_q0(string input);
void parser_B(string input);
void parser_F(string input);
void parser_N(string input);
void parser_delta(string input);
void handle_line_comment(string &input);

void simulator(string input);
void check_input_string(string input);
void print_spaces(int count);
void print_instant_description();
int symbol_compare(string a, string b);