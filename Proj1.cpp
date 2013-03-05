#include <iostream>
#include <queue>
#include <iterator>
#include <stdlib.h>
using namespace std;

class Node {
    private:
        queue<int> paths;
        bool visited;

    public:
        Node(){ visited = false;}
        void addPath (int);
        bool isVisited() { return visited; };
        void visit() { visited = true;}
        queue<int> getPaths (){ return paths; }
        int removePath();
};

int nextUnvisitedNode(Node* array, int size){
    for(int i = 0; i < size; i++){
        if(!array[i].isVisited())
            return i;
    }
    return -1;
}

int main ()
{
    int testCase, numDominos, numConnections, i = 0;
    int from, to, numVisited = 0, manualDrops = 0;

    // Ler quantos testes há
    cin >> testCase;
    // Ler o numero de Dominos e de Conections
    cin >> numDominos >> numConnections;

    Node* array = new Node[numDominos];

    // Populate paths
    for(i = 0; i < numConnections; i++){
        cin >> from >> to;
        array[from-1].addPath(to-1);
    }

    int currentNode = 0;
    manualDrops++;
    while(true){
        cout << "Visiting: " << currentNode+1 << endl;
        array[currentNode].visit();
        numVisited++;
        if(numVisited >= numDominos)
            break;
        currentNode = array[currentNode].removePath();
        if(currentNode == -1){
            currentNode = nextUnvisitedNode(array, numDominos);
            manualDrops++;
        }
    }

    cout << "END -> " << manualDrops << endl;

//    queue<Node>::const_iterator nodeIterator;
//    for (nodeIterator = dominos.begin(); nodeIterator != dominos.end(); ++nodeIterator) { cout << i++; }

  return 0;
}

/** Add a Path to a node **/
void Node::addPath(int value){
    paths.push(value);
}

/** Remove and Return Path to a node **/
int Node::removePath(){
    if(paths.empty())
        return -1;
    int answer = paths.front();
    paths.pop();
    return answer;
}
