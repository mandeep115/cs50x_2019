#include <iostream>
#include <cctype>
#include <cstring> 
using namespace std;

void encrypt(string ptxt, int key);

int main(int argc, char *argv[2]) {
        //basic check if user types anything more than 2 argument program ends and return 1
    if (argc !=2){
        cout << "Usage: ./caesar key" << endl;
        return 1;
        
    }

    for (int i=0, n = strlen(argv[1]); i<n ; i++){
        //we are looking into every character of user input
        if (isdigit((argv[1][i])) != true) {
            cout << "Usage: ./caesar key" << endl;
            return 1;
            //if user inputs anyting but a number programs ends and return 1
        }
        else {
            //if all is cool program continiues
            continue;
        }
    }
    //this is our key
    int key = stoi(argv[1]);

    cout << "Your key is: " << key << endl;
    
    //string for plain text and encrypted text

    string ptxt  ;
    cout << "Plain Text: ";

    //get string using getline
    getline(cin, ptxt);
    cout << "Encrypted Text: ";
    
    // encrypt and print
    encrypt(ptxt, key);

    cout << endl;

    return 0;
}

void encrypt(string ptxt, int key) {
    string  entxt;
    for (int i=0, n=ptxt.length(); i<n; i++){

        //for upper case letter
        if (int(ptxt[i]) <= 97 && int(ptxt[i]) >= 65) {
            entxt[i] = ((ptxt[i]+key-65)%26)+65;
        }

        // for lower case letter
        else if (int(ptxt[i]) >=98 && int(ptxt[i]) <= 122) {
            entxt[i] = ((ptxt[i]+key-97)%26)+97;
        }

        // for everything else like SPACE or any character
        else {
            entxt[i] = ptxt[i];
        }
        
        // Print everything we just calculated

        cout  << entxt[i];
    }
}