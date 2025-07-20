#include <iostream>
#include <string>

using namespace std;

/* Thought Process:

- The program receives a number that indicates how many strings need to be checked for balanced brackets.
- For each string:
  - If its length is odd, it cannot be balanced (no way to form pairs).
  - Otherwise, we examine each character in the string.
- We use a stack to keep track of the open brackets:
  - Every time we see an opening bracket, we push it to the stack.
  - For every closing bracket, we check if the top of the stack matches it.
    - If it matches, we pop the top (a pair is completed).
    - If not, or if the stack is empty, the string is unbalanced.
- The stack represents the nested structure:
  - The first opening bracket pushed must be the last one to be closed (LIFO).
  - Before closing a bracket, every nested (more recent) one must be closed first.

Input:

n       → number of strings to validate  
s       → each string containing brackets only: (), [], {}

Output:

- For each string, print "YES" if the brackets are balanced, otherwise print "NO".

What to do:

1. Read the number of test cases.
2. For each string:
   a. Check if the length is even (quick fail if not).
   b. Create an empty stack.
   c. Iterate through the characters:
      - Push if it’s an opening bracket.
      - If it’s a closing bracket, check the top of the stack:
         - If it matches, pop it.
         - If not, mark as unbalanced.
   d. After the loop, if the stack is empty, it’s balanced.
3. Output the result accordingly.
*/

// Bracket represents a single element in the stack
struct Bracket {
    char bracket; // The character value of the bracket ('{', '(', '[')
    Bracket* prevBracket; // Pointer to the previous node in the stack
};

// BracketStack is a custom implementation of a stack data structure
class BracketStack {
    private:
        Bracket* lastBracket; // Pointer to the top element of the stack
    public:
        // Constructor
        BracketStack() {
            lastBracket = nullptr;
        }

        // Getter
        char getLastBracketValue() {
            return lastBracket->bracket;
        }
        
        // Pushes a new bracket onto the top of the stack
        void addBracket(char bracket) {
            Bracket* newBracket = new Bracket{bracket, nullptr};

            if (lastBracket != nullptr) {
                newBracket->prevBracket = lastBracket;
            }
            lastBracket = newBracket;
        }

        // Delete the top element from the stack
        void deleteBracket() {
            if (lastBracket != nullptr) {
                Bracket* delBracket = lastBracket;
                lastBracket = lastBracket->prevBracket;
                delete delBracket;
            }
        }

        // Check if the stack is empty
        bool isStackEmpty() {
            return lastBracket == nullptr;
        }
        
        // Destructor
        ~BracketStack() {
            while (lastBracket != nullptr) {
                deleteBracket();
            }
        }
};

int main() {
    int numOfStrings;

    // Read the number of test cases
    cin >> numOfStrings;
    
    // Loop through each test case
    for (int i=0; i<numOfStrings; i++) {
        BracketStack stack; // Create a new stack for each string
        string stringOfBrackets; // Variable to hold the input string of brackets
        char lastBracket; 
        bool isBalanced = true; // Flag to track if the current string is balanced

        // Read the string of brackets for the current test case
        cin >> stringOfBrackets;
        
        // Iterate over each character in the input string
        for (char bracket : stringOfBrackets) {
            // If it's an opening bracket, push it onto the stack
            if (bracket == '{' || bracket == '(' || bracket == '[') {
                stack.addBracket(bracket);

            // If it's a closing bracket, check for a match
            } else {
                // First, if the stack is empty, there's no opening bracket to match => Unbalanced
                if (stack.isStackEmpty()) {
                    isBalanced = false;
                    break;
                } else {
                    lastBracket = stack.getLastBracketValue(); // Get the last opening bracket from the top of the stack
                    
                    // Check if the current closing bracket matches the last opening bracket
                    if ((lastBracket == '{' && bracket == '}') || (lastBracket == '(' && bracket == ')') || (lastBracket == '[' && bracket == ']')) {
                        stack.deleteBracket();

                    // If they don't match => Unbalanced
                    } else {
                        isBalanced = false;
                        break;
                    }
                }
            }
        }

        // A string is balanced if two conditions are met:
        // 1. The `isBalanced` flag is still true
        // 2. The stack is empty 

        if (isBalanced && stack.isStackEmpty()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}