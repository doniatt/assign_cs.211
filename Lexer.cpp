#include <iostream>
#include <cctype>
#include <string>

using namespace std;

int charClass;
string lexeme;
char nextChar;
int nextToken;
int index = 0;

string input = "float rec_area = (len + wid) * 2;";

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
#define END_OF_INPUT -1
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define SEMICOLON 27

void addChar() {
    lexeme += nextChar;
}

void getChar() {
    if (index < input.length()) {
        nextChar = input[index++];
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar) || nextChar == '_')
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else {
        charClass = END_OF_INPUT;
    }
}

void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

int lookup(char ch) {
    switch (ch) {
    case '(': addChar(); return LEFT_PAREN;
    case ')': addChar(); return RIGHT_PAREN;
    case '+': addChar(); return ADD_OP;
    case '-': addChar(); return SUB_OP;
    case '*': addChar(); return MULT_OP;
    case '/': addChar(); return DIV_OP;
    case '=': addChar(); return ASSIGN_OP;
    case ';': addChar(); return SEMICOLON;
    default: addChar(); return -1;
    }
}

int lex() {
    lexeme = "";
    getNonBlank();
    switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;
    case UNKNOWN:
        nextToken = lookup(nextChar);
        getChar();
        break;
    case END_OF_INPUT:
        nextToken = -1;
        lexeme = "EOF";
        break;
    }
    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}

int main() {
    getChar();
    while (nextToken != -1)
        lex();
    return 0;
}