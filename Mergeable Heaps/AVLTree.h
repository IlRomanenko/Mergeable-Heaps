#pragma once
#include "Base.h"

struct avl_tree
{
    avl_tree *left, *right;
    int key, height, size;

    avl_tree(int _key)
    {
        left = right = nullptr;
        key = _key;
        height = 1;
        size = 1;
    }
};

typedef avl_tree* p_avl;

int getHeight(p_avl root)
{
    if (!root)
        return 0;
    return root->height;
}

int getSize(p_avl root)
{
    if (!root)
        return 0;
    return root->size;
}

int getKey(p_avl root)
{
    if (!root)
        return 0;
    return root->key;
}

int b_factor(p_avl root)
{
    if (!root)
        return 0;
    return getHeight(root->right) - getHeight(root->left);
}

void update(p_avl root)
{
    if (!root)
        return;
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    root->size = 1 + getSize(root->left) + getSize(root->right);
}

p_avl rotateLeft(p_avl root)
{
    p_avl result = root->right;
    root->right = root->right->left;
    update(root->right);
    result->left = root;
    update(result);
    return result;
}

p_avl rotateRight(p_avl root)
{
    p_avl result = root->left;
    root->left = root->left->right;
    update(root->left);
    result->right = root;
    update(result);
    return result;
}

p_avl balance(p_avl root)
{
    update(root);

    if (b_factor(root) == 2)
    {
        if (b_factor(root->right) < 0)
            root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    if (b_factor(root) == -2)
    {
        if (b_factor(root->left) > 0)
            root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    return root;
}

p_avl insert(p_avl root, int key)
{
    if (!root)
    {
        root = new avl_tree(key);
        return root;
    }
    if (root->key > key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);
    return balance(root);
}

int getMin(p_avl root)
{
    if (!root->left)
        return root->key;
    return getMin(root->left);
}

p_avl removeMin(p_avl root) 
{
    if (root->left == nullptr)
        return root->right;
    root->left = removeMin(root->left);
    return balance(root);
}