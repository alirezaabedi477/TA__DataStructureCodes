//4001406135
#include <iostream>
#include <string>
#include "link_list.h"
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
                cout<<"Those "<<value<<" has any childs? 1(true) or 0(false): ";
                cin>>check;//check if value have any child
            }while(check != 0 && check != 1);//dont allow user to enter value except 0, and 1
            int num1 = 0 ;
            if(check){
                cout<<"How many kids those "<<value<<" have? ";
                cin>>num1;//enter number of childs
                array = new input_type[num1];// make array with proper size
                cout<<"-----------------------------------------------------\n";
                for (int j = 0 ; j < num1 ; j++){
                    cout<<"Enter value of "<<j+1<<" child of "<<value<<": ";
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
class Tree {
    private:
        General_Tree_Nodes<input_type>* Tree_head = nullptr;
    public:
        Tree(input_type value){
            General_Tree_Nodes<input_type>* new_part = new General_Tree_Nodes<input_type>(value);
            Tree_head = new_part;
        }
        void BFS(General_Tree_Nodes<input_type>* temp){//Breadth first search
            if ( temp->childs == nullptr || temp == nullptr)   return;
            if(temp == Tree_head){
                a.append_front(temp->data);
            }
            General_Tree_Nodes<input_type>* temp2 = new General_Tree_Nodes<input_type>(*temp);
            while(!a.is_empty()){
                input_type value = a.pop_first();
                cout<<value;
                while(temp2->childs != nullptr){
                    a.append_front(temp2->childs->data);
                    temp2->childs = temp2->childs->right_sibling;
                }
                temp2 = temp;
                while(temp2->childs != nullptr){
                    if(temp2->data == value){
                        BFS(temp2->childs);
                    }
                    temp2->childs = temp2->childs->right_sibling;
                }
            }
        }
        void DFS(){//Depth first search

        }
        void show(string name){
            if(name == "BFS"){
                link_list <input_type> a;
                BFS(Tree_head);
            }
        }

};
int main(){
    Tree <char> tree('a');
    tree.show("BFS");


    return 0;
}