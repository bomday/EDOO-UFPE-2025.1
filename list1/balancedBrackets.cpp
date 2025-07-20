#include <iostream>
#include <string>

using namespace std;

struct Node {
    char bracket;
    Node* prevBracket;
};

class BracketStack {
    private:
        Node* lastBracket;
    public:
        BracketStack() {
            lastBracket = nullptr;
        }

        char getLastBracketValue() {
            return lastBracket->bracket;
        }

        void addBracket(char bracket) {
            Node* newBracket = new Node{bracket, nullptr};

            if (lastBracket != nullptr) {
                newBracket->prevBracket = lastBracket;
            }
            lastBracket = newBracket;
        }

        void deleteBracket() {
            if (lastBracket != nullptr) {
                Node* delBracket = lastBracket;
                lastBracket = lastBracket->prevBracket;
                delete delBracket;
            }
        }

        bool isStackEmpty() {
            return lastBracket == nullptr;
        }

        ~BracketStack() {
            while (lastBracket != nullptr) {
                Node* delBracket = lastBracket;
                lastBracket = lastBracket->prevBracket;
                delete delBracket;
            }
        }
};

int main() {
    int numOfStrings;

    cin >> numOfStrings;
    
    for (int i=0; i<numOfStrings; i++) {
        BracketStack stack;
        string stringOfBrackets;
        char lastBracket;
        bool isBalanced = true;

        cin >> stringOfBrackets;
        
        for (char bracket : stringOfBrackets) {
            if (bracket == '{' || bracket == '(' || bracket == '[') {
                stack.addBracket(bracket);
            } else {
                if (stack.isStackEmpty()) {
                    isBalanced = false;
                    break;
                } else {
                    lastBracket = stack.getLastBracketValue();
                    if ((lastBracket == '{' && bracket == '}') || (lastBracket == '(' && bracket == ')') || (lastBracket == '[' && bracket == ']')) {
                        stack.deleteBracket();
                    } else {
                        isBalanced = false;
                        break;
                    }
                }
            }
        }

        if (isBalanced && stack.isStackEmpty()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}