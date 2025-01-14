#include "message.h"
#include "utils.h"
extern bool verbose;
void PrintErr() {
  if (verbose)
    cerr << "==================== ERR ====================" << endl;
}
void PrintEnd() {
  if (verbose)
    cerr << "==================== END ====================" << endl;
}
void PrintRun() {
  if (verbose)
    cerr << "==================== RUN ====================" << endl;
}
void PrintDivider() {
  if (verbose)
    cerr << "---------------------------------------------" << endl;
}
void PrintInput(const string &input) {
  if (verbose)
    cerr << "Input: " << input << endl;
}