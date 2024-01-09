#include <iostream>
using namespace std;
template<class Keys, class T>
class Node{
	private:
		Keys key;
		T elem;
		Node<Keys,T> *Left;
		Node<Keys,T> *Right;
		Node<Keys,T> *Parent;
	public:
		Node(){
			Left = NULL;
			Right = NULL;
			Parent = NULL;
		}		
		Node<Keys,T> *getParent(){return Parent;}
						
		Node<Keys,T> *getLeft(){return Left;}
						
		Node<Keys,T> *getRight(){return Right;}
					
		void TreeLeft(Node<Keys,T> *p){Left = p;}
			
		void TreeRight(Node<Keys,T> *p){Right = p;}
					
		void TreeParent(Node<Keys,T> *p){Parent = p;}
		
		int hasLeft(){return Left != NULL;}
			
		int hasRight(){return Right != NULL;}
			
		T getElem(){return elem;}
			
		void TreeElem(T e){elem = e;}
			
		void TreeKey(Keys k){key = k;}
			
		Keys getKey(){return key;}		
};

template<class Keys, class T>
void visit (Node<Keys,T> *p){
	cout<<p->getElem()<<" ";
}

template<class Keys, class T>
class Tree{
	private:
		Node<Keys,T> *root;
		long count;
		void inOrder (Node<Keys,T>*, Node<Keys,T>*&first, int &kt);
		void remove(Node<Keys,T>*&);
	public:
		Tree();
		Node<Keys,T> *getRoot();
		int size();
		int isEmpty();
		int isInternal(Node<Keys,T>*);
		int isExternal(Node<Keys,T>*);
		int isRoot(Node<Keys,T>*);
		void preOrder(Node<Keys,T>*, void (*visit)(Node<Keys,T> *));
		void inOrder(Node<Keys,T>*,void (*visit)(Node<Keys,T> *));
		void postOrder(Node<Keys,T>*,void (*visit)(Node<Keys,T> *));
		Node<Keys,T> *search(Keys,Node<Keys,T>*);
		Node<Keys,T> *insert(Keys,T);
		void remove(Keys);
};
template<class Keys, class T>
	Tree<Keys,T> :: Tree(){
		root = NULL;
		count = 0;
	}

template<class Keys, class T>
	Node<Keys,T> *Tree<Keys,T>:: getRoot(){
		return root;
	}
	
template<class Keys, class T>
	int Tree<Keys,T> :: size(){
		return count;
	}
	
template<class Keys, class T>
	int Tree<Keys,T> :: isEmpty(){
		if(root == NULL)
			return 1;
		else
			return 0;
	}

template<class Keys, class T>
	int Tree<Keys,T> :: isInternal(Node<Keys,T> *p){
		if(p->hasLeft()  || p-> hasRight())
			return 1;
		else
			return 0;
	}
	
template<class Keys, class T>
	int Tree<Keys,T> :: isExternal(Node<Keys,T> *p){
		if(!p->hasLeft() && !p->hasRight())
			return 1;
		else
			return 0;
	}

template<class Keys, class T>
	int Tree<Keys,T> :: isRoot(Node<Keys,T> *p){
		if(p->getParent() == NULL)
			return 1;
		else
			return 2;
	}
	
template<class Keys, class T>
	void Tree<Keys,T> :: preOrder(Node<Keys,T> *p,void (*visit)(Node<Keys,T> *)){
		if(p != NULL){
			visit(p);
			preOrder(p->getLeft(), visit);
			preOrder(p->getRight(),visit);
		}
	}
	
template<class Keys, class T> 
	void Tree<Keys,T> :: inOrder(Node<Keys,T> *p, void (*visit)(Node<Keys,T> *)){
	if(p != NULL){
		inOrder(p->getLeft(),visit);
		visit(p);
		inOrder(p->getRight(),visit);
	}
}

template<class Keys, class T>
	void Tree<Keys,T> :: postOrder(Node<Keys,T> *p, void (*visit)(Node<Keys,T>*)){
		if(p != NULL){
			postOrder(p->getLeft(), visit);
			postOrder(p->getRight(), visit);
			visit(p);
		}		
	}

template<class Keys,class T>
	Node<Keys,T> *Tree<Keys,T> :: search(Keys key , Node<Keys,T>*p){
		if (p != NULL){
			if(p -> getKey() > key)
				return search(key, p->getLeft());
			if (p->getKey() == key)
				return p;
			else
				return search(key, p->getRight());		
		}
		else 
			return NULL;
	}
	
template<class Keys, class T>
	Node<Keys,T>* Tree<Keys,T> :: insert(Keys key, T elem){
		Node<Keys,T> *p;
		Node<Keys,T> *q = new Node<Keys,T>();
		q->TreeKey(key);
		q->TreeElem(elem);
		
		if (root == NULL){
			root = q;
			count++;
		}
		else{
			p = root;
			while(p != NULL){
				if(key < p->getKey())
					if(p->getLeft() == NULL){
						q->TreeParent(p);
						p->TreeLeft(q);
						count++;
						p = NULL;
					}
					else
						p = p->getLeft();
					
				else if (key > p->getKey())
					if(p->getRight() == NULL){
						q->TreeParent(p);
						p->TreeRight(q);
						count++;
						p = NULL;
					}
					else
						p = p->getRight();
				else{
				
					delete q;
					p = NULL;
				}
			}
		}
		return q;
	}
template<class Keys, class T>	
void Tree<Keys,T> :: inOrder (Node<Keys,T>*p, Node<Keys,T>*&first, int &kt){
	if (p != NULL && kt != 1){
		inOrder(p->getLeft(),first,kt);
		if(kt == 0){
			first = p;
			kt = 1;
		}
	}
} 

template <class Keys, class T>
void Tree<Keys,T>::remove(Node<Keys,T> *&v)
{
	Node<Keys,T> *p;
	if(!v->hasLeft() && !v->hasRight()){
		p = v->getParent();
		if(p != NULL){
			if(v == p->getLeft())
				p->TreeLeft(NULL);
			else
				p->TreeRight(NULL);
		}
	}
	if (v->hasLeft() && !v->hasRight()){
		p = v->getParent();
		v->getLeft()->TreeParent(p);
		if(v == p->getLeft())
			p->TreeLeft(v->getLeft());
		else
			p->TreeRight(v->getLeft());	
	}
	if (!v->hasLeft() && v->hasRight()){
		p = v->getParent();
		v->getRight()->TreeParent(p);
		if(v == p->getLeft())
			p->TreeLeft(v->getRight());
		else
			p->TreeRight(v->getRight());	
		}
	count--;
	delete v;
}

template <class Keys, class T>
void  Tree<Keys,T>::remove(Keys key)
{
	Node<Keys,T>*v = search(key, root);
	if(v==NULL) return;
	if(v->hasLeft()&& v->hasRight())//Có ca hai con
	{
		Node<Keys,T> *first;
		int kt=0;
		inOrder(v->getRight(), first, kt);
		v->TreeKey(first->getKey());
		v->TreeElem(first->getElem());
		remove(first);
    }
	else
        remove(v);
}	

int main(){
}
