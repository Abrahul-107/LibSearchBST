#include<bits/stdc++.h>
using namespace std;

class Student
{
public:
    string name;
    int id_no;
    string stream;
    string book1, book2;
    int book_no, issuedbook;

    Student(string name, int id_no, string stream)
    {
        this->name = name;
        this->id_no = id_no;
        this->stream = stream;
        this->book1 = "";
        this->book2 = "";
        this->book_no = 0;
        this->issuedbook = 0;
    }
};

void selectionSort(vector<Student> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j].id_no < arr[min_idx].id_no) // Sort according to ID number of student
                min_idx = j;
        }
        swap(arr[min_idx], arr[i]);
    }
}

void display(const vector<Student> &arr)
{
    for (const auto &student : arr)
    {
        cout << "\nName of Student: " << student.name;
        cout << "\nId of Student: " << student.id_no;
        cout << "\nStream of Student: " << student.stream;
    }
    for (const auto &books : arr)
    {
        cout << "\nName of Student: " << books.name;
      
    }

}

class Node
{
public:
    string key;
    Node *left;
    Node *right;

    Node(string item)
    {
        key = item;
        left = nullptr;
        right = nullptr;
    }
};

class BST
{
public:
    Node *root;

    BST()
    {
        root = nullptr;
    }

    void insert(string key)
    {
        root = insertRec(root, key);
    }

    Node *insertRec(Node *root, string key)
    {
        if (root == nullptr)
        {
            root = new Node(key);
            return root;
        }

        if (key < root->key) // If book name < root then place it as left child
            root->left = insertRec(root->left, key);
        else if (key > root->key) // If book name > root then place it as Right child
            root->right = insertRec(root->right, key);
        else
            cout << "Error: Duplicate book name." << endl;

        return root;
    }

    void update(string key, string key1)
    {
        deleteKey(key);
        insert(key1);
    }

    bool containsNode(string value)
    {
        return containsNodeRecursive(root, value);
    }

    bool containsNodeRecursive(Node *current, string key)
    {
        if (current == nullptr)
        {
            return false;
        }
        if (key == current->key)
        {
            return true;
        }
        return key < current->key
                   ? containsNodeRecursive(current->left, key)
                   : containsNodeRecursive(current->right, key);
    }

    void printTree()
    {
        printTreeRec(root, 0);
    }

    void printTreeRec(Node *t, int space)
    {
        if (t == nullptr)
            return;

        space += 5;
        printTreeRec(t->right, space);

        cout << endl;
        for (int i = 5; i < space; i++)
            cout << " ";
        cout << "[" << t->key << "]";

        printTreeRec(t->left, space);
    }

    void deleteKey(string key)
    {
        root = deleteRec(root, key);
    }

    Node *deleteRec(Node *root, string key)
    {
        if (root == nullptr)
            return root;

        if (key < root->key)
            root->left = deleteRec(root->left, key);
        else if (key > root->key)
            root->right = deleteRec(root->right, key);
        else
        {
            if (root->left == nullptr)
                return root->right;
            else if (root->right == nullptr)
                return root->left;

            root->key = minValue(root->right);
            root->right = deleteRec(root->right, root->key);
        }

        return root;
    }

    string minValue(Node *root)
    {
        string minv = root->key;
        while (root->left != nullptr)
        {
            minv = root->left->key;
            root = root->left;
        }
        return minv;
    }

    void printInorder(Node *node)
    {
        if (node == nullptr)
            return;

        printInorder(node->left);
        cout << node->key << "        ";
        printInorder(node->right);
    }

    void printInorder()
    {
        printInorder(root);
    }

    void inorder()
    {
        inorderRec(root);
    }

    void inorderRec(Node *root)
    {
        if (root != nullptr)
        {
            inorderRec(root->left);
            cout << root->key << endl;
            inorderRec(root->right);
        }
    }
};

int main()
{

    printf("LIbrary Management system using BINARY SEARCH TREE data structure for optimal search and update");
    ifstream reader("Books.txt");
    ifstream reader2("NumberOfBooks.txt");
    ifstream reader3("IdofBooks.txt");

    ofstream br("append.txt", ios::app);
    ofstream br1("append.txt", ios::app);
    ofstream br2("append.txt", ios::app);
    ofstream br3("append.txt", ios::app);

    BST tree;
    map<string, int> hashmapping;
    vector<Student> array = {
        Student("Rahul", 17, "MCA-GIETU"),
        Student("Sai_kiran", 69, "B.Tech-CUAT"),
        Student("Vivek", 96, "MCA-KIIT"),
        Student("AnupBRO", 8008, "MCA-KIIT")};

    int arr[100][2] = {0};

    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", ltm);
    string currentDateTime(buffer);

    int i = 0;
    bool e1 = false;
    while (!e1)
    {
        cout << "\n.....................................";
        cout << "\n1. Librarian Login.";
        cout << "\n2. User Login.";
        cout << "\n3. Exit.";
        cout << "\n.....................................";
        cout << "\nEnter Your choice:";
        int ch1;
        cin >> ch1;

        switch (ch1)
        {
        case 1:
        { // For Librarian login
            string pwd1 = "abd17";
            string id1 = "abd360";

            cout << "\nEnter UserId: ";
            string id2;
            cin >> id2;

            cout << "\nEnter Password: ";
            string pwd2;
            cin >> pwd2;

            if (id1 != id2)
                cout << "Invalid Userid." << endl;
            else if (pwd1 != pwd2)
                cout << "Invalid Password." << endl;
            else
            {
                cout << "Login successfully." << endl;
                bool e2 = false;
                while (!e2)
                {
                    cout << "\n.....................................";
                    cout << "\n1. Add book.";
                    cout << "\n2. Delete book.";
                    cout << "\n3. Update book.";
                    cout << "\n4. Print Books Details.";
                    cout << "\n5. Print Books in-order.";
                    cout << "\n6. Print tree.";
                    cout << "\n7. Exit.";
                    cout << "\n.....................................";
                    cout << "\nEnter Your choice:";
                    int ch2;
                    cin >> ch2;

                    switch (ch2)
                    {
                    case 1:
                    { // To add a book
                        string line;
                        while (getline(reader, line))
                        {
                            tree.insert(line);
                            hashmapping[line] = i;
                            i++;
                        }
                        int j = i;

                        int o = 0;
                        string number;
                        while (getline(reader2, number))
                        {
                            int result = stoi(number);
                            if (j != o)
                                arr[o][0] = result;
                            o++;
                        }

                        int pq = 0;
                        string number1;
                        while (getline(reader3, number1))
                        {
                            int result1 = stoi(number1);
                            if (j != pq)
                                arr[pq][1] = result1;
                            pq++;
                        }

                        cout << "\nEnter name of book:";
                        string name;
                        cin >> name;
                        bool z1 = tree.containsNode(name);

                        if (z1)
                        {
                            cout << "\nIt is already exists.";
                        }
                        else
                        {
                            cout << "\nEnter quantity of book:";
                            int quantity;
                            cin >> quantity;
                            br1 << name << endl;
                            br2 << quantity << endl;
                            br3 << quantity << endl;

                            tree.insert(name);
                            hashmapping[name] = i;
                            arr[i][0] += quantity; // Total quantity of books
                            arr[i][1] += quantity; // Available quantity of books
                            i++;
                        }
                        break;
                    }
                    case 2:
                    { // To delete a book
                        cout << "\nEnter name of book:";
                        string b1;
                        cin >> b1;

                        bool x = tree.containsNode(b1);
                        if (x)
                        {
                            tree.deleteKey(b1);
                            hashmapping.erase(b1);
                        }
                        break;
                    }
                    case 3:
                    { // To update a book
                        cout << "\nEnter name of book which you want to Update:";
                        string oldName;
                        cin >> oldName;

                        cout << "\nEnter Updated name of book:";
                        string newName;
                        cin >> newName;

                        bool z = tree.containsNode(newName);
                        if (z)
                            cout << "\nIt is already exists.";
                        else
                        {
                            tree.update(oldName, newName);
                            auto it = hashmapping.find(oldName);
                            if (it != hashmapping.end())
                            {
                                int temp = it->second;
                                hashmapping.erase(oldName);
                                hashmapping[newName] = temp;
                            }
                        }
                        break;
                    }
                    case 4:
                    { // To print books details
                        cout << ".................................................";
                        cout << "\nBook Name                Quantity";
                        cout << "\n.................................................";
                        for (const auto &it : hashmapping)
                        {
                            cout << "\n"
                                 << it.first;
                            int q = it.second;
                            cout << "                     " << arr[q][0];
                        }
                        cout << "\n.................................................";
                        break;
                    }
                    case 5:
                    { // Print Books in-order
                        cout << "Books Inorder:\n";
                        tree.printInorder();
                        break;
                    }
                    case 6:
                    { // Print tree
                        cout << "\n.................................................";
                        tree.printTree();
                        cout << "\n.................................................";
                        break;
                    }
                    case 7:
                    { // Exit from Librarian menu
                        e2 = true;
                        break;
                    }
                    default:
                        cout << "Invalid input. Please try again.";
                        break;
                    }
                }
            }
            break;
        }
        case 2:
        { // For User login
            bool e3 = false;
            while (!e3)
            {
                cout << "\n.....................................";
                cout << "\n1. Issue Book.";
                cout << "\n2. Submit Book.";
                cout << "\n3. Student Details.";
                cout << "\n4. Book Details.";
                cout << "\n5. Exit.";
                cout << "\n.....................................";
                cout << "\nEnter Your choice:";
                int ch3;
                cin >> ch3;

                switch (ch3)
                {
                case 1:
                { // To issue a book
                    cout << "\nEnter student id:";
                    int sid;
                    cin >> sid;

                    auto it = find_if(array.begin(), array.end(), [&](const Student &s)
                                      { return s.id_no == sid; });
                    if (it != array.end())
                    {
                        int j = it - array.begin();
                        cout << "\nName of student is: " << array[j].name;
                        cout << "\nStream of student is: " << array[j].stream;

                        if (array[j].book_no == 2)
                            cout << "\nSorry. You cannot issue any more books.";
                        else
                        {
                            cout << "\nEnter name of book:";
                            string bookName;
                            cin >> bookName;

                            bool y = tree.containsNode(bookName);
                            if (y)
                            {
                                int z = hashmapping[bookName];
                                if (arr[z][1] == 0)
                                {
                                    cout << "\nSorry book is not available.";
                                }
                                else
                                {
                                    br << "Student id: " << array[j].id_no << endl;
                                    br << "Student Name: " << array[j].name << endl;
                                    br << "Stream: " << array[j].stream << endl;
                                    br << "Name of Book: " << bookName << endl;
                                    br << "Issued Date and Time: " << currentDateTime << endl;

                                    if (array[j].book1 == "")
                                        array[j].book1 = bookName;
                                    else
                                        array[j].book2 = bookName;

                                    array[j].book_no += 1;
                                    array[j].issuedbook += 1;
                                    arr[z][1] -= 1;

                                    cout << "\nBook is issued successfully.";
                                }
                            }
                            else
                            {
                                cout << "\nNo such book available.";
                            }
                        }
                    }
                    else
                    {
                        cout << "\nStudent id is invalid.";
                    }
                    break;
                }
                case 2:
                { // To submit a book
                    cout << "\nEnter student id:";
                    int sid;
                    cin >> sid;

                    auto it = find_if(array.begin(), array.end(), [&](const Student &s)
                                      { return s.id_no == sid; });
                    if (it != array.end())
                    {
                        int j = it - array.begin();
                        cout << "\nName of student is: " << array[j].name;
                        cout << "\nStream of student is: " << array[j].stream;

                        if (array[j].book_no == 0)
                            cout << "\nSorry. You have not issued any book.";
                        else
                        {
                            cout << "\nEnter name of book:";
                            string bookName;
                            cin >> bookName;

                            bool z = tree.containsNode(bookName);
                            if (z)
                            {
                                int u = hashmapping[bookName];

                                if (array[j].book1 == bookName || array[j].book2 == bookName)
                                {
                                    if (array[j].book1 == bookName)
                                        array[j].book1 = "";
                                    else if (array[j].book2 == bookName)
                                        array[j].book2 = "";

                                    array[j].book_no -= 1;
                                    arr[u][1] += 1;

                                    cout << "\nBook is submitted successfully.";
                                }
                                else
                                {
                                    cout << "\nNo such book issued by you.";
                                }
                            }
                            else
                            {
                                cout << "\nNo such book available.";
                            }
                        }
                    }
                    else
                    {
                        cout << "\nStudent id is invalid.";
                    }
                    break;
                }
                case 3:
                { // Student Details
                    cout << "\nEnter student id:";
                    int sid;
                    cin >> sid;

                    auto it = find_if(array.begin(), array.end(), [&](const Student &s)
                                      { return s.id_no == sid; });
                    if (it != array.end())
                    {
                        int j = it - array.begin();
                        cout << "\nName of student is: " << array[j].name;
                        cout << "\nStream of student is: " << array[j].stream;
                        cout << "\nNumber of book issued: " << array[j].issuedbook;
                    }
                    else
                    {
                        cout << "\nStudent id is invalid.";
                    }
                    break;
                }
                case 4:
                { // Book Details
                    cout << "\nEnter name of book:";
                    string bookName;
                    cin >> bookName;

                    bool z = tree.containsNode(bookName);
                    if (z)
                    {
                        int u = hashmapping[bookName];
                        cout << "\nTotal quantity of book: " << arr[u][0];
                        cout << "\nAvailable quantity of book: " << arr[u][1];
                    }
                    else
                    {
                        cout << "\nNo such book available.";
                    }
                    break;
                }
                case 5:
                { // Exit from User menu
                    e3 = true;
                    break;
                }
                default:
                    cout << "Invalid input. Please try again.";
                    break;
                }
            }
            break;
        }
        case 3: // Exit from the main menu
            e1 = true;
            break;
        default:
            cout << "Invalid input. Please try again.";
            break;
        }
    }

    reader.close();
    reader2.close();
    reader3.close();
    br.close();
    br1.close();
    br2.close();
    br3.close();

    return 0;
}
