// Jahongir Hayitov CS-01
// Shunting Yard Algorithm - transfer to Reverse Polish Notation
#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

template <typename T>
// Stack implementation by class
class StackArray {
    public:
        // size of the stack
        int size = 0;
        // volume of the stack
        int volume = 0;
        // the main stack array
        vector<T> arr;
        // push method
        void push(T n) {
            if(volume == 0) {
                arr.push_back(n);
                // change the volume by 2
                volume += 2;
                arr.resize(2);
                size += 1;
                return;
            }
            // push the data
            arr[size] = n;
            size++;
            if(size == volume) {
                // if the space is full then double
                volume *= 2;
                arr.resize(volume);
            }
        }
        // pop method
        T pop() {
            size--;
            return arr[size];
        }
        // for printing all values
        void all() {
            for(int i=0; i<size; i++) cout<<arr[i]<<" ";
            cout<<endl;
        }
        // is empty or not
        bool empty() {
            return !size;
        }
        // top element of the stack
        T top() {
            return arr[size-1];
        }
};


template <typename T>
// Queue implementation by class
class QueueArray {
    public:
        int frontPosition=-1, backPosition=0;
        // size of the queue
        int size = 0;
        // volume of the queue
        int volume = 0;
        // the main queue array
        vector<T> arr;
        // push method
        void push(T n) {
            if(volume == 0) {
                arr.push_back(n);
                // front and back
                frontPosition = 0;
                backPosition = 1;
                // change the volume by 2
                volume += 2;
                arr.resize(2);
                size += 1;
                return;
            }
            // push the data
            arr[backPosition] = n;
            size++;
            if(++backPosition == volume) {
                // if the space is full then double
                volume *= 2;
                arr.resize(volume);
            }
        }
        // pop method
        T pop() {
            size--;
            return arr[frontPosition++];
        }
        // for printing all values
        void all() {
            for(int i=frontPosition; i<backPosition; i++) cout<<arr[i]<<" ";
            cout<<endl;
        }
        // is empty or not
        bool empty() {
            return !size;
        }
        // front element of the queue
        T front() {
            return arr[frontPosition];
        }
};


void plusMinusPriority(StackArray<string>& S, string operation, QueueArray<string>& Q) {
    // pop high priority oper. for adding & subtracting
    while(!S.empty() && (S.top() != "(")) {
        Q.push(S.top());
        S.pop();
    }
    S.push(operation);
}

void multiDividePriority(StackArray<string>& S, string operation, QueueArray<string>& Q) {
    // pop high priority oper. for multiplication & division
    while(!S.empty() && (S.top() == "min" || S.top() == "max" || S.top() == "/" || S.top() == "*")) {
        Q.push(S.top());
        S.pop();
    }
    S.push(operation);
}

void bracePriority(StackArray<string>& S, string operation, QueueArray<string>& Q) {
    // until the beginning of the bracket
    while(!S.empty() && !(S.top() == "(")) { 
        Q.push(S.top());
        S.pop();
    }
    // if there is a min or max
    if(!S.empty()) {
        S.pop();
        if(!S.empty() && (S.top() == "min" || S.top() == "max")) {
            Q.push(S.top());
            S.pop();
        } 
    }
}

void commaPriority(StackArray<string>& S, QueueArray<string>& Q) {
    // comma inside the min or max case
    while(!S.empty() && !(S.top() == "(")) { 
        Q.push(S.top());
        S.pop();
    }
}


int main() {
    string str;
    // stack for arithmetic operations
    StackArray<string>* S = new StackArray<string>();
    // queue for numbers and operation for high priority
    QueueArray<string>* Q = new QueueArray<string>();
    while(cin>>str) {
        if((str[0] - '0') >= 0 && (str[0] - '0') <= 9) {
            // if number then offer to queue
            (*Q).push(str);
        } else {
            // else check every case possibilities
            if(str == "+" || str == "-") plusMinusPriority(*S, str, *Q);
            else if(str == "*" || str == "/") multiDividePriority(*S, str, *Q);
            else if(str == "(" || str == "min" || str == "max") (*S).push(str);
            else if(str == ",") commaPriority(*S, *Q);
            else if(str == ")") bracePriority(*S, str, *Q);
        }
    }    
    
    // push to the queue until stack is empty
    while(!(*S).empty()) {
        (*Q).push((*S).top());
        (*S).pop();
    }
    
    // print every element of queue from left to right
    while(!(*Q).empty()) {
        cout<<(*Q).front()<<" ";
        (*Q).pop();
    }
    
    // Delete unnecessary objects
    delete S;
    delete Q;
    
    return 0;
}
