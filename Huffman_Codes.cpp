#include<bits/stdc++.h>
using namespace std;
#define ll long long int

map<char,string> codes;
map<char,ll> frequency;

class Min_Heap_Node
{
public:


    char data;
    ll frequency;
    Min_Heap_Node *left,*right;
    Min_Heap_Node(){

    }
    Min_Heap_Node(const Min_Heap_Node &x){
        data = x.data;
        frequency = x.frequency;
        left = x.left;
        right = x.right;
    }
    void set_Min_Heap_Node(char data,ll frequency){
        this->data = data;
        this->frequency = frequency;
        left = NULL;
        right = NULL;
    }
};

void swapp(Min_Heap_Node &a,Min_Heap_Node &b){
    Min_Heap_Node temp = a;
    a = b;
    b = temp;
}

class Min_Heap {
public:
    Min_Heap_Node *MH;
    ll capacity;
    ll heap_size;

    Min_Heap(ll capacity){
        heap_size = 0;
        this->capacity = capacity;
        MH = new Min_Heap_Node[capacity];
    }

    void insert_key(char data,ll frequency){
        if(heap_size == capacity){
            cout<<"FULL"<<endl;
            return;
        }

        heap_size++;
        ll i = heap_size-1;
        MH[i].set_Min_Heap_Node(data,frequency);

        while(i!=0 && MH[(i-1)/2].frequency > MH[i].frequency){
            swapp(MH[(i-1)/2],MH[i]);
            i = (i-1)/2;
        }
    }

    void insert_key(Min_Heap_Node x){
        if(heap_size == capacity){
            cout<<"FULL"<<endl;
            return;
        }

        heap_size++;
        ll i = heap_size-1;
        MH[i] = x;

        while(i!=0 && MH[(i-1)/2].frequency > MH[i].frequency){
            swapp(MH[(i-1)/2],MH[i]);
            i = (i-1)/2;
        }
    }
    void Min_Heapify(ll i){
        ll l = 2*i + 1;
        ll r = 2*i + 2;
        ll smallest = i;
        if(l<heap_size&&MH[l].frequency<MH[i].frequency){
            smallest = l;
        }
        if(r<heap_size&&MH[r].frequency<MH[smallest].frequency){
            smallest = r;
        }
        if(smallest != i){
            swapp(MH[i],MH[smallest]);
            Min_Heapify(smallest);
        }
    }

    Min_Heap_Node extract_min(){
        Min_Heap_Node retnode;

        if(heap_size<=0){
            retnode.set_Min_Heap_Node('0',0);
            return retnode;
        }
        if(heap_size == 1){
            heap_size--;

            return MH[0];
        }
        retnode = MH[0];
        MH[0] = MH[heap_size-1];
        heap_size--;
        Min_Heapify(0);
        return retnode;
    };
};

void calculate_frequency(string s){
    for(ll i=0;i<s.length();i++){
        frequency[s[i]]++;
    }
}

Min_Heap *Heap;

void insert_in_heap(){
    for(auto h:frequency){
        Heap->insert_key(h.first,h.second);
    }
}

void go_to_all_leaves(Min_Heap_Node coded_heap,string s){
    // cout<<coded_heap.data<<"->"<<coded_heap.frequency<<endl;
    if(coded_heap.right!=NULL){
        go_to_all_leaves(*coded_heap.right,s+"1");
    }
    if(coded_heap.left!=NULL){
        go_to_all_leaves(*coded_heap.left,s+"0");
    }
    if(coded_heap.left == NULL && coded_heap.right == NULL){

        codes[coded_heap.data] = s;
        // cout<<s<<" , ";
    }
}

void decoded_(Min_Heap_Node *coded_heap,string s){
    Min_Heap_Node *temp = coded_heap;
    for(ll i=0;s[i];i++){
        x:
        if(s[i] == '1'){
            if(temp->right == NULL){
                cout<<temp->data;
                temp = coded_heap;
                goto x;
            }
            temp = temp->right;
        }
        if(s[i] == '0'){
            if(temp->left == NULL){
                cout<<temp->data;
                temp = coded_heap;
                goto x;
            }
            temp = temp->left;
        }
    }
    cout<<temp->data;
}

int main(){
    Heap = new Min_Heap(52);
    string str = "geeksforgeeks";
    string encoded_string,decoded_string;
    calculate_frequency(str);
    insert_in_heap();

    while(Heap->heap_size != 1){
        Min_Heap_Node rig = Heap->extract_min();
        Min_Heap_Node lef = Heap->extract_min();

        Min_Heap_Node mai;
        mai.set_Min_Heap_Node('#',rig.frequency+lef.frequency);
        mai.left = new Min_Heap_Node(lef);
        mai.right = new Min_Heap_Node(rig);
        // cout<<mai.data<<"->"<<mai.frequency<<":::: ::: ";
        // cout<<mai.left->data<<"("<<mai.left->frequency<<")"<<" "<<mai.right->data<<"("<<mai.right->frequency<<")"<<endl;
        Heap->insert_key(mai);
    }
    Min_Heap_Node coded_heap = Heap->extract_min();
    go_to_all_leaves(coded_heap,"");
    for(auto val:codes){
        cout<<val.first<<" -> "<<val.second<<endl;
    }

    string coded = "";
    for(ll i=0;i<str.length();i++){
        coded += codes[str[i]];
    }
    cout<<coded<<endl;
    decoded_(&coded_heap,coded);
}



//Using Priority Queue Min Heap
/*
struct compare {
    bool operator()(Min_Heap_Node *l,Min_Heap_Node *r){
        return (l->frequency > r->frequency);
    }
};

priority_queue<Min_Heap_Node* , vector<Min_Heap_Node*>,compare> min_heap;
*/