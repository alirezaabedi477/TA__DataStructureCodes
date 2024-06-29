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
        }
};
template < typename input_type > 
class Binary_Tree {
    private:
        Binary_Tree_Nodes<input_type>* head = nullptr;
        int length = 0;
        input_type *in_ord;
        input_type *pre_ord;
    public:
        void make_array(){
            cout<<"please enter length of in-order and pre-order: ";
            cin>>length;
            in_ord = new input_type[length];
            pre_ord = new input_type[length];
            cout<<"Please enter in-order of tree one by one: \n";
            for(int i = 0; i < length; i++){
                cin>>in_ord[i];
            }
            cout<<"Please enter pre-order of tree one by one: \n";
            for(int i = 0; i < length; i++){
                cin>>pre_ord[i];
            }
        }
        void make_tree(int start, int end){
            if (start > end || end > length)   return;
            if((end - start) == 3 ){
                Binary_Tree_Nodes<input_type>* temp = new Binary_Tree_Nodes<input_type>(pre_ord[start]);
                temp->left_child = new Binary_Tree_Nodes<input_type>(pre_ord[start+1]);
                temp->right_child = new Binary_Tree_Nodes<input_type>(pre_ord[start+2]);
                head = temp;
                return;
            }
            if((end - start) == 2){
                int k = 0;
                Binary_Tree_Nodes<input_type>* temp = new Binary_Tree_Nodes<input_type>(pre_ord[start]);
                for (; in_ord[k] != pre_ord[start]; k++);
                if(pre_ord[start+1] == in_ord[k-1]){
                    temp->left_child = new Binary_Tree_Nodes<input_type>(pre_ord[start+1]);
                }else if(pre_ord[start+1] == in_ord[k+1]){
                    temp->right_child = new Binary_Tree_Nodes<input_type>(pre_ord[start+1]);
                }
                return;
            }
            for(int i = start; i < end; i++){// loop for pre order
                for(int j = 0; j < end; j++){// loop for in order
                    if(in_ord[j] == pre_ord[i]){
                        make_tree(i+1, i+j+1);//left child
                        make_tree(i+j+1, end);//right childs
                        return;
                    }
                }
                break;
            }
        }
        void remake(){
            make_array();
            make_tree(0, length);
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
        }
        
};
int main(){
    Binary_Tree<char> tree;
    tree.remake();


    return 0;
}