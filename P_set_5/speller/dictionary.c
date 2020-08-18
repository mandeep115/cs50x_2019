// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 200000;

// Initiate hash_value
// Unsigned int for positive values
unsigned int hash_value;

// Initialize number of words in hash table
unsigned int word_count;

// Hash table
node *table[N];

// Hashes word to a number
unsigned int hash(const char *word) {
    // http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;

    while ((c = tolower(*word++)))
        
        // << is the left shift operator
        // http://www.fredosaurus.com/notes-cpp/expressions/bitops.html
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary) {
    // opening the dictionary file
    FILE *file = fopen(dictionary, "r");
    
    if (file == NULL) {
        return false;
    }
    // space for the word
    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF) {
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            return false;
        }
        // copy the word in node
        strcpy(n->word, word);
        // hash the word
        hash_value = hash(word);
        // set new pointer 
        n->next = table[hash_value];
        // set head to new pointer
        table[hash_value] = n;
        // incriment word count
        word_count++;
    }
    // close the file 
    fclose(file);
    // return true if everything goes well
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void) {    
    if (word_count > 0) {
        return word_count;
    }
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word) {
    // take the word and hash it to get hash_value
    hash_value = hash(word);
    // use a for loop to access linked list at the table[hash_value]
    for (node *tmp = table[hash_value]; tmp != NULL; tmp = tmp->next) {
        
        // If the word is in the dictionnary
        // strcasecmp: is case-insensitive
        
        if (strcasecmp(word, tmp->word) == 0) {
            return true;
        }

    }
    // return false if word not found
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void) {
    for (int f = 0; f < N; f++){

        node *cursor = table[f];

        while (cursor) {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        if (f == N - 1 && cursor == NULL) {
            return true;
        }
    }
    
    return false;
}
