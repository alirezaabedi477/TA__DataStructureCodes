//4001406135 alirezaabedi
class LinkedList {
   public: 
          node* start; 
         node* create_node(int value); 
         void insert(int value); 
         void deleteFirst(); 
         void display(); 
         LinkedList() 
         { 
             start = NULL; 
         } 
 }; 
 node *LinkedList::create_node(int value) { 
     struct node *temp; 
     temp = new (struct node); 
     if (temp == NULL) { 
          cout << "Memory not allocated " << endl; 
          return 0; 
     } else { 
          temp->info = value; 
          temp->next = NULL; 
          return temp; 
     } 
 } 
 void LinkedList::insert(int value) { 
     struct node *temp, *s; 
     temp = create_node(value); 
     if(start == NULL){ 
          start = temp; 
          cout << value << " Inserted at List" << endl; 
          return; 
     } 
     s = start; 
     while (s->next != NULL) { 
          s = s->next; 
     } 
     temp->next = NULL; 
     s->next = temp; 
     cout << value << " Inserted at List" << endl; 
 } 
 void LinkedList::deleteFirst() { 
     if (start == NULL) { 
          cout << "The List is Empty" << endl; 
          return; 
     } 
     node *temp = start; 
     start = start->next; 
     delete temp; 
 } 
 void LinkedList::display() { 
     struct node *temp; 
     if (start == NULL) { 
          cout << "The List is Empty" << endl; 
          return; 
     } 
     temp = start; 
     cout << "Elements of list are: " << endl; 
     while (temp != NULL) { 
          cout << temp->info << "->"; 
          temp = temp->next; 
     } 
     cout << "NULL" << endl; 
 } 
  int main() {
    LinkedList l; 
    l.insert(11); 
    l.insert(22); 
    l.insert(33); 
    cout << "display List" << endl; 
    l.display(); 
    l.deleteFirst(); 
    l.display(); 
    return 0; 
} 