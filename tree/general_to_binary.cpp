//4001406135
#include <iostream>
#include <string>
using namespace std; 
template < typename input_type > 
class General_Tree_Nodes { 
    public:
        input_type data = input_type(); 
        General_Tree_Nodes<input_type>* father = nullptr;
        General_Tree_Nodes<input_type>* childs = nullptr;//will point to first left child of current data 
        General_Tree_Nodes<input_type>* right_sibling = nullptr;//point to next right General_Tree_Nodes which is child of current data
        General_Tree_Nodes<input_type>* left_sibling = nullptr;//point to previous left General_Tree_Nodes which is child of current data
        General_Tree_Nodes(input_type value){ 
            this->data = value; 
            add_child(data);//call this function to give this value it`s childs
        }
        void add_child(input_type value){ 
            int check = 0; // it work like a bool, 1 = true, 0 = false
            input_type* array;// an array of current General_Tree_Nodes childs
            do{
                cout<<"Those "<<value<<" has any childs? \nenter 1 for true or 0 for false: ";
                cin>>check;//check if value have any child
            }while(check != 0 && check != 1);//dont allow user to enter value except 0, and 1
            int num1 = 0 ;
            if(check){
                cout<<"How many kids those "<<value<<" have? ";
                cin>>num1;//enter number of childs
                array = new input_type[num1];// make array with proper size
                cout<<"-----------------------------------------------------\n";
                for (int j = 0 ; j < num1 ; j++){
                    string num = number_word(j+1);
                    cout<<"Enter value of "<<i<<" child of "<<value<<": ";
                    cin>>array[j];//get value for every child    
                }
            }else{
                num1 = 0 ;
            }
            cout<<"-----------------------------------------------------\n";
            for(int i = 0 ; i < num1 ; i++){
                cout<<array[i]<<" is child of "<<this->data<<".\n";// Do it so we can help user find out which value is child of which value
                General_Tree_Nodes<input_type>* new_child = new General_Tree_Nodes<input_type>(array[i]);
                new_child->father = this;//give all childs there father which is same for all of them
                if(i == 0){
                    childs = new_child;//if childs == nullptr so first child will gbe given to childs
                }else{//otherwise it will add to end of link list of General_Tree_Nodes
                    General_Tree_Nodes<input_type>* temp = childs; 
                    while(temp->right_sibling != nullptr){
                        temp = temp->right_sibling;//move to last childs so we can add next child to end of link list
                    }
                    new_child->left_sibling = temp;//make a two way link list of childs where each link list Node is a Tree_part
                    temp->right_sibling = new_child;//make a two way link list of childs where each link list Node is a Tree_part
                }
            }
        }
}; 
template < typename input_type > 
class Binary_Tree_Nodes{
    public:
        input_type data = input_type();
        Binary_Tree_Nodes<input_type>* parent = nullptr;// point to parent of current part
        Binary_Tree_Nodes<input_type>* left_child = nullptr;// point to left child of current part if exist 
        Binary_Tree_Nodes<input_type>* right_child = nullptr;// point to right child of current part if exist 
        Binary_Tree_Nodes(input_type value){
            this->data = value;
        }
};
//=======================================================================================================================
template < typename input_type > 
class Result {
    public:
        Binary_Tree_Nodes<input_type>* Binary_head = nullptr;
        General_Tree_Nodes<input_type>* General_head = nullptr;
        General_Tree_Nodes<input_type>* General_temp = nullptr;
        Result(input_type value){
            General_head = new General_Tree_Nodes<input_type>(value);//first we make out general tree
            General_temp = new General_Tree_Nodes<input_type>(*General_head);// we will make an copy of General_tree to maintain the original general tree
            General_to_binary(General_temp, Binary_head);//now we convert it
        }
        void General_to_binary(General_Tree_Nodes<input_type>* head, Binary_Tree_Nodes<input_type>* Binary_temp){
            if(head->childs == nullptr)     return; // if there is no child, return
            if(Binary_temp == nullptr){
                Binary_head = new Binary_Tree_Nodes(head->data);//give head to binary tree
                General_to_binary(head, Binary_head);//call function to convert tree from general to binary
            }else{// if Binary_head != nullptr then we have to make its left and right childs
                if(Binary_temp->left_child == nullptr){//this will make first left child
                    Binary_Tree_Nodes<input_type>* add = new Binary_Tree_Nodes(head->childs->data);//make binary leaf with same value
                    add->parent = Binary_temp;
                    Binary_temp->left_child = add;//add it to Binary tree
                    General_to_binary(head->childs, Binary_temp->left_child);//do all this again for sub_tree of curent leaf
                    head->childs = head->childs->right_sibling;//move for next data value
                    General_to_binary(head, Binary_temp);
                }else{//this will make right childs of left child which have been made it upper if condition
                    Binary_temp = Binary_temp->left_child;//move to left child
                    while(head->childs != nullptr){//move on until there is no child to add
                        Binary_Tree_Nodes<input_type>* add = new Binary_Tree_Nodes(head->childs->data);//make binary leaf with same value
                        add->parent = Binary_temp;
                        Binary_temp->right_child = add;//add it to Binary tree
                        General_to_binary(head->childs, Binary_temp->right_child);//do all this again for sub_tree of curent leaf
                        Binary_temp = Binary_temp->right_child;
                        head->childs = head->childs->right_sibling;//move for next data value
                    }
                }
            }
        }
        //==================================================================================================
        void in_order(Binary_Tree_Nodes<input_type>* temp){//LVR
            if(temp->left_child != nullptr){
                in_order(temp->left_child);
            }
            cout<<temp->data<<", ";
            if(temp->right_child != nullptr){
                in_order(temp->right_child);
            }
        }
        //==================================================================================================
        void pre_order(Binary_Tree_Nodes<input_type>* temp){//VLR
            cout<<temp->data<<", ";
            if(temp->left_child != nullptr){
                pre_order(temp->left_child);
            }
            if(temp->right_child != nullptr){
                pre_order(temp->right_child);
            }
        }
        //==================================================================================================
        void post_order(Binary_Tree_Nodes<input_type>* temp){//LRV
            if(temp->left_child != nullptr){
                post_order(temp->left_child);
            }
            if(temp->right_child != nullptr){//LRV
                post_order(temp->right_child);
            }
            cout<<temp->data<<", ";
        }
        //==================================================================================================
        void show(string way){
            if (way == "LVR"){
                in_order(Binary_head);
            }
            if (way == "VLR"){
                pre_order(Binary_head);
            }
            if (way == "LRV"){
                post_order(Binary_head);
            }
        }
};
int main(){
    int s;
    cout<<"please enter value of tree`s head: ";
    cin>>s;
    Result<int> tree(s);
    cout<<"in order: ";
    tree.show("LVR");
    cout<<'\n';
    cout<<"pre order: ";
    tree.show("VLR");
    cout<<'\n';
    cout<<"post order: ";
    tree.show("LRV");
    return 0;
}

