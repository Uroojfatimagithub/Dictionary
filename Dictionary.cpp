//So, the reason for defining both private and public functions is to encapsulate
// the internal workings of the binary search tree within the Dictionary class. External code interacts 
//with the public functions (insertWord and searchWord), while the internal implementation is hidden and 
//managed by the private functions (insert and search).
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class TreeNode {
public:
    string key;  //word
    string value;  //definition
    TreeNode* left;
    TreeNode* right;

    TreeNode(string k, string v) : key(k), value(v), left(NULL), right(NULL) {}  //parameterized constructor
};

class Dictionary {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, const string& key, const string& value);  //root hogi subtree ki jhan py specific node insert honi hy
    TreeNode* search(TreeNode* node, const string& key);  //subtree ki wo root hogi jhan py searching ho rhi hogi
    TreeNode* findMin(TreeNode* node);
    TreeNode* remove(TreeNode* node, const string& key);
    void inOrderTraversal(TreeNode* node);

public:
    Dictionary() : root(NULL) {}

    void insertWord(const string& key, const string& value);
    string searchWord(const string& key);
    void removeWord(const string& key);
    void displayAllWords();
    ~Dictionary();
};

TreeNode* Dictionary::insert(TreeNode* node, const string& key, const string& value) {
    if (node == NULL) {   //matlab if tree empty hua to new node simple daal dengy
        return new TreeNode(key, value);
    }

    if (key < node->key) { //jo value daalna chahty agar wo less hui root node sy to left py jana
        node->left = insert(node->left, key, value);
    } else if (key > node->key) {
        node->right = insert(node->right, key, value);
    } else {
        node->value = value;    //left na hui right na gae to matlab jo root node hy subtree ki value us k equal hy
    }

    return node;  //return kar deni valur after insertion root node ki 
}

void Dictionary::insertWord(const string& key, const string& value) {
    root = insert(root, key, value);
}

TreeNode* Dictionary::search(TreeNode* node, const string& key) {
    if (node == NULL || node->key == key) {
        return node;  //return the rrot node agar pehli hi value match kar gae ya root null hua to
    }

    if (key < node->key) {
        return search(node->left, key);
    } else {
        return search(node->right, key);
    }
}

string Dictionary::searchWord(const string& key) {
    TreeNode* result = search(root, key);
    if (result != NULL) {
        return result->value;
    } else {
        return "Word not found in the dictionary.";
    }
}

TreeNode* Dictionary::findMin(TreeNode* node) {
    while (node->left != NULL) {   //minimum node find karni jab tak last wala left tree nhi aa jata tab tak left py jaaty rhen jab pohonch jaen or null ho jay to value return kar den
        node = node->left;//minimum find kar rhi because deletion men kaam ata jab 2 childs hon 
    }          //right subtree ki sab sy choti value delete karni
    return node;
}

TreeNode* Dictionary::remove(TreeNode* node, const string& key) {
    if (node == NULL) {
        return NULL;   //agar empty hui to kuch delete nhi hoga return null kar den
    }

    if (key < node->key) {
        node->left = remove(node->left, key);
    } else if (key > node->key) {
        node->right = remove(node->right, key);
    } else {
	if (node->left == NULL) {  //for one child deletion
            TreeNode* temp = node->right;//left child na hua to right sy replace kar dengy ek pointer rakh ena right py or phir
            delete node;//node delete karny k baad wo pointer connect kar dena
            return temp;
        } else if (node->right == NULL) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }

        TreeNode* temp = findMin(node->right);//pointer rakhna right subtree k minimum node py
        node->key = temp->key;  //jo minimum value thi wo replace kar deni hy us value sy jo delete karni
        node->value = temp->value;//same for definition
        node->right = remove(node->right, temp->key);//phir jana or us minimum value ko node k right sy dlete kar dena
    }
    return node;
}

void Dictionary::removeWord(const string& key) {
    root = remove(root, key);
}

void Dictionary::inOrderTraversal(TreeNode* node) {
    if (node != NULL) {
        inOrderTraversal(node->left);
        cout << node->key << ": " << node->value << endl;
        inOrderTraversal(node->right);
    }
}

void Dictionary::displayAllWords() {
    inOrderTraversal(root);
}

Dictionary::~Dictionary() {
    // Implement destructor to free allocated memory
}

int main() {
    Dictionary dictionary;

    // Inserting words and their definitions
    dictionary.insertWord("art", "the expression or application of human creative skill");
    dictionary.insertWord("business", "the practice of making one's living by engaging in commerce");
    dictionary.insertWord("culture", "the arts and other manifestations of human intellectual achievement");
    dictionary.insertWord("education", "the process of receiving or giving systematic instruction");
    dictionary.insertWord("family", "a group of individuals living under one roof");
    dictionary.insertWord("health", "the state of being free from illness or injury");
    dictionary.insertWord("innovation", "the introduction of something new");
    dictionary.insertWord("justice", "the quality of being fair and reasonable");
    dictionary.insertWord("knowledge", "facts, information, and skills acquired through experience or education");
    dictionary.insertWord("leadership", "the action of leading a group of people");
    dictionary.insertWord("music", "vocal or instrumental sounds combined in such a way as to produce beauty");
    dictionary.insertWord("nature", "the physical world and everything in it");
    dictionary.insertWord("opportunity", "a set of circumstances that makes it possible to do something");
    dictionary.insertWord("politics", "the activities associated with the governance of a country");
    dictionary.insertWord("quality", "the standard of something as measured against other things");
    dictionary.insertWord("respect", "a feeling of deep admiration for someone or something");
    dictionary.insertWord("science", "the intellectual and practical activity encompassing the systematic study");
    dictionary.insertWord("technology", "the application of scientific knowledge for practical purposes");
    dictionary.insertWord("unity", "the state of being united or joined as a whole");
    dictionary.insertWord("value", "the regard that something is held to deserve; the importance");
    dictionary.insertWord("wisdom", "the quality of having experience, knowledge, and good judgment");
    dictionary.insertWord("xylography", "the art of engraving on wood, especially in Chinese, Japanese, or Korean");
    dictionary.insertWord("yearn", "have an intense feeling of longing for something");
    dictionary.insertWord("zealous", "having or showing zeal; full of enthusiasm");

    int choice;
    do {
        cout << "\nDictionary Menu:\n";
        cout << "1. Search for a word\n";
        cout << "2. Add a new word\n";
        cout << "3. Remove a word\n";
        cout << "4. Display all words and definitions\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                // User searches for a word
                string userWord;
                cout << "Enter a word: ";
                cin >> userWord;
                cout << "Definition of '" << userWord << "': " << dictionary.searchWord(userWord) << endl;
            } break;
            case 2: {
                // User adds a new word
                string newWord, definition;
                cout << "Enter a new word: ";
                cin >> newWord;
                cout << "Enter the definition: ";
                cin.ignore(); // Clear buffer
                getline(cin, definition);
                dictionary.insertWord(newWord, definition);
                cout << "Word added successfully!\n";
            } break;
            case 3: {
                // User removes a word
                string wordToRemove;
                cout << "Enter the word to remove: ";
                cin >> wordToRemove;
                dictionary.removeWord(wordToRemove);
                cout << "Word removed successfully!\n";
            } break;
            case 4:
                // Display all words and definitions
                cout << "\nAll Words and Definitions:\n";
                dictionary.displayAllWords();
                break;
            case 5:
                cout << "Exiting the dictionary. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}

