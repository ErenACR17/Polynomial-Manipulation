#include <iostream>
using namespace std;

// Node structure for polynomial term
struct Node{
    int coeff;
    int exp;
    Node* next;

    Node(int c,int e){
        coeff = c;
        exp = e;
        next = nullptr;
    }
};

// Inserts a term into the list (used for input)
void insertTerm(Node*& head,int c,int e){
    if(c==0) return;

    Node* newNode = new Node(c,e);

    if(!head || newNode->exp > head->exp){
        newNode->next = head;
        head = newNode;
    }
    else{
        Node* current = head;
        while(current->next && current->next->exp > e){
            current = current->next;
        }

        if(current->exp == e){
            current->coeff += c;
            delete newNode;
        }
        else if(current->next && current->next->exp == e){
            current->next->coeff += c;
            delete newNode;
        }
        else{
            newNode->next = current->next;
            current->next = newNode;
        }
    }
}

// Appends a term to the end of the list
void appendTerm(Node*& head,Node*& tail,int c,int e){
    if(c==0) return;

    Node* newNode=new Node(c,e);

    if(!head){
        head = tail = newNode;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }
}

// Prints the polynomial
void printPolynomial(Node* head){
    if(!head){
        cout<<"0"<<endl;
        return;
    }

    Node* current=head;
    while(current){
        if(current!=head && current->coeff>0)
            cout<<"+";

        cout<<current->coeff;

        if(current->exp>0){
            cout<<"x";
            if(current->exp>1)
                cout<<"^"<<current->exp;
        }
        current=current->next;
    }
    cout<<endl;
}

// Adding polynomials
Node* addPolynomials(Node* p1,Node* p2){
    Node* result=nullptr;
    Node* tail=nullptr;

    while(p1 && p2){
        if(p1->exp > p2->exp){
            appendTerm(result,tail,p1->coeff,p1->exp);
            p1=p1->next;
        }
        else if(p1->exp < p2->exp){
            appendTerm(result,tail,p2->coeff,p2->exp);
            p2=p2->next;
        }
        else{
            appendTerm(result,tail,p1->coeff+p2->coeff,p1->exp);
            p1=p1->next;
            p2=p2->next;
        }
    }

    while(p1){
        appendTerm(result,tail,p1->coeff,p1->exp);
        p1=p1->next;
    }

    while(p2){
        appendTerm(result,tail,p2->coeff,p2->exp);
        p2=p2->next;
    }

    return result;
}

// Subtracting polynomials
Node* subtractPolynomials(Node* p1,Node* p2){
    Node* result=nullptr;
    Node* tail=nullptr;

    while(p1 && p2){
        if(p1->exp > p2->exp){
            appendTerm(result,tail,p1->coeff,p1->exp);
            p1=p1->next;
        }
        else if(p1->exp < p2->exp){
            appendTerm(result,tail,-p2->coeff,p2->exp);
            p2=p2->next;
        }
        else{
            appendTerm(result,tail,p1->coeff-p2->coeff,p1->exp);
            p1=p1->next;
            p2=p2->next;
        }
    }

    while(p1){
        appendTerm(result,tail,p1->coeff,p1->exp);
        p1=p1->next;
    }

    while(p2){
        appendTerm(result,tail,-p2->coeff,p2->exp);
        p2=p2->next;
    }

    return result;
}

int main(){
    Node* poly1=nullptr;
    Node* poly2=nullptr;
    int n,c,e;

    cout<<"Enter the number of terms in Polynomial 1: ";
    cin>>n;
    cout<<"Enter terms (coefficient exponent):"<<endl;

    for(int i=0;i<n;i++){
        cin>>c>>e;
        insertTerm(poly1,c,e);
    }

    cout<<"Enter the number of terms in Polynomial 2: ";
    cin>>n;
    cout<<"Enter terms (coefficient exponent):"<<endl;

    for(int i=0;i<n;i++){
        cin>>c>>e;
        insertTerm(poly2,c,e);
    }

    cout<<"\nOutput:"<<endl;
    cout<<"Polynomial 1: ";
    printPolynomial(poly1);

    cout<<"Polynomial 2: ";
    printPolynomial(poly2);

    Node* sumResult = addPolynomials(poly1,poly2);
    cout<<"Result of Addition:"<<endl;
    printPolynomial(sumResult);

    Node* subResult = subtractPolynomials(poly1,poly2);
    cout<<"Result of Subtraction:"<<endl;
    printPolynomial(subResult);

    return 0;
}
