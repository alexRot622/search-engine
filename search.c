#include <math.h>
#include "search.h"

int searchDir(invertedIndex *index, char *dirname)
{
    struct dirent *entry;
    static char filepath[BUF_SIZE];
    float idf, tf;
    DIR *dir;
    size_t noFile;

    dir = opendir(dirname);
    if(dir == NULL) {
        return -1;
    }
    memset(filepath, 0, BUF_SIZE);
    noFile = 0;
    
    while((entry = readdir(dir))) {
        strcat(filepath, dirname);
        if(filepath[strlen(filepath) - 1] != '/') {
            strcat(filepath, "/");
        }
        strcat(filepath, entry->d_name);
        if(entry->d_type == DT_REG) {
            index->filenames[noFile] = strdup(entry->d_name);
            if(index->filenames[noFile] == NULL) {
                for(size_t i = 0; i < noFile; i++) {
                    free(index->filenames[i]);
                }
                free(index->filenames);
                closedir(dir);
                return -1;
            }
            for(size_t i = 0; i < index->noTerms; i++) {
                if((tf = searchFile(index->terms[i], filepath))) {
                    SET_BIT(index->found[i], noFile);
                    index->tfidf[i][noFile] = tf;
                }
            }
            noFile++;
        }
        memset(filepath, 0, BUF_SIZE);
    }
    closedir(dir);
    for(size_t i = 0; i < index->noTerms; i++) {
        idf = 0;
        for(size_t j = 0; j < index->noFiles; j++) {
            idf += GET_BIT(index->found[i], j);
        }
        if(idf != 0) {
            idf = log2f(1 + index->noFiles / idf);
        }
        for(size_t j = 0; j < index->noFiles; j++) {
            index->tfidf[i][j] *= idf;    
        }
    }
    return 0;
}

float searchFile(char *str, char *filename)
{
    static const char separators[] = {" \n\t"};
    static char buf[BUF_SIZE];
    char *tok;
    float found = 0, terms = 0;
    FILE *inFile;

    inFile = fopen(filename, "r");
    if(inFile == NULL) {
        fprintf(stderr, "ERROR: Could not open file \"%s\"\n", filename);
        return -1;
    }
    memset(buf, '\0', BUF_SIZE);
    while(fread(buf, sizeof(char), BUF_SIZE, inFile)) {
        for(tok = strtok(buf, separators); tok; tok = strtok(NULL, separators)) {
            if(strcasecmp(str, tok) == 0) {
                found++;
            }
            terms++;
        }
        memset(buf, '\0', BUF_SIZE);
    }
    fclose(inFile);
    return found / terms;
}

char **getTerms(char *str, size_t *len)
{
    static const char *operators = "()!&| \n";
    char *tok, *temp, **terms, **newTerms;

    terms = (char **) malloc(MAX_TERMS * sizeof(char *));
    temp = strdup(str);
    if(temp == NULL) {
        printf("ERROR: could not allocate memory\n");
        return NULL;
    }
    *len = 0;
    for(tok = strtok(temp, operators); tok; tok = strtok(NULL, operators)) {
        terms[*len] = strdup(tok);
        if(terms[*len] == NULL) {
            printf("ERROR: could not allocate memory\n");
            for(size_t i = 0; i <= *len; i++) {
                free(terms[i]);
            }
            free(terms);
            free(temp);
            return NULL;
        }
        (*len)++;
    }
    /* reallocate the terms array so as to only have "len" elements */
    newTerms = realloc(terms, (*len) * sizeof(char *));
    if(newTerms == NULL) {
            printf("ERROR: could not allocate memory\n");
            for(size_t i = 0; i <= *len; i++) {
                free(terms[i]);
            }
            free(terms);
            free(temp);
            return NULL;
    }
    terms = newTerms;
    free(temp);
    return terms;
}

size_t countFiles(char *dirname)
{
    struct dirent *entry;
    DIR *dir;
    size_t count = 0;

    dir = opendir(dirname);
    if(dir == NULL) {
        exit(-1);
    }
    while((entry = readdir(dir))) {
        if(entry->d_type == DT_REG) {
            count++;
        }
    }
    closedir(dir);
    return count;
}
