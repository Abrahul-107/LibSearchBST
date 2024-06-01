import java.io.*;
import java.text.SimpleDateFormat;
import java.util.*;

class Student {
    String name;
    int id_no;
    String Stream;
    String book1, book2;
    int book_no, issuedbook;

    Student(String name, int id_no, String Stream) {
        this.name = name;
        this.id_no = id_no;
        this.Stream = Stream;
    }
}

class Node {
    String key;
    Node left, right;

    public Node(String item) {
        key = item;
        left = right = null;
    }
}

class BinaryTree {
    Node root;

    void insert(String key) {
        root = insertRec(root, key);
    }

    Node insertRec(Node root, String key) {
        if (root == null) {
            root = new Node(key);
            return root;
        }

        if (key.compareTo(root.key) < 0)
            root.left = insertRec(root.left, key);
        else if (key.compareTo(root.key) > 0)
            root.right = insertRec(root.right, key);
        else
            System.out.println("Error: Duplicate entry");

        return root;
    }

    boolean containsNode(String key) {
        return containsNodeRec(root, key);
    }

    boolean containsNodeRec(Node current, String key) {
        if (current == null)
            return false;
        if (key.equalsIgnoreCase(current.key))
            return true;
        return key.compareTo(current.key) < 0
                ? containsNodeRec(current.left, key)
                : containsNodeRec(current.right, key);
    }

    void delete(String key) {
        root = deleteRec(root, key);
    }

    Node deleteRec(Node root, String key) {
        if (root == null)
            return root;

        if (key.compareTo(root.key) < 0)
            root.left = deleteRec(root.left, key);
        else if (key.compareTo(root.key) > 0)
            root.right = deleteRec(root.right, key);
        else {
            if (root.left == null)
                return root.right;
            if (root.right == null)
                return root.left;
            root.key = minValue(root.right);
            root.right = deleteRec(root.right, root.key);
        }

        return root;
    }

    String minValue(Node root) {
        String minv = root.key;
        while (root.left != null) {
            minv = root.left.key;
            root = root.left;
        }
        return minv;
    }

    void printInorder() {
        printInorderRec(root);
    }

    void printInorderRec(Node node) {
        if (node != null) {
            printInorderRec(node.left);
            System.out.print(node.key + " ");
            printInorderRec(node.right);
        }
    }

    void printTree() {
        printTreeRec(root, 0);
    }

    void printTreeRec(Node root, int space) {
        if (root == null)
            return;
        space += 5;
        printTreeRec(root.right, space);
        System.out.println();
        for (int i = 5; i < space; i++)
            System.out.print(" ");
        System.out.print("[" + root.key + "]");
        printTreeRec(root.left, space);
    }
}

public class LibraryManagement {
    private static Scanner input = new Scanner(System.in);
    private static final String LIBRARIAN_ID = "abd360";
    private static final String LIBRARIAN_PASSWORD = "abd17";
    private static SimpleDateFormat formatter = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
    private static Calendar cal = Calendar.getInstance();
    private static Student[] students = {
            new Student("Rahul", 1741078, "MCA-GIETU"),
            new Student("Saikiran", 1741086, "B.Tech-Centurion"),
            new Student("Vivek", 1741052, "MCA-KIIT")
    };
    private static BinaryTree tree = new BinaryTree();
    private static HashMap<String, Integer> bookMapping = new HashMap<>();
    private static int[][] bookQuantities = new int[100][2];

    public static void main(String[] args) throws IOException {
        try (BufferedReader reader = new BufferedReader(new FileReader("x.txt"));
                BufferedReader reader2 = new BufferedReader(new FileReader("y.txt"));
                BufferedReader reader3 = new BufferedReader(new FileReader("z.txt"));
                BufferedWriter br = new BufferedWriter(new FileWriter("append.txt", true))) {

            String line;
            int i = 0;
            while ((line = reader.readLine()) != null) {
                tree.insert(line);
                bookMapping.put(line, i);
                i++;
            }

            loadBookQuantities(reader2, reader3, i);

            boolean exit = false;
            while (!exit) {
                System.out.println("\n1. Librarian Login\n2. User Login\n3. Exit");
                int choice = input.nextInt();
                switch (choice) {
                    case 1:
                        librarianLogin();
                        break;
                    case 2:
                        userLogin(br);
                        break;
                    case 3:
                        exit = true;
                        break;
                }
            }
        }
    }

    private static void loadBookQuantities(BufferedReader reader2, BufferedReader reader3, int i) throws IOException {
        String number;
        int j = 0;
        while ((number = reader2.readLine()) != null) {
            int result = Integer.parseInt(number);
            if (j < i)
                bookQuantities[j][0] = result;
            j++;
        }

        int k = 0;
        while ((number = reader3.readLine()) != null) {
            int result = Integer.parseInt(number);
            if (k < j)
                bookQuantities[k][1] = result;
            k++;
        }
    }

    private static void librarianLogin() {
        System.out.println("\nEnter UserId:");
        String id = input.next();
        System.out.println("\nEnter Password:");
        String password = input.next();

        if (!LIBRARIAN_ID.equals(id) || !LIBRARIAN_PASSWORD.equals(password)) {
            System.out.println("Invalid UserId or Password.");
            return;
        }

        System.out.println("Login successful.");
        boolean exit = false;
        while (!exit) {
            System.out.println(
                    "\n1. Add book\n2. Delete book\n3. Update book\n4. Print Books Details\n5. Print Books in-order\n6. Print tree\n7. Exit");
            int choice = input.nextInt();
            switch (choice) {
                case 1:
                    addBook();
                    break;
                case 2:
                    deleteBook();
                    break;
                case 3:
                    updateBook();
                    break;
                case 4:
                    printBooksDetails();
                    break;
                case 5:
                    tree.printInorder();
                    break;
                case 6:
                    tree.printTree();
                    break;
                case 7:
                    exit = true;
                    break;
            }
        }
    }
    private static void addBook() {
        System.out.println("\nEnter name of book:");
        String name = input.next();
        if (tree.containsNode(name)) {
            System.out.println("Book already exists.");
            return;
        }

        System.out.println("Enter quantity of book:");
        int quantity = input.nextInt();

        tree.insert(name);
        int index = bookMapping.size();
        bookMapping.put(name, index);
        bookQuantities[index][0] += quantity;
        bookQuantities[index][1] += quantity;

        System.out.println("Book added successfully.");
    }

    private static void deleteBook() {
        System.out.println("Enter name of book:");
        String name = input.next();
        if (!tree.containsNode(name)) {
            System.out.println("Book not found.");
            return;
        }

        tree.delete(name);
        bookMapping.remove(name);
        System.out.println("Book deleted successfully.");
    }

    private static void updateBook() {
        System.out.println("Enter name of book:");
        String name = input.next();
        if (!tree.containsNode(name)) {
            System.out.println("Book not found.");
            return;
        }

        int index = bookMapping.get(name);
        System.out.println("Enter quantity of book to add:");
        int quantity = input.nextInt();
        bookQuantities[index][0] += quantity;

        System.out.println("Book updated successfully.");
    }

    private static void printBooksDetails() {
        for (Map.Entry<String, Integer> entry : bookMapping.entrySet()) {
            int index = entry.getValue();
            System.out.println("Name: " + entry.getKey());
            System.out.println("Total Quantity: " + bookQuantities[index][0]);
            System.out.println("Available Quantity: " + bookQuantities[index][1]);
        }
    }

    private static void userLogin(BufferedWriter br) throws IOException {
        boolean exit = false;
        while (!exit) {
            System.out.println("\n1. Issue book\n2. Return book\n3. Exit");
            int choice = input.nextInt();
            switch (choice) {
                case 1:
                    issueBook(br);
                    break;
                case 2:
                    returnBook();
                    break;
                case 3:
                    exit = true;
                    break;
            }
        }
    }

    private static void issueBook(BufferedWriter br) throws IOException {
        System.out.println("Enter your id:");
        int id = input.nextInt();

        Student student = getStudentById(id);
        if (student == null) {
            System.out.println("Student not found.");
            return;
        }

        System.out.println("Enter name of book:");
        String book = input.next();
        if (!tree.containsNode(book)) {
            System.out.println("Book not found.");
            return;
        }

        int index = bookMapping.get(book);
        if (bookQuantities[index][1] <= 0) {
            System.out.println("Book out of stock.");
            return;
        }

        if (student.issuedbook >= 2) {
            System.out.println("You have already issued 2 books.");
            return;
        }

        if (student.book1 == null) {
            student.book1 = book;
        } else if (student.book2 == null) {
            student.book2 = book;
        }

        bookQuantities[index][1]--;
        student.issuedbook++;
        br.write("Name: " + student.name + " Book: " + book + " Time: " + formatter.format(cal.getTime()));
        br.newLine();
        System.out.println("Book issued successfully.");
    }

    private static void returnBook() {
        System.out.println("Enter your id:");
        int id = input.nextInt();

        Student student = getStudentById(id);
        if (student == null) {
            System.out.println("Student not found.");
            return;
        }

        System.out.println("Enter name of book:");
        String book = input.next();

        if (student.book1 == null && student.book2 == null) {
            System.out.println("No books issued to you.");
            return;
        }

        int index = bookMapping.get(book);
        if (student.book1 != null && student.book1.equalsIgnoreCase(book)) {
            student.book1 = null;
            bookQuantities[index][1]++;
            student.issuedbook--;
        } else if (student.book2 != null && student.book2.equalsIgnoreCase(book)) {
            student.book2 = null;
            bookQuantities[index][1]++;
            student.issuedbook--;
        } else {
            System.out.println("You have not issued this book.");
            return;
        }

        System.out.println("Book returned successfully.");
    }

    private static Student getStudentById(int id) {
        for (Student student : students) {
            if (student.id_no == id) {
                return student;
            }
        }
        return null;
    }
}
