#include <bits/stdc++.h>
#include "pda.h"
#include "utils.h"
#include "message.h"
using namespace std;
extern bool verbose;
class PDA{
    public:
    map<string, int> states;
    map<string, int> symbols;
    map<string, int> stack_symbols;
    vector<int> final_states;
    int start_state;
    int current_state;
    stack<int> pda_stack;
    
    // 定义转移函数的结构
    struct Transition {
        int current_state;    // 当前状态
        int input_symbol;  // 输入符号
        int stack_top;     // 栈顶符号
        int next_state;       // 下一个状态
        vector<int> push_symbols; 
    };

    vector<Transition> transitions; // 存储所有转移函数
    PDA(){
        symbols["_"] = 0;
    }
};
PDA pda;
void Stringsplit(const string& str, const string& split, vector<string>& res)
{
	std::regex reg(split);		// 匹配split
	std::sregex_token_iterator pos(str.begin(), str.end(), reg, -1);
	decltype(pos) end;              // 自动推导类型 
	for (; pos != end; ++pos){
		res.push_back(pos->str());
	}
}
bool isStringRepeatedInFile(const std::string& filename, const std::string& target) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return false;
    }
    std::unordered_map<std::string, int> occurrences;
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = 0;
        while ((pos = line.find(target, pos)) != std::string::npos) {
            occurrences[target]++;
            pos += target.length();
        }
    }
    file.close();
    
    // 如果目标字符串出现超过1次，则认为重复
    return occurrences[target] > 1;
}
bool read_pda(string filename){
    ifstream file(filename);
    if(!file){
        cerr<<"File not found"<<endl;
        return false;
    }
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }
    string line;
    while(getline(file, line)){
        if (line.empty() || line[0] == ';') {
            continue; 
        }
        if(line.find("#Q") == 0){
            if(isStringRepeatedInFile(filename, "#Q")){
                cerr<<"syntax error"<<endl;
                return false;
            }
            int posl = line.find("{");
            int posr = line.find("}");
            if(posl == string::npos || posr == string::npos){
                cerr<<"syntax error"<<endl;
                return false;
            }
            string states = line.substr(posl+1, posr-posl-1);
            vector<string> res;
            Stringsplit(states, ",", res);
            for(int i = 0; i < res.size(); i++){
                pda.states[res[i]] = i;
            }
        }
        else if(line.find("#S") == 0){
            if(isStringRepeatedInFile(filename, "#S")){
                cerr<<"syntax error"<<endl;
                return false;
            }
            int posl = line.find("{");
            int posr = line.find("}");
            if(posl == string::npos || posr == string::npos){
                cerr<<"syntax error"<<endl;
                return false;
            }
            string symbols = line.substr(posl+1, posr-posl-1);
            vector<string> res;
            Stringsplit(symbols, ",", res);
            for(int i = 0; i < res.size(); i++){
                if(res[i] == " " || res[i] == "," || res[i] == "{" || res[i] == "}" || res[i] == "*" || res[i] == "_"){
                    cerr<<"syntax error"<<endl;
                    return false;
                }
                pda.symbols[res[i]] = i+1;
            }
        }
        else if(line.find("#G") == 0){
            if(isStringRepeatedInFile(filename, "#G")){
                cerr<<"syntax error"<<endl;
                return false;
            }
            int posl = line.find("{");
            int posr = line.find("}");
            if(posl == string::npos || posr == string::npos){
                cerr<<"syntax error"<<endl;
                return false;
            }
            string stack_symbols = line.substr(posl+1, posr-posl-1);
            vector<string> res;
            Stringsplit(stack_symbols, ",", res);
            for(int i = 0; i < res.size(); i++){
                if(res[i] == " " || res[i] == "," || res[i] == "{" || res[i] == "}" || res[i] == "*" || res[i] == "_"){
                    cerr<<"syntax error"<<endl;
                    return false;
                }
                pda.stack_symbols[res[i]] = i;
            }
        }
        else if(line.find("#q0") == 0){
            if(isStringRepeatedInFile(filename, "#q0")){
                cerr<<"syntax error"<<endl;
                return false;
            }
            vector<string> res;
            Stringsplit(line, " ", res);
            pda.start_state = pda.states[res.back()];
        }
        else if(line.find("#z0") == 0){
            if(isStringRepeatedInFile(filename, "#z0")){
                cerr<<"syntax error"<<endl;
                return false;
            }
            vector<string> res;
            Stringsplit(line, " ", res);
            pda.pda_stack.push(pda.stack_symbols[res.back()]);
        }
        else if(line.find("#F") == 0){
            if(isStringRepeatedInFile(filename, "#F")){
                cerr<<"syntax error"<<endl;
                return false;
            }
            int posl = line.find("{");
            int posr = line.find("}");
            if(posl == string::npos || posr == string::npos){
                cerr<<"syntax error"<<endl;
                return false;
            }
            string final_state = line.substr(posl+1, posr-posl-1);
            vector<string> res;
            Stringsplit(final_state, ",", res);
            for(int i = 0; i < res.size(); i++){
                pda.final_states.push_back(pda.states[res[i]]);
            }
        }
        else{
            vector<string> res;
            Stringsplit(line, " ", res);
            if (res.size() == 5) {
                PDA::Transition transition;
                transition.current_state = pda.states[res[0]];
                transition.input_symbol = pda.symbols[res[1]];
                transition.stack_top = pda.stack_symbols[res[2]];
                transition.next_state = pda.states[res[3]];
                string push_symbols = res[4];
                for (char symbol : push_symbols) {
                    if(symbol == '_'){
                        continue;
                    }
                    transition.push_symbols.push_back(pda.stack_symbols[string(1, symbol)]);
                }
                pda.transitions.push_back(transition);
            }
            else{
                cerr<<"syntax error"<<endl;
                return false;
            }
        }
    }
    return true;
}
int simulate_pda(const string& input) {
    for(int i = 0; i < input.size(); i++){
        if(pda.symbols.find(string(1, input[i])) == pda.symbols.end()){
            IllegalInput(input, i);
            return 3;
        }
    }
    if(!verbose){
        if(input.empty()){
            bool flag = true;
            while(flag){
                flag = false;
                for (const auto& transition : pda.transitions) {
                    if (transition.current_state == pda.current_state &&
                        transition.input_symbol == 0 &&
                        transition.stack_top == pda.pda_stack.top()) {
                        pda.current_state = transition.next_state;
                        pda.pda_stack.pop();
                        flag = true;
                        for (auto rit = transition.push_symbols.rbegin(); rit != transition.push_symbols.rend(); ++rit) {
                            pda.pda_stack.push(*rit);
                        }
                        break;
                    }
                }
                auto it = find(pda.final_states.begin(), pda.final_states.end(), pda.current_state);
                if(it != pda.final_states.end() && pda.pda_stack.size() == 0){
                    return 1;
                }
            }
            return 2;
        }
        for(int i = 0; i < input.size(); i++){
            int input_symbol = pda.symbols[string(1, input[i])];
            bool flag = false;
            for (const auto& transition : pda.transitions) {
                if (transition.current_state == pda.current_state &&
                    transition.input_symbol == input_symbol &&
                    transition.stack_top == pda.pda_stack.top()) {
                    pda.current_state = transition.next_state;
                    pda.pda_stack.pop();
                    flag = true;
                    for (auto rit = transition.push_symbols.rbegin(); rit != transition.push_symbols.rend(); ++rit) {
                        pda.pda_stack.push(*rit);
                    }
                    break;
                }
            }
            bool empty_flag = true;
            while(!empty_flag){
                empty_flag = false;
                for (const auto& transition : pda.transitions) {
                    if (transition.current_state == pda.current_state &&
                        transition.input_symbol == 0 &&
                        transition.stack_top == pda.pda_stack.top()) {
                        pda.current_state = transition.next_state;
                        pda.pda_stack.pop();
                        empty_flag = true;
                        for (auto rit = transition.push_symbols.rbegin(); rit != transition.push_symbols.rend(); ++rit) {
                            pda.pda_stack.push(*rit);
                        }
                        break;
                    }   
                }
            }
            if(!flag){
                return 2;
            }
            auto it = find(pda.final_states.begin(), pda.final_states.end(), pda.current_state);
            if(it != pda.final_states.end() && pda.pda_stack.size() == 0 && i == input.size()-1 ){
                return 1;
            }
        }
        bool empty_flag = true;
        while(empty_flag){
            empty_flag = false;
            for (const auto& transition : pda.transitions) {
                if (transition.current_state == pda.current_state &&
                    transition.input_symbol == 0 &&
                    transition.stack_top == pda.pda_stack.top()) {
                    pda.current_state = transition.next_state;
                    pda.pda_stack.pop();
                    empty_flag = true;
                    for (auto rit = transition.push_symbols.rbegin(); rit != transition.push_symbols.rend(); ++rit) {
                        pda.pda_stack.push(*rit);
                    }
                    break;
                }
            }
            auto it = find(pda.final_states.begin(), pda.final_states.end(), pda.current_state);
            if(it != pda.final_states.end() && pda.pda_stack.size() == 0){
                return 1;
            }
        }
        return 2;
    }
    else{
        int step = 0;
        print_pda(step);
        if(input.empty()){
            bool flag = true;
            while(flag){
                flag = false;
                for (const auto& transition : pda.transitions) {
                    if (transition.current_state == pda.current_state &&
                        transition.input_symbol == 0 &&
                        transition.stack_top == pda.pda_stack.top()) {
                        pda.current_state = transition.next_state;
                        pda.pda_stack.pop();
                        flag = true;
                        for (auto rit = transition.push_symbols.rbegin(); rit != transition.push_symbols.rend(); ++rit) {
                            pda.pda_stack.push(*rit);
                        }
                        step++;
                        print_pda(step);
                        break;
                    }
                }
                auto it = find(pda.final_states.begin(), pda.final_states.end(), pda.current_state);
                if(it != pda.final_states.end() && pda.pda_stack.size() == 0){
                    return 1;
                }
            }
            return 2;
        }
        for(int i = 0; i < input.size(); i++){
            int input_symbol = pda.symbols[string(1, input[i])];
            bool flag = false;
            for (const auto& transition : pda.transitions) {
                if (transition.current_state == pda.current_state &&
                    transition.input_symbol == input_symbol &&
                    transition.stack_top == pda.pda_stack.top()) {
                    pda.current_state = transition.next_state;
                    pda.pda_stack.pop();
                    flag = true;
                    for (auto rit = transition.push_symbols.rbegin(); rit != transition.push_symbols.rend(); ++rit) {
                        pda.pda_stack.push(*rit);
                    }
                    step++;
                    print_pda(step);
                    break;
                }
            }
            bool empty_flag = true;
            while(!empty_flag){
                empty_flag = false;
                for (const auto& transition : pda.transitions) {
                    if (transition.current_state == pda.current_state &&
                        transition.input_symbol == 0 &&
                        transition.stack_top == pda.pda_stack.top()) {
                        pda.current_state = transition.next_state;
                        pda.pda_stack.pop();
                        empty_flag = true;
                        for (auto rit = transition.push_symbols.rbegin(); rit != transition.push_symbols.rend(); ++rit) {
                            pda.pda_stack.push(*rit);
                        }
                        step++;
                        print_pda(step);
                        break;
                    }   
                }
            }
            if(!flag){
                return 2;
            }
            auto it = find(pda.final_states.begin(), pda.final_states.end(), pda.current_state);
            if(it != pda.final_states.end() && pda.pda_stack.size() == 0 && i == input.size()-1 ){
                return 1;
            }
        }
        bool empty_flag = true;
        while(empty_flag){
            empty_flag = false;
            for (const auto& transition : pda.transitions) {
                if (transition.current_state == pda.current_state &&
                    transition.input_symbol == 0 &&
                    transition.stack_top == pda.pda_stack.top()) {
                    pda.current_state = transition.next_state;
                    pda.pda_stack.pop();
                    empty_flag = true;
                    for (auto rit = transition.push_symbols.rbegin(); rit != transition.push_symbols.rend(); ++rit) {
                        pda.pda_stack.push(*rit);
                    }
                    step++;
                    print_pda(step);
                    break;
                }
            }
            auto it = find(pda.final_states.begin(), pda.final_states.end(), pda.current_state);
            if(it != pda.final_states.end() && pda.pda_stack.size() == 0){
                return 1;
            }
        }
        return 2;
    }
}

void print_pda(int step){
    cerr<<"Step  : "<<step<<endl;
    for(std::map<string,int>::iterator it = pda.states.begin();it!=pda.states.end();it++) {
		if(it->second==pda.current_state){
            cerr<<"State : "<<it->first<<endl;
            break;
        }
	} 
    if(pda.pda_stack.size() == 0){
        cerr<<"Stack : _"<<endl;
    }
    else{
        for(std::map<string,int>::iterator it = pda.stack_symbols.begin();it!=pda.stack_symbols.end();it++) {
            if(it->second==pda.pda_stack.top()){
                cerr<<"Stack : "<<it->first<<endl;
                break;
            }
        } 
    }
    PrintDivider();
}

