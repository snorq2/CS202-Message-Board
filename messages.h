/*
 * Sawyer Norquist
 * CS202
 * Program 3
 * messages.h
 * 8/5/2020
 *
 * This is the header file for my string class and the primary message classes driving the rest of the program.
 * Includes message classes, node classes, and the LLL management class.  The tree management class moved outside of this
 * header due to being integrated into the user interface.
 */

#include <iostream>
#include <cstring>

static const int MAX_USER_INPUT = 5000;

//My string class replacement.  Uses a dynamically allocated array at its heart.
//Supports a full range of operators, including interactions with char*'s
class UString
{

    private:
        char *word;
        void display(std::ostream &output);
        int len() const;

    public:
        UString();
        UString(const UString &source);
        UString(const char *source);
        ~UString();
        friend std::istream &operator>>(std::istream &input, UString &destination);
        friend std::ostream &operator<<(std::ostream &output, const UString &source);
        friend UString operator+(const UString &first, const UString &second);
        friend UString operator+(const UString &first, const char *second);
        friend UString operator+(const char *first, const UString &second);
        friend bool operator<(const UString &first, const UString &second);
        friend bool operator<(const UString &first, const char *second);
        friend bool operator<(const char *first, const UString &second);
        friend bool operator<=(const UString &first, const UString &second);
        friend bool operator<=(const UString &first, const char *second);
        friend bool operator<=(const char *first, const UString &second);
        friend bool operator>=(const UString &first, const UString &second);
        friend bool operator>=(const UString &first, const char *second);
        friend bool operator>=(const char *first, const UString &second);
        friend bool operator>(const UString &first, const UString &second);
        friend bool operator>(const UString &first, const char *second);
        friend bool operator>(const char *first, const UString &second);
        friend bool operator==(const UString &first, const UString &second);
        friend bool operator==(const UString &first, const char *second);
        friend bool operator==(const char *first, const UString &second);
        friend bool operator!=(const UString &first, const UString &second);
        friend bool operator!=(const UString &first, const char *second);
        friend bool operator!=(const char *first, const UString &second);
        UString &operator=(const UString &source);
        UString &operator=(const char *source);
        UString &operator+=(const UString &source);
        UString &operator+=(const char *source);
        char &operator[](int index) const;
        
};

//Base class for other message classes, also the class used to reply to posts
//Has two private data members - first is for whoever created the message, second is the body of the message.
//Supports comparison, extraction, and assignment operators.  Comparisons use the sender for evaluation.
class Message
{

    private:
        UString sender;
        UString body;

    public:
        Message();
        Message(const UString &source);
        Message(const Message &source);
        friend std::ostream &operator<<(std::ostream &output, const Message &source);
        friend bool operator<(const Message &first, const Message &second);
        friend bool operator<(const Message &first, const UString &second);
        friend bool operator<(const UString &first, const Message &second);
        friend bool operator<=(const Message &first, const Message &second);
        friend bool operator<=(const Message &first, const UString &second);
        friend bool operator<=(const UString &first, const Message &second);
        friend bool operator>=(const Message &first, const Message &second);
        friend bool operator>=(const Message &first, const UString &second);
        friend bool operator>=(const UString &first, const Message &second);
        friend bool operator>(const Message &first, const Message &second);
        friend bool operator>(const Message &first, const UString &second);
        friend bool operator>(const UString &first, const Message &second);
        friend bool operator==(const Message &first, const Message &second);
        friend bool operator==(const Message &first, const UString &second);
        friend bool operator==(const UString &first, const Message &second);
        friend bool operator!=(const Message &first, const Message &second); 
        friend bool operator!=(const Message &first, const UString &second); 
        friend bool operator!=(const UString &first, const Message &second); 
        Message &operator=(const Message &source);
        void write();
        void display_sender() const;
        void display_message() const;
        bool is_user(const UString &to_check);

    protected:
        void display_sender(std::ostream &output) const;
        void display_message(std::ostream &output) const;

};

//Message node class to allow integration into the LLL
class Message_Node: public Message
{

    private:
        Message_Node *next;

    public:
        Message_Node();
        Message_Node(const Message_Node &source);
        Message_Node(const Message &source);
        Message_Node *&get_next();
        void set_next(Message_Node *to_set);

};

//LLL class for Messages.  Includes a tail pointer, as inserts are always at the rear
//Implemented as strong ADT, using a select set of operators to interact with the list
//as well as a few member functions.
class Message_List
{

    private:
        Message_Node *head;
        Message_Node *tail;
        Message_Node *copy_list(Message_Node *source, Message_Node *&new_copy);
        void delete_list();
        void delete_list(Message_Node *current);
        void add_message(const Message &source);
        void add_message(const Message *source);
        void add_message(Message_Node *source);
        void display_all(Message_Node *current) const;
        void display_all(std::ostream &output, Message_Node *current) const;
        void delete_user(Message_Node *&last, Message_Node *&current, const UString &current_user);

    public:
        Message_List();
        Message_List(const Message_List &source);
        ~Message_List();
        Message_List operator=(const Message_List &source);
        friend std::ostream &operator<<(std::ostream &output, const Message_List &source);
        Message_List &operator+=(const Message &source);
        void display_all() const;
        void display_all(std::ostream &output) const;
        void delete_user(const UString &current_user);
        bool has_replies() const;

};

//Primary derived class object, serves as the first in a list of messages.
//Contains a UString object to add a subject line, and a pointer to a Message_List
//Message_List is implemented as pointer to allow easier moves/deletes in the tree structure
//Overloads the comparison operator so they operate off the subject instead of the sender - this is to sort the tree structure
//Not implemented as a strong ODT, as it contains its own method for modifying its subject line.
class Post: public Message
{

    private:
        UString subject;
        Message_List *replies;

    public:
        Post();
        Post(const Post &source);
        Post(const UString &source);
        ~Post();
        friend std::ostream &operator<<(std::ostream &output, const Post &source);
        friend bool operator<(const Post &first, const Post &second);
        friend bool operator<(const Post &first, const UString &second);
        friend bool operator<(const UString &first, const Post &second);
        friend bool operator<=(const Post &first, const Post &second);
        friend bool operator<=(const Post &first, const UString &second);
        friend bool operator<=(const UString &first, const Post &second);
        friend bool operator>=(const Post &first, const Post &second);
        friend bool operator>=(const Post &first, const UString &second);
        friend bool operator>=(const UString &first, const Post &second);
        friend bool operator>(const Post &first, const Post &second);
        friend bool operator>(const Post &first, const UString &second);
        friend bool operator>(const UString &first, const Post &second);
        friend bool operator==(const Post &first, const Post &second);
        friend bool operator==(const Post &first, const UString &second);
        friend bool operator==(const UString &first, const Post &second);
        friend bool operator!=(const Post &first, const Post &second); 
        friend bool operator!=(const Post &first, const UString &second); 
        friend bool operator!=(const UString &first, const Post &second); 
        Post &operator=(const Post &source);
        void write_subject();
        void show_replies();
        void add_message(const UString &user);
        void transfer_node(Post &source); //NOT SAFE - does shallow copy of replies and sets arguments replies to NULL.  Used for tree delete.

};

//Tree node derived Post class
class Post_Node: public Post
{

    private:
        Post_Node *left;
        Post_Node *right;

    public:
        Post_Node();
        Post_Node(const Post_Node &source);
        Post_Node(const Post &source);
        Post_Node(const UString &source);
        Post_Node &operator=(const Post_Node &source);
        Post_Node &operator=(const Post &source);
        Post_Node *&get_left();
        Post_Node *&get_right();
        void set_left(Post_Node *to_set);
        void set_right(Post_Node *to_set);

};
