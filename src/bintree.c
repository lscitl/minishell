/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bintree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:07:31 by seseo             #+#    #+#             */
/*   Updated: 2022/06/14 19:34:22 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bintree.h"

BinTree	*makeBinTree(BinTreeNode rootNode)
{
	BinTree		*pBinTree;
	BinTreeNode	*pRootNode;

	pBinTree = malloc(sizeof(BinTree));
	if (pBinTree == NULL)
		return (NULL);
	pRootNode = malloc(sizeof(BinTreeNode));
	if (pRootNode == NULL)
	{
		free(pBinTree);
		return (NULL);
	}
	*pRootNode = rootNode;
	pRootNode->pLeftChild = NULL;
	pRootNode->pRightChild = NULL;
	pBinTree->pRootNode = pRootNode;
	return (pBinTree);
}

BinTreeNode	*getRootNodeBT(BinTree *pBinTree)
{
	if (pBinTree != NULL)
		return (pBinTree->pRootNode);
	return (NULL);
}

BinTreeNode	*insertLeftChildNodeBT(BinTreeNode *pParentNode, BinTreeNode element)
{
	BinTreeNode	*pChildNode;

	if (pParentNode->pLeftChild != NULL)
		return (NULL);
	pChildNode = malloc(sizeof(BinTreeNode));
	if (pChildNode == NULL)
		return (NULL);
	*pChildNode = element;
	pChildNode->pLeftChild = NULL;
	pChildNode->pRightChild = NULL;
	pParentNode->pLeftChild = pChildNode;
	return (pChildNode);
}

BinTreeNode	*insertRightChildNodeBT(BinTreeNode *pParentNode, BinTreeNode element)
{
	BinTreeNode	*pChildNode;

	if (pParentNode->pRightChild != NULL)
		return (NULL);
	pChildNode = malloc(sizeof(BinTreeNode));
	if (pChildNode == NULL)
		return (NULL);
	*pChildNode = element;
	pChildNode->pLeftChild = NULL;
	pChildNode->pRightChild = NULL;
	pParentNode->pRightChild = pChildNode;
	return (pChildNode);
}

BinTreeNode	*getLeftChildNodeBT(BinTreeNode *pNode)
{
	if (pNode == NULL)
		return (NULL);
	return (pNode->pLeftChild);
}

BinTreeNode	*getRightChildNodeBT(BinTreeNode *pNode)
{
	if (pNode == NULL)
		return (NULL);
	return (pNode->pRightChild);
}

void	deleteBinTree(BinTree *pBinTree)
{
	deleteBinTreeNode(getRootNodeBT(pBinTree));
	free(pBinTree);
}

void	deleteBinTreeNode(BinTreeNode *pNode)
{
	if (pNode == NULL)
		return ;
	deleteBinTreeNode(pNode->pLeftChild);
	deleteBinTreeNode(pNode->pRightChild);
	free(pNode);
}

void	preorderTraversalBinTree(BinTreeNode *pParentNode)
{
	if (pParentNode == NULL)
		return ;
	printf("%c ", pParentNode->data);
	preorderTraversalBinTree(pParentNode->pLeftChild);
	preorderTraversalBinTree(pParentNode->pRightChild);
}

void	inorderTraversalBinTree(BinTreeNode *pParentNode)
{
	if (pParentNode == NULL)
		return ;
	inorderTraversalBinTree(pParentNode->pLeftChild);
	printf("%c ", pParentNode->data);
	inorderTraversalBinTree(pParentNode->pRightChild);
}

void	postorderTraversalBinTree(BinTreeNode *pParentNode)
{
	if (pParentNode == NULL)
		return ;
	postorderTraversalBinTree(pParentNode->pLeftChild);
	postorderTraversalBinTree(pParentNode->pRightChild);
	printf("%c ", pParentNode->data);
}

static BinTreeNode	*preorderSearch(BinTreeNode *pParentNode, char c)
{
	BinTreeNode	*pReturnNode = NULL;

	if (pParentNode == NULL)
		return (NULL);
	if (pParentNode->data == c)
		pReturnNode = pParentNode;
	if (pReturnNode == NULL)
		pReturnNode = preorderSearch(pParentNode->pLeftChild, c);
	if (pReturnNode == NULL)
		pReturnNode = preorderSearch(pParentNode->pRightChild, c);
	return (pReturnNode);
}

BinTreeNode	*searchBinTreeNode(BinTree *pBinTree, char c)
{
	return (preorderSearch(getRootNodeBT(pBinTree), c));
}
