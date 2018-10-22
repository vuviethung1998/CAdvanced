/*--------------------------------------------------------- */

typedef struct {
	char name[50];
	char reverseName[50];
} dataTypeBST;

typedef struct BSTNode {
	dataTypeBST data;
	struct BSTNode *parent;
	struct BSTNode *left;
	struct BSTNode *right;
} BSTNode;

/*-------the only change when data type change BEGIN---------------- */

int compare(dataTypeBST rootData, dataTypeBST data) {

	// if rootData more than data
	if (strcmp(rootData.reverseName, data.reverseName) > 0) {
		return(1);
	}
	else if (strcmp(rootData.reverseName, data.reverseName) == 0 ) {
		return(0);
	}
	
	return(-1);
}

void displayBSTNode(BSTNode *root) {

	printf("%s\n", root->data.name);
	return;
}

/*-------the only change when data type change END------------------ */
/*----------------------------------------------------------*/

BSTNode *makeNewBSTNode(dataTypeBST data) {

	BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));

	newNode->data = data;
	newNode->parent = NULL;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return(newNode);
}

void BST_init(BSTNode **root) {
	*root = NULL;
	return;
}

BSTNode *findMax(BSTNode *root)
{
    if (root == NULL) return(NULL);

    BSTNode *max = root;
    while (max->right != NULL)
        max = max->right;

    return(max);
}

BSTNode *findMin(BSTNode *root)
{
    if (root == NULL) return(NULL);

    BSTNode *min = root;
    while (min->left != NULL)
        min = min->left;

    return(min);
}

BSTNode *search(BSTNode *root, dataTypeBST data) {
	if (root == NULL) {
		return(NULL);
	}

	if (compare(root->data, data) == 0) return(root);
	
	if ( compare(root->data, data) == 1 )
		return( search(root->left, data) );
	else
		return( search(root->right, data) );
}

void insertBST(BSTNode **root, BSTNode *parent, dataTypeBST data) {
   
	if (*root == NULL) {

		BSTNode *newNode = makeNewBSTNode(data);
		newNode->parent = parent;
		*root = newNode;

		return;
	}

	if ( compare((*root)->data, data) == 1) {
		insertBST( &((*root)->left), *root, data);
	}
	else {
		insertBST( &((*root)->right), *root, data);
	}
	
}

/*------- del -------*/

void spliceOut(BSTNode *current_node) {
	
    // if the current node is leaf
    if (current_node->left == NULL && current_node->right == NULL) {
        if (current_node->parent->left == current_node)
            current_node->parent->left = NULL;
        else
            current_node->parent->right = NULL;
    }

	// if the current node has any child
	else if ( (current_node->left == NULL) || (current_node->right == NULL) ) {
		
		if (current_node->left != NULL) {
			if (current_node->parent->left == current_node)
                current_node->parent->left = current_node->left;
            else
                current_node->parent->right = current_node->left;
			
            current_node->left->parent = current_node->parent;
        }
        else {
            if (current_node->parent->left == current_node)
                current_node->parent->left = current_node->right;
            else
                current_node->parent->right = current_node->right;
			
            current_node->right->parent = current_node->parent;
        }
    }
	
    free(current_node);
	
    return;
}

BSTNode *findSuccessor(BSTNode *currentNode) {

	BSTNode *succ = NULL;
    if (currentNode->right != NULL) {
        succ = findMin(currentNode->right);
	}
   	else {
		
        if (currentNode->parent) {
			if (currentNode->parent->left == currentNode)
                succ = currentNode->parent;
            else {
                currentNode->parent->right = NULL;
                succ = findSuccessor(currentNode->parent);
                currentNode->parent->right = currentNode;
            }
        }
	}
	return(succ);
}
	
void del(BSTNode **root, dataTypeBST data) {

	// the tree is empty
	if (*root == NULL) {
		return;
	}
	else if ( compare((*root)->data, data) == 1 ) {
		del( &((*root)->left), data);
	}
	else if ( compare((*root)->data, data) == -1 ) {
		del( &((*root)->right), data);
	}
	else {
		BSTNode *delNode = *root;

		// case 1: node is a leaf (no descendants)
		if ((delNode->left == NULL) && (delNode->right == NULL)) {
			// if the delNode is a left child
			if (delNode->parent->left == delNode) {
				delNode->parent->left = NULL;
				free(delNode);
				printf("Node deld!\n");
				return;
			}

			// if the delNode is a right child
			else if (delNode->parent->right == delNode) {
				delNode->parent->right = NULL;
				free(delNode);
				printf("Node deld!\n");
				return;
			}
		}
		
		// case 2: node has one child
		else if ((delNode->left == NULL) || (delNode->right == NULL) ) {
			// if the delNode has left child
			if (delNode->left != NULL) {
				// if the delNode is a left child
				if (delNode->parent->left == delNode) {
					delNode->left->parent = delNode->parent;
					delNode->parent->left = delNode->left;
					free(delNode);
					printf("Node deld!\n");
					return;
				}
				
				// if the delNode is a right child
				else if (delNode->parent->right == delNode) {
					delNode->left->parent = delNode->parent;
					delNode->parent->right = delNode->left;
					free(delNode);
					printf("Node deld!\n");
					return;
				}
				// otherwise the delNode is the root
				else {
					delNode->data = delNode->left->data;
					delNode->left = delNode->left->left;
					delNode->right = delNode->left->right;
					free(delNode);
					printf("Node deld!\n");
				}
			}
			
			// if the delNode has right child
			else {
				// if the delNode is left child
				if (delNode->parent->left == delNode) {
					delNode->right->parent = delNode->parent;
					delNode->parent->left = delNode->right;
					free(delNode);
					printf("Node deld!\n");
					return;
				}
				
				// if the delNode is right child
				else if (delNode->parent->right == delNode) {
					delNode->right->parent = delNode->parent;
					delNode->parent->right = delNode->right;
					free(delNode);
					printf("Node deld!\n");
					return;
				}
				// otherwise the delNode is the root
				else {
					delNode->data = delNode->right->data;
					delNode->left = delNode->right->left;
					delNode->right = delNode->right->right;
					return;
				}
			}
		}
		
		// case 3: the delNode has both child
		else {
			BSTNode *succ = findSuccessor(delNode);
			delNode->data = succ->data;
			spliceOut(succ);
			printf("Node deld!\n");
		}
	}	
}
/*---del end-------- */
/*---------------------- tree traversal ----------------------------*/

void inorder(BSTNode *root) {

	if (root == NULL) return;

	inorder(root->left);
	displayBSTNode(root);
	inorder(root->right);
}

void postorder(BSTNode *root) {
	if (root == NULL) return;
	
	postorder(root->left);
	postorder(root->right);
	displayBSTNode(root);
}

void preorder(BSTNode *root) {
	if (root == NULL) return;

	displayBSTNode(root);
	preorder(root->left);
	preorder(root->right);
}

/*---------------------------------------------------------------------*/

