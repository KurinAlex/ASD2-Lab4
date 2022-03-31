# Algorithms and data structures 2 - Lab 4

Implement a binary search tree to effectively solve the problem.
Structure Player has the following fields: nickname, rank, amount of experience, donut size, etc. 
Create a sorted "database" of players, in which you can quickly check the presence of the desired player and find all the players in the specified interval:
1. Create a structure for storing objects with characteristics according to the selected task, 
   choose a criterion for comparing two objects and overload the necessary operators.
2. Implement a binary search tree:
    1. Create a base element of the Node tree that will contain data and pointers to two descendants - left and right. 
       If necessary, add a pointer to the parent node.
    2. Create a BinarySearchTree structure with the basic methods of the binary search tree without balancing:
        - insert (object) add a new element to the tree (no duplicates)
        - find (object) check the presence of an element in the tree
        - erase (object) to delete an element from the tree
        - size () find the number of elements in the tree
    3. Implement additional methods for working with wood:
        - print () print all tree elements in sorted order
        - height () find the height of the tree
        - findInRange (minObject, maxObject) find all elements in the tree between [minObject, maxObject], 
          return their number (or dynamic array (vector) with these elements)
3. Perform the test using testBinarySearchTree () function. Check the correctness and speed of work, comparing with the ready-made library solution STL set.
   
Optional extra task:
1. Implement binary search tree methods to work with subtrees:
    - merge (tree1, tree2) combine two trees into one
    - split (tree, object) to divide the binary search tree by key into two others, in the first all elements <object, in the second> = object
    - eraseRange (minObject, maxObject) delete all tree elements in the [minObject, maxObject] interval using the methods created above
2. Implement in BinarySearchTree the logic of balancing by type of AVL-tree or other balanced tree (red-ebony tree, splay tree)

Additional task:
Implement a prefix tree for the autocomplete program.
Example of execution:
Input: algorithm
Output: algorithm, algorithmic, algorithmically, algorithms
1. Create a basic element of the Node tree, which will contain a hash table, where the key is a text symbol, 
   the value is a pointer to the corresponding Node, as well as a Boolean note whether this node is the end of the word. 
   You can use a static or dynamic array instead of a hash table, although this is not very optimal.
2. Create a Trie structure and implement the basic methods of the prefix tree:
    - insert (word) add a new word to the tree
    - findByPrefix (word) find all words that start with a given prefix
3. Read from the file all existing words and build a prefix tree with them. The word file can be found here:
    - https://github.com/dwyl/english-words/raw/master/words_alpha.txt
    - https://github.com/dwyl/english-words/blob/master/words_alpha.zip?raw=true
4. Test the correctness of the prefix tree, using different prefixes entered from the keyboard.
