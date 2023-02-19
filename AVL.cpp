#include "AVL.h"

#include <iostream>
using namespace std;

AVL::AVL()
{
    numofwords=0;
}

void AVL::destroyTree(NodeAVL *r)
{
    if (r!=nullptr)
        //αν το δένδρο δεν είναι άδειο καταστρέφονται αναδρομικά το δεξί και το αριστερό υποδένδρο
    {
        destroyTree(r->left);
        destroyTree(r->right);
        delete(r);
    }
}

int AVL::max(int a, int b)
{
    if(a>b)
        return a;
    else
        return b;
}

int AVL::height(NodeAVL *N)
{
    if(N==nullptr)
        return 0;
    return N->height;
}

int AVL::getBalance(NodeAVL *N)
{
    if(N==nullptr)
        return 0;
    return height(N->left)-height(N->right);
}

NodeAVL *AVL::rightRotate(NodeAVL *y)
{
    NodeAVL *x=y->left;
    NodeAVL *T2=x->right;

    //Εκτέλεση περιστροφής
    x->right=y;
    y->left=T2;

    //Ενημέρωση ύψους κόμβων
    y->height=max(height(y->left), height(y->right))+1;
    x->height=max(height(x->left), height(x->right))+1;

    //Επιστροφή νέας ρίζας
    return x;
}

NodeAVL *AVL::leftRotate(NodeAVL *x)
{
    NodeAVL *y=x->right;
    NodeAVL *T2=y->left;

    //Εκτέλεση περιστροφής
    y->left=x;
    x->right=T2;

    //Ενημέρωση ύψους κόμβων
    x->height=max(height(x->left), height(x->right))+1;
    y->height=max(height(y->left), height(y->right))+1;

    //Επιστροφή νέας ρίζας
    return y;
}

NodeAVL* AVL::newNode(string w, int counter)
{
    NodeAVL* node=new NodeAVL();
    node->word=w;
    node->cnt=counter;
    node->left=nullptr;
    node->right=nullptr;
    node->height=1; //ο νέος κόμβος προστίθεται αρχικά ως φύλλο
    return(node);
}

NodeAVL* AVL::insert_word(NodeAVL* node, const string &word)
{
    if(node==nullptr)
    {
        numofwords++;
        return(newNode(word,1));
    }

    if(word<node->word) //αν η λέξη είναι μικρότερη από την λέξη του κόμβου
        node->left=insert_word(node->left, word); //αναδρομική κλήση για την εισαγωγή της λέξης στο αριστερό υποδένδρο
    else if(word>node->word) //αν η λέξη είναι μεγαλύτερη από την λέξη του κόμβου
        node->right=insert_word(node->right, word); //αναδρομική κλήση για την εισαγωγή της λέξης στο δεξί υποδένδρο
    else //αν η λέξη υπάρχει ήδη στο δένδρο
    {
        node->cnt=node->cnt+1; //αυξάνεται το πλήθος εμφανίσεων της λέξης
        return node;
    }

    //ενημέρωση ύψους του κόμβου
    node->height=1+max(height(node->left), height(node->right));

    //έλεγχος αν το δένδρο είναι ισοζυγισμένο
    int balance=getBalance(node);

    //αν το δένδρο δεν είναι ισοζυγισμένο υπάρχουν 4 περιπτώσεις

    //Left Left Case
    if(balance>1 && word<node->left->word)
        return rightRotate(node);

    //Right Right Case
    if(balance<-1 && word>node->right->word)
        return leftRotate(node);

    //Left Right Case
    if(balance>1 && word>node->left->word)
    {
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }

    //Right Left Case
    if(balance<-1 && word<node->right->word)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    //επιστροφή του κόμβου (που δεν έχει αλλάξει)
    return node;
}

void AVL::inOrder(NodeAVL *p) //Left, Root, Right
{
    if (p==nullptr)
        return;

    inOrder(p->left);
    cout<<p->word<<" "<<p->cnt<<endl;
    inOrder(p->right);
}

void AVL::preOrder(NodeAVL *p) //Root, Left, Right
{
    if (p==nullptr)
        return;
    cout<<p->word<<" "<<p->cnt<<endl;
    preOrder(p->left);
    preOrder(p->right);
}

void AVL::postOrder(NodeAVL *p) //Left, Right, Root
{
    if(p==nullptr)
        return;
    postOrder(p->left);
    postOrder(p->right);
    cout<<p->word<<" "<<p->cnt<<endl;
}

int AVL::getNumofwords()
{
    return numofwords;
}

NodeAVL *AVL::min(NodeAVL *start)
{
    if(start==nullptr) //αν το δένδρο είναι άδειο
        return nullptr;
    NodeAVL *p=start;
    while(p->left!=nullptr)
        p=p->left;
    return p; //επιστροφή του αριστερότερου (ελάχιστου) κόμβου
}

NodeAVL* AVL::deleteNodeAVL(NodeAVL *root, const string &word)
{
    if(root==nullptr)
    {
        return root;
    }

    if(word<root->word) //αν η λέξη κλειδί είναι μικρότερη από τη λέξη του κόμβου
        root->left=deleteNodeAVL(root->left, word); //αναδρομική κλήση για τη διαγραφή της λέξης από το αριστερό υποδένδρο

    else if(word>root->word) //αν η λέξη κλειδί είναι μεγαλύτερη από τη λέξη του κόμβου
        root->right=deleteNodeAVL(root->right, word); //αναδρομική κλήση για τη διαγραφή της λέξης από το δεξί υποδένδρο

    else //αν η λέξη του κόμβου είναι ίδια με τη λέξη κλειδί τότε ο κόμβος πρέπει να διαγραφεί
    {
        //κόμβος με 1 ή κανένα παιδί
        if( (root->left==nullptr) || (root->right==nullptr) )
        {
            NodeAVL *temp = root->left ? root->left : root->right;

            if(temp==nullptr) //αν δεν υπάρχει κανένα παιδί
            {
                temp=root;
                root=nullptr;
            }
            else //αν υπάρχει ένα παιδί
                *root=*temp;

            numofwords--; //μείωση του πλήθους των λέξεων που υπάρχουν στο δένδρο

            free(temp);
        }
        else //κόμβος με 2 παιδιά
        {
            //ο κόμβος αντικαθιστάται από τον ελάχιστο κόμβο του δεξιού υποδένδρου
            NodeAVL *temp=min(root->right);

            root->word=temp->word;
            root->cnt=temp->cnt;

            root->right=deleteNodeAVL(root->right,temp->word);
        }
    }

    //αν το δένδρο είχε μόνο έναν κόμβο
    if(root==nullptr)
    {
        numofwords--;
        return root;
    }

    //ενημέρωση ύψους του κόμβου
    root->height=1+max(height(root->left),height(root->right));

    //έλεγχος αν το δένδρο είναι ισοζυγισμένο
    int balance=getBalance(root);

    //αν το δένδρο δεν είναι ισοζυγισμένο υπάρχουν 4 περιπτώσεις

    //Left Left Case 
    if(balance>1 && getBalance(root->left)>=0)
        return rightRotate(root);

    //Left Right Case 
    if(balance>1 && getBalance(root->left)<0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    //Right Right Case 
    if(balance<-1 && getBalance(root->right)<=0)
        return leftRotate(root);

    //Right Left Case 
    if(balance<-1 && getBalance(root->right)>0)
    {
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

bool AVL::search_word(NodeAVL *root, const string &keyword, int &cnt)
{
    NodeAVL *s;
    s=root;
    while(s!=nullptr && keyword!=s->word)
        //όσο υπάρχουν παιδιά και δεν έχει βρεθεί η λέξη
    {
        if(keyword>s->word) //αν η λέξη κλειδί είναι μεγαλύτερη της λέξη του κόμβου
            s=s->right; //αναζήτηση στο δεξί υποδένδρο
        else
            s=s->left; //αναζήτηση στο αριστερό υποδένδρο
    }

    if(s==nullptr)
        return false;
    cnt=s->cnt;
    return true;
}
