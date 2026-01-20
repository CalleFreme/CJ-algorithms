#include <stdlib.h> // eller stddef.h
#include <stdio.h>

struct TreeNode {
	int value;
	struct TreeNode* left; // Varje nod har pekare till vänster och höger barn (om sådana finns)
	struct TreeNode* right;
};

struct Tree {
	struct TreeNode* root; // Ett träd definieras som en pekare till trädets rot-nod.
};

struct Tree createTree() {
	struct Tree tree;
	tree.root = NULL; // Initialize root to NULL. Från början är trädet tomt.
	return tree;
}

/* ---------- Hjälp: skapa nod ---------- */
struct TreeNode* createNode(int value) {
	// Allokera minne för en ny nod
	// Syntax: (type*)malloc(sizeof(type));
	// Varför type*? För att malloc returnerar en void*-pekare som vi måste casta om.
	// Castar vi inte, så vet inte kompilatorn vilken typ pekaren har.
    struct TreeNode* n = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (!n) {
		perror("malloc"); // perror skriver ut felmeddelande till stderr
		exit(1); // Avsluta programmet med felkod 1
    }
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

/* ---------- Enkel queue för TreeNode* (cirkulär buffer) ---------- */
struct Queue {
	// Vi använder en kö för BFS-traversal.
	struct TreeNode** data; // pekare till array av TreeNode*. D.v.s pekare till pekare = **.
    int capacity;
	int head;   // index för nästa pop. Anger var början av kön ligger.
	int tail;   // index för nästa push. Anger var slutet av kön ligger.
    int size;
};

struct Stack {
	// Vi kan använda en stack för DFS-traversal (preorder, inorder, postorder).
    struct TreeNode** data;
    int capacity;
	int top; // En stack behöver bara ett "top"-index för att veta var toppen av stacken är.
	int size;
};

struct Queue createQueue(int capacity) {
    struct Queue q;
	// Varför TreeNode**? För att vi vill lagra pekare till TreeNodes i kön.
    q.data = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * capacity);
    if (!q.data) {
        perror("malloc");
        exit(1);
    }
    q.capacity = capacity;
	q.head = 0; // Från början är både head och tail på 0.
    q.tail = 0;
    q.size = 0;
    return q;
}

void destroyQueue(struct Queue* q) {
	free(q->data); // Frigör minnet för arrayen
	q->data = NULL; // Undvik dangling pointer
    q->capacity = 0;
    q->head = q->tail = q->size = 0;
}

int isEmptyQueue(const struct Queue* q) {
    return q->size == 0;
}

void enqueue(struct Queue* q, struct TreeNode* node) {
    if (q->size == q->capacity) {
        fprintf(stderr, "Queue overflow: increase capacity.\n");
        exit(1);
    }
	q->data[q->tail] = node; // Den nya noden ska bli den nya svansen/tail. Längst bak i kön.
	q->tail = (q->tail + 1) % q->capacity; // Cirkulär hantering. Om vi når slutet, börja om från början.
    q->size++;
}

struct TreeNode* dequeue(struct Queue* q) {
    if (isEmptyQueue(q)) {
        return NULL;
    }
	struct TreeNode* node = q->data[q->head]; // Plocka fram noden som är längst fram i kön.
	q->head = (q->head + 1) % q->capacity; // Cirkulär hantering. Huvudet flyttas framåt.
    q->size--;
    return node;
}

/* ---------- BFS traversal: level-order print ---------- */
void printBfs(struct Tree* tree) {
	// En funktion som går igenom hela trädet på bredden och skriver ut värdena i noderna.
    if (tree->root == NULL) {
        return; // tomt träd
    }

    // Kapacitet: för demo räcker 64, men välj större om du har större träd.
	struct Queue q = createQueue(64); // Varför en två-potens? För enkel cirkulär hantering.

    enqueue(&q, tree->root);

    while (!isEmptyQueue(&q)) {
        struct TreeNode* current = dequeue(&q);
        printf("%d ", current->value);

        if (current->left != NULL) {
            enqueue(&q, current->left);
        }
        if (current->right != NULL) {
            enqueue(&q, current->right);
        }
    }

    destroyQueue(&q);
}

/* ---------- Frigör träd (postorder) ---------- */
void destroyTreeNodes(struct TreeNode* root) {
	// Frigör alla noder i trädet med postorder-traversal, rekursivt.
    // Utgår från en root node.
    if (root == NULL) return;
	destroyTreeNodes(root->left); // Först vänster subträd
	destroyTreeNodes(root->right); // Sedan höger subträd
	free(root); // Frigör noden själv
}

int main() {
    struct Tree myTree = createTree();

    /*
        Bygg ett litet träd (inte nödvändigtvis BST):
                8
              /   \
             3     10
            / \      \
           1   6      14
    */
    myTree.root = createNode(8);
    myTree.root->left = createNode(3);
    myTree.root->right = createNode(10);
    myTree.root->left->left = createNode(1);
    myTree.root->left->right = createNode(6);
    myTree.root->right->right = createNode(14);
	// Hur skulle vi kunna lägga till fler noder? Skriv en insert-funktion!
	// Kan vi använda en loop för att skapa ett större träd?
	// Ja, genom att använda en insert-funktion som sätter in noder på rätt plats, givet en array av värden.

    // Breadth-first traversal (level-order):
    printf("BFS: ");
    printBfs(&myTree);
    printf("\n");

    destroyTreeNodes(myTree.root);
    myTree.root = 0;

    return 0;
}