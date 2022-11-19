/*
 * Sawyer Norquist
 * CS202
 * Program 3
 * communication.cpp
 * 8/5/2020
 *
 * Implementation of the definitions in communication.h
 *
 */

#include "communication.h"

using namespace::std;

//Default construtor, no items in tree
Room::Room():parent(NULL){}

//Copy constructor
Room::Room(const Room &source):user(source.user), parent(NULL)
{

    if(source.parent)
        copy_tree(source);
    
}

//destructor
Room::~Room()
{

    if(parent)
        delete_tree();

}

//Helper wrapper function for copying the tree
//argument is the source object
void Room::copy_tree(const Room &source)
{

    //if source is null, nothing to do
    if(!source.parent)
        return;

    parent = copy_tree(source.parent);

}

//Recursive portion of copying a tree
//Argument is the current Post_Node to copy
//Operates by setting the new object's left/right node to the address returned by the next recursion
Post_Node *Room::copy_tree(Post_Node *current)
{

    //End of list!  Return NULL to set the previous left/right pointer correctly
    if(!current)
        return NULL;

    //Create new Post_Node, using copy constructor from current pointer
    //Recurse off the left/right setters
    Post_Node *new_node = new Post_Node(*current);
    new_node->set_left(current->get_left());
    new_node->set_right(current->get_right());

    //return address of new node to previous recursion
    return new_node;    

}

//Wrapper for the delete tree function
void Room::delete_tree()
{

    //If parent is NULL, nothing to do
    if(!parent)
        return;

    delete_tree(parent);

    return;
    
}

//Recursive delete function for the tree
//Argument is the current node to delete
void Room::delete_tree(Post_Node *&current)
{

    //if NULL, at end of list!
    if(!current)
        return;

    //Recurse to the end of all leaves...
    delete_tree(current->get_left());
    delete_tree(current->get_right());

    //then delete as the stack unwinds
    delete current;

    return;

}

//Wrapper function for adding a post
//Takes a Post object to be added to the tree
//Return is if the Post was added - returns false if a Post by the same subject name exists
bool Room::add_post(const Post &source)
{

    return add_post(parent, source);

}

//Recursive portion of the add_post function
//Takes in the current pointer being evaluated, and the Post object to be copied in
//Returns true if the Post is added, false if the subject already exists
bool Room::add_post(Post_Node *&current, const Post &source)
{

    //Made it to a new leave - create a new Post_Node here and return true
    if(!current)
    {

        current = new Post_Node(source);
        return true;

    }

    //Checks if the current object matches the source - returns false if match occurs
    if(*current == source)
        return false;

    //Navigate the tree to the right spot for insertion
    if(*current > source)
        return add_post(current->get_left(), source);
    else
        return add_post(current->get_right(), source);

}

//Assignment operator overload
Room Room::operator=(const Room &source)
{

    //Check for self-assignment
    if(this == &source)
        return *this;

    //If parent has data, delete it first
    if(parent)
    {

        delete_tree();
        parent = NULL;

    }

    //Copy tree over
    copy_tree(source);

    //set user object
    user = source.user;

    return *this;
    
}

//User interface for writing a new Post object
void Room::write_post()
{

    //First create a Post_Node with the user name
    Post_Node new_post(user);

    //Ask for subject and message body
    new_post.write_subject();
    new_post.write();

    //Add the post - if an existing Post with that subject is found, reprompts until the Post can be added
    while(!add_post(new_post))
    {

        cout << "Post already exists - try again with a different subject" << endl;
        new_post.write_subject();

    }

    return;
    
}

//Display function wrapper
void Room::display() const
{

    //If no data in tree, say so
    if(!parent)
    {

        cout << "No posts!" << endl;
        return;

    }

    display(parent);
    return;

}

//recursive portion of display function, does inorder display
//Argument is the current node to display
void Room::display(Post_Node *current) const
{

    //At end of tree!
    if(!current)
        return;

    //First go all the way left, display, jump right and go left again
    display(current->get_left());
    cout << endl << *current << endl;
    display(current->get_right());

    return;

}

//User interface for deleting a specific Post by subject
//Should compare againt active user to validate permission, but ran out of time
void Room::delete_subject()
{

    UString input;  //Input for which subject is to be deleted
    bool node_found = true;  //Redundant, but used to catch value of the delete_subject recursive portion

    //prompt for input and call recursive function
    cout << "Which subject do you want to delete? ";
    cin >>input;
    node_found = delete_subject(parent, input);

    //Output if post was found or not
    if(node_found)
        cout << endl << "Success - post deleted" << endl;
    else
        cout << endl << "Failure - post not found" << endl;

    return;

}

//Recursive portion of deleting a post
//Takes in current post to evaluate as well as a UString to compare against
//Returns true if a candidate node was found and deleted
bool Room::delete_subject(Post_Node *&current, UString to_delete)
{

    //No further to go, node has not been found
    if(!current)
        return false;

    //If match is found, go to delete the node
    if(*current == to_delete)
    {

        delete_node(current, current);
        return true;

    }

    //Otherwise compare at current and decide which direction to go next
    if(*current > to_delete)
        return delete_subject(current->get_left(), to_delete);
    else
        return delete_subject(current->get_right(), to_delete);

}

//Helper function for deleting a node
//First arg is the candidate for inorder successor.  Second arg is address of the node to delete
void Room::delete_node(Post_Node *&current, Post_Node *copy_to)
{

    //First need to directly evaluate the node we're trying to delete
    if(current == copy_to)
    {

        //if no left or right pointers, is leaf and can just delete directly
        if(!current->get_left() && !current->get_right())
        {

            delete current;
            current = NULL;
        
        //If node has only one child, just copy the pointer up and delete the node
        }else if(!current->get_left() && current->get_right())
        {

            Post_Node *to_delete = current;

            current = current->get_right();
            delete to_delete;

        }else if(current->get_left() && !current->get_right())
        {

            Post_Node *to_delete = current;
            current = current->get_left();
            delete to_delete;

        //if none of these cases are true, need to find inorder successor
        //Does first navigation to the right
        }else
            delete_node(current->get_right(), copy_to);

        return;

    }

    //then evaluate if we have further left to go
    //if not, we have arrived and can proceed with the delete
    if(!current->get_left())
    {

        //first, copy node contents over
        //Requires a special function to avoid needless deep copy of a Message_List object
        copy_to->transfer_node(*current);

        //if there's a right child, need to copy that pointer up before deleting this node
        if(current->get_right())
        {

            Post_Node *to_delete = current;
            current = current->get_right();
            delete to_delete;

        //otherwise we know it's a leaf and safe to delete as-is
        }else
        {

            delete current;
            current = NULL;

        }

        return;

    }

    //recurse left!
    delete_node(current->get_left(), copy_to);

    return;

}

//Primary user interface for the Room class
void Room::menu()
{

    int input = 0;

    //Starting off by requiring a user to be generated
    cout << "Please enter current user: ";
    cin >> user;

    do
    {

        cout << endl << endl << endl;
        cout << "Current user: " << user << endl;
        cout << "1 - Show all posts" << endl;
        cout << "2 - Add post" << endl;
        cout << "3 - View/reply to post" << endl;
        cout << "4 - Delete post (WARNING - deletes all replies!)" << endl;
        cout << "5 - Change user" << endl;
        cout << "0 - Exit" << endl;
        cout << "Select: ";
        cin >> input;

        if(!cin.good())
            input = -1;

        cin.clear();
        cin.ignore(500, '\n');

        switch(input)
        {

            case 0:
                break;

            case 1:
                display();
                break;

            case 2:
                write_post();
                break;

            case 3:
                view_message();
                break;

            case 4:
                delete_subject();
                break;

            case 5:
                cout << endl << "Please enter new user: ";
                cin >> user;
                cout << endl;
                break;

            default:
                cout << "Invalid input - expecting number between 0 and 5" << endl;
                break;

        }

    }while(input != 0);

    return;

}

//Function to look at a specific Post
//Takes in a subject from the user to search the tree
//Pulls out a pointer to the object so multiple functions can be used depending on user input
void Room::view_message()
{

    UString subject_search;  //Container for user query
    char input = 'a';  //Checks for user input on program query
    Post_Node *active_node = NULL;  //Holder for the referenced node

    cout << "Which subject would you like to check? ";
    cin >>subject_search;

    //Call function to return the node based on the input UString
    active_node = find_node(subject_search);

    //If active_node is NULL, the node didn't exist
    if(!active_node)
    {

        cout << "Subject not found" << endl;
        return;

    }

    //Show node contents, including the replies
    cout << *active_node << endl << "Replies:" << endl;
    active_node->show_replies();

    //Check if user wants to post a reply, loop is for data validation purposes
    do
    {

        cout << endl << "Would you like to reply? (y/n): ";
        cin >> input;

        cin.clear();
        cin.ignore(500, '\n');

        input = toupper(input);

        if(input !='Y' && input != 'N')
            cout << "Invalid response" << endl;

    }while(input != 'N' && input != 'Y');

    //if user says yes, call the function to create a reply
    if(input == 'Y')
        active_node->add_message(user);

    return;

}

//wrapper function for the node find function
//Arg is the subject line to find, return is the address of the object
Post_Node *Room::find_node(const UString subject_check)
{

    if(!parent)
        return NULL;

    return find_node(parent, subject_check);

}

//recursive portion of the node find function
//first arg is the node to be evaluated, second is the subject line to find, and the return is the address of the node
Post_Node *Room::find_node(Post_Node *current, const UString subject_check)
{

    if(!current)
        return NULL;

    if(*current == subject_check)
        return current;

    if(*current > subject_check)
        return find_node(current->get_left(),subject_check);
    else
        return find_node(current->get_right(), subject_check);

}
