#include <iostream>
#include <queue>
#include <iterator>
#include <stdlib.h>
using namespace std;

/** Node that represents a domino **/
class Node {
    private:
        /** All possible knockdowns from this domino **/
        queue<int> _paths;
        /** If this domino was already knocked down **/
        bool _visited;

    public:
        Node(){ _visited = false;}
        /** Add a possible knockdown from this domino **/
        void addPath (int);
        /** Return if this domino was already knocked down **/
        bool isVisited() { return _visited; };
        /** Knockdown this domino **/
        void visit() { _visited = true;}
        /** Get all possible knockdowns from this domino **/
        queue<int> getPaths (){ return _paths; }
        /**  **/
        int removePath();
};

/** Add a Path to a node **/
void Node::addPath(int value){
    _paths.push(value);
}

/** Remove and Return Path to a node **/
int Node::removePath(){
    if(_paths.empty())
        return -1;
    int answer = _paths.front();
    _paths.pop();
    return answer;
}


class DominoRun {
    private:
        int _numDominos;
        int _numConnections;
        int _manualDrops;
        int _currentNode;
        int _numVisited;
        Node* _dominoArray;

    public:
        DominoRun();
        int nextUnvisitedNode();
        int cicle();
        int getManualDrops() { return _manualDrops; }

};

DominoRun::DominoRun(){
    int from, to;
    cin >> _numDominos >> _numConnections;
    _manualDrops = 1;
    _currentNode = _numVisited = 0;
    _dominoArray = new Node[_numDominos];
    for(int i = 0; i < _numConnections; i++){
        cin >> from >> to;
        _dominoArray[from-1].addPath(to-1);
    }
}

int DominoRun::nextUnvisitedNode(){
    for(int i = 0; i < _numDominos; i++){
        if(!_dominoArray[i].isVisited())
            return i;
    }
    return -1;
}

int DominoRun::cicle(){
    while(true){
        cout << "Visiting Node: " << _currentNode+1;
        _dominoArray[_currentNode].visit();
        _numVisited++;
        if(_numVisited >= _numDominos)
            return _manualDrops;
        _currentNode = _dominoArray[_currentNode].removePath();
        if(_currentNode == -1){
            _currentNode = nextUnvisitedNode();
            _manualDrops++;
        }
        cout << " , and going for: " << _currentNode+1 << endl;
    }
}

int main ()
{
    int numberCases;
    int *answers;

    // Ler quantos testes há
    cin >> numberCases;
    answers = new int[numberCases];

    for(int i = 0; i < numberCases; i++){
        DominoRun *dominoCase = new DominoRun();
        answers[i] = dominoCase->cicle();
    }

    cout << "END" << endl;
    for(int i = 0; i < numberCases; i++)
        cout << answers[i] << endl;

  return 0;
}
