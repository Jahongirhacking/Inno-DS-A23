// Jahongir Hayitov CS-01
#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define rep(i,n) for (ll i = 0; i < (n); ++i)

// stack implementation by static array
template <class E>
class StackArray {
public:
    StackArray() {
        E empty;
        empty.element = "";
        data[0] = empty;
    };
    unsigned int size = 0;
    // check whether it is empty or not
    bool isEmpty(){
        return !size;
    }
    // return top element of the stack
    E top() {
        if(size > 0)
        {
            return data[size];
        }
        // else return empty
        E empty;
        return empty;
    }
    // push new element to top
    void push(E element) {
        //check if the size less than of array capacity.
        if(size < capacity) {
            size++;
            data[size] = element;
        }
        else if(size == capacity)
        {
            // new capacity is old * 2.
            int newCapacity = capacity * 2;
            // then declare new array for copying.
            E* copyArr = new E[newCapacity];
            // exchange
            for(int i =0 ; i < size ; i++ ) {
                copyArr[i] = data[i];
            }
            // make old capacity = new one.
            capacity = newCapacity;
            // assign the new array to the array of data.
            data = copyArr;
            // delete copy of Array
            delete[] copyArr;
            //insert the element into stack.
            size++;
            data[size] = element;
        }
    }
    // pop the top element from stack
    void pop() {
        if(size > 0) {
            size--;
        }
    }
private:
    // capacity of array
    unsigned int capacity = 1001;
    // main static array
    E* data = new E[capacity] ;
};

int main() {
    string closeDelimiters[101], openDelimiters[101];
    int indexOfDelim = 0;
    // struct which holds delimiter and its array position
    struct elementAndPosition {
        string element;
        int position;
    };

    // stack for managing delimiters
    StackArray<elementAndPosition> *rules = new StackArray<elementAndPosition>();
    
    int n, k;
    string open, close;
    string line;

    // n - number of delimiter pairs
    // k - number of lines
    cin >> n >> k;
    rep(i, n) {
        cin >> open >> close;
        closeDelimiters[indexOfDelim] = close;
        openDelimiters[indexOfDelim++] = open;
    }

    // error handling
    getline(cin, line);

    int index;
    rep(i, k) {
        getline(cin, line);
        string temp = "";
        index = 1;
        for(int j = 0; j < line.size(); j++) {
            // if whitespace then split
            if(line[j]==' ' || j==line.size()-1) {
                if(j == line.size()-1) {
                    temp += line[j];
                }
                // check delimiters
                rep(it, indexOfDelim) {
                    if(temp == openDelimiters[it]) {
                        // if open delimiter
                        elementAndPosition elem;
                        elem.element = temp;
                        elem.position = it;
                        rules->push(elem);
                    } else if(temp == closeDelimiters[it]) {
                        // close delimiter
                        // if this case : ()} 
                        if(rules->top().element == "") {
                            cout<<"Error in line "<<i+1<<", column "<<index
                                <<": unexpected closing token "<<temp<<".";
                            return 0;
                        }
                        // if this case: (} 
                        if(openDelimiters[it] != rules->top().element) {
                            cout<<"Error in line "<<i+1<<", column "<<index<<": expected "
                                <<closeDelimiters[rules->top().position]<<" but got "<<temp<<".";
                            return 0;
                        }
                        // if there is no error then pop
                        rules->pop();
                    }
                }

                // update the index
                if(j != line.size()-1) {
                    index = j+2;
                }

                // clear the temporary string
                temp = "";
                continue;
            }
            // add to temporary string
            temp += line[j];
        }
    }

    // if this case: ({} 
    if(rules->top().element != "") {
        cout<<"Error in line "<<k<<", column "<<line.size()+2<<": expected "
            <<closeDelimiters[rules->top().position]<<" but got end of input.";
        return 0;
    }

    // Everything is fine
    cout<<"The input is properly balanced.";
    return 0;
}
