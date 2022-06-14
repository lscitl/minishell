#ifndef _BIN_TREE_
# define _BIN_TREE_

# include <stdio.h>
# include <stdlib.h>

typedef struct	BinTreeNodeType
{
	int						visited;
	char					data;
	struct BinTreeNodeType	*pLeftChild;
	struct BinTreeNodeType	*pRightChild;
}	BinTreeNode;

typedef struct	BinTreeType
{
	struct BinTreeNodeType	*pRootNode;
}	BinTree;

BinTree		*makeBinTree(BinTreeNode rootNode);
BinTreeNode	*getRootNodeBT(BinTree *pBinTree);
BinTreeNode	*insertLeftChildNodeBT(BinTreeNode *pParentNode, BinTreeNode element);
BinTreeNode	*insertRightChildNodeBT(BinTreeNode *pParentNode, BinTreeNode element);
BinTreeNode	*getLeftChildNodeBT(BinTreeNode *pNode);
BinTreeNode	*getRightChildNodeBT(BinTreeNode *pNode);
void		deleteBinTree(BinTree *pBinTree);
void		deleteBinTreeNode(BinTreeNode *pNode);

void		preorderTraversalBinTree(BinTreeNode *pParentNode);
void		inorderTraversalBinTree(BinTreeNode *pParentNode);
void		postorderTraversalBinTree(BinTreeNode *pParentNode);

void		preorderTraversalBinTreeIter(BinTreeNode *pParentNode);
void		inorderTraversalBinTreeIter(BinTreeNode *pParentNode);
void		postorderTraversalBinTreeIter(BinTreeNode *pParentNode);

int			getMaxLevel(BinTree *pBinTree);
int 		getMaxLevelRec(BinTree *pBinTree);

void		printBinTree(BinTree *pBinTree);

BinTreeNode	*searchBinTreeNode(BinTree *pBinTree, char c);

#endif

#ifndef _COMMON_TREE_DEF_
# define _COMMON_TREE_DEF_

# define TRUE		1
# define FALSE		0

#endif
