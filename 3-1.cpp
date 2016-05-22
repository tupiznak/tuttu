/*
Вычислить разницу глубин наивного дерева поиска и декартового дерева. Разница может быть отрицательна.
*/
#include <iostream>
#include <stdlib.h>

using namespace std;

template<class T>
struct BSTNode
{
    BSTNode *left;
    BSTNode *right;
    T data;
    BSTNode(const T& data):
        left(NULL),
        right(NULL),
        data(data){};
}; 

template <class T>
class Tree
{
public:
    Tree():
        root(NULL){};
    ~Tree(){};
    
    void Add(const T& data);
    bool Has(const T& data) const;
    void List(const BSTNode<T> *node) const;
    void Destroy(BSTNode<T> *node);
    BSTNode<T> *Root() const{return root;};
    int Height(BSTNode<T> *node) const;
private:
    BSTNode<T> *root;
};

template <class T>
void Tree<T>::Destroy(BSTNode<T> *node)
{
    if(node==NULL)
        return;
    Destroy(node->left);  
    Destroy(node->right);
    delete node;  
}

template <class T>
void Tree<T>::Add(const T& data)
{
    BSTNode<T> **node=&root;
    for(;*node;)
    {
        if((*node)->data<=data)
            node=&(*node)->right;
        else
            node=&(*node)->left;
    }
    *node=new BSTNode<T>(data);
}

template <class T>
void Tree<T>::List(const BSTNode<T> *node) const
{
    if(node==NULL)
        return;
    cout<<node->data<<" ";    
    List(node->left);
    List(node->right);
}

template <class T>
int Tree<T>::Height(BSTNode<T> *node) const
{
    if(node==NULL)
        return 1;
    int tmp1=Height(node->left);
    int tmp2=Height(node->right);
    return tmp1>tmp2?tmp1+1:tmp2+1;
}

template<class T>
struct DecartNode
{
    DecartNode *left;
    DecartNode *right;
    T data;
    long long int priority;
    DecartNode(const T& data, const long long int priority):
        left(NULL),
        right(NULL),
        data(data),
        priority(priority){};
}; 

template <class T>
class DecartTree
{
public:
    DecartTree():
        root(NULL){};
    ~DecartTree(){};
    
    void Add(const T& data, const long long int priority, DecartNode<T> *&node);
    DecartNode<T> *Search(const long long int priority) const;
    void List(const DecartNode<T> *node) const;
    void Destroy(DecartNode<T> *node);
    DecartNode<T> *Root() const{return root;};
    int Height(DecartNode<T> *node) const;
private:
    DecartNode<T> *root;
    void Split( DecartNode<T>* currentNode, const T& key, DecartNode<T>*& left,DecartNode<T>*& right );
    DecartNode<T>* Merge( DecartNode<T>* left, DecartNode<T>* right );
};

template <class T>
void DecartTree<T>::Split( DecartNode<T>* currentNode, const T& key, DecartNode<T>*& left,DecartNode<T>*& right )
{
    if( currentNode == 0 ) 
    {
        left = 0;
        right = 0;
    } 
    else if( currentNode->data <= key ) 
    {
        Split( currentNode->right, key, currentNode->right, right );
        left = currentNode;
    } 
    else 
    {
        Split( currentNode->left, key, left, currentNode->left );
        right = currentNode;
    }
}

template <class T>
DecartNode<T>* DecartTree<T>::Merge( DecartNode<T>* left, DecartNode<T>* right )
{
    if( left == 0 || right == 0 )
        return left == 0 ? right : left;
    if( left->priority > right->priority ) 
    {
        left->right = Merge( left->right, right );
        return left;
    }
    right->left = Merge( left, right->left );
    return right;
}

template <class T>
void DecartTree<T>::Destroy(DecartNode<T> *node)
{
    if(node==NULL)
        return;
    Destroy(node->left);  
    Destroy(node->right);
    delete node;  
}

template <class T>
void DecartTree<T>::Add(const T& data, const long long int priority, DecartNode<T>*& node)
{
    if(node == NULL)
    {
        node = new DecartNode<T>(data, priority);  
        return;
    }
    if(priority <= node->priority)
    {
        if(node->data > data)
            Add(data, priority, node->left);
        else 
            Add(data, priority, node->right);
    }
    else
    {
        DecartNode<T>* left = NULL;
        DecartNode<T>* right = NULL;
        
        Split(node, data, left, right);
        
        DecartNode<T>* curr = new DecartNode<T>(data, priority);
        curr->left = left;
        curr->right = right;
        
        node = curr;
    }
}

template <class T>
DecartNode<T> *DecartTree<T>::Search(const long long int priority) const
{
    const DecartNode<T> *node=root;
	for(;;)
	{
		if (node == NULL) return 0;
		else if (priority < node->priority) node = node->left;  
		else return node;  
	}
}

template <class T>
void DecartTree<T>::List(const DecartNode<T> *node) const
{
    if(node==NULL)
        return;
    cout<<node->data<<" ";    
    List(node->left);
    List(node->right);
}

template <class T>
int DecartTree<T>::Height(DecartNode<T> *node) const
{
    if(node==NULL)
        return 1;
    int tmp1=Height(node->left);
    int tmp2=Height(node->right);
    return tmp1>tmp2?tmp1+1:tmp2+1;
}

int main()
{
    DecartTree<long long int> a;
    DecartNode<long long int> *root=a.Root();
    Tree<long long int> b;
    int n;
    cin>>n;
    for(int i=0,tmp_k,tmp_p;i<n;i++)
    {
        cin>>tmp_k>>tmp_p;
        a.Add(tmp_k,tmp_p,root);
        b.Add(tmp_k);
    }
    cout<<b.Height(b.Root())-a.Height(root);
    a.Destroy(root);
    b.Destroy(b.Root());
//    system("pause");
    return 0;
}
