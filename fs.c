#include <stdio.h>
#include <stdlib.h>
#define MAX 50
int memory[MAX]; 
void initMemory() {
    for (int i = 0; i < MAX; i++) memory[i] = 0;
}
void printMemory() {
    for (int i = 0; i < MAX; i++) printf("%d", memory[i]);
    printf("\n");
}
void sequentialAllocation(int start, int length) {
    if (start < 0 || start + length > MAX) {
        printf("Error: Not enough space.\n"); return;
    }
    for (int i = start; i < start + length; i++)
        if (memory[i]) { printf("Error: Block %d occupied.\n", i); return; }
    for (int i = start; i < start + length; i++) memory[i] = 1;
    printf("Sequential: %d to %d allocated.\n", start, start + length - 1);
    printMemory();
}
void indexedAllocation(int indexBlock, int n, int blocks[]) {
    if (memory[indexBlock]) { printf("Error: Index block occupied.\n"); return; }
    for (int i = 0; i < n; i++)
        if (memory[blocks[i]]) { printf("Error: Block %d occupied.\n", blocks[i]); return; }
    memory[indexBlock] = 1;
    for (int i = 0; i < n; i++) memory[blocks[i]] = 1;
    printf("Indexed: Index %d → ", indexBlock);
    for (int i = 0; i < n; i++) printf("%d ", blocks[i]);
    printf("\n");
    printMemory();
}
void linkedAllocation(int n, int blocks[]) {
    for (int i = 0; i < n; i++)
        if (memory[blocks[i]]) { printf("Error: Block %d occupied.\n", blocks[i]); return; }
    for (int i = 0; i < n; i++) memory[blocks[i]] = 1;
    printf("Linked: ");
    for (int i = 0; i < n; i++) {
        printf("%d", blocks[i]);
        if (i < n - 1) printf(" -> ");
    }
    printf("\n");
    printMemory();
}
int main() {
    initMemory();
    int choice;
    while (1) {
        printf("\nMenu:\n1. Sequential\n2. Indexed\n3. Linked\n4. Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            int start, length;
            printf("Enter start block & length: ");
            scanf("%d %d", &start, &length);
            sequentialAllocation(start, length);
        }
        else if (choice == 2) {
            int indexBlock, n;
            printf("Enter index block: "); scanf("%d", &indexBlock);
            printf("Enter no. of blocks: "); scanf("%d", &n);
            int blocks[n];
            printf("Enter %d blocks: ", n);
            for (int i = 0; i < n; i++) scanf("%d", &blocks[i]);
            indexedAllocation(indexBlock, n, blocks);
        }
        else if (choice == 3) {
            int n;
            printf("Enter no. of blocks: "); scanf("%d", &n);
            int blocks[n];
            printf("Enter %d blocks: ", n);
            for (int i = 0; i < n; i++) scanf("%d", &blocks[i]);
            linkedAllocation(n, blocks);
        }
        else if (choice == 4) {
            printf("Exiting...\n"); break;
        }
        else printf("Invalid choice!\n");
    }
    return 0;
}