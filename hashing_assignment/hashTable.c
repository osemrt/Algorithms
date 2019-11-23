#include "header_files/declarations.h"

void ht_create(int size) {

	hashTable = (HashTable*)createArrayFromHeap(HASH_TABLE, 1);
	hashTable->arr = (Entry*)createArrayFromHeap(ENTRY, size);
	hashTable->size = size;

	for (int i = 0; i < hashTable->size; i++) {
		hashTable->arr[i].status = EMPTY;
		hashTable->arr[i].hashNode = (HashNode*)createArrayFromHeap(HASH_NODE, 1);
	}

}

int ht_put(FILE* fp1, unsigned long int key, Entry* entry) {

	int i = 0;
	int index = hash(key, i);
	Entry currentEntry = hashTable->arr[index];


	while (currentEntry.status == OCCUPIED) {

		char* filePath = currentEntry.hashNode->filePath;
		FILE* fp2 = fopen(filePath, "r");
		if (fp2 == NULL) {
			printf("%s could not be added to the table...\n", filePath);
			return -1;
		}
		else {

			if (compareFiles(fp1, fp2) == FALSE) {
				i++;
				index = hash(key, i);
				currentEntry = hashTable->arr[index];
				fclose(fp2);
			}
			else {
				fclose(fp2);
				char* newFileName = entry->hashNode->fileName;
				char* currentFileName= currentEntry.hashNode->fileName;
				printf("\n\"%s\" was already added as \"%s\"...\n", newFileName, currentFileName);
				return SAME;
			}
			
		}
	}

	if (currentEntry.status == EMPTY) {
		hashTable->arr[index] = *entry;
		return index;
	}

	//TODO: is there any other situation?


}


void ht_print() {

	if (hashTable != NULL) {
		printf("\nPrinting hashTable...\n");
		int i;
		for (i = 0; i < hashTable->size; i++) {
			if (hashTable->arr[i].status == OCCUPIED) {
				printf("%d: (%s)\n", i, hashTable->arr[i].hashNode->fileName);
			}
			else if (hashTable->arr[i].status == EMPTY) {
				printf("%d: %s\n", i, "");
			}
			else {
				printf("%d: %s\n", i, "DELETED!");
			}
		}

	}
	else {
		printf("HashTable is not created yet!\n");
	}

	


}











