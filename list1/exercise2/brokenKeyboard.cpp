#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 

using namespace std;

/* Thought Process:

- Non-letter characters work normally.
- Check how many full lines can be typed even with broken keys.
- Determine which other letters may be broken based on invalid lines.
- Test if a line can be typed without using the broken keys.
- Identify letters used that are not available on the keyboard (broken).

Input:

- List of broken keys
- Followed by multiple lines of text to type
- "END" marks the end of a case (and should be counted)
- "finish" ends all cases (and should not be counted)

Output:

- Letter "w": 59 total characters  
- Letter "h" (header): 4 spaces  
- Letter "h" (body): 2 spaces per case

Output layout:

1st column (positions 1 to 11) → case number (aligned depending on digit count)
2nd column (positions 12 to 30) → number of lines that can be typed
3rd column (position 31 onward) → letters that *may* be broken (based on unused ones)

Alignment rules:

- 1-digit case number → uses 7th position  
- 2-digit number → uses positions 6 and 7  
- 3-digit number → uses positions 5, 6, and 7  
- Lines count follows similar logic: uses up to positions 19, 20, and 21

What to do:

1. Continuously read input until "finish" appears, as the number of inputs is unknown.
2. Every time "END" appears, increment the case counter.
3. Detect whether you're reading broken keys or normal text lines.
4. Store broken keys in a list.
5. Once broken key reading is turned off, read lines until reaching "END".
6. For each line:
   - Check if it contains any broken key.
   - If it doesn't, consider it as a valid line.
   - Remove letters found in the line from the alphabet string (potentially not broken).
7. Store data:
   - `int` vector: case number, number of valid lines (stored in pairs)
   - `string` vector: letters that might be broken (one per case)
8. After encountering "finish", print the vectors using the specified layout.
*/

// Structure for the output line
struct OutputInfo {
    int caseNumber;
    int printableLines;
    string brokenKeys;
};

// Checks if a string can be fully typed given a set of broken keys
bool checkIfIsPrintable(string stringToCheck, string stringToCompare) {

    for (char letter : stringToCheck) {
        if (stringToCompare.find(letter) != string::npos) {
            return false; // Cannot type if the letter is broken
        }
    }

    return true; // All letters are usable
};

// Prints the final output table in the required format
void printTable(vector<OutputInfo> outputInfo) {

    // print head
    cout << "+----------+----------------+-----------------------------+" << endl;
    cout << "| Keyboard | # of printable | Additionally, the following |" << endl;
    cout << "|          |      lines     |  letter keys can be broken  |" << endl;
    cout << "+----------+----------------+-----------------------------+" << endl;

    for (int i=0; i<outputInfo.size(); i++) {
        int keyboardNumber = outputInfo[i].caseNumber;
        int printableLines = outputInfo[i].printableLines;
        string brokenKeys = outputInfo[i].brokenKeys;

        /* Print case infos */

        // Print keyboard number with proper alignment
        cout << "|" << setw(6) << keyboardNumber << setw(5);

        // Print number of printable lines with proper alignment
        cout << "|" << setw(9) << printableLines << setw(9);

        // Print broken keys string and fill the remaining space
        cout << "| " << brokenKeys;
        int outputSpaceLentgh = 29 - brokenKeys.size();
        cout << setw(outputSpaceLentgh) << "|" << endl;

        // Print row separator
        cout << "+----------+----------------+-----------------------------+" << endl;
    }
}

int main() {
    string keyboardInput; // Stores inputs
    int numCase = 0; // Track number of test cases
    vector<OutputInfo> outputInfo; // Stores case results

    // Process multiple cases until "finish"
    while (getline(cin, keyboardInput) && keyboardInput != "finish") {
        int numPrintableLines = 0; 
        bool isPrintable = true; // Flag for line printability
        bool isEndActivate = false; // Flag for activate END 
        string alphabetStr = "abcdefghijklmnopqrstuvwxyz"; 
        string keysThatCanBeBrokenStr; // Possible broken keys based on untyped letters
        string keysThatCanNotBeBrokenStr; // Letters confirmed to be usable
        string brokenKeysStr; // Actual broken keys for the case

        // Step 0: Store case
        numCase++;

        // Step 1: Store broken keys on first read (lower case)
        for (char brokenLetter : keyboardInput) {
            brokenKeysStr += std::tolower(brokenLetter);
        }

        // Step 2: Run case lines 
        while (getline(cin, keyboardInput)) {
            
            string keyboardInputLowerCase;

            // Step 3: Store text input on lower case
            for (char letter : keyboardInput) {
                keyboardInputLowerCase += std::tolower(letter);
            }

            // Step 4: Check if the input has broken keys
            isPrintable = checkIfIsPrintable(keyboardInputLowerCase, brokenKeysStr);

            // Step 5: Add each character from the valid line to the "cannot be broken" set if it is printable
            if (isPrintable) {
                numPrintableLines++; 
                
                // Add keys to the "cannot be broken" set
                for (char letter : keyboardInputLowerCase) {
                    int letterPosition = letter - 'a';

                    // Add to safe list only if it's not already there
                    if (keysThatCanNotBeBrokenStr.find(letter) == string::npos) { 
                        keysThatCanNotBeBrokenStr.push_back(alphabetStr[letterPosition]);    
                    } 
                } 
            }

            if (keyboardInput == "END") {
                break;
            }  
        }

        // Step 6: Identify which letters may still be broken (unused and not in broken list)
        for (char letter : alphabetStr) {
            int letterPosition = letter - 'a';

            // Letter not proven to work and not already in the broken list
            if (keysThatCanNotBeBrokenStr.find(letter) == string::npos && brokenKeysStr.find(letter) == string::npos) {
                if (keysThatCanBeBrokenStr.find(letter) == string::npos) { 
                    keysThatCanBeBrokenStr.push_back(alphabetStr[letterPosition]);
                }
            }
        }

        // Step 7: Store case result
        outputInfo.push_back({numCase, numPrintableLines, keysThatCanBeBrokenStr});
    }
    
    // Step 8: Print all collected output
    printTable(outputInfo);
}