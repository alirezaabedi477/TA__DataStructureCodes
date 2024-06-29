//4001406135
#include <iostream>
using namespace std; 
template < typename input_type > 
class Binary_Tree_Nodes{
    public:
        input_type data = input_type();
        Binary_Tree_Nodes<input_type>* parent = nullptr;// point to parent of current part
        Binary_Tree_Nodes<input_type>* left_child = nullptr;// point to left child of current part if exist 
        Binary_Tree_Nodes<input_type>* right_child = nullptr;// point to right child of current part if exist 
        Binary_Tree_Nodes(input_type value){
            this->data = value;
            add_child(value, this);          
        }
        void add_child(input_type value, Binary_Tree_Nodes<input_type>* temp){
            int left = 0;// it work like a bool, 1 = true, 0 = false
            input_type value_left = input_type();
            int right = 0;// it work like a bool, 1 = true, 0 = false
            input_type value_right = input_type();
            do{
                cout<<"Those '"<<value<<"' have left child? 1(true) or 0(false): ";
                cin>>left;// check for exist of left child
            }while(left != 0 && left != 1);//dont allow user to enter value except 0, and 1
            do{ 
                cout<<"Those "<<value<<" have right child? 1(true) or 0(false): ";
                cin>>right;// check for exist of right child 
            }while(right != 0 && right != 1);//dont allow user to enter value except 0, and 1
            if(left || right)// Do this only for prettier print in terminal
                cout<<"-----------------------------------------------------\n"; 
            if(left){
                cout<<"Enter value of '"<<value<<"' left child: ";
                cin>>value_left;
            }        
            if(right){
                cout<<"Enter value of '"<<value<<"' right child: ";
                cin>>value_right;
            }
            if(left){
                cout<<"-----------------------------------------------------\n";        
                cout<<value_left<<" is left child of '"<<value<<"'.\n";
                left_child = new Binary_Tree_Nodes<input_type>(value_left);
                left_child->parent = this;
            }
            if(right){
                cout<<"-----------------------------------------------------\n";        
                cout<<value_right<<" is right child of '"<<value<<"'.\n";
                right_child = new Binary_Tree_Nodes<input_type>(value_right);
                right_child->parent = this;
            }
            temp->left_child = left_child;
            temp->right_child = right_child;           
        }
};
template < typename input_type > 
class Binary_Tree {
    private:
        Binary_Tree_Nodes<input_type>* head = nullptr;
        int hight = 0;
    public:
        Binary_Tree(input_type value){
            head = new Binary_Tree_Nodes<input_type>(value);
            int hight_temp = 0;
            hight_tree(head, hight, hight_temp, 0, 0);
        }
        //==================================================================================================
        void hight_tree(Binary_Tree_Nodes<input_type>* temp, int& hight, int& current_hight, bool show, int target){
            if(show == 1){
                if(current_hight+1 == target){
                    cout<<temp->data<<", ";
                    return;
                }
                current_hight++;
                if(temp->left_child != nullptr){
                    hight_tree(temp->left_child, hight, current_hight, 1, target);
                }
                if(temp->right_child != nullptr){
                    hight_tree(temp->right_child, hight, current_hight, 1, target);
                }
                current_hight--;
            }else{
                if(temp->left_child == nullptr && temp->right_child == nullptr){
                    if(current_hight > hight){
                        hight = current_hight;
                    }
                    current_hight--;
                    return;
                }
                if(temp->left_child != nullptr){
                    current_hight++;
                    hight_tree(temp->left_child, hight, current_hight, 0, 0);
                }
                if(temp->right_child != nullptr){
                    current_hight++;
                    hight_tree(temp->right_child, hight, current_hight, 0, 0);
                }
                current_hight--;
            }
        }
        //==================================================================================================
        void BFS(Binary_Tree_Nodes<input_type>* temp){
            int hight_temp = 0;
            for(int i = 1; i <= hight+1; i++){
                hight_temp = 0;
                hight_tree(temp, hight, hight_temp, 1, i);
            }
        }
        //==================================================================================================
        void DFS(Binary_Tree_Nodes<input_type>* temp){
            cout<<temp->data<<", ";
            if(temp->left_child != nullptr){
                DFS(temp->left_child);
            }
            if(temp->right_child != nullptr){
                DFS(temp->right_child);
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
                in_order(head);
            }
            if (way == "VLR"){
                pre_order(head);
            }
            if (way == "LRV"){
                post_order(head);
            }
            if (way == "BFS"){
                BFS(head);
            }
            if (way == "DFS"){
                DFS(head);
            }
        }
        
};
int main(){
    Binary_Tree<int> tree(10);
    cout<<"============================================\n";
    cout<<"In order: ";
    tree.show("LVR");
    cout<<"\nPre order: ";
    tree.show("VLR");
    cout<<"\nPost order: ";
    tree.show("LRV");
    cout<<"\nBFS: ";
    tree.show("BFS");
    cout<<"\nDFS: ";
    tree.show("DFS");
    cout<<"\n============================================";
    return 0;
}