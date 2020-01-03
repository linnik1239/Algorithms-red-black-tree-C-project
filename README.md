# Algorithms red-black tree C project

The name on the main file for running is Kmin.c
This project is written in C language.
I used data structure binary search tree red-black because of the project requirements to contain maximum k inner nodes for keeping memory management complexity to be O(K).
There are 3 arrays with the sizes 200,400,800.
While we are running on array elements, for each element we are using the function 'insert'.
If the number of elements is less than k then for each element of array allocated dynamically the node, after insertion the INSERTFIXUP if it's needed, the run time complexity for each of these operations is O(log k).

If at present the number of elements is exactly k and we are trying to insert the new element then if the new element if bigger than the maximal element in the dataset then the new element is not inserted, else the maximal element is deleted according to and the new element is inserted according to INSERTFIXUP.
Each of these actions is taken run time complexity O(log k) for keeping the red-black tree to be balanced.

The printing action of k sorted minimal elements is done by function printkMin() on pre-order traversal.
This tree is balanced what makes the run time complexity of this operation to be O(k).


There is makefile for making compilation in Ubuntu.

