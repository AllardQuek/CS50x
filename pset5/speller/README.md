# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

A word of the maximum length (45).

## According to its man page, what does `getrusage` do?

returns resource usage measures for who, such as RUSAGE_SELF

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

It appears that the rusage struct takes considerable chunk of memory so we better avoid making extraneous copies.
For one, there is a benefit in not having to create new variables. Also, calculate() could have the wrong values if the value for before and after are modified outside of the function. By passing reference instead of value, calculate() always has access to the latest variable data.


## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

It reads characters one-by-one into the word buffer until it reaches EOF. Words can only contain alphabetical characters and apostrophes.
Words that are longer than LENGTH and thus wouldn't fit into the buffer are dropped entirely. Words which contain numbers are ignored completely as well.
Whole words are then terminated with a NUL character and checked against the dictionary of valid words.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

Because %s would treat words containing numbers and other disallowed characters as valid which based on our definition of the word is not.


## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

To declare that the data that the pointer points to must not be changed.
Declaring "const char*" creates a mutable pointer to an immutable char. By using const char*, if you accidentally try to change the value it points to, the compiler would give a warning. Since the words from the text and the dictionary are not supposed to be manipulated in this solution, it is safer to declare a const.



Singly-linked list is like a dictionary?

Create:
sllnode* create(VALUE val) #sllnode is a type defined before using typedef
sllnode* new = create(6)
Steps --> Dynamically allocate space for new sllnode (malloc), check if ptr returned is null, initialize node's value field, initialize node's next field, return pointer to newly created sllnode


Search; check if word matches word in dict:
bool find(sllnode* head, VALUE val) #VALUE val is the item you are looking for in the sll
Steps --> Create a traversal pointer to the first item in sll (duplicate current ptr as 1st item must always be kept tracked of)
if node's val field is what we are looking for return success
else move traversal ptr to next ptr in the list, repeat 2nd step
if reached end of list, return failure

Insert:
sllnode* insert(sllnode* head, VALUE val)
Steps: Dyn all space for new sllnode, check didn't run out of memory, populate and insert node at the START of list, return a ptr to the new head of list


Unload/free dict from memory:
void destroy(sllnode* head); #sllnode *head is a pointer to the first item in the sll
Steps --> if reached null ptr, stop
Delete rest of list
Free current NODE


HASHTABLES

hash is a number spit out by hash function telling you to go to that nth element in an array
hashtable is an ARRAY of LINKED LISTS, where each element of the ARRAY is a node POINTER pointing to the vert FIRST node in that linked LIST

TRIES
'reTRIEval', similar to upside-down tree, root at top, branches to other nodes of similar data type. Nodes w/0 branches are leaves.
essentially a tree with an array as each of its children
time taken approaches constant time, approx const no. of steps to insert or search for data
malloc first node, assign ptr to keep track
when mapping keys to values, open gate and malloc space for new node, open another gate, repeat
rmb to create traversal ptr to help with pointer mvmts


STACKS
like trays in canteen, LIFO, similar to sll, but cannot insert or delete from anywhere in the list, ONLY from the TOP, i.e first element
implement as array/sll
rmb to create traversal ptr to help w mvmts and keep track of first list item AT ALL TIMES

QUEUES
similar to stack, another kind of data struct, FIFO, implemented as array/list





DATA STRUCTS


*** USING HASHTABLE AND LINKED LISTS ***

creating a node:
typedef struct node
{
    char word[LENGTH + 1]
    struct node *next
}
node;

# creating nodes
node *node1 = malloc(sizeof(node));
node *node2 = malloc(sizeof(node));
# copy word in quotes to node 1's field called word
strcpy(node1->word, "Hello");
strcpy(node2->word, "world");
# link nodes by first accessing node's 'next' field and assigning node 2 to be equal to it.
node1->next = node2

# create an array of nodes; array name is hashtable, number of nodes is 50
node *hashtable[50];

# populate hashtable with words in dict, need to first read contents of dict
# look for string in dict file called file, add string to variable called word
while (fscanf(file, "%s", word) != EOF)
{
    # for every scanned word, malloc a node for it
    node *newnode = malloc(sizeof(node));

    # and check if malloc succeeded
    if (newnode == NULL)
    {
        unload();
        return false;
    }

    # if succeeded, proceed to copy the word into the node by accessing word field of the node
    strcopy(newnode->word, word);

    # insert this new node into a linked list by
    # first: adding node to head of list,
    newnode->next = head

    # then shift ptr to new first node
    head = newnode:

    # how to know which word goes into which linked list? hash function; takes a string, returns an index, deterministic
    # hash the word: hash newnode->word, which will give an index of a bucket in hashtable, then INSERT into linked list
}


    node* cursor = head;

    while (cursor != NULL)
    {
        node* temp = cursor;
        cursor = cursor->next
        free(temp)
    }


*** END OF HASHTABLES AND LL ***



*** USING TRIES to represent the dictionary data structure ***
every node contains an array of NODE PTRS (one for each 26 alphabets AND apotrophe which is '\'')
each element in the array points to another node , if node is NULL then that letter isn't the next letter in any word
every node must indicate whether it is the LAST CHAR of a word

typedef struct node
{
    bool is_word; (returns true or false if word)
    struct node *children[27]; (an array of 27 nodes)
}
node;


# create pointer to root/top of the tree
node *root;

# scanning thru dict 1 word at a time, iterate thru the try
check value at children[i], if NULL, malloc a new node and have children[i] point to this new node
if not NULL move to new node and continue
if reached end of word, set is_word to true

# e.g. insert "fox" into empty dict, so for f MALLOC A NEW NODE
f: root->children[5] (as f is 6th letter of alphabet)
o: root->children[5]->children[14]
x: root->children[5]->children[14]->children[23]
finally, set is_word to true

# e.g. insert "foo"
f: alr created node, no need new one
o: "
o: make new node, alloc space using malloc, checking whether malloc returns NULL
if node create succeed, reached end of word, set is_word to true

# e.g. insert "dog"
d: root->children[3]
o: root->children[3]->children[14]  (new node must be created here)
g: root->children[3]->children[14]->children[6]  (create new node again)
set is_word to true

# e.g. insert "do", a substring of "dog"
NO NEED to create any more nodes
just navigate to 'o' and set is_word to true


*** END OF USING TRY ***


        //if char is not last char in word
        // if (c != '\n')
        // {
        //     //if no node created yet
        //     if (temp->children[i] == NULL)
        //     {
        //         //malloc new node
        //         temp->children[i] = malloc(sizeof(node));
        //         //have children[i] point to this new node
        //         temp = temp->children[i];
        //     }

        //     //node alr created
        //     temp = temp->children[i];
        // }


        // //reached end of a word after reading all its chars
        // else
        // {
        //     temp->is_word = true;
        //     dictsize++;

        //     //IMPT!!! rewind temp BACK TO ROOT
        //     temp = root;
        // }


for (int i = 0; i < 27; i++)
    {   // BASE case
        if (temp->children[i] == NULL)
        {
            free(temp);
        }

        //RECURSIVE case
        else if (temp->children[i] != NULL)
        {
            temp = temp->children[i];
        }
    }

    return true;





            else if (lowletter == '\0')
        {
            if (temp->is_word == true)
            {
              return true;
            }

            else if (temp->is_word == false)
            {
                return false;
            }
        }