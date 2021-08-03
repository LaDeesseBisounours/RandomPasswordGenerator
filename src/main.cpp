#include <fstream>
#include <exception>
#include <string>
#include <iostream>

using namespace std;

class invalid_arg_class : public exception {
  virtual const char* what() const throw()
  {
    return "InvalidArgument";
  }
} invalid_arg;
class out_of_range_class : public exception {
  virtual const char* what() const throw()
  {
    return "out_of_range";
  }
} out_range;

typedef  unsigned pwSize;
typedef  unsigned counter;
typedef  bool uniquenessCounter;

struct returnParse {
    int retVal;
    bool mustExit;
};

struct returnParse parseInput(counter argc, char** argv, pwSize& size) {
    counter index = 1;
    uniquenessCounter sizeOptionPassed = false;
    for(; index < argc; index++) {
        string s(argv[index]);
        if (!s.compare("-s")) {

            if (sizeOptionPassed) {
                cerr << "Passing twice -s flag" << endl;
                return { 1, true };
            }

            if (index + 1 >= argc) {
                cerr << "Missing number argument for -s" << endl;
                return { 2, true };
            }

            index++;
            string num(argv[index]);
            try {
                int newSize = stoi(num);
                if (newSize <= 0)
                    throw  invalid_arg;
                else if (newSize >= 35)
                    throw  out_range;
                size = newSize;
            } catch(invalid_argument& e) {
                cerr << "Invalid argument for -s [non-zero positive integer]" << endl;
                return { 2, true };
            }catch (invalid_arg_class& e){
                cerr << "Invalid argument for -s [non-zero positive integer]" << endl;
                return { 3, true };
            }catch (out_of_range_class& e){
                cerr << "Argument out of range for -s [non-zero positive integer]" << endl;
                return { 4, true };
            } catch (out_of_range& e) {
                cerr << "Argument out of range for -s [non-zero positive integer]" << endl;
                return { 5, true };
            }
        }
        else if (!s.compare("-h") or !s.compare("--help")) {
            cout << "Usage:" << endl 
                << "   -s [non zero positive integer] : default size 16" << endl
                << "   -h|--help display help" << endl;
            return { 0, true };
        } else {
            cerr << "Unknown option \"" << s << "\"" << endl;
            return { 6, true };
        }
    }
    return { 0, false };
}

string generatePass(const pwSize size) {
    const unsigned lowestAscii = 33;
    const unsigned highestAscii = 126;
    const unsigned diff = highestAscii - lowestAscii;
    const string randFileName = "/dev/random";

    fstream randFile(randFileName);
    if (not randFile.is_open()) {
        cerr << "error: Could not open " << randFileName << endl;
        return "";
    }

    string result(size, 'x');
    for (counter index = 0; index < size; index++) {
        unsigned char character;
        randFile >> character;
        character %= diff;
        result[index] = static_cast<char>(character + lowestAscii) ;
    }
    return result;
}

int main(int argc, char ** argv) {
    pwSize defaultPwSize = 16;
    const returnParse res = parseInput(static_cast<counter>(argc), argv, defaultPwSize);
    if (res.mustExit)
        return res.retVal;

    string password = generatePass(defaultPwSize);
    cout << "Password: " << password << endl;
}
