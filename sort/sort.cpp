#include<iostream>

using namespace std;

void bubble_sort(int a[], int len) {
    int i, j, temp;
    for (i = 0; i < len; i++) {
        for (j = i + 1; j < len; j++) {
            if (a[j] < a[i]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    cout << "Sorted array is : \n";
    for (i = 0; i < len; i++) {
        cout << a[i] << "\t";
    }
}


//...............................................................................

int findSmallest(int[], int, int);

void selection_sort(int myarray[], int lenth) {
    int pos, temp;
    for (int i = 0; i < lenth; i++) {
        pos = findSmallest(myarray, i, lenth);
        temp = myarray[i];
        myarray[i] = myarray[pos];
        myarray[pos] = temp;
    }
    cout << "\n Sorted array is :\n";
    for (int i = 0; i < lenth; i++) {
        cout << myarray[i] << "\t";
    }
}

int findSmallest(int myarray[], int i, int lenth) {
    int ele_small, position, j;
    ele_small = myarray[i];
    position = i;
    for (j = i + 1; j < lenth; j++) {
        if (myarray[j] < ele_small) {
            ele_small = myarray[j];
            position = j;
        }
    }
    return position;
}

//..................................................................................

void insertion_sort(int myarray[], int len) {
    for (int k = 1; k < len; k++) {
        int temp = myarray[k];
        int j = k - 1;
        while (j >= 0 && temp <= myarray[j]) {
            myarray[j + 1] = myarray[j];
            j = j - 1;
        }
        myarray[j + 1] = temp;
    }
    cout << "\nSorted array is :\n";
    for (int i = 0; i < len; i++) {
        cout << myarray[i] << "\t";
    }
}


//..............................................................................


void swap(int arr[], int pos1, int pos2) {
    int temp;
    temp = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = temp;
}

int partition(int arr[], int low, int high, int pivot) {
    int i = low;
    int j = low;
    while (i <= high) {
        if (arr[i] > pivot) {
            i++;
        } else {
            swap(arr, i, j);
            i++;
            j++;
        }
    }
    return j - 1;
}

void quickSort(int arr[], int low, int high) {

    if (low < high) {
        int pivot = arr[high];
        int pos = partition(arr, low, high, pivot);

        quickSort(arr, low, pos - 1);
        quickSort(arr, pos + 1, high);
    }
}

int quick_sort(int arr[], int n) {
    quickSort(arr, 0, n - 1);
    cout << "sorted array is : " << "\t";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\t";
    }

}


//.........................................................................................

void merge(int *, int, int, int);

void merge_sort(int *arr, int low, int high) {
    int mid;
    if (low < high) {
        mid = (low + high) / 2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, high);
        merge(arr, low, high, mid);
    }
}

void merge(int *arr, int low, int high, int mid) {
    int i, j, k, c[50];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high) {
        if (arr[i] < arr[j]) {
            c[k] = arr[i];
            k++;
            i++;
        } else {
            c[k] = arr[j];
            k++;
            j++;
        }
    }

    while (i <= mid) {
        c[k] = arr[i];
        k++;
        i++;
    }
    while (j <= high) {
        c[k] = arr[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++) {
        arr[i] = c[i];
    }
}

int merge_sort(int myarray[], int num) {
    merge_sort(myarray, 0, num - 1);
    cout << "Sorted array is :\n";
    for (int i = 0; i < num; i++) {
        cout << myarray[i] << "\t";
    }
}


//...................................................................................


struct Node {
    int key;
    struct Node *left, *right;
};

struct Node *newNode(int item) {
    struct Node *temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void storeSorted(Node *root, int arr[], int &i) {
    if (root != NULL) {
        storeSorted(root->left, arr, i);
        arr[i++] = root->key;
        storeSorted(root->right, arr, i);
    }
}

Node *insert(Node *node, int key) {

    if (node == NULL) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

void treeSort(int arr[], int n) {
    struct Node *root = NULL;

    root = insert(root, arr[0]);
    for (int i = 1; i < n; i++)
        root = insert(root, arr[i]);

    int i = 0;
    storeSorted(root, arr, i);
}

void bst(int arr[], int n) {
    treeSort(arr, n);
    cout << "sorted array is : ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

}

//.........................................................................................


int main() {
    int mycase;
    cout
            << " for bubble sort = 1 \n for selection sort = 2 \n for insertion sort = 3 \n for merge sort = 4 \n for quick sort = 5 \n for bst = 6 : \n ";
    cin >> mycase;
    switch (mycase) {
        case 1: {

            int size;
            cout << "Enter size of your array" << "\n";
            cin >> size;
            int arr[size];
            cout << "Enter your numbers" << "\n";
            for (int i = 0; i < size; i++) {
                cin >> arr[i];

            }
            bubble_sort(arr, size);
            break;
        }

        case 2: {
            int size;
            cout << "Enter size of your array" << "\n";
            cin >> size;
            int arr[size];
            cout << "Enter your numbers" << "\n";
            for (int i = 0; i < size; i++) {
                cin >> arr[i];
            }
            selection_sort(arr, size);

            break;
        }
        case 3: {
            int size;
            cout << "Enter size of your array" << "\n";
            cin >> size;
            int arr[size];
            cout << "Enter your numbers" << "\n";
            for (int i = 0; i < size; i++) {
                cin >> arr[i];

            }
            insertion_sort(arr, size);

            break;
        }

        case 4: {
            int size;
            cout << "Enter size of your array" << "\n";
            cin >> size;
            int arr[size];
            cout << "Enter your numbers" << "\n";
            for (int i = 0; i < size; i++) {
                cin >> arr[i];

            }
            merge_sort(arr, size);


            break;
        }
        case 5: {
            int size;
            cout << "Enter size of your array" << "\n";
            cin >> size;
            int arr[size];
            cout << "Enter your numbers" << "\n";
            for (int i = 0; i < size; i++) {
                cin >> arr[i];

            }
            quick_sort(arr, size);


            break;
        }
        case 6: {
            int size;
            cout << "Enter size of your array" << "\n";
            cin >> size;
            int arr[size];
            cout << "Enter your numbers" << "\n";
            for (int i = 0; i < size; i++) {
                cin >> arr[i];

            }
            bst(arr, size);

            break;
        }
    }

    return 0;
}