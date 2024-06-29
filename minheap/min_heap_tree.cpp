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
        }
};
template < typename input_type > 
class Binary_Tree {
    private:
        Binary_Tree_Nodes<input_type>* head = nullptr;
    public:
        //==================================================================================================
        Binary_Tree_Nodes<input_type>* find_last_node(bool remove_insert){
            /*
            because we need to find last node in both insert and remove 
            and way of finding last node for each on is different, so i make it in
            to part one for insert which is while remove_insert == 0 and one for remove
            which is while remove_insert == 1
            */
            Binary_Tree_Nodes<input_type>* temp = head;
            int hight = 0;
            int hight_temp = 0;
            while(temp->left_child != nullptr){//calculate hight of tree
                hight++;
                temp = temp->left_child;
            }
            Binary_Tree_Nodes<input_type>* last = nullptr;
            if(remove_insert == 0){// if function call is about insert
                last_node(head, last, hight, hight_temp, 0);//call last_node function for insert
            }else{// if function call is about remove
                last_node(head, last, hight, hight_temp, 1);//call last_node function for remove
            }
            if(last == nullptr){
                /* 
                if last_node don`t find any thing its mean tree is complete and full
                so for insert we have to go to left most node and
                for remove we have to go to right most node
                */
                if(remove_insert == 0){// if function call is about insert
                    Binary_Tree_Nodes<input_type>* temp = head;
                    while(temp->left_child != nullptr){
                        temp = temp->left_child;
                    }
                    last = temp;
                }else{// if function call is about remove
                    Binary_Tree_Nodes<input_type>* temp = head;
                    while(temp->right_child != nullptr){
                        temp = temp->right_child;
                    }
                    last = temp->parent;
                }
            }
            return last;
        }
        //==================================================================================================
        void insert(input_type value){
            if(head == nullptr){
                head = new Binary_Tree_Nodes<input_type>(value);
            }else{
                Binary_Tree_Nodes<input_type>* last = find_last_node(0);//call find_last_node function for insert
                fill(last, value);//insert value to its place and then correct place of it base on data of nodes
            }
        }
        //==================================================================================================
        input_type remove(){
            if(head == nullptr){
                return input_type();
            }
            input_type value = input_type();
            value = head->data;//store value of head to return it after remove
            Binary_Tree_Nodes<input_type>* last = find_last_node(1);//call find_last_node function for remove
            if(last->left_child != nullptr && last->right_child != nullptr){//if last have both left and right childs head will be replace by right child
                head->data = last->right_child->data;
                last->right_child->parent->right_child = nullptr;
            }else if(last->left_child != nullptr && last->right_child == nullptr){//if last have only left child head will be replace by left child
                head->data = last->left_child->data;
                last->left_child->parent->left_child = nullptr;
            }else{// if last don`t have any child head will be replace by last
                head = nullptr;
                return value;
            }//because its min heap tree we dont have a situation where tree have right child and dint have left child because in this situation tree is not complete
            right_place(head, 1);//call right_place function for remove
            return value;
        }
        //==================================================================================================
        void last_node(Binary_Tree_Nodes<input_type>* temp, Binary_Tree_Nodes<input_type>*& last, int tree_hight, int& current_hight, bool remove_insert){
            /*
            because we need to find last node in both insert and remove 
            and way of finding last node for each on is different, so i make it in
            to part one for insert which is while remove_insert == 0 and one for remove
            which is while remove_insert == 1
            */
           if(remove_insert == 0){// if function call is about insert
                if(tree_hight == 0){
                    last = temp;
                    return;
                }
                if(temp->left_child != nullptr){
                    current_hight++;
                    last_node(temp->left_child, last, tree_hight, current_hight, 0);//call last_node function for insert
                }else{
                    bool a1 = (last == nullptr);//because we need only one last place so if it has been found already we dont search any more
                    if(!a1){
                        return;
                    }
                    bool a2 = (temp->left_child == nullptr && temp->right_child == nullptr);
                    bool a3 = (temp->parent->right_child != nullptr && temp->parent->right_child->left_child == nullptr && temp->parent->right_child->right_child == nullptr);
                    bool a4 = (current_hight == tree_hight);
                    //if a2 and a3 and a4 be true it mean that temp is leaf, otherwise it`s not
                    if(a2 && a3 && a4){
                        current_hight--;
                        return;
                    }else{
                        if(a1 && a3){
                            last = temp;
                        }else if(a1 && !a3){
                            last = temp->parent;
                        }
                        current_hight--;
                        return;
                    }
                }
                if(temp->right_child != nullptr){
                    current_hight++;
                    last_node(temp->right_child, last, tree_hight, current_hight, 0);//call last_node function for insert
                }else{
                    bool a1 = (last == nullptr);//because we need only one last place so if it has been found already we dont search any more
                    if(!a1){
                        return;
                    }
                    bool a2 = (temp->left_child == nullptr && temp->right_child == nullptr);
                    bool a3 = (temp->parent->left_child != nullptr && temp->parent->left_child->left_child == nullptr && temp->parent->left_child->right_child == nullptr);
                    bool a4 = (current_hight == tree_hight);
                    //if a2 and a3 and a4 be true it mean that temp is leaf, otherwise it`s not
                    if(a2 && a3 && a4){
                        current_hight--;
                        return;
                    }else{
                        if(a1 && a3){
                            last = temp;
                        }else if(a1 && !a3){
                            last = temp->parent;
                        }
                        current_hight--;
                        return;
                    }
                }
                current_hight--;
           }else{// if function call is about remove
                if(tree_hight == 0){
                    last = temp;
                    return;
                }
                if(tree_hight == 1 && temp->left_child != nullptr && (temp->right_child == nullptr || temp->right_child != nullptr)){
                    last = temp;
                    return;
                }
                if(temp->right_child != nullptr){
                    current_hight++;
                    last_node(temp->right_child, last, tree_hight, current_hight, 1);//call last_node function for remove
                }else{
                    bool a1 = (last == nullptr);//because we need only one last place so if it has been found already we dont search any more
                    if(!a1){
                        return;
                    }
                    bool a2 = (temp->left_child == nullptr && temp->right_child == nullptr);
                    bool a3 = (temp->parent->left_child != nullptr && temp->parent->left_child->left_child == nullptr && temp->parent->left_child->right_child == nullptr);
                    bool a4 = (current_hight == tree_hight);
                    //if a2 and a3 and a4 be true it mean that temp is leaf, otherwise it`s not
                    if(a2 && a4){
                        if(a1 && !a3){
                            last = temp;
                        }else if(a1 && a3){
                            last = temp->parent;
                        }
                    }
                }
                if(temp->left_child != nullptr){
                    current_hight++;
                    last_node(temp->left_child, last, tree_hight, current_hight, 1);//call last_node function for remove
                }else{
                    bool a1 = (last == nullptr);//because we need only one last place so if it has been found already we dont search any more
                    if(!a1){
                        return;
                    }
                    bool a2 = (temp->left_child == nullptr && temp->right_child == nullptr);
                    bool a3 = (temp->parent->right_child != nullptr && temp->parent->right_child->left_child == nullptr && temp->parent->right_child->right_child == nullptr);
                    bool a4 = (current_hight == tree_hight);
                    //if a2 and a3 and a4 be true it mean that temp is leaf, otherwise it`s not
                    if(a2 && a4){
                        if(a1 && !a3){
                            last = temp;
                        }else if(a1 && a3){
                            last = temp->parent;
                        }
                    }
                }
                current_hight--;
            }
        }
        //==================================================================================================
        void fill(Binary_Tree_Nodes<input_type>* last, input_type value){
            if(last->left_child == nullptr && last->right_child == nullptr){
                last->left_child = new Binary_Tree_Nodes<input_type>(value);
                last->left_child->parent = last;
                right_place(last->left_child, 0);//call right_place function for insert
            }else if(last->left_child != nullptr && last->right_child == nullptr){
                last->right_child = new Binary_Tree_Nodes<input_type>(value);
                last->right_child->parent = last;
                right_place(last->right_child, 0);//call right_place function for insert
            }
        }
        //==================================================================================================
        void right_place(Binary_Tree_Nodes<input_type>* node, bool remove_insert){
            /*
            because we need to find right place of node in both insert and remove 
            and way of finding right place for each on is different, so i make it 
            in to part one for insert which is while remove_insert == 0 and one for
            remove which is while remove_insert == 1
            */
            if(remove_insert == 0){// if function call is about insert
                if(node->parent == nullptr){
                    return;
                }
                if(node->data >= node->parent->data){// nodes of childs must be larger than parent in min heap tree
                    return;
                }else{
                    input_type temp = node->data;
                    node->data = node->parent->data;
                    node->parent->data = temp;
                    right_place(node->parent, 0);//call right_place function for insert
                    
                }
            }else{// if function call is about remove
                if(node->left_child == nullptr && node->right_child == nullptr){
                    return;
                }else if((node->left_child != nullptr && node->right_child != nullptr)){
                    if((node->data < node->left_child->data) && (node->data < node->right_child->data)){//check which child of node is smaller so node will be change by that
                        return;
                    }else{
                        if(node->left_child->data < node->right_child->data){
                            input_type temp = node->data;
                            node->data = node->left_child->data;
                            node->left_child->data = temp;
                            right_place(node->left_child, 1);//call right_place function for remove
                            return;
                        }else{
                            input_type temp = node->data;
                            node->data = node->right_child->data;
                            node->right_child->data = temp;
                            right_place(node->right_child, 1);//call right_place function for remove
                            return;
                        }
                    }
                }else if((node->left_child != nullptr && node->right_child == nullptr)){
                    if(node->data < node->left_child->data){
                        return;
                    }else{
                        input_type temp = node->data;
                        node->data = node->left_child->data;
                        node->left_child->data = temp;
                        right_place(node->left_child, 1);//call right_place function for remove
                        return;
                    }
                }
            }
        }        
};
int main(){
    Binary_Tree<int> tree;
    tree.insert(100);
    tree.insert(90);
    tree.insert(80);
    tree.insert(70);
    tree.insert(60);
    tree.insert(50);
    tree.insert(40);
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);
    while(true){
        int a = tree.remove();
        if(a == int())  break;
        cout<<a<<'\n';
    }
    cout<<"Tree is empty!!!!\n";
    return 0;
}