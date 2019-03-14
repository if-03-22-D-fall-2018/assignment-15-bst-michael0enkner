/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			bst.cpp
 * Author(s):		Peter Bauer
 * Due Date:		May 31, 2017
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include "bst.h"
#include <stdlib.h>
#include "general.h"

struct Node {
  int value;
  struct Node* left;
  struct Node* right;
};

Bst new_bst()
{
  return 0;
}

void delete_bst(Bst bst)
{
  if (bst == 0)
  {
    return;
  }
  delete_bst(bst->left);
  delete_bst(bst->right);
  sfree(bst);
}

int get_depth(Bst bst)
{
  if(bst == 0)
    {
        return 0;
    }
    else
    {
      int lchild = get_depth(bst->left);
      int rchild = get_depth(bst->right);

      if(lchild <= rchild)
      {
        return rchild+1;
      }
      else
      {
        return lchild+1;
      }
    }
}

void add(Bst* bst, int value)
{
  if ((*bst) == 0)
    {
      Node* newnode = NewNode(value);
      (*bst) = newnode;
      return;
    }
    if (value <= (*bst)->value)
    {
      if ((*bst)->left == 0)
      {
        Node* newnode = NewNode(value);
        (*bst)->left = newnode;
      }
      else
      {
        Node* bst_to_add = (*bst)->left;
        add(&bst_to_add, value);
      }
    }
    else
    {
      if ((*bst)->right == 0)
      {
        Node* newnode = NewNode(value);
        (*bst)->right = newnode;
      }
      else
      {
        Node* bst_to_add = (*bst)->right;
        add(&bst_to_add, value);
      }
    }
}

Bst NewNode(int value)
{
  Bst new_node = (Bst)malloc(sizeof(struct Node));
  new_node->value = value;
  new_node->left = 0;
  new_node->right = 0;
  return new_node;
}

int root_value(Bst bst)
{
  if (bst == 0)
  {
    return 0;
  }
  return bst->value;
}

Bst left_subtree(Bst root)
{
  if (root == 0)
  {
    return 0;
  }
  return root->left;
}

Bst right_subtree(Bst root)
{
  if (root == 0)
  {
    return 0;
  }
  return root->right;
}

int traverse_pre_order(Bst bst, int *elements, int start)
{
  if(bst == 0) return start;
  elements[start] = bst->value;
  start++;
  start = traverse_pre_order(bst->left, elements, start);
  start = traverse_pre_order(bst->right, elements, start);
  return start;
}

int traverse_in_order(Bst bst, int *elements, int start)
{
  if(bst == 0) return start;
  start = traverse_in_order(bst->left, elements, start);
  elements[start] = bst->value;
  start++;
  start = traverse_in_order(bst->right, elements, start);
  return start;
}

int traverse_post_order(Bst bst, int *elements, int start)
{
  if (bst == 0) return start;
  start = traverse_post_order(bst->left, elements, start);
  start = traverse_post_order(bst->right, elements, start);
  elements[start] = bst->value;
  start++;
  return start;
}

bool are_equal(Bst bst1, Bst bst2)
{
  if (bst1 == 0 && bst1 == 0)
  {
     return true;
  }
  if (get_depth(bst1) == get_depth(bst2))
  {
    int *elements = new int[get_depth(bst1)];
    traverse_pre_order(bst1,elements, 0);
    int *elements2 = new int[get_depth(bst2)];
    traverse_pre_order(bst2,elements2, 0);
    return (bst1->value == bst2->value && have_equal_nodes(elements,elements2,get_depth(bst1)));
  }
  return false;
}

bool have_equal_nodes(int* elements, int* elements2, int length)
{
  for (int i = 0; i < length+1; i++)
  {
    if (elements[i] != elements2[i])
    {
      return false;
    }
  }
  return true;
}

void most_left_longest_branch(Bst bst, Bst* branch)
{
  if(bst == 0) return;

  if(get_depth(bst->right) > get_depth(bst->left))
  {
    add(branch, bst->value);
    most_left_longest_branch(&(*bst->right), branch);
  }
  else if(get_depth(bst->right) <= get_depth(bst->left))
  {
    add(branch, bst->value);
    most_left_longest_branch(&(*bst->left), branch);
  }
}

int get_number_of_subtrees(Bst bst)
{
  if (bst == 0) return -1;
  int *elements = new int[get_depth(bst)];
  return traverse_pre_order(bst, elements, 0)-1;
}
