/*
 * Sawyer Norquist
 * CS202
 * Program 3
 * messages.cpp
 * 8/5/2020
 *
 * Implementation for all functions in messages.h
 */

#include "messages.h"

using namespace::std;

//Default UString constructor
UString::UString():word(NULL){}

//UString copy constructor
UString::UString(const UString &source):word(NULL)
{

    if(source.word)
    {

        word = new char[strlen(source.word) + 1];
        strcpy(word, source.word);

    }

}

//UString copy constructor that allows a new object to be created from a char*
UString::UString(const char *source):word(NULL)
{

    if(source)
    {

        word = new char[strlen(source) + 1];
        strcpy(word, source);

    }

}

//Returns current number of characters in UString
int UString::len() const
{

    return strlen(word);

}

//Destructor
UString::~UString()
{

    if(word)
        delete[] word;

}

//Overloaded insertion operator
//Takes in istream object and UString object
//Uses getline function to avoid the newline being extracted from the stream
//Rightsizes the UString object to avoid excessive memory usage
istream &operator>>(istream &input, UString &destination)
{

    char *temp = new char[MAX_USER_INPUT + 1];

    if(destination.word)
        delete[] destination.word;

    input.getline(temp, MAX_USER_INPUT);
    destination.word = new char[strlen(temp) + 1];
    strcpy(destination.word, temp);

    delete[] temp;
    
    return input;
    
}

//Inserts UString into the passed ostream object
ostream &operator<<(ostream &output, const UString &source)
{

    output << source.word;
    return output;

}

//The following three operations take in UString and char* sets
//performing concantinations and returning the concantenated result
//as the residual value
UString operator+(const UString &first, const UString &second)
{

    char *temp = new char[first.len() + second.len() + 1];
    strcpy(temp, first.word);
    strcat(temp, second.word);
    return UString(temp);

}

UString operator+(const UString &first, const char *second)
{

    char *temp = new char[first.len() + strlen(second) + 1];
    strcpy(temp, first.word);
    strcat(temp, second);
    return UString(temp);

}

UString operator+(const char *first, const UString &second)
{

    char *temp = new char[strlen(first) + second.len() + 1];
    strcpy(temp, first);
    strcat(temp, second.word);
    return UString(temp);

}

//The next series of comparison operator functions take in sets of UStrings
//and char*'s and runs the comparison using strcmp from the cstring library
bool operator<(const UString &first, const UString &second)
{

    if(strcmp(first.word, second.word) < 0)
        return true;
    else
        return false;

}

bool operator<(const UString &first, const char *second)
{

    if(strcmp(first.word, second) < 0)
        return true;
    else
        return false;

}

bool operator<(const char *first, const UString &second)
{

    if(strcmp(first, second.word) < 0)
        return true;
    else
        return false;

}

bool operator<=(const UString &first, const UString &second)
{

    if(strcmp(first.word, second.word) <= 0)
        return true;
    else
        return false;

}

bool operator<=(const UString &first, const char *second)
{

    if(strcmp(first.word, second) <= 0)
        return true;
    else
        return false;

}

bool operator<=(const char *first, const UString &second)
{

    if(strcmp(first, second.word) <= 0)
        return true;
    else
        return false;

}

bool operator>=(const UString &first, const UString &second)
{

    if(strcmp(first.word, second.word) >= 0)
        return true;
    else
        return false;

}

bool operator>=(const UString &first, const char *second)
{

    if(strcmp(first.word, second) >= 0)
        return true;
    else
        return false;

}

bool operator>=(const char *first, const UString &second)
{

    if(strcmp(first, second.word) >= 0)
        return true;
    else
        return false;

}

bool operator>(const UString &first, const UString &second)
{

    if(strcmp(first.word, second.word) > 0)
        return true;
    else
        return false;

}

bool operator>(const UString &first, const char *second)
{

    if(strcmp(first.word, second) > 0)
        return true;
    else
        return false;

}

bool operator>(const char *first, const UString &second)
{

    if(strcmp(first, second.word) > 0)
        return true;
    else
        return false;

}

bool operator==(const UString &first, const UString &second)
{

    if(strcmp(first.word, second.word) == 0)
        return true;
    else
        return false;

}

bool operator==(const UString &first, const char *second)
{

    if(strcmp(first.word, second) == 0)
        return true;
    else
        return false;

}
bool operator==(const char *first, const UString &second)
{

    if(strcmp(first, second.word) == 0)
        return true;
    else
        return false;

}

bool operator!=(const UString &first, const UString &second)
{

    if(strcmp(first.word, second.word) != 0)
        return true;
    else
        return false;

}

bool operator!=(const UString &first, const char *second)
{

    if(strcmp(first.word, second) != 0)
        return true;
    else
        return false;

}

bool operator!=(const char *first, const UString &second)
{

    if(strcmp(first, second.word) != 0)
        return true;
    else
        return false;

}

//The next two operators allow assignment to the member object from
//either another UString object or a char*
UString &UString::operator=(const UString &source)
{

    if(this == &source)
        return *this;

    if(word)
        delete[] word;

    word = new char[source.len() + 1];
    strcpy(word, source.word);

    return *this;

}

UString &UString::operator=(const char *source)
{

    if(word)
        delete[] word;

    word = new char[strlen(source) + 1];
    strcpy(word, source);

    return *this;

}

//The next two operators concantinate to the member object from either
//another UString object or a char*
UString &UString::operator+=(const UString &source)
{

    if(!source.word)
        return *this;

    char *temp = new char[len() + source.len() + 1];

    strcpy(temp, word);
    strcat(temp, source.word);

    if(word)
        delete[] word;

    word = temp;

    return *this;

}

UString &UString::operator+=(const char *source)
{

    if(!source)
        return *this;

    char *temp = new char[len() + strlen(source) + 1];

    strcpy(temp, word);
    strcat(temp, source);

    if(word)
        delete[] word;

    word = temp;

    return *this;

}

//Allow direct access via array operator overload
char &UString::operator[](int index) const
{

    return word[index];

}

//default constructor
Message::Message(){}

//Allows instantiation using a UString object to set the sender field
Message::Message(const UString &source):sender(source){}

//copy constructor
Message::Message(const Message &source):sender(source.sender), body(source.body){}

//Insertion operator - does message formatting for appropriate output
ostream &operator<<(std::ostream &output, const Message &source)
{

    output << "Sender: " << source.sender << endl;
    output << source.body << endl;

    return output;

}

//The following series of comparators allow for combinations of UString and Message objects to be compared
//Uses the strcmp function with the sender field being the comparator in all Message objects
bool operator<(const Message &first, const Message &second)
{

    if(first.sender < second.sender)
        return true;
    else
        return false;

}

bool operator<(const Message &first, const UString &second)
{

    if(first.sender < second)
        return true;
    else
        return false;

}

bool operator<(const UString &first, const Message &second)
{

    if(first < second.sender)
        return true;
    else
        return false;

}

bool operator<=(const Message &first, const Message &second)
{

    if(first.sender <= second.sender)
        return true;
    else
        return false;

}

bool operator<=(const Message &first, const UString &second)
{

    if(first.sender <= second)
        return true;
    else
        return false;

}

bool operator<=(const UString &first, const Message &second)
{

    if(first <= second.sender)
        return true;
    else
        return false;

}

bool operator>=(const Message &first, const Message &second)
{

    if(first.sender >= second.sender)
        return true;
    else
        return false;

}

bool operator>=(const Message &first, const UString &second)
{

    if(first.sender >= second)
        return true;
    else
        return false;

}

bool operator>=(const UString &first, const Message &second)
{

    if(first >= second.sender)
        return true;
    else
        return false;

}

bool operator>(const Message &first, const Message &second)
{

    if(first.sender > second.sender)
        return true;
    else
        return false;

}

bool operator>(const Message &first, const UString &second)
{

    if(first.sender > second)
        return true;
    else
        return false;

}

bool operator>(const UString &first, const Message &second)
{

    if(first > second.sender)
        return true;
    else
        return false;

}

bool operator==(const Message &first, const Message &second)
{

    if(first.sender == second.sender)
        return true;
    else
        return false;

}

bool operator==(const Message &first, const UString &second)
{

    if(first.sender == second)
        return true;
    else
        return false;

}

bool operator==(const UString &first, const Message &second)
{

    if(first == second.sender)
        return true;
    else
        return false;

}

bool operator!=(const Message &first, const Message &second)
{

    if(first.sender <= second.sender)
        return true;
    else
        return false;

}

bool operator!=(const Message &first, const UString &second)
{

    if(first.sender <= second)
        return true;
    else
        return false;

}

bool operator!=(const UString &first, const Message &second)
{

    if(first <= second.sender)
        return true;
    else
        return false;

}

//Assignment operator, copies in from another Message
//No other assignments are possible as we now have multiple internal data members
Message &Message::operator=(const Message &source)
{

    if(this == &source)
        return *this;

    sender = source.sender;
    body = source.body;

    return *this;

}

//Prompts user for input and writes to the body data member
void Message::write()
{

    cout << "What is your message? ";
    cin >> body;

    return;

}

//Outputs sender data to cout - not used
void Message::display_sender() const
{

    cout << "Sender: " << sender << endl;

    return;

}

//Outputs sender data to cout - not used
void Message::display_message() const
{

    cout << "Body: " << body << endl;

    return;

}

//Protected helper function to allow derived classes insertion operators to display sender data as needed
void Message::display_sender(ostream &output) const
{

    output << sender;

    return;

}

//Protected helper function to allow derived classes insertion operators to display body data as needed
void Message::display_message(ostream &output) const
{

    output << body;

    return;

}

//Default constructor, always want the next pointer to start NULL;
Message_Node::Message_Node():next(NULL){}

//First copy constructor, takes in a Message_Node but ignores the next pointer
Message_Node::Message_Node(const Message_Node &source):Message(source), next(NULL){}

//Copy constructor to allow a Message object to instantiate a node - also sets next to NULL;
Message_Node::Message_Node(const Message &source):Message(source), next(NULL){}

//Getter for next
Message_Node *&Message_Node::get_next()
{

    return next;

}

//setter for next
void Message_Node::set_next(Message_Node *to_set)
{

    next = to_set;
    return;

}

//Message_List default constructor, set head and tail to NULL
Message_List::Message_List():head(NULL), tail(NULL){}

//Copy constructor
Message_List::Message_List(const Message_List &source):head(NULL), tail(NULL)
{

    if(source.head)
        head = copy_list(source.head, tail);

}

//Message_List destructor
Message_List::~Message_List()
{

    delete_list();

}

//recursive function for coping the LLL portion of Message_List
//Takes in the source object's head pointer and the current object's LLL tail pointer
//Returns the address of the new node
Message_Node *Message_List::copy_list(Message_Node *source, Message_Node *&new_copy)
{

    //At end of list, set new node at tail, and return that address
    if(source->get_next() == NULL)
    {

        new_copy = new Message_Node(*source);
        new_copy->set_next(NULL);
        return new_copy;

    }

    //create a new node copying the current source node
    //Set the next using the return value from the next recursion
    //Then pass the new nodes address back to the previous recursion
    Message_Node *temp = new Message_Node(*source);
    temp->set_next(copy_list(source->get_next(), new_copy));
    return temp;

}

//Wrapper function for deleting the LLL
void Message_List::delete_list()
{

    delete_list(head);
    head = NULL;
    tail = NULL;

    return;

}

//Recursive function for deleting the LLL
//Takes in pointer to next node as argument
void Message_List::delete_list(Message_Node *current)
{

    if(!current)
        return;

    delete_list(current->get_next());
    delete current;

    return;

}

//Wrapper function for add_message recursion
//Takes in a const Message object, wraps it in a Message_node, then sends it to the final add method
//Used to help the append operator (+=)
void Message_List::add_message(const Message &source)
{

    //Creates new object, will ultimately be added directly - avoids extra copies being made
    Message_Node *new_node = new Message_Node(source);
    add_message(new_node);

    return;

}

//Wrapper function for add_message recursion
//Takes in a const Message pointer, converts and wraps it in a Message_Node, then sends it to the final add method
//Not used
void Message_List::add_message(const Message *source)
{

    if(!source)
        return;

    //Creates new object, will ultimately be added directly - avoids extra copies being made
    Message_Node *new_node = new Message_Node(*source);
    add_message(new_node);

    return;

}

//Primary add_message function
//Takes in a Message_Node pointer, and if not NULL, adds to the end of the list
//Not recursive as this is always a tail add
void Message_List::add_message(Message_Node *source)
{

    //Check that source has an object
    if(!source)
        return;

    //If tail is NULL, need to copy address directly to tail
    //Else the tail next gets the address
    if(!tail)
        tail = source;
    else
    {

        tail->set_next(source);
        tail = source;

    }

    //If tail was NULL, head will be - set head
    if(!head)
        head = tail;

    return;

}

//Assignment operator for Message_List, can only assign from another Message_List
Message_List Message_List::operator=(const Message_List &source)
{

    //Check for self-reference
    if(this == &source)
        return *this;

    //If not self reference, start with deleting existing data
    delete_list();

    //If the source is empy, we're done
    if(!source.head)
        return *this;

    //Otherwise we need to copy the data
    head = copy_list(source.head, tail);

    return *this;

}

//Insertion operator function - uses helper function to place data in ostream object
ostream &operator<<(ostream &output, const Message_List &source)
{

    source.display_all(output, source.head);
    return output;

}

//Append operator
//Simply calls the add_message function with the right args and returns *this for the residual value
Message_List &Message_List::operator+=(const Message &source)
{

    add_message(source);

    return *this;

}

//Basic display all wrapper function for output, default to cout
//Not used
void Message_List::display_all() const
{

    if(!head)
    {

        cout << "List is empty!" << endl;
        return;

    }

    display_all(head);
    return;

}

//Recursive display function, default to cout
//Takes in a Message_Node pointer for display
//Not used
void Message_List::display_all(Message_Node *current) const
{

    if(!current)
        return;

    cout << *current << endl;
    display_all(current->get_next());

    return;

}

//Helper wrapper function for displaying data - inserts to passed ostream object
//Properly formats data for display in the stream
void Message_List::display_all(ostream &output) const
{

    //If no items in list, say its empty
    if(!head)
    {

        output << "List is empty!" << endl;
        return;

    }

    //Otherwise run recursive function
    display_all(output, head);
    return;

}

//Recursive portion of the helper display function
//Reads data from the passed in Message_Node object into the ostream object
void Message_List::display_all(ostream &output, Message_Node *current) const
{

    if(!current)
        return;

    output << *current << endl;
    display_all(output, current->get_next());

    return;

}

//Wrapper function for delete search
//Argument is the sender to delete from messages
void Message_List::delete_user(const UString &current_user)
{

    //check for a list that only has one item
    if(head == tail && *head == current_user)
    {
        
        delete head;
        head = NULL;
        tail = NULL;
        return;

    }

    delete_user(head, head, current_user);

}

//Recursive function for deleting a user from the LLL
//First argument is the last node looked at, second is the current node being looked at, last argument is the user to be removed
void Message_List::delete_user(Message_Node *&last, Message_Node *&current, const UString &current_user)
{

    //End of list, all done!
    if(!current)
        return;

    //First case, match is found at head
    //Catch head address, set head to its own next, then delete the old address and resume recursing
    if(current == head && *current == current_user)
    {

        Message_Node *to_delete = head;
        head = head->get_next();
        delete to_delete;

        delete_user(head, head, current_user);
        return;

    }

    //Second case, match found at tail
    //Set copy of current to avoid an alias issue, set tail to the last node and set next to NULL, delete the node
    if(current == tail && *current == current_user)
    {

        Message_Node *to_delete = current;
        tail = last;
        tail->set_next(NULL);
        delete to_delete;

        return;

    }

    //Third case, match found in middle of list
    //Use last pointer to connect around current and delete current using a holding pointer to avoid aliasing issues
    //Then resume recursing
    if(*current == current_user)
    {

        Message_Node *to_delete = current;
        last->set_next(current->get_next());
        delete to_delete;
        delete_user(last, last->get_next(), current_user);
        return;

    }

    delete_user(current, current->get_next(), current_user);
    return;

}

//Function to see if list has data in it
//Helps output functions in Post class
bool Message_List::has_replies() const
{

    if(!head)
        return false;
    else
        return true;

}

//default constructor, calls new Message_List object by default at the replies pointer
Post::Post():replies(NULL)
{

    replies = new Message_List;

}

//copy constructor
//Creates new Message_List and copies data over
Post::Post(const Post &source):Message(source), subject(source.subject), replies(NULL)
{

   if(source.replies)
   {

       replies = new Message_List;
       *replies = *source.replies;

   }

   return;

}

//Constructor to take in UString to set the sender
//Creates new Message_List object by default
Post::Post(const UString &source):Message(source), replies(NULL)
{

    replies = new Message_List;

}

//Post destructor
Post::~Post()
{

    if(replies)
        delete replies;

}

//Overloaded insertion operator
//Inserts data to the passed ostream object from the Post object
ostream &operator<<(ostream &output, const Post &source)
{

    output << "Sender: ";
    source.display_sender(output);
    output << endl << "Subject: " << source.subject << endl;
    source.display_message(output);

    //Check if there are replies or not
    if(!source.replies->has_replies())
        output << endl << "No replies";
    else
        output << endl << "Post has replies";

    return output;

}

//The following comparators can compare various combinations of Post and UString objects
//Uses subject as the comparing key
bool operator<(const Post &first, const Post &second)
{

    if(first.subject < second.subject)
        return true;
    else
        return false;

}

bool operator<(const Post &first, const UString &second)
{

    if(first.subject < second)
        return true;
    else
        return false;

}

bool operator<(const UString &first, const Post &second)
{

    if(first < second.subject)
        return true;
    else
        return false;

}

bool operator<=(const Post &first, const Post &second)
{

    if(first.subject <= second.subject)
        return true;
    else
        return false;

}

bool operator<=(const Post &first, const UString &second)
{

    if(first.subject <= second)
        return true;
    else
        return false;

}

bool operator<=(const UString &first, const Post &second)
{

    if(first <= second.subject)
        return true;
    else
        return false;

}

bool operator>=(const Post &first, const Post &second)
{

    if(first.subject >= second.subject)
        return true;
    else
        return false;

}

bool operator>=(const Post &first, const UString &second)
{

    if(first.subject >= second)
        return true;
    else
        return false;

}

bool operator>=(const UString &first, const Post &second)
{

    if(first >= second.subject)
        return true;
    else
        return false;

}

bool operator>(const Post &first, const Post &second)
{

    if(first.subject > second.subject)
        return true;
    else
        return false;

}

bool operator>(const Post &first, const UString &second)
{

    if(first.subject > second)
        return true;
    else
        return false;

}

bool operator>(const UString &first, const Post &second)
{

    if(first > second.subject)
        return true;
    else
        return false;

}

bool operator==(const Post &first, const Post &second)
{

    if(first.subject == second.subject)
        return true;
    else
        return false;

}

bool operator==(const Post &first, const UString &second)
{

    if(first.subject == second)
        return true;
    else
        return false;

}

bool operator==(const UString &first, const Post &second)
{

    if(first == second.subject)
        return true;
    else
        return false;

}

bool operator!=(const Post &first, const Post &second)
{

    if(first.subject <= second.subject)
        return true;
    else
        return false;

}

bool operator!=(const Post &first, const UString &second)
{

    if(first.subject <= second)
        return true;
    else
        return false;

}

bool operator!=(const UString &first, const Post &second)
{

    if(first <= second.subject)
        return true;
    else
        return false;

}

//Post assignment operator
Post &Post::operator=(const Post &source)
{

    //Check for self-assignment
    if(this == &source)
        return *this;

    //Call base class assignment, then copy over data members using their overloaded operators
    Message::operator=(source);
    subject = source.subject;
    *replies = *source.replies;

    return *this;

}

//Prompts user input and stores response in the subject data member
void Post::write_subject()
{

    cout << "Enter subject: ";
    cin >> subject;

    return;

}

//Takes in a UString for the user
//Creates a new Message object with that data, calls the write function to prompt user input, then appends to the Message_List object
void Post::add_message(const UString &user)
{

    Message new_message(user);
    new_message.write();

    *replies += new_message;
    return;

}

//Because the insertion operator only shows core Post data, this function is to display all items from the Message_List object
void Post::show_replies()
{

    //Check that replies exist and display appropriately
    if(replies->has_replies())
        cout << *replies;
    else
        cout << "No replies";

    cout << endl;
    return;

}

//This operation is NOT SAFE for the argument
//Takes in a Post pointer
//Copies data into the member object, and does a SHALLOW copy of the Message_List pointer before setting the arguments pointer to NULL to avoid double-free errors later
//Shallow copy is to allow a more efficient list transfer in the tree class' copy/delete functions
void Post::transfer_node(Post &source)
{

    Message::operator=(source);
    subject = source.subject;
    replies = source.replies;
    source.replies = NULL;
    return;

}

//Tree node default constructor
Post_Node::Post_Node():left(NULL), right(NULL){}

//Copy constructor - always set pointers to NULL to avoid unwanted behavior
Post_Node::Post_Node(const Post_Node &source):Post(source), left(NULL), right(NULL){}

//Use a Post object as the copy reference, sets pointers to NULL
Post_Node::Post_Node(const Post &source):Post(source), left(NULL), right(NULL){}

//Creates new object using a UString to pass in user name, sets pointers to null
Post_Node::Post_Node(const UString &source):Post(source), left(NULL), right(NULL){}

//Overloaded assignment operator
//This one does copy over the pointers
Post_Node &Post_Node::operator=(const Post_Node &source)
{

    //check for self-reference
    if(this == &source)
        return *this;

    //Copy pointers and the Post data over
    left = source.left;
    right = source.right;
    Post::operator=(source);

    //residual value
    return *this;

}

//Can also assign a Post - this one sets the pointers to NULL
Post_Node &Post_Node::operator=(const Post &source)
{

    left = NULL;
    right = NULL;
    Post::operator=(source);

    return *this;

}

//Left node getter
Post_Node *&Post_Node::get_left()
{

    return left;

}

//Right node getter
Post_Node *&Post_Node::get_right()
{

    return right;

}

//Left node setter
void Post_Node::set_left(Post_Node *to_set)
{

    left = to_set;
    return;

}

//Right node setter
void Post_Node::set_right(Post_Node *to_set)
{

    right = to_set;
    return;

}
