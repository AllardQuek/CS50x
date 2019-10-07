// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> //for malloc!
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// defining global variables
node* root;
node* temp;
int dictsize = 0;

// Returns true if word is in dictionary else false; check must be case-insensitive, word CANNOT be modified
bool check(const char *word)
{
    // TODO
    // All words in dictionary are lower-case. If word in dict, return true
    temp = root;

    //for every char in word to be tested
    for (int j = 0, n = strlen(word) + 1; j <= n; j++)
    {
        int i;
        char lowletter = tolower(word[j]);

        if (isalpha(lowletter)) //for word[j] = 'f'
            i = lowletter - 97;

        else if (lowletter == '\'')
            i = 26;


        //NOT reached end of string,
        if (lowletter != '\0')
        {
            //but gate closed
            if (temp->children[i] == NULL)
                return false;
            //but gate open, i.e part of a word
            else
                temp = temp->children[i];
        }

        else if (lowletter == '\0')
        {
            if (temp->is_word == true)
                return true;
        }
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //create pointer to root/top of the tree, never touch root again, USE CALLOC!! So that you initialise the value of mem allocated to 0, else could be some garbage value
    root = calloc(1, sizeof(node));
    temp = root;
    int i;

    //opening dict
    FILE* dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return 1;
    }


    //for every char in each word in dict, keep getting chars until reach the end of dict file
    //check value at children[i], if NULL, malloc a new node and have children[i] point to this new node
    for (int c = fgetc(dict); c != EOF; c = fgetc(dict))
    {
        if (isalpha(c))
        {
            i = tolower(c) - 97;
            if (temp->children[i] == NULL)
            {
                temp->children[i] = calloc(1, sizeof(node));
                //have children[i] point to this new node
                temp = temp->children[i];
            }

            else if (temp->children[i] != NULL)
            {
                temp = temp->children[i];
            }
        }

        else if (c == '\'')
        {
            i = 26;
            if (temp->children[i] == NULL)
            {
                temp->children[i] = calloc(1, sizeof(node));
                temp = temp->children[i];
            }

            else if (temp->children[i] != NULL)
            {
                temp = temp->children[i];
            }
        }

        //if done with last char in word
        if (c == '\n')
        {
            temp->is_word = true;
            dictsize++;
            // RESET temp back to root
            temp = root;
        }
    }

    //RMB to close dict after done using it
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictsize;
}

// Unloads/Frees dictionary from memory, returning true if successful else false
void unloadnode(node* cursor);

bool unload(void)
{
    // use free, unload from bottom to top, RECURSION (base case, normal case)
    // travel to lowest possible node, free all pointers in children then the node itself
    unloadnode(root);
    return true;
}


void unloadnode(node* cursor)
{
    //free children, then free node itself
    for (int i = 0; i < 27; i++)
    if (cursor->children[i] != NULL)
    {
        unloadnode(cursor->children[i]);
    }

    free(cursor);
}