struct FileEntry{
	unsigned int FILE_FstClusLO;
	unsigned int FILE_Mode;
	struct FileEntry* next;
};

struct FileEntry *root = NULL;

int isFileOpen(const unsigned int clusterNum){
	struct FileEntry *temp = root;
	while(temp!=NULL){
		if(temp->FILE_FstClusLO==clusterNum){
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

void addFileEntry(const unsigned int clusterNum, char* mode){
	struct FileEntry* temp = calloc(1, sizeof(struct FileEntry));
	temp->FILE_FstClusLO = clusterNum;
	temp->FILE_Mode = 1;
	temp->next = NULL;
	if(root==NULL){
		root = temp;
	}
	else{
		struct FileEntry *itr = root;
		while(itr->next!=NULL){
			itr = itr->next;
		}
		itr->next = temp;
	}
}

void removeFileEntry(unsigned int clusterNum){
	struct FileEntry* itr1;
	struct FileEntry* itr2 = NULL;
	for (itr1 = root; itr1 != NULL; itr2 = itr1, itr1 = itr1->next) {
		if (itr1->FILE_FstClusLO == clusterNum) {
			if (itr2 == NULL) {
				root = itr1->next;
			}
			else {
				itr2->next = itr1->next;
			}
			free(itr1);
			return;
		}
	}
}
