#include <iostream>
#include <list>
#include <stdlib.h>

#define UNDIFINED -1

using namespace std;

int _INDEX_ = 1;
int _SCC_INDEX_ = 1;
int _ID_ = 1;

class Scc;

class Node {
    private:
        Scc* _myScc;
        int _id;
        list<Node*> _sucessores;
        int _index;
        int _lowlink;

    public:
        Node();
        bool isUndifined();
        void setIndex(int);
        int getIndex();
        int getId();
        void setLowlink(int);
        int getLowlink();
        void addSucessor (Node*);
        list<Node*> *getSucessores();
        void setScc(Scc*);
        Scc *getScc();
};

Node::Node(){ _index = UNDIFINED; _id = _ID_++; }
bool Node::isUndifined(){ return _index == UNDIFINED; }
void Node::setIndex(int index){ _index = index; }
int Node::getIndex(){ return _index; }
int Node::getId(){ return _id; }
void Node::setLowlink(int lowlink){ _lowlink = lowlink; }
int Node::getLowlink(){ return _lowlink; }
void Node::addSucessor(Node* sucessor){ _sucessores.push_front(sucessor); }
list<Node*> *Node::getSucessores(){ return &_sucessores; }
void Node::setScc(Scc *scc){ _myScc = scc; }
Scc *Node::getScc(){ return _myScc; }



class Scc{
    private:
        bool visited;
        list<Node*> _Scc;
        int index;

    public:
        Scc() { index = _SCC_INDEX_++; }
        void addScc(Node*);
        list<Node*>* getScc();
        int getIndex() { return index; }
        void visit() { visited = true; }
        bool isVisited() { return visited; }
};

void Scc::addScc(Node* node){
    _Scc.push_front(node);
    node->setScc(this);
}
list<Node*> *Scc::getScc(){ return &_Scc; }

class DominoRun {
    private:
        int _numDominos;
        int _numConnections;
        int _manualDrops;
        Node* _dominoArray;
        list<Node*> _S;
        list<Scc*> _Scc;

    public:
        DominoRun();
        void incrementManualDrops();
        int getManualDrops();
        int getNumDominos();
        int getNumConnections();
        list<Node*> *getS();
        void addToS(Node*);
        bool isInS(Node*);
        void findSCCs();
        void strongConnect(Node*);
        list<Scc*> *getScc();
        void printScc();
};

DominoRun::DominoRun(){
    int from, to;
    cin >> _numDominos >> _numConnections;
    _manualDrops = 0;
    _dominoArray = new Node[_numDominos];
    for(int i = 0; i < _numConnections; i++){
        cin >> from >> to;
        _dominoArray[from-1].addSucessor(&_dominoArray[to-1]);
    }
}

void DominoRun::addToS(Node* node){ _S.push_front(node); }
void DominoRun::incrementManualDrops() { _manualDrops++; }
int DominoRun::getNumDominos() { return _numDominos; }
int DominoRun::getNumConnections() { return _numConnections; }
list<Node*> *DominoRun::getS() { return &_S; }
list<Scc*> *DominoRun::getScc() { return &_Scc; }

int DominoRun::getManualDrops() {
    list<Node*> *sucessores;
    for(int i = 0; i < _numDominos; i++){
        sucessores = _dominoArray[i].getSucessores();
        for(list<Node*>::iterator it = sucessores->begin(); it != sucessores->end(); it++){
            Node* sucessor = *it;
            if(sucessor->getScc()->getIndex() != _dominoArray[i].getScc()->getIndex())
                sucessor->getScc()->visit();
        }
    }
    for(list<Scc*>::iterator it = _Scc.begin(); it != _Scc.end(); it++){
        Scc *scc = *it;
        if(!scc->isVisited())
            _manualDrops++;
    }

    return _manualDrops;
}

void DominoRun::printScc() {
    for(list<Scc*>::iterator Scc_it = _Scc.begin(); Scc_it != _Scc.end(); Scc_it++){
        cout << "Scc -> ";
        Scc *scc = *Scc_it;
        list<Node*> *scc_list = scc->getScc();
        for(list<Node*>::iterator node_it = scc_list->begin(); node_it != scc_list->end(); node_it++){
            cout << "[";
            Node* sucessor = *node_it;
            cout << sucessor->getId() << "] " << "Visited = " << scc->isVisited();
        }
    cout << endl;
    }
}

bool DominoRun::isInS(Node* node){
    Node *aux;
    for (list<Node*>::iterator it=_S.begin(); it != _S.end(); ++it){
        aux = *it;
        if(node->getIndex() == aux->getIndex())
            return true;
    }
    return false;
}

void DominoRun::strongConnect(Node* node){
    node->setIndex(_INDEX_);
    node->setLowlink(_INDEX_);
    _INDEX_++;
    addToS(node);

    Node * sucessor;
    for(list<Node*>::iterator it = node->getSucessores()->begin(); it != node->getSucessores()->end(); it++){
        sucessor = *it;
        if(sucessor->isUndifined()){
            strongConnect(sucessor);
            node->setLowlink(min(node->getLowlink(), sucessor->getLowlink()));
        } else if (isInS(sucessor))
            node->setLowlink(min(node->getLowlink(), sucessor->getIndex()));
    }

    if(node->getLowlink() == node->getIndex()){
        Scc* scc = new Scc();
        Node* sucessor;
        do{
            sucessor = _S.front();
            _S.pop_front();
            scc->addScc(sucessor);
            sucessor->setScc(scc);
        }while(sucessor->getId() != node->getId());
        _Scc.push_front(scc);
    }
}

void DominoRun::findSCCs(){
    for(int i = 0; i < _numDominos; i++)
        if(_dominoArray[i].isUndifined())
            strongConnect(&_dominoArray[i]);
}

int main (){
    int numberCases;
    int *answers;

    // Ler quantos testes há
    cin >> numberCases;
    answers = new int[numberCases];

    for(int i = 0; i < numberCases; i++){
        DominoRun *dominoCase = new DominoRun();
        dominoCase->findSCCs();
        cout << dominoCase->getManualDrops() << endl;
//        dominoCase->printScc();
//
//        list<Scc*> *scc = dominoCase->getScc();
//        list<Scc*>::iterator it, aux;
//        for(it = scc->begin(); it != scc->end(); it++)
//
    }

  return 0;
}
