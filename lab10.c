#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Trie structure
struct Trie {
    struct Trie *children[26]; // 26 for lowercase English alphabets
    int count; // Counter for occurrences of a word
};

// Function to initialize a Trie
struct Trie *createTrie() {
    struct Trie *myTree = (struct Trie *)malloc(sizeof(struct Trie));
    
        myTree->count = 0;
        for (int i = 0; i < 26; i++)
            myTree->children[i] = NULL;
    return myTree;
}

// Inserts a word into the trie
void insert(struct Trie *pTrie, char *word, int k) {
    for (int i = k; word[i] != '\0'; i++) {
        int index = word[i] - 'a'; // Convert character to index
        if (pTrie->children[index] == NULL) {
            pTrie->children[index] = createTrie();           
        }
        pTrie = pTrie->children[index]; // Move to the child node
    }
    pTrie->count++; // Increment occurrence count
    return;
}



// Searches for a word in the trie and returns its occurrence count
int numberOfOccurrences(struct Trie *pTrie, char *word) {
    int nextIndex;
    for(int i = 0; i < strlen(word); i++){
        nextIndex = word[i] - 'a';
        if (pTrie->children[nextIndex] == NULL) {
            return 0;
        }
        pTrie = pTrie->children[nextIndex];
    }
    return pTrie->count;
}


// Function to deallocate memory for the trie nodes
struct Trie *deallocateTrie(struct Trie *root) {
        for (int i = 0; i < 26; i++){
            if(root->children[i] != NULL){
                deallocateTrie(root->children[i]);
        }
        }  
        free(root);
        return NULL;
}

// Reads the dictionary file and stores words in the array
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    int numOfWords;
    fscanf(file, "%d", &numOfWords);
    

    for(int i = 0; i < numOfWords; i++){
        pInWords[i] = malloc(256 * sizeof(char)); 
        fscanf(file, "%s", pInWords[i]);
    }

    fclose(file);
    return numOfWords;
}

int main(void) {
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }
    struct Trie *pTrie = createTrie();
    
    for (int i = 0; i < numWords; i++) {
        insert(pTrie, inWords[i],0);

    }
    //printf("anotherthigns");
    // Test cases
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
        printf("%d",i);
    }

    // Deallocate memory for the trie
    pTrie=deallocateTrie(pTrie);
    if (pTrie != NULL)
		printf("There is an error in this program\n");
    return 0;
}
