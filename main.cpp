#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;

class Node {
public:
    int value;
    int row;
    int col;
    Node* next = NULL;
};

class SparseMatrix {
private:
    Node *head;
    Node *tail;
    int size;
public:
    SparseMatrix() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    void setHead(Node *head){
        this->head = head;
    }
    Node* getHead(){
        return this->head;
    }
    void setTail(Node *tail){
        this->tail = tail;
    }
    Node* getTail(){
        return this->tail;
    }
    void setMatrixSize(int size){
        this->size = size;
    }
    int getMatrixSize(){
        return this->size;
    }

    Node* addToSparseMatrix(int value, int row, int col){
        Node *newNode = new Node();
        newNode->value = value;
        newNode->row = row;
        newNode->col = col;

        if (head != NULL) {
            tail->next = newNode; //then add to tail
            tail = newNode;
        }
        else {
            head = newNode; //list is empty, so set as head
            tail = newNode;
        }
    }

    int getValue(int row, int col){
        //get the head of the linked list/sparse
        Node *curr = getHead();
        int value = 0;

        while(curr != NULL ){
            if(curr->row == row && curr->col == col){
                //this is the element you wanted
                value = curr->value;
                return value;
                break;
            }
            else{
                curr = curr->next;
            }
        }
        //if no element was found with the desired row/col pair, that means it was a zero element
        return value;
    }

    SparseMatrix getMinor(int row, int col){
        //the minor of a[i, j] is the matrix formed by removing the ith row of the jth column
        SparseMatrix *minor = new SparseMatrix;

        int newRowPos = 0;
        int newColPos = 0;

        for(int i = 0; i <= size-1; i++){
            if(i == row){
                //all elements in this row should be skipped as they are NOT part of the minor
                continue;
            }
            newColPos = 0;
            for(int j = 0; j <= size-1; j++){
                if(j == col){
                    //all elements in this col should be skipped as they are NOT part of the minor
                    continue;
                }
                //only add it if its not zero
                if(this->getValue(i, j)!= 0){
                    minor->addToSparseMatrix(this->getValue(i, j), newRowPos, newColPos);
                }
                newColPos++;
            }
            newRowPos++;
        }
        minor->setMatrixSize(size-1);
        return *minor;
    }



    int getDeterminant(SparseMatrix *m){
        //formula: det = SUM of (-1)^(i+j) * a[i,j] * det(minor(a[i, j]))
        int determinant = 0;

        if(size == 4){
            for(int i = 0; i < size; i++){
                //det = SUM of (-1)^(i+j) * a[i,j] * det(minor(a[i, j]))
                //(RECURSIVE STEP)
                (m->getMinor(0, i));
                cout << "head: " << getHead();
            }
        }
        if(size == 2){
            //simple 2x2 determinant (BASE CASE)
            return (getValue(0, 0) * getValue(1, 1)) - (getValue(0, 1) * getValue(1, 0));
        }

        for(int i = 0; i < size; i++){
            //det = SUM of (-1)^(i+j) * a[i,j] * det(minor(a[i, j]))
            //(RECURSIVE STEP)
            determinant = determinant + (getValue(0, i) * (m->getMinor(0, i)).getDeterminant(m)) * pow(-1, i);
        }
        return determinant;
    }


};


int main() {
    string line;
    int rowCount = 0;
    int spaceCount = 0;
    SparseMatrix *matrix = new SparseMatrix;
    int row = -1;
    int col = 0;
    int value = 0;
    bool neg = false;
    int test;
    string token;

    /*while(cin.good()){
        cout << "enter line: ";
        getline(cin, line);
        neg = false;
        if(line == "q"){
            break;
        }
        row++;
        col = 0;

        for( char c : line ){
            //count spaces between elements to determine if its square.
            if(isspace(c, std::cin.getloc())) ++spaceCount ;
        }
        rowCount++;

        //parse integers in this line
        for( char c : line ){
            //check if character is NON-ZERO digit. if so, add value to matrix.
            // otherwise, continue, but increment row/col to represent '0' placeholder.

            if(isdigit(c, std::cin.getloc())){
                if(c != '0'){
                    if(neg){
                        value = -(c - '0');
                    }else{
                        value = (c - '0');
                    }
                    matrix->addToSparseMatrix(value, row, col);
                }
                col++;
            }
            else if(c == '-'){
                neg = true;
            }
            else{
                neg = false;
            }
        }

    }
*/
    while(cin.good()){
        getline(cin, line);
        row++;
        col = 0;

        if(line == "q"){
            break;
        }

        for( char c : line ){
            //count spaces between elements to determine if its square.
            if(isspace(c, std::cin.getloc())) ++spaceCount;
        }
        rowCount++;

        stringstream lineStream(line);
        while(lineStream >> token)
        {
            test = stoi(token);
            if(test != 0){
                matrix->addToSparseMatrix(test, row, col);
            }
            col++;
        }
    }
    if(spaceCount != rowCount*(rowCount-1)){
        //not a square matrix
        cout << "Error! Non-square matrix!";
        return 0;
    }

    matrix->setMatrixSize(rowCount);
    cout<< matrix->getDeterminant(matrix);

}