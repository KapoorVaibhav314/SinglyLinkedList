#include<iostream>
using namespace std;

class Node{
    public:
    int data;
    Node *next;
    //created a template of node with fields data and next pointer
    
    //constructor
    Node(int data){
        this->data=data;
        this-> next=NULL;
    }
 
    //Destructor
    ~Node(){
        int value = this-> data; //we did this so we can use this value to specify (see below)
        //which node we deleted 
        if(this-> next != NULL){
            delete next;
            this-> next = NULL;
        }
        cout << "memory is free for node with data "<<value<<endl;
    }
};

void insertAtHead(Node* &head, int d){
   //creating new node temp with data d
   Node* temp = new Node(d);
   temp-> next = head;
   head = temp;
}
// node created, the next of this "temp" node should point to other node
// head = temp, head now points to temp
// we are taking reference here cause we want changes in original

void print(Node* &head){
    Node* temp = head;

    while(temp!=NULL){
        cout << temp->data << " ";
        temp = temp-> next;
   }
   cout<<endl;
}

//To print, make a temp node like head
//Untill this temp reaches NULL, print data and jump to next node

void insertAtTail(Node* &tail, int d){
    //create a new node
    Node* temp = new Node(d);
    //we have to remove NULL and make the node point to next node
    tail -> next = temp; 
    //now tail should point to the last node
    tail = temp;
}

void insertAtPosition(Node* &tail, Node* &head, int position, int d){
    
    //handles the insert at beginning case
    if(position == 1){
       //insertAtHead is a function that inserts new node at beginning (remember?)
       insertAtHead(head, d);
       return;
    }

    Node* temp = head;
    int count=1;
    while(count<position-1){
        //to reach nth node, traverse through (n-1) nodes
        temp= temp -> next;
        count++;
    }

     //inserting at the last position
    if(temp->next == NULL){
        insertAtTail(tail, d);
        return;
    }

    //creating a node for d
    Node* nodeToInsert = new Node(d);
    nodeToInsert -> next = temp -> next;
    //we first connect nodeToInsert to next node by pointing it to the node temp's node originally pointed to
    temp -> next = nodeToInsert;
    //now we bring the temp to the nodeToInsert
}

void deleteNode(int position, Node* &head){
    //deleting first/start node
    if(position == 1){
        Node *temp = head;
        //shift head to next node and free the memory
        head = head -> next;
        //while we delete a node, we don't want it to point to anything in our memory
        temp -> next = NULL;
        delete temp;
        //we'll have to write a destructor for this
    }
    else{
        //deleting any middle or last node
        Node* curr = head;
        Node* prev = NULL;

        int count=1;
        while(count<position){
         prev = curr; 
         //since current is going fwd, we need something to point to node current was poitning at
         curr = curr -> next; //to move current forward
         count++;
        }
        
        //we are deleting that node, so prev's next should directly point to that which current was pointing at
        prev -> next = curr -> next;
        curr -> next = NULL; // we don't want deleted node to point to any other location in our memory 
        delete curr; //to free it
    }
}

int main(){
    Node* node1 = new Node(10);

    //create head node and point it to the first node
    Node* head = node1;
    Node* tail = node1;
    //since it's only 1 node atm, we'll point head and tail to same location
    print(head);

    insertAtTail(tail, 12);
    insertAtTail(tail, 15);
    print(head);

    insertAtPosition(tail, head, 4, 22);
    print(head);

    deleteNode(4,head);
    print(head);

}

