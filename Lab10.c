#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int ALPHA_SZ = 26;

struct Trie{
    struct Trie *child[26];
    int isEnd;
};

struct Trie* init(){
    return calloc(1, sizeof(struct Trie));
}

void insert(struct Trie **ppTrie, char *word){

    struct Trie *current = (*ppTrie);
    int len = strlen(word);
    char c;
    for(int i = 0; i < len; i++){
        c = word[i];
        if(current->child[c % 97] == NULL){
            current->child[c % 97] = (struct Trie*)calloc(1, sizeof(struct Trie));
        }
        current = current->child[c % 97];
    }
    current->isEnd++;

}
int numberOfOccurances(struct Trie *pTrie, char *word){
    struct Trie* current = pTrie;
    int count = 0, len = strlen(word);
    char c;

    for(int i = 0; i < len; i++){
        c = word[i];
        if(current->child[c % 97] == NULL){
            break;
        }
        current = current->child[c % 97];
    }
    if(current->isEnd){
        count++;
    }
    return count;
}

struct Trie *deallocateTrie(struct Trie *pTrie){

    for(int i = 0; i < ALPHA_SZ; i++){
        if((pTrie->child[i]) != NULL){
            (pTrie->child[i]) = deallocateTrie(pTrie->child[i]);
        }
    }
    free(pTrie);

}

int main(void)
{
    // read the number of the words in the dictionary
    //  parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    struct Trie* trie = init();

    for (int i = 0; i < 5; i++){
        insert(&trie, pWords[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    free(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");
    return 0;
}