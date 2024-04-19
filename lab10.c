#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Trie structure
struct Trie {
    struct Trie *children[26]; // 26 for lowercase English alphabets
    int isWord; // Flag to mark end of a word
    int count; // Counter for occurrences of a word
};

// Function to initialize a Trie
struct Trie *createTrie() {
    struct Trie *myTree = (struct Trie *)malloc(sizeof(struct Trie));
    printf("are things being created?\n");
        myTree->isWord = 0;
        myTree->count = 0;
        for (int i = 0; i < 26; i++)
            myTree->children[i] = NULL;
    return myTree;
}

// Inserts a word into the trie
void insert(struct Trie *pTrie, char *word, int k) {
    // Down to the end, insert the word.
    if (k == strlen(word)) {
    pTrie->isWord = 1;
    pTrie->count++;
    printf("word found\n");
    return;
    }
    printf("or not\n");
    // See if the next place to go exists, if not, create it.
    int nextIndex = word[k] - 'a';
    if (pTrie->children[nextIndex] == NULL){
        printf("something got created\n");
        pTrie->children[nextIndex] = createTrie(); 
    }
    insert(pTrie->children[nextIndex], word, k+1);
}

// Searches for a word in the trie and returns its occurrence count
int numberOfOccurrences(struct Trie *root, char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (!root->children[index]) {
            printf("Word not found: %s\n", word);
            return 0; // Word not found
        }
        root = root->children[index];
    }
    if (root !=NULL && root->isWord !=0) {
        printf("Word found: %s, count: %d\n", word, root->count);
        return root->count; // Word found, return its occurrence count
    }
    printf("Word not found: %s\n", word);
    return 0; // Word not found
}


// Function to deallocate memory for the trie nodes
struct Trie *deallocateTrie(struct Trie *root) {
    if (root) {
        for (int i = 0; i < 26; i++)
            if (root->children[i] != NULL)
                deallocateTrie(root->children[i]);
        free(root);
    }
}

// Reads the dictionary file and stores words in the array
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    int count = 0;
    char word[256];
    while (fscanf(file, "%s", word) != EOF) {
        pInWords[count] = strdup(word);
        count++;
    }
    fclose(file);
    return count;
}

int main(void) {
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }

    struct Trie *pTrie = ((struct Trie*)malloc(sizeof(struct Trie)));
    pTrie = createTrie();
    
    for (int i = 0; i < numWords; i++) {
        printf("run num %d\n",i);
        insert(pTrie, inWords[i],0);
    }
    printf("anotherthigns");
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
