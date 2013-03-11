#include <iostream>
#include <list>
#include <stdlib.h>

#define UNDIFINED -1

using namespace std;

int _INDEX_ = 0;
int _ID_ = 0;

class Node {
    private:
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



class DominoRun {
    private:
        int _numDominos;
        int _numConnections;
        int _manualDrops;
        Node* _dominoArray;
        list<Node*> _S;

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
};

DominoRun::DominoRun(){
    int from, to;
    cin >> _numDominos >> _numConnections;
    _manualDrops = 1;
    _dominoArray = new Node[_numDominos];
    for(int i = 0; i < _numConnections; i++){
        cin >> from >> to;
        _dominoArray[from-1].addSucessor(&_dominoArray[to-1]);
    }
}

void DominoRun::addToS(Node* node){ _S.push_front(node); }
void DominoRun::incrementManualDrops() { _manualDrops++; }
int DominoRun::getManualDrops() { return _manualDrops; }
int DominoRun::getNumDominos() { return _numDominos; }
int DominoRun::getNumConnections() { return _numConnections; }
list<Node*> *DominoRun::getS() { return &_S; }

bool DominoRun::isInS(Node* node){
    Node *aux;
    for (list<Node*>::iterator it=_S.begin(); it != _S.end(); ++it){
        aux = *it;
        if(node->getId() == aux->getIndex())
            return true;
    }
    return false;
}

void DominoRun::strongConnect(Node* node){
    node->setIndex(_INDEX_);
    node->setLowlink(_INDEX_);
    _INDEX_++;
    addToS(node);

    for(unsigned int i = 0; i < _S.size(); i++){
        if(_dominoArray[i].isUndifined()){
            strongConnect(&_dominoArray[i]);
            node->setIndex(min(node->getLowlink(), _dominoArray[i].getLowlink()));
        } else if (isInS(&_dominoArray[i]))
            node->setLowlink(min(node->getLowlink(), _dominoArray[i].getIndex()));
    }

    if(node->getLowlink() == node->getIndex()){
        list<Node*> connected_components;
        Node* sucessor;
        do{
            sucessor = _S.front();
            _S.pop_front();
            connected_components.push_front(sucessor);
        }while(sucessor->getId() != node->getId());
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
        answers[i] = dominoCase->getManualDrops();
    }

    cout << "END" << endl;
    for(int i = 0; i < numberCases; i++)
        cout << answers[i] << endl;

  return 0;
}
