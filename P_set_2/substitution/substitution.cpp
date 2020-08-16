#include <iostream>
#include <cctype>
#include <cstring> 
using namespace std;

void encrypt(string ptxt, char key[26]);

int main(int argc, char *argv[2]) {

    if (argc !=2){
        cout << "Usage: ./substitution key" << endl;
        return 1;
    }

    int s = strlen(argv[1]);

    if (s!=26) {
        cout << "Length of key: " << s << endl;
        cout << "Key must contain 26 characters." << endl;
        return 1;
    }

    for (int i=0; i<26 ; i++){
        //we are looking into every character of user input
        bool a = isalpha(argv[1][i]);
        if (a==true) {
            continue;
        }
        else {
            cout << "Usage: ./substitution key" << endl;
            return 1;
        }
    }

    for (int i=0; i <= 25; i++) {
        char el_1 = argv[1][i];
        for (int j = i+1; j <= 25; j++) {
            char el_2 = argv[1][j];
            if (el_1 == el_2) {
                cout << el_1 << " " << el_2 << "Invalid Key!!" << endl << "Key should contain discrit characters" << endl;
                return 1; 
            }
            else continue;
        }
    }

    char key[26];

    // This is our keys we have calubrated our code to work with upper case key,
    // so if user enters lower case key we will convert it into upper case
    for (int i=0; i<26; i++) {
        key[i] = argv[1][i];
        if (islower(key[i])) key[i]=toupper(key[i]);
    }
    
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

void encrypt(string ptxt, char key[]) {
    string entxt;
    int k = 0;
    for (int i = 0, n = ptxt.length(); i<n; i++) {
        if (isupper(ptxt[i])){
            k = ((ptxt[i]-65)%26);
            entxt[i] = key[k];
            cout << entxt[i];
        }
        else if (islower(ptxt[i])) {
            k = ((ptxt[i]-97)%26);
            entxt[i] = key[k];
            cout << char(entxt[i]+32);
        }
        else {
            cout << ptxt[i];
        }
    }
}