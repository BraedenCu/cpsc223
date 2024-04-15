#include "BSTNode.h"

#include <cassert>
#include <algorithm>
#include <string>
#include <vector>

#define ABORT_UNLESS(e) \
    if (!(e))           \
    {                   \
        return;         \
    }

/********************
 * FRIEND FUNCTIONS *
 ********************/

/**
 * This function is implemented for you, for your convenience.
 *
 * @param dir a direction
 * @return the opposite of dir, or ROOT if dir is ROOT.
 */
BSTNode::Direction opposite_direction(BSTNode::Direction dir)
{
    // Two implementations are shown (one commented out). You may use either.

    // BSTNode::Direction opp = dir;
    // if (dir == BSTNode::Direction::LEFT)
    // {
    //     opp = BSTNode::Direction::RIGHT;
    // }
    // else if (dir == BSTNode::Direction::RIGHT)
    // {
    //     opp = BSTNode::Direction::LEFT;
    // }
    // return opp;
    return BSTNode::Direction(BSTNode::Direction::RIGHT - dir);
}

/***********************
 *       GETTERS       *
 * IMPLEMENTED FOR YOU *
 ***********************/

int BSTNode::data() const
{
    return this->mData;
}

int BSTNode::count() const
{
    return this->mCount;
}

int BSTNode::height() const
{
    return this->mHeight;
}

const BSTNode *BSTNode::left_child() const
{
    return this->mLeft;
}

const BSTNode *BSTNode::right_child() const
{
    return this->mRight;
}

/********************
 * CONSTRUCTORS AND *
 *    DESTRUCTOR    *
 ********************/

/*
 * These BSTNode constructors use intializer lists. They are complete and you
 *  may not modify them.
 *
 * More info here: https://en.cppreference.com/w/cpp/language/constructor
 */
BSTNode::BSTNode() : mCount(0),
                     mHeight(-1), mColor(BLACK),
                     mLeft(nullptr), mRight(nullptr), parent(nullptr)
{
}

BSTNode::BSTNode(int data)
    : mData(data),
      mCount(1),
      mHeight(0),
      mColor(BLACK),
      mLeft(new BSTNode()),
      mRight(new BSTNode()),
      parent(nullptr) {}

/*
 * The BSTNode copy constructor is incomplete. YOU MUST COMPLETE IT. You may
 *  use an initializer list, or you may write a traditional constructor
 *  function, or both.
 */

/**
 * Copy constructor.
 *
 * @param other the node to copy
 * @return the root of a tree that is a copy of the tree rooted at other
 * @result creates a new node with the same properties as other by
 *  performing a pre-order deep copy of the tree rooted at other. The root
 *  of the new tree has parent nullptr (it is considered the ultimate root
 *  of its tree).
 *
 * Runtime Complexity: O(n)
 */
/**
 * Copy constructor: make a copy of everything from the “other” BSTNode
○ Some values can be easily copied over by simply setting them equal to your “this” values,
others require a more in-depth approach
○ Should be a pre-order deep copy (visit root, then left, then right). All nodes should be copied,
not just direct children.
○ As you copy all nodes, update other values as needed
○ Have default values if we don’t know something exists yet*/
BSTNode::BSTNode(const BSTNode &other)
    : mData(other.mData), mCount(other.mCount), mHeight(other.mHeight), mColor(other.mColor), parent(nullptr)
{
    if (other.has_child(LEFT) && !other.mLeft->is_empty()) 
    {
        mLeft = new BSTNode(*other.mLeft);
        mLeft->parent = this;  // Set the parent pointer of the left child
    } 
    else 
    {
        mLeft = new BSTNode();  // Create a sentinel node for the left child
    }

    // Copy the right subtree if it exists and is not a sentinel node
    if (other.has_child(RIGHT) && !other.mRight->is_empty()) 
    {
        mRight = new BSTNode(*other.mRight);
        mRight->parent = this;  // Set the parent pointer of the right child
    } 
    else 
    {
        mRight = new BSTNode();  // Create a sentinel node for the right child
    }
}


/**
 * Destructor.
 *
 * @param this the root of the tree to free
 * @result Performs a post-order delete to free all memory owned by this.
 *
 * Remember: `this` is automatically freed at the end of a destructor.
 *
 * Runtime Complexity: O(n)
 */
BSTNode::~BSTNode()
{
//  TODO TODO FIX FIX FIX
    if (this->has_child(LEFT)) {
        delete mLeft;
    }

    if (this->has_child(RIGHT)) {
        delete mRight;
    }
}

/********************
 * PUBLIC FUNCTIONS *
 ********************/

/**
 * Returns the minimum value in the tree rooted at this.
 *
 * @param this the root of the tree
 * @return a pointer to the node with the minimum value in the tree rooted
 *  at this
 * @assumes this is not an empty tree
 *
 * Runtime Complexity: O([height of tree rooted at this])
 */
const BSTNode *BSTNode::minimum_value() const
{
// TODO TODO FIX FIX FIX

    const BSTNode* current = this;
    while (current->has_child(LEFT)) 
    {
        current = current->left_child();
    }

    return current;
}

/**
 * Returns the maximum value in the tree rooted at this.
 *
 * @param this the root of the tree
 * @return a pointer to the node with the maximum value in the tree rooted
 *  at this
 * @assumes this is not an empty tree
 *
 * Runtime Complexity: O([height of tree rooted at this])
 */
const BSTNode *BSTNode::maximum_value() const
{
// TODO TODO FIX FIX FIX
    const BSTNode* current = this;
    while (current->has_child(RIGHT)) 
    {
        current = current->right_child();
    }

    return current;
}

/**
 * @param this the root of the tree
 * @return the total of all counts in the tree rooted at this
 *
 * Runtime Complexity: O(n)
 */
int BSTNode::count_total() const
{
// TODO TODO FIX FIX FIX
    if (is_empty()) 
    {
        return 0;
    } 
    else 
    {
        int count = mCount;
        if (has_child(LEFT)) 
        {
            count += left_child()->count_total();
        }
        if (has_child(RIGHT)) 
        {
            count += right_child()->count_total();
        }
        return count;
    }
}


/**
 * Searches for value in this.
 *
 * @param this the root of the tree
 * @param value the value for which to search in the tree
 * @return a pointer to the node with value in the tree rooted at this, or
 *  an empty tree if value is not in this
 *
 * Runtime Complexity: O([height of tree rooted at this])
 */
const BSTNode *BSTNode::search(int value) const
{
// TODO TODO FIX FIX
    if (value == mData) 
    {
        return this;
    } 
    else if (value < mData && has_child(LEFT)) 
    {
        return mLeft->search(value);
    } 
    else if (value > mData && has_child(RIGHT))
    {
        return mRight->search(value);
    } 
    else 
    {
        // return empty tree
        return new BSTNode();
    }
}

/**
 * Inserts value into this.
 *
 * @param this the root of the tree
 * @param value the value to insert
 * @return a pointer to the root of the tree into which value has just been
 *  inserted, with parent `nullptr`
 * @result inserts (a single occurrence of) value into the tree rooted at
 *  this. Uses the "naive BST" insertion algorithm.
 *
 * Runtime Complexity: O([height of tree rooted at this])
 */

/**
 * Insert: Insert a particular value into the tree
○ Find where the value should go using the binary search tree invariant
○ Note the case of that value already existing in the tree (mCount)
○ Assuming you get to where the value should go and it doesn’t already exist, there should be an
empty node there. Make sure you deal with it
○ Return root of the tree into which value was just inserted
*/
BSTNode* BSTNode::bst_insert(int value) 
{
// TODO TODO WORKING
    BSTNode *root = this;

    if(is_empty()) 
    {
        BSTNode* left = new BSTNode();
        BSTNode* right = new BSTNode();
        this->mData = value;
        this->mCount += 1;
        this->mRight = left;
        this->mLeft = right;
        this->mHeight = 0;
    }
    else if(this->mData == value) 
    {
        mCount +=1;
    }
    else if(this->mData == value) 
    {
        mCount += 1;
    }
    else 
    {
        if (value > mData) 
        {
            mRight -> bst_insert(value);
        }
        else 
        {
            mLeft -> bst_insert(value);
        }
    }

    make_locally_consistent();
    return root;
}


BSTNode *BSTNode::avl_insert(int value)
{
    BSTNode *root = this;

    if (root->is_empty())
    {
        delete root;
        root = new BSTNode(value);
    }
    else if (root->mData > value)
    {
        root->mLeft = root->mLeft->avl_insert(value);
    }
    else if (root->mData < value)
    {
        root->mRight = root->mRight->avl_insert(value);
    }
    else
    {
        root->mCount++;
    }

    root->make_locally_consistent();

    return root->avl_balance();
}

BSTNode *BSTNode::rbt_insert(int value)
{
    // This function is implemented for you, but rbt_insert_helper is not.
    // Think about why the helper function is useful or necessary.

    BSTNode *root = this->rbt_insert_helper(value);
    root->mColor = Color::BLACK;
    return root;
}

/*
 * This function is private, but is is kept here for locality with rbt_insert.
 */
BSTNode *BSTNode::rbt_insert_helper(int value)
{
    BSTNode *root = this;

    if (root->is_empty())
    {
        delete root;
        root = new BSTNode(value);
        root->mColor = RED;
    }
    else if (root->mData < value)
    {
        root->mRight = root->mRight->rbt_insert_helper(value);
    }
    else if (root->mData > value)
    {
        root->mLeft = root->mLeft->rbt_insert_helper(value);
    }
    else
    {
        root->mCount++;
    }

    root->make_locally_consistent();

    return root->rbt_eliminate_red_red_violation();
}


BSTNode *BSTNode::bst_remove(int value)
{
    /********************************
     ****** BST Removal Begins ******
     ********************************/

    // Do the removal
    BSTNode *root = this;
    
    // case one: mCount greater than 1
    if (value == mData && mCount > 1) 
    {
        mCount -= 1; // decrement the count
    } 
    else if (value < mData && has_child(LEFT)) 
    {
        mLeft = mLeft->bst_remove(value); // continue recursing
    } 
    else if (value > mData && has_child(RIGHT)) 
    {
        mRight = mRight->bst_remove(value); // continue recursing
    } 
    else if (value == mData) // when value to remove is found
    {
        if (has_child(LEFT) && has_child(RIGHT)) 
        {
            // case two: node has 2 children
            BSTNode* replacement = (BSTNode*) mRight->minimum_value();
            mData = replacement->mData;
            mCount = replacement->mCount;
            replacement->mCount = 1;
            mRight = mRight->bst_remove(replacement->mData);
           
        } 
        else if (has_child(LEFT) && !has_child(RIGHT)) 
        {
            // case three: node has 1 child (left)
            BSTNode* left = mLeft;    
            //delete this;
            return left;
            
        } 
        else if (!has_child(LEFT) && has_child(RIGHT)) 
        {
            // case three: node has 1 child (right)
            BSTNode* right = mRight;
            //delete this;
            return right;
        } 
        else 
        {
            // case four: node has no children
            //delete this;
            return new BSTNode();
        }
    }
    // Make the root locally consistent
    make_locally_consistent();

    /********************************
     ****** BST Removal Ends ******
     ********************************/

    return root;
}

BSTNode *BSTNode::avl_remove(int value)
{
    BSTNode *root = this;

    if (root->mData > value) // recurse left
    {
        root->mLeft = root->mLeft->avl_remove(value);
    }
    else if (root->mData < value) // recurse right
    {
        root->mRight = root->mRight->avl_remove(value);
    }
    else if (root->mData == value) // target found
    {
        if (root->mCount > 1)
        {
            root->mCount--;
        }
        else if (root->mLeft->is_empty() && root->mRight->is_empty()) // no children
        {
            delete root;
            root = new BSTNode();
            root->make_locally_consistent();
        }
        else if (!root->mLeft->is_empty() && root->mRight->is_empty()) // one left child
        {
            BSTNode *temp = new BSTNode(*root->mLeft);
            delete root;
            root = temp;
        }
        else if (root->mLeft->is_empty() && !root->mRight->is_empty()) // one right child
        {
            BSTNode *temp = new BSTNode(*root->mRight);
            delete root;
            root = temp;
        }
        else
        {
            BSTNode *right_successor = (BSTNode *)root->mRight->minimum_value(); // find the successor
            root->mData = right_successor->mData;
            root->mCount = right_successor->mCount;
            right_successor->mCount = 1;
            root->mRight = root->mRight->avl_remove(right_successor->mData); // remove the successor
        }
    }
    root->make_locally_consistent();

    return root->avl_balance();
}

BSTNode *BSTNode::rbt_remove(int value)
{
    // This function is implemented for you.

    BHVNeighborhood nb(this, ROOT);
    BSTNode *to_delete = nullptr;
    BSTNode *root = this->rbt_remove_helper(value, nb, to_delete);
    nb.fix_blackheight_imbalance();
    delete to_delete;
    return root;
}

/**
 * @param this the root of the tree
 * @return the number of non-empty nodes in the tree rooted at this
 *
 * Runtime Complexity: O(n)
 */
int BSTNode::node_count() const
{
// TODO TODO FIX FIX FIX
    if (is_empty()) 
    {
        return 0;
    } 
    else 
    {
        int count = 1;
        if (has_child(LEFT)) 
        {
            count += left_child()->node_count();
        }
        if (has_child(RIGHT)) 
        {
            count += right_child()->node_count();
        }
        return count;
    }
}

bool BSTNode::is_empty() const
{
    // This function is implemented for you.

    // There are three ways to determine if a binary search tree is empty:
    //  By multiplicity
    bool empty_by_count = this->mCount == 0;

    // By height
    bool empty_by_height = this->mHeight == -1;

    // By children
    bool empty_by_children = !this->mLeft && !this->mRight;

    // All three should give the same answer.
    // If they don't, then something is very wrong!
    assert(!this->mLeft == !this->mRight);
    assert(empty_by_count == empty_by_height);
    assert(empty_by_height == empty_by_children);

    // Return any of the equivalent checks
    return empty_by_count;
}

/*************************
 * BEGIN PRIVATE SECTION *
 *************************/

BSTNode *BSTNode::child(Direction dir) const
{
    // This function is implemented for you.

    BSTNode *child = nullptr;
    if (dir == LEFT)
    {
        child = this->mLeft;
    }
    else if (dir == RIGHT)
    {
        child = this->mRight;
    }
    return child;
}

void BSTNode::set_child(Direction dir, BSTNode *child)
{
    // This function is implemented for you.

    if (dir != ROOT)
    {
        if (dir == LEFT)
        {
            this->mLeft = child;
        }
        else if (dir == RIGHT)
        {
            this->mRight = child;
        }
        child->parent = this;
    }
}

bool BSTNode::has_child(Direction dir) const
{
    // This function is implemented for you.

    return !this->is_empty() && !this->child(dir)->is_empty();
}

BSTNode::RRVNeighborhood::RRVNeighborhood(BSTNode *root)
    : g{root}, p{nullptr}, x{nullptr}, y{nullptr}, shape{SHAPE_NONE}
{
    /*
     * This function is implemented for you. DO NOT MODIFY IT, but study it
     *  carefully so you know what is going on.
     */

    // Stop if g is RED or too short
    ABORT_UNLESS((this->g->mColor == BLACK) &&
                 (this->g->mHeight > 1));

    if (this->g->mLeft->mColor == BLACK)
    {
        // If there is a red-red violation, it's to the right
        this->y = this->g->mLeft;
        this->p = this->g->mRight;

        // Stop if g has two BLACK children
        ABORT_UNLESS(this->p->mColor == RED);

        if (this->p->mLeft->mColor == RED)
        {
            this->shape = RL;
            this->x = this->p->mLeft;
        }
        else
        {
            // Stop if there is no red-red violation
            ABORT_UNLESS(this->p->mRight->mColor == RED);

            this->shape = RR;
            this->x = this->p->mRight;
        }
    }
    else if (this->g->mRight->mColor == BLACK)
    {
        // If there is a red-red violation, it's to the left
        this->y = this->g->mRight;
        this->p = this->g->mLeft;

        if (this->p->mLeft->mColor == RED)
        {
            this->shape = Shape::LL;
            this->x = this->p->mLeft;
        }
        else
        {
            // Stop if there is no red-red violation
            ABORT_UNLESS(p->mRight->mColor == RED);

            this->shape = LR;
            this->x = this->p->mRight;
        }
    }
    else
    {
        // Both children of g are RED. Find the red-red violation
        BSTNode *lc = this->g->mLeft;
        BSTNode *llc = lc->mLeft;
        BSTNode *lrc = lc->mRight;
        BSTNode *rc = this->g->mRight;
        BSTNode *rlc = rc->mLeft;
        BSTNode *rrc = rc->mRight;

        if (llc && llc->mColor == RED)
        {
            this->shape = LL;
            this->p = lc;
            this->x = llc;
            this->y = rc;
        }

        if (lrc && lrc->mColor == RED)
        {
            // Stop if there are multiple red-red violations
            ABORT_UNLESS(this->shape == SHAPE_NONE);

            this->shape = LR;
            this->p = lc;
            this->x = lrc;
            this->y = rc;
        }

        if (rlc && rlc->mColor == RED)
        {
            // Stop if there are multiple red-red violations
            ABORT_UNLESS(this->shape == Shape::SHAPE_NONE);

            this->shape = Shape::RL;
            this->p = rc;
            this->x = rlc;
            this->y = lc;
        }

        if (rrc && rrc->mColor == RED)
        {
            // Stop if there are multiple red-red violations
            ABORT_UNLESS(this->shape == SHAPE_NONE);

            this->shape = RR;
            this->p = rc;
            this->x = rrc;
            this->y = lc;
        }

        // Stop if there is no red-red violation
        ABORT_UNLESS(this->shape != SHAPE_NONE);
    }
}

BSTNode::BHVNeighborhood::BHVNeighborhood(BSTNode *n, Direction dir)
    : n{n}, p{nullptr}, s{nullptr}, c{nullptr}, d{nullptr},
      del_case{CASE_NONE}, dir{dir}
{
    /*
     * This function is implemented for you. DO NOT MODIFY IT, but study it
     *  carefully so you know what is going on.
     */

    ABORT_UNLESS(this->n && !this->n->is_empty() &&
                 this->n->mColor == BLACK);

    this->p = this->n->parent;

    if (!this->p)
    {
        this->del_case = CASE_1;
        assert(dir == ROOT);
        this->dir = ROOT;
    }
    else
    {
        assert(!this->p->is_empty());
        assert(this->dir != ROOT);

        this->s = this->p->child(opposite_direction(dir));
        this->c = this->s->child(dir);
        this->d = this->s->child(opposite_direction(dir));

        if (this->p->mColor == BLACK &&
            this->s->mColor == BLACK &&
            (!this->c || this->c->mColor == BLACK) &&
            (!this->d || this->d->mColor == BLACK))
        {
            this->del_case = CASE_2;
        }
        else if (this->p->mColor == BLACK &&
                 this->s->mColor == RED)
        {
            assert(this->c && this->c->mColor == BLACK);
            assert(this->d && this->d->mColor == BLACK);

            this->del_case = CASE_3;
        }
        else if (this->p->mColor == RED &&
                 this->s->mColor == BLACK &&
                 (!this->c || this->c->mColor == BLACK) &&
                 (!this->d || this->d->mColor == BLACK))
        {
            this->del_case = CASE_4;
        }
        else if (this->s->mColor == BLACK &&
                 (this->c && this->c->mColor == RED) &&
                 (!this->d || this->d->mColor == BLACK))
        {
            this->del_case = CASE_5;
        }
        else if (this->s->mColor == BLACK &&
                 (this->d && this->d->mColor == RED))
        {
            this->del_case = CASE_6;
        }
        else
        {
            this->del_case = CASE_NONE;
        }
    }
}

BSTNode *BSTNode::rbt_remove_helper(int value, BHVNeighborhood &nb, BSTNode *&to_delete)
{
    // This function is implemented for you, for your convenience.
    // DO NOT MODIFY IT, but study it carefully so you know what is going on.

    BSTNode *root = this;

    // If root is empty, value is not in this tree, so do nothing.
    // Only if root is not empty, do something
    if (!root->is_empty())
    {
        if (value < root->mData)
        {
            nb.dir = LEFT;
            root->mLeft = root->mLeft->rbt_remove_helper(value, nb, to_delete);
        }
        else if (value > root->mData)
        {
            nb.dir = RIGHT;
            root->mRight = root->mRight->rbt_remove_helper(value, nb, to_delete);
        }
        else
        {
            // We found the value. Remove it.
            if (root->mCount > 1)
            {
                root->mCount--;
            }
            else
            {
                if (root->mLeft->is_empty() &&
                    root->mRight->is_empty())
                {
                    // root has no children. We may have to do extra work.

                    // Get its neighborhood
                    nb = BHVNeighborhood(this, nb.dir);

                    // Delete it
                    root = new BSTNode();
                    to_delete = this;
                }
                else if (!root->mLeft->is_empty() &&
                         root->mRight->is_empty())
                {
                    // this has one (left) child. Promote this's child
                    this->mLeft->mColor = root->mColor;
                    root = this->mLeft;
                    this->mLeft = nullptr;
                    to_delete = this;
                }
                else if (root->mLeft->is_empty() &&
                         !root->mRight->is_empty())
                {
                    // this has one (right) child. Promote this's child
                    this->mRight->mColor = this->mColor;
                    root = this->mRight;
                    this->mRight = nullptr;
                    to_delete = this;
                }
                else
                {
                    /*
                     * this has two children.
                     *
                     * Find the successor to use as a replacement, then remove it
                     * entirely from this's right subtree. This requires setting
                     * the replacement's multiplicity to 1 so that the node is entirely
                     * removed rather than simply having its multiplicity decremented.
                     * Removal is the only place a const-to-non-const cast should
                     * appear in your solution.
                     *
                     * TODO: (optional) Rewrite this section of code to eliminate
                     *  the const-to-non-const cast.
                     */

                    BSTNode *replacement = (BSTNode *)root->mRight->minimum_value();
                    root->mData = replacement->mData;
                    root->mCount = replacement->mCount;
                    replacement->mCount = 1;
                    nb.dir = RIGHT;
                    root->mRight = root->mRight->rbt_remove_helper(replacement->mData, nb, to_delete);
                }
            }
        }
    }

    root->make_locally_consistent();

    return root;
}

BSTNode *BSTNode::dir_rotate(Direction dir)
{
    // This function is implemented for you.

    BSTNode *root = this;
    if (dir == LEFT)
    {
        root = root->left_rotate();
    }
    else if (dir == RIGHT)
    {
        root = root->right_rotate();
    }
    return root;
}


BSTNode *BSTNode::right_rotate()
{
    // Leave this assert statement here for your own benefit.
    assert(!this->mLeft->is_empty());

    BSTNode *new_root       = this->mLeft;
    BSTNode *new_root_child = new_root->mRight;
    
    new_root->mRight = this;
    this->mLeft = new_root_child;

    this->make_locally_consistent();
    new_root->make_locally_consistent();

    return new_root;
}

BSTNode *BSTNode::left_rotate()
{
    // Leave this assert statement here for your own benefit.
    assert(!this->mRight->is_empty());

    BSTNode *new_root       = this->mRight;
    BSTNode *new_root_child = new_root->mLeft;

    new_root->mLeft = this;
    this->mRight = new_root_child;

    this->make_locally_consistent();
    new_root->make_locally_consistent();

    return new_root;
}


int BSTNode::find_avl_balance(BSTNode *node)
{
    if (node->is_empty())
    {
        return 0;
    }
    else {
        return node->mLeft->mHeight - node->mRight->mHeight;
    }
}

BSTNode *BSTNode::avl_balance()
{
    int bal = find_avl_balance(this);
    if (bal < -1)
    {
        if (find_avl_balance(this->mRight) <= 0) // R
        {
            return this->left_rotate(); // R + R
        }
        else
        {
            this->mRight = this->mRight->right_rotate(); // R + L
            return this->left_rotate(); 
        }
    }
    else if (bal > 1)
    {
        if (find_avl_balance(this->mLeft) >= 0) // L
        {
            return this->right_rotate(); // L + L
        }
        else
        {
            this->mLeft = this->mLeft->left_rotate(); // L + R
            return this->right_rotate();
        }
    }
    return this;
}



BSTNode *BSTNode::rbt_eliminate_red_red_violation()
{
    /*
     * Get this's neighborhood (children + grandchildren), which might have
     *  shape NONE if this is BLACK or this.height <= 1 or there is no red-red
     *  violation in the neighborhood of this.
     */
    RRVNeighborhood nb(this);

    if (nb.shape != SHAPE_NONE)
    {
        //uncle is red then swap colors
        if (nb.y->mColor == RED)
        {
            nb.g->mColor = RED;
            nb.p->mColor = BLACK;
            nb.y->mColor = BLACK;
        }
        else
        {
            switch (nb.shape)
            {
            case LR: // fixing LR case
                nb.g->mLeft = nb.g->mLeft->left_rotate();
                nb.g = nb.g->right_rotate();
                nb.g->swap_colors_with(nb.g->mRight);
                nb.g->make_locally_consistent();
                break;
            case LL: // fixing LL case 
                nb.g = nb.g->right_rotate();
                nb.g->swap_colors_with(nb.g->mRight);
                nb.g->make_locally_consistent();
                break;
            case RL: // fixing RL case
                nb.g->mRight = nb.g->mRight->right_rotate();
                nb.g = nb.g->left_rotate();
                nb.g->swap_colors_with(nb.g->mLeft);
                nb.g->make_locally_consistent();
                break;
            case RR: // fixing RR case
                nb.g = nb.g->left_rotate(); 
                nb.g->swap_colors_with(nb.g->mLeft);
                nb.g->make_locally_consistent();
                break;
            default:
                // INVALID case. Do nothing.
                break;
            }
            return nb.g; // new root
        }
    }
    return this;
}


void BSTNode::BHVNeighborhood::fix_blackheight_imbalance()
{
    /*
     * This function is implemented for you. DO NOT MODIFY IT, but study it
     *  carefully so you understand what is going on.
     */

    BHVNeighborhood nb = *this;

    // While we have a parent, thus we are not at the root
    while (nb.p)
    {

        // Find the direction of nb.p relative to its parent.
        Direction pdir = ROOT;
        if (nb.p->parent)
        {
            if (nb.p == nb.p->parent->mLeft)
            {
                pdir = LEFT;
            }
            else if (nb.p == nb.p->parent->mRight)
            {
                pdir = RIGHT;
            }
            else
            {
                /*
                 * nb.p->parent is non-null, so we must have a violated
                 *  invariant of our tree if we get here.
                 */
                assert(false);
            }
        }
        BSTNode *parent = nb.p->parent;

        // Decide which case to process
        switch (nb.del_case)
        {
        case CASE_2:
        {
            // p, s, c, d are all black
            assert(nb.p->mColor == BLACK);
            assert((nb.s == nullptr) || nb.s->mColor == BLACK);
            assert((nb.c == nullptr) || nb.c->mColor == BLACK);
            assert((nb.d == nullptr) || nb.d->mColor == BLACK);

            /*
             * After painting S red all paths passing through S, which are
             *  precisely those paths not passing through N, have one fewer
             *  black node. Now all paths in the subtree rooted by P have the
             *  same number of black nodes, but one fewer than the paths that
             *  do not pass through P. Recompute the neighborhood at P and
             *  iterate rebalancing up one tree level.
             */
            nb.s->mColor = RED;
            nb = BHVNeighborhood(nb.p, pdir);
            break;
        }
        case CASE_3:
        {
            // s red, so p, c, d black
            assert(nb.s->mColor == RED);
            assert(nb.p->mColor == BLACK);
            assert((nb.c == nullptr) || nb.c->mColor == BLACK);
            assert((nb.d == nullptr) || nb.d->mColor == BLACK);

            /*
             * A dir-rotation at P turns S into N’s grandparent. Then after
             *  reversing the colors of P and S, the path through N is still
             *  short one black node. But N now has a red parent P after the
             *  reassignment a black sibling S, so the transformations in cases
             *  CASE_4, CASE_5, or CASE_6 are able to restore the RB-shape.
             */
            BSTNode *s = nb.p->dir_rotate(nb.dir);
            assert(s == nb.s);
            if (pdir != ROOT)
            {
                parent->set_child(pdir, s);
            }
            nb.p->swap_colors_with(nb.s);
            nb = BHVNeighborhood(nb.n, nb.dir);
            assert(nb.del_case >= CASE_4);
            break;
        }
        case CASE_4:
        {
            // s, c, d black, and p red
            assert((nb.s == nullptr) || nb.s->mColor == BLACK);
            assert((nb.c == nullptr) || nb.c->mColor == BLACK);
            assert((nb.d == nullptr) || nb.d->mColor == BLACK);
            assert(nb.p->mColor == RED);

            /*
             * Exchanging the colors of S and P does not affect the number of
             *  black nodes on paths going through S, but it does add one to
             *  the number of black nodes on paths going through N, making up
             *  for the deleted black node on those paths. CASE_4 is a terminal
             *  case: after this step the tree is balanced.
             */
            nb.p->swap_colors_with(nb.s);
            return;
            break;
        }
        case CASE_5:
        {
            // s, d, black; c red
            assert(nb.s->mColor == BLACK);
            assert(nb.c->mColor == RED);
            assert((nb.d == nullptr) || nb.d->mColor == Color::BLACK);

            /*
             * After a (1-dir)-rotation at S the nephew C becomes S’s parent
             *  and N’s new sibling. The colors of S and C are exchanged. All
             *  paths still have the same number of black nodes, but now N has
             *  a black sibling whose distant child is red, so the neighborhood
             *  is in CASE_6. Neither N nor its parent P are affected by this
             *  transformation, and P may be red or black.
             */
            nb.p->set_child(opposite_direction(nb.dir),
                            nb.s->dir_rotate(opposite_direction(nb.dir)));
            nb.c->swap_colors_with(nb.s);
            nb = BHVNeighborhood(nb.n, nb.dir);
            assert(nb.del_case == CASE_6);
            break;
        }
        case CASE_6:
        {
            // s is black, d is red
            assert(nb.s && nb.s->mColor == BLACK);
            assert(nb.d && nb.d->mColor == RED);

            /**
             * After a dir-rotation at P the sibling S becomes the parent of P
             *  and S’s distant child D. The colors of P and S are exchanged,
             *  and D is made black. The whole subtree still has the same mColor
             *  at its root S, namely either red or black ( in the diagram),
             *  which refers to the same mColor both before and after the
             *  transformation. This way requirement 3 is preserved. The paths
             *  in the subtree not passing through N (i.o.w. passing through D
             *  and node 3 in the diagram) pass through the same number of
             *  black nodes as before, but N now has one additional black
             *  ancestor: either P has become black, or it was black and S was
             *  added as a black grandparent. Thus, the paths passing through N
             *  pass through one additional black node, so that requirement 4
             *  is restored and the total tree is in RB-shape. CASE_6 is a
             *  terminal case: after this step the tree is balanced.
             */
            BSTNode *s = nb.p->dir_rotate(nb.dir);
            assert(s == nb.s);
            if (pdir != ROOT)
            {
                parent->set_child(pdir, s);
            }
            nb.p->swap_colors_with(nb.s);
            nb.d->mColor = BLACK;
            return;
            break;
        }
        default:
            // CASE_NONE or CASE_1 (should never happen; nb.p is non-null)
            // Leave this assert statement here for your own benefit.
            assert(false);
            break;
        }
    }
}

int BSTNode::height_diff() const
{
    // This function is implemented for you.

    int diff = 0;
    if (!this->is_empty())
    {
        diff = this->mRight->mHeight - this->mLeft->mHeight;
    }
    return diff;
}

void BSTNode::make_locally_consistent()
{
    // This function is implemented for you.

    if (!this->is_empty())
    {
        this->mHeight = 1 + std::max(this->mLeft->mHeight,
                                     this->mRight->mHeight);
        this->mLeft->parent = this;
        this->mRight->parent = this;
    }
}

void BSTNode::swap_colors_with(BSTNode *other)
{
    // This function is implemented for you

    Color t = this->mColor;
    this->mColor = other->mColor;
    other->mColor = t;
}