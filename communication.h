/*
 * Sawyer Norquist
 * CS202
 * Program 3
 * communication.h
 * 8/5/2020
 *
 * Definitions of the primary user interface and the tree management.  Minimal operator overloading is used here as objects
 * of this type are not intended to be used separately.
 */

#include "messages.h"

//Primary class definition.  Contains a UString for the active user, and a Post_Node pointer for the parent
//Includes multiple functions for manipulating the tree, as well as basic user interface options
class Room
{

    private:
        UString user;
        Post_Node *parent;
        void copy_tree(const Room &source);
        Post_Node *copy_tree(Post_Node *source);
        void delete_tree();
        void delete_tree(Post_Node *&current);
        bool add_post(const Post &source);  //update to use 'user' and validate post doesn't already exist
        bool add_post(Post_Node *&current, const Post &source);
        Post_Node *find_node(const UString subject_check);
        Post_Node *find_node(Post_Node *current, const UString subject_check);
        void display(Post_Node *current) const;
        bool delete_subject(Post_Node *&current, UString to_delete); //update to check username
        void delete_node(Post_Node *&current, Post_Node *copy_to);

    public:
        Room();
        Room(const Room &source);
        ~Room();
        Room operator=(const Room &source);
        void write_post();
        void view_message();
        void display() const;
        void delete_subject();
        void menu();

};
