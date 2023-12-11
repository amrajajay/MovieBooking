#include <iostream>
#include "BinarySearchTree.h"
using namespace std;
void BinarySearchTree::insert(BookTicket &val)
{
    bool inserted = search_and_insert(this->root, val);
    if (!inserted)
    {
        cout << "System Duplicate Booking Error" << endl;
    }
}
bool BinarySearchTree::search_and_insert(BinaryNode *&sub_root, BookTicket &val)
{
    // 1. Stopping condition
    bool return_val = false;
    if (sub_root == nullptr)
    {
        sub_root = new BinaryNode(val);
        return true;
    }
    // 2. recursive condition
    else if (sub_root->data.get_booking_id() > val.get_booking_id())
    {
        return search_and_insert(sub_root->left, val);
    }
    else if (sub_root->data.get_booking_id() < val.get_booking_id())
    {
        return search_and_insert(sub_root->right, val);
    }
    else if (sub_root->data.get_booking_id() == val.get_booking_id())
    {
        return_val = false;
    }
    return return_val;
}
void BinarySearchTree::remove(BookTicket &val)
{

    bool removed = search_and_remove(this->root, val);
    if (!removed)
    {
        cout << "Booking Data not found" << endl;
    }
}

bool BinarySearchTree::search_and_remove(BinaryNode *&sub_root, BookTicket &val)
{
    bool return_val;
    if (sub_root == nullptr)
    {
        return false;
    }
    else if (sub_root->data.get_booking_id() > val.get_booking_id())
    {
        return search_and_remove(sub_root->left, val);
    }
    else if (sub_root->data.get_booking_id() < val.get_booking_id())
    {
        return search_and_remove(sub_root->right, val);
    }
    else
    {
        return_val = true;
        if (sub_root->left == nullptr && sub_root->right == nullptr)
        {
            delete sub_root;
            sub_root = nullptr;
        }
        else if (sub_root->left == nullptr)
        {
            BinaryNode *temp = sub_root;
            sub_root = sub_root->right;
            delete temp;
        }
        else if (sub_root->right == nullptr)
        {
            BinaryNode *temp = sub_root;
            sub_root = sub_root->left;
            delete temp;
        }
        else
        {
            BinaryNode *&sucessor = get_successor(sub_root->right);
            sub_root->data = sucessor->data;
            return search_and_remove(sub_root->right, sucessor->data);
        }
    }
    return return_val;
}
BinaryNode *&BinarySearchTree::get_successor(BinaryNode *&sub_root)
{
    if (sub_root->left == nullptr)
        return sub_root;
    return get_successor(sub_root->left);
}
BinaryNode *&BinarySearchTree::search_in_bst(BinaryNode *&sub_root, string val)
{
    if (sub_root == nullptr || sub_root->data.get_booking_id() == val)
    {
        return sub_root;
    }
    else if (sub_root->data.get_booking_id() > val)
    {
        return search_in_bst(sub_root->left, val);
    }
    else
    // if (sub_root->data.get_booking_id() < val)
    {
        return search_in_bst(sub_root->right, val);
    }
}
BookTicket BinarySearchTree::search(string val)
{

    BinaryNode *res = search_in_bst(this->root, val);
    if (res == nullptr)
    {
        return BookTicket();
    }
    return res->data;
}