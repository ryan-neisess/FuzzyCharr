//source for lab 4 tests and aux

#include "lab4test.h"

//list visualization.  prints out targetList to console
void printList(ListNode * targetList) {
	ListNode * pCurr = targetList;
	
	printf("Current List Contents:\n");
	while (pCurr != NULL) {
		printf("%d -> ", pCurr->data);
		pCurr = pCurr->pNext;
	}
	printf("NULL\n\n");
}

//wrapper for the merge lists function test
void task4wrapper(void) {
	printf("  **Testing mergeList (task 4)...\n\n");
	ListNode * arrLists[5] = { NULL };
	insertAtFront(&arrLists[0], 2);
	insertAtFront(&arrLists[0], 3);
	insertAtFront(&arrLists[0], 5);
	insertAtFront(&arrLists[0], 6);
	insertAtFront(&arrLists[0], 9);
	insertAtFront(&arrLists[2], 8);
	insertAtFront(&arrLists[3], 1);
	insertAtFront(&arrLists[4], 4);
	insertAtFront(&arrLists[4], 7);

	printf("Initial List Configuration***\n\n");
	for (int i = 0; i < 5; i++) {
		printf("List %d\n", i);
		printList(arrLists[i]);
	}

	ListNode * mergedList = mergeLists(arrLists, 5);

	printf("Merged List\n");
	printList(mergedList);

	//free memory
	for (int i = 0; i < 5; i++) {
		deleteList(&arrLists[i]);
	}
	deleteList(&mergedList);

	system("pause");
}

//wrapper for the detect cycle function test
void task5wrapper(void) {
	printf("  **Testing cycle detection (task 5)...\n\n");
	
	int numTestsFailed = 0;
	ListNode * testList = NULL;


	insertAtFront(&testList, 5);
	insertAtFront(&testList, 3);
	insertAtFront(&testList, 8);
	insertAtFront(&testList, 11);
	insertAtFront(&testList, 2);
	insertAtFront(&testList, 9);

	printf("  -Testing for list with no cycle...  ");
	if (detectCycle(testList)) {
		printf("FAILED\n");
		numTestsFailed++;
	}
	else {
		printf("PASSED\n");
	}

	//now making the next to last element point to itself
	printf("  -Testing for single element cycle...  ");
	ListNode * pCurr = testList;
	for (int i = 0; i < 4; i++) {
		pCurr = pCurr->pNext;
	}
	ListNode * pTemp = pCurr->pNext;
	pCurr->pNext = pCurr;

	if (detectCycle(testList)) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
		numTestsFailed++;
	}
	//clear the portion of the list that is "lost" from memory
	free(pTemp);

	//now making the fourth element point to the first one
	printf("  -Testing for multiple element cycle...  ");
	pCurr = testList;
	for (int i = 0; i < 3; i++) {
		pCurr = pCurr->pNext;
	}
	pTemp = pCurr;
	pCurr->pNext = testList;
	if (detectCycle(testList)) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
		numTestsFailed++;
	}
	//pTemp is still at the original "end" of the list
	//before it loops back to the "beginning"
	pTemp->pNext = NULL;
	//now list is no longer circular and can be deleted
	free(testList);
	printf("\n");
	if (numTestsFailed == 0) {
		printf("ALL cycle detection TESTS PASSED\n\n");
	}
	else {
		printf("Cycle detection TESTS FAILED\n\n");
	}
	system("pause");
}

//wrapper for the reversing list function test
void task6wrapper(void) {
	printf("  **Testing list reversal (task 6)...\n\n");

	ListNode * testList = NULL;
	printf("Testing reversal of empty list:\n");
	printList(testList);
	printf("Reversing list...\n");
	reverseList(&testList);
	printList(testList);
	printf("\n");
	
	printf("Testing reversal of list with one element:\n");
	insertAtFront(&testList, 5);
	printList(testList);
	printf("Reversing list...\n");
	reverseList(&testList);
	printList(testList);
	printf("\n");

	printf("Testing reversal of list with two elements:\n");
	insertAtFront(&testList, 8);
	printList(testList);
	printf("Reversing list...\n");
	reverseList(&testList);
	printList(testList);
	printf("\n");

	printf("Testing reversal of list with multiple elements:\n");
	insertAtFront(&testList, 2);
	insertAtFront(&testList, 3);
	insertAtFront(&testList, 7);
	printList(testList);
	printf("Reversing list...\n");
	reverseList(&testList);
	printList(testList);
	printf("\n");
	system("pause");
}