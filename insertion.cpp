#include<iostrem>
using namespace std;

class Node
{
public:
    int data;
    Node* next;

    Node (int val)
    {
        data=val;
        next=NULL;
    }

};

class List
{
    Node* head;
    Node* tail;

public:
    List()
    {
        head=tail=NULL;// as at first the link list will be empty
    }
    void push_front(int val)
    {
        Node* newNode=new Node(val);
        if(head==NULL)
        {
            head=tail=newNode;
            return;
        }
        else{
            newNode->next=head;
            head=newNode;
        }
    }
};





int main()
{


}
