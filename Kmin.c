/*  Student name: Teodor Linnik */
/*  Student ID: 312728017       */
/*  Student name: Amiel Ferman */
/*  Student ID: 302440466       */


/*         Explanation of the project       */
/* As required I used for maintain the lowest K elements the "red black tree", as required the complexy of insertion is*/
/* theta(log k). If number of current elements are less than k, the  new elements will be inserting anyway and will be making */
/* the "fixup" after inserting, all this algoritms are taking  theta(log k) as we studied. If num of elements in tree are k*/
/* then if the key of new nude is larger than the nude with maximun key, so this nude will not be inserted, else, the current nude*/
/* with maximum key will be deleted and the tree will be fixed up all this algoritms are taking  theta(log k) as we studied*/
/* and then the new nude will be inserted all this algoritms are taking  theta(log k) as we studied and the ney nude with maximum key*/
/* will be found, this also will be taken theta(log k) complexity. This mean that all algorithm of insertion take theta(log k) complexity.*/

/* After every checking point the k lowest elements will printed sorted the complexity of this is Theta(K) because in tree are */
/* k inner nudes.*/






#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct RBTree *createNode();
struct RBTree *createExterior();
struct RBTree *insert(struct RBTree *T, int key, int k, int reset);
struct RBTree *leftRotate(struct RBTree *T, struct RBTree *x);
struct RBTree *rightRotate(struct RBTree *T, struct RBTree *x);
struct RBTree *RBInsertFixup(struct RBTree *T, struct RBTree *z);
struct RBTree *RBinsert(struct RBTree *T, struct RBTree *newNode);
struct RBTree *TreeMinimum( struct RBTree *x);
struct RBTree *TreeMaximum(struct RBTree *x);
struct RBTree *TreeSuccessor(struct RBTree *x);
struct RBTree *RBdelete(struct RBTree *T, struct RBTree *z);
struct RBTree *RBDeleteFixup(struct RBTree *T, struct RBTree *x);
void deleteNode(struct RBTree *x);
void ArrInput(int *Arr, int n, struct RBTree *T);
void ArrInputK(int *Arr, int n, struct RBTree *T, int k);
void deleteAllTree(struct RBTree *T);
void printKmin(struct RBTree *T);



typedef struct RBTree {  /*Struct for nude*/
	char color;   /* Color, 'R' is red and 'B' is black*/
	int key;      /*Key for nude*/
	char type;    /* this mean if this nude is inner 'I' or exterior (NULL) intersection 'N'*/
	struct RBTree *father;   /*Pointers to the left, right son or to the father.*/
	struct RBTree *left;
	struct RBTree *right;
}RBTree;


typedef struct maxPtr {   /*Struct for pointing to the max nude among per k lowest elements and a value for for local max.*/
	int value; 
	struct RBTree *node;
}maxPtr;


int main() {
	int A[200];  /*The arrays*/
	int B[400];
	int C[800];
	struct RBTree *T; /* RB tree for storing the data of k lowest elements.*/

	T = NULL;
	ArrInput(A, 200, T);
	ArrInput(B, 400, T);
	ArrInput(C, 800, T);

	getchar();
        return 0;

}



struct RBTree *createExterior() {  /*Creating the exterior (NULL) nude*/
	struct RBTree *node;
	node = (struct RBTree*)malloc(sizeof(RBTree));
	node->color = 'B';
	node->type = 'N';
	node->left = NULL;
	node->right = NULL;
	node->father = NULL;
	return node;
}

struct RBTree *createNode() { /*Creating inner nude.*/
	struct RBTree *node;
	node = (struct RBTree*)malloc(sizeof(RBTree));
	node->color = 'R';
	node->type = 'I';
	node->left = NULL;
	node->right = NULL;
	node->father = NULL;

	return node;
}

struct RBTree *insert(struct RBTree *T, int key,int k,int reset) { /*Insert element to the tree if element lower than current max or if num of elements are less than k*/
	static maxPtr maxPtr;      /*Pointer to te max nude on the tree .Must be static for insertion*/
	static int numElements=0;  /*current number of elements in tree.Must be static for insertion*/
	struct RBTree *newNode;
	struct RBTree *anchor;
	if (reset) { /*needed if I use new tree and inserting elements again.*/
		numElements = 0;
		maxPtr.node = NULL;
		maxPtr.value = -1;

	}
	if (numElements < k) {  /*If num of elements is less than k*/
		++numElements;
		newNode = createNode();
		if (key > maxPtr.value) {
			maxPtr.node = newNode;
			maxPtr.value = key;
		}
		newNode->key = key;
		T = RBinsert(T, newNode);
	}
	else {
		if (key < maxPtr.value) {  /*If num of elemens is equall to k and current elements is under current max elements so this current max element must be deleted and new element must be inserted instread.*/
			newNode = createNode();
			newNode->key = key;
			anchor = maxPtr.node;
			T = RBdelete(T,anchor);
			T = RBinsert(T, newNode);
			maxPtr.node = TreeMaximum(T);
			maxPtr.value = maxPtr.node->key;
			
		}
	}
	return T;
}



struct RBTree *RBinsert(struct RBTree *T, struct RBTree *newNode) {  /*Insertion to the red black tree.*/
	struct RBTree *x, *y;
	y = NULL;
	x = T;
	if (x == NULL) {
		T = newNode;
		T->color = 'B';
		T->father = NULL;
		T->left = createExterior();
		T->left->father = T;
		T->right = createExterior();
		T->right->father = T;
		return T;
	}
	while (x->type != 'N') {
		y = x;
		if (newNode->key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
		if (newNode->key < y->key) {
			free(y->left);
			y->left = NULL;
			y->left = newNode;
			newNode->father = y;
		}
		else {
			free(y->right);
			y->right = NULL;
			y->right = newNode;
			newNode->father = y;
		}
	newNode->left = createExterior();
	newNode->left->father = newNode;
	newNode->right = createExterior();
	newNode->right->father = newNode;
	newNode->color = 'R';

	T = RBInsertFixup(T, newNode);
	return T;

}


struct RBTree *leftRotate(struct RBTree *T, struct RBTree *x) { /*Left rotation*/
	struct RBTree *y, *z;
	y = x->right;
	z = x->father;
	x->right = y->left;
	if (y->left->type != 'N') {
		y->left->father = x;
	}
	y->left = x;
	x->father = y;
	y->father = z;
	if (z==NULL || z->type == 'N') {
		T = y;
	}
	else
	{
		if (z->left == x) {
			z->left = y;
		}
		else {
			z->right = y;
		}
	}
	return T;

}
struct RBTree *rightRotate(struct RBTree *T, struct RBTree *x) { /*Right rotation*/
	struct RBTree *y, *z;
	y = x->left;
	z = x->father;
	x->left = y->right;
	if (y->right->type != 'N') {
		y->right->father = x;
	}
	y->right = x;
	x->father = y;
	y->father = z;
	if (z == NULL || z->type == 'N') {
		T = y;
	}
	else
	{
		if (z->right == x) {
			z->right = y;
		}
		else {
			z->left = y;
		}
	}
	return T;

}

struct RBTree *RBInsertFixup(struct RBTree *T, struct RBTree *z) { /*Rb ibsert fixup*/
	struct RBTree *y;

	while (z->father != NULL && z->father->father != NULL && z->father->color == 'R') {



		if (z->father->father->left != NULL && z->father == z->father->father->left) {
			y = z->father->father->right;

			if (y->type != 'N' && y->color == 'R') {
				z->father->color = 'B';
				y->color = 'B';
				z->father->father->color = 'R';
				z = z->father->father;
			}
			else {
				if (z == z->father->right) {
					T = leftRotate(T, z->father);
					z = z->left;
				}
				z->father->color = 'B';
				z->father->father->color = 'R';
				T = rightRotate(T, z->father->father);
			}
		}
		else {
			y = z->father->father->left;

			if (y->type!= 'N' && y->color == 'R') {
				z->father->color = 'B';
				y->color = 'B';
				z->father->father->color = 'R';
				z = z->father->father;
			}
			else {
				if (z == z->father->left) {
					T = rightRotate(T, z->father);
					z = z->right;;
				}
				z->father->color = 'B';
				z->father->father->color = 'R';
				T = leftRotate(T, z->father->father);
			}
		}
	}
	T->color = 'B';
	return T;
}

struct RBTree *TreeMinimum(struct RBTree *x) {  /*The nude with min key in tree*/
	if (x->type == 'N') {
		return NULL;
	}
	while (x->left->type != 'N') {
		x = x->left;
	}
	return x;
}
struct RBTree *TreeMaximum(struct RBTree *x) {/*The nude with max key in tree*/
	if (x->type == 'N') {
		return NULL;
	}
	while (x->right->type != 'N') {
		x = x->right;
	}
	return x;
}

struct RBTree *TreeSuccessor(struct RBTree *x) { /* The TreeSuccessor in tree*/
	struct RBTree *y;
	if (x == NULL || x->type == 'N') {
		return NULL;
	}
	if (x->right->type != 'N') {
		return TreeMinimum(x->right);
	}
	y = x->father;
	while (y->type != 'N' && x == y->right) {
		x = y;
		y = y->father;
	}
	return y;
}

struct RBTree *RBdelete(struct RBTree *T, struct RBTree *z) { /*Delete node from RB tree*/
	struct RBTree *y,*x;


	if (z->left->type == 'N' || z->right->type == 'N') {
		y = z;
	}
	else {
		y = TreeSuccessor(T);
	}
	

	if (y->left->type != 'N') {
		x = y->left;
		deleteNode(y->right);
	}
	else {
		x = y->right;
		deleteNode(y->left);
	}
	x->father = y->father; 
	
	if (y->father == NULL) {
		T = x;
	}
	else {
		if (y == y->father->left) {
			y->father->left = x;
		}
		else {
			y->father->right = x;
		}
	}
	if (y != x) {
		z->key = y->key;
	}
	if (y->color == 'B') {
		T = RBDeleteFixup(T, x);
	}
	deleteNode(y);
	return T;
}

struct RBTree *RBDeleteFixup(struct RBTree *T, struct RBTree *x) { /*Fixup after deleted nude from RB tree.*/
	struct RBTree * w;

	while ((x->color=='B') && (T != x)) {
		if (x == x->father->left) {
			w = x->father->right;
			if (w->color=='R') {
				w->color='B';
				x->father->color = 'R';
				T = leftRotate(T, x->father);
				w = x->father->right;
			}
			if ((w->right->color=='B') && (w->left->color == 'B')) {
				w->color='R';
				x = x->father;
			}
			else {
				if (w->right->color=='B') {
					w->left->color = 'B';
					w->color = 'R';
					T=rightRotate(T, w);
					w = x->father->right;
				}
				w->color =x->father->color;
				x->father->color='B';
				w->right->color='B';
				T = leftRotate(T, x->father);
				x = T; 
			}
		}
		else { 
			w = x->father->left;
			if (w->color=='R') {
				w->color = 'B';
				x->father->color = 'R';
				T = rightRotate(T, x->father);
				w = x->father->left;
			}
			if ((w->right->color == 'B') && (w->left->color == 'B')) {
				w->color = 'R';
				x = x->father;
			}
			else {
				if (w->left->color =='B') {
					w->right->color = 'B';
					w->color = 'R';
					T = leftRotate(T, w);
					w = x->father->left;
				}
				w->color = x->father->color;
				x->father->color = 'B';
				w->left->color= 'B';
				T = rightRotate(T, x->father);
				x = T; 
			}
		}
	}
	x->color = 'B';
	return T;



}
void deleteNode(struct RBTree *x) {  /*Deleting nude from tree*/
	x->father = NULL;  
	x->left = NULL;
	x->right = NULL;
	free(x);
	x = NULL;
}

void deleteAllTree(struct RBTree *T) {  /*Delete all nudes in tree and releasing the memory.*/
	if (T != NULL) {
		deleteAllTree(T->left);
		deleteAllTree(T->right);
		deleteNode(T);

	}
}


void ArrInput(int *Arr, int n,struct RBTree *T) { /*for input per n , n=200,400,800*/
	ArrInputK(Arr, n, T, 10); /*K = 10*/
	ArrInputK(Arr, n, T, 50); /*K = 50*/
	ArrInputK(Arr, n, T, 100);/*K = 100*/
}

void ArrInputK(int *Arr, int n, struct RBTree *T, int k) {
	int i;
	int n1 = n / 4;  /*Checking points*/
	int n2 = n / 2;
	int n3 = 3*(n / 4);
        T = NULL;
	Arr[0] = (rand() % 1024);
	T = insert(T, Arr[0], 10, 1);  /*For making reset and the static variables in function when we use new array.*/
	for (i = 1; i <= n1; ++i) {
		Arr[i] = (rand() % 1024);
		T = insert(T, Arr[i], k, 0);
	}
	/*First checking point*/
	printf("n = %d, k = %-3d ,n1 = %-3d \n\n",n,k,n1 );
	printKmin(T);
	printf("\n\n");

	for (i = (n1+1); i <= n2; ++i) {
		Arr[i] = (rand() % 1024);
		T = insert(T, Arr[i], k, 0);
	}
	/*Second checking point*/
	printf("n = %d, k = %-3d ,n2 = %-3d \n\n", n, k, n2);
	printKmin(T);
	printf("\n\n");
	for (i = (n2 + 1); i <= n3; ++i) {
		Arr[i] = (rand() % 1024);
		T = insert(T, Arr[i], k, 0);
	}
	/*Third checking point*/
	printf("n = %d, k = %-3d ,n3 = %-3d \n\n", n, k, n3);
	printKmin(T);
	printf("\n\n");
	for (i = (n3 + 1); i < n; ++i) {
		Arr[i] = (rand() % 1024);
		T = insert(T, Arr[i], k, 0);
	}

	/*Reliasing the memory of tree*/
	deleteAllTree(T);
}


void printKmin(struct RBTree *T) {  /*Printing sorted min k elements, complexity of time is Theta(K) because there are maximun k inner nudes in tree.*/
	if (T != NULL && T->type != 'N') {
		printKmin(T->left);
		printf("%4d| ", T->key);
		printKmin(T->right);

	}
}
