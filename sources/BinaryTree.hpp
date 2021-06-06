#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <memory>
#include <stack>



namespace ariel
{
    template <typename T>
    class BinaryTree
    {

        struct Node
        {
            T value;
            Node *right;
            Node *left;

            Node(T val) : value(val), right(nullptr), left(nullptr) {}
            Node(const Node* n) : value(n->value)
            {
                    if (n->left != nullptr)
                    {
                        this->left = new Node(n->left);
                    }
                    if (n->right != nullptr)
                    {
                        this->right = new Node(n->right);
                    }
            }

       
        };
        class _iterator
        {
            void in_order(Node *r);

            void post_order(Node *r);

            void pre_order(Node *r);
         
            unsigned long i;
            typename std::vector<Node *> order;
           

        public:
            _iterator(int type, Node *n) : i(0)
            {
                if (type == 1)
                {

                    in_order(n);
                }
                else if (type == 2)
                {
                    pre_order(n);
                }
                else if (type == 3)
                {
                    post_order(n);
                }
               
                order.push_back(nullptr);
            }


            _iterator &operator++()
            {
                ++i;
                return *this;
            }

            _iterator operator++(int)
            {
                _iterator ans = *this;
                ++i;
                return ans;
            }

            T &operator*()
            {
                return this->order[i]->value;
            }

            T *operator->()
            {
                return &(this->order[i]->value);
            }

            bool operator==(const _iterator &it) const
            {
                return order[i] == it.order[it.i];
            }

            bool operator!=(const _iterator &it) const
            {
                return order[i]  != it.order[it.i];
            }
        };

        Node *root ;
     


    public:
    
        BinaryTree<T>():root(nullptr)
        {
        }
        BinaryTree(const BinaryTree &o)
        {
            if (o.root != nullptr)
            {
                root = new Node(o.root);
            }
        }

        BinaryTree(BinaryTree &&n) noexcept
        {

            root = n.root;
            n.root = nullptr;
        }
        BinaryTree &operator=(BinaryTree &&n) noexcept
        {
          

            root = n.root;
            n.root = nullptr;

            return *this;
        }
        BinaryTree& operator=(const BinaryTree &n)
        {
            if (this == &n)
            {
                return *this;
            }

            delete(this->root);

            root = new Node(n.root);
            
            return *this;
        }
       
       
        ~BinaryTree()
        {
            if (this->root!=nullptr)
            {
              delete this->root;
            }
            
        }
        BinaryTree<T> &add_root(T r);

        BinaryTree<T> &add_left(T e, T add);

        BinaryTree<T> &add_right(T e, T add);

        _iterator begin()
        {
        
            return _iterator(1, root);
        }
        _iterator end()
        {
            return _iterator(1, nullptr);
        }
        _iterator begin_inorder()
        {
     
            return  begin();
        }
        _iterator end_inorder()
        {
        
            return end();
        }
        _iterator begin_preorder()
        {
     
            return _iterator(2, root);
        }
        _iterator end_preorder()
        {
            return _iterator(2, nullptr);
        }
        _iterator begin_postorder()
        {
           
            return _iterator(3, root);
        }
        _iterator end_postorder()
        {
            return _iterator(3, nullptr);
        }
        Node *find(T tofind)
        {
 
            std::stack<Node *> stack;
            Node *curr = root;

            while (curr != nullptr ||!static_cast<bool>(stack.empty()))
            {
                while (curr != nullptr)
                {
                    if (curr->value == tofind)
                    {
                        return curr;
                    }
                    stack.push(curr);
                    curr = curr->left;
                }
                curr = stack.top();
                stack.pop();
                curr = curr->right;
            }
            return nullptr;
        }
        template <typename O>
        friend std::ostream &operator<<(std::ostream &out, BinaryTree<T> const &b);
      
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &out, BinaryTree<T> const &b)
    {

        out << "tree";
        return out;
    }
    template <typename T>
    void BinaryTree<T>::_iterator::in_order(Node *r)
    {
        if (r == nullptr)
        {
            return;
        }
        in_order(r->left);
        order.push_back(r);
        in_order(r->right);
    }

    template <typename T>
    void BinaryTree<T>::_iterator::post_order(Node *r)
    {
        if (r == nullptr)
        {
            return;
        }
        post_order(r->left);
        post_order(r->right);
        order.push_back(r);
    }
    template <typename T>
    void BinaryTree<T>::_iterator::pre_order(Node *r)
    {
        {
            if (r == nullptr)
            {
                return;
            }
            order.push_back(r);
            pre_order(r->left);
            pre_order(r->right);
        }
    }
    template <typename T>
    BinaryTree<T> &BinaryTree<T>::add_root(T r)
    {
        if (root == nullptr)
        {
            root = new Node(r);
        }
        else
        {
            root->value = r;
        }

        return *this;
    }
    template <typename T>
    BinaryTree<T> &BinaryTree<T>::add_right(T e, T add)
    {
        Node *ex = find(e);
        if (ex == nullptr)
        {

            throw std::invalid_argument{"e does not exsist in the tree"};
        }
        if (ex->right == nullptr)
        {
            ex->right = new Node(add);
        }
        else
        {
            ex->right->value = add;
        }

        return *this;
    }
    template <typename T>
    BinaryTree<T> &BinaryTree<T>::add_left(T e, T add)
    {
        Node *ex = find(e);
        if (ex == nullptr)
        {

            throw std::invalid_argument{"e does not exsist in the tree"};
        }
        if (ex->left == nullptr)
        {
            ex->left = new Node(add);
        }
        else
        {
            ex->left->value = add;
        }

        return *this;
    }
}
