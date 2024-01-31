#include <iostream>
#include <string>
using namespace std;
class LinkedList
{
private:
    struct Node
    {
        string text;
        Node* left, * right, * top, * bottom;
        explicit Node(string txt) : text(move(txt))
        {
            left = right = nullptr;
            top = bottom = nullptr;
        }
        bool equals(const string& otherText) const
        {
            return (text == otherText);
        }
    };
    Node* lineHead;
public:
    bool isEmpty()
    {
        return (lineHead == nullptr);
    }
    bool hasOneNode()
    {
        return lineHead->right == nullptr && lineHead->bottom == nullptr;
    }
    LinkedList() 
    {
        lineHead = nullptr;
    }
    void addText(int x, int y, const string& text) 
    {
        Node* newNode = new Node(text);
        if (isEmpty())
        {
            lineHead = newNode;
        }
        else 
        {
            if (x < 1)
            {
                newNode->bottom = lineHead;
                lineHead->top = newNode;
                lineHead = newNode;
            }
            else 
            {
                Node* tempHead = lineHead;
                Node* previousLine = nullptr;
                int line = 1;
                while (line < x && tempHead != nullptr) 
                {
                    previousLine = tempHead;
                    line++;
                    tempHead = tempHead->bottom;
                }
                if (tempHead == nullptr) 
                {
                    tempHead = newNode;
                    tempHead->top = previousLine;
                    previousLine->bottom = tempHead;
                }
                else 
                {
                    if (y < 1) 
                    {
                        newNode->right = tempHead;
                        tempHead->left = newNode;
                    }
                    else 
                    {
                        Node* temp = tempHead;
                        int words = 0;
                        do
                        {
                            words++;
                            if (temp->right != nullptr)
                            {
                                temp = temp->right;
                            }
                        } 
                        while (words < y && temp->right != nullptr);
                        if (temp->right == nullptr)
                        {
                            temp->right = newNode;
                            newNode->left = temp;
                        }
                        else 
                        {
                            newNode->right = temp->right;
                            temp->right->left = newNode;
                            newNode->left = temp;
                            temp->right = newNode;
                        }
                    }
                }
            }
        }
    }
    void searchText(const string& text) 
    {
        if (!isEmpty()) 
        {
            Node* temp_head = lineHead;
            int line = 1;
            do
            {
                Node* temp = temp_head;
                int textCount = 0;
                while (temp != nullptr)
                {
                    textCount++;
                    if (temp->equals(text)) 
                    {
                        cout << "(" << line << ", " << textCount << "), " << endl;
                    }
                    temp = temp->right;
                }
                temp_head = temp_head->bottom;
            }
            while (temp_head != nullptr);
        }
    }
    void deleteText(const string& text) 
    {
        if (!isEmpty()) 
        {
            if (hasOneNode())
            {
                if (lineHead->equals(text)) 
                {
                    Node* temp = lineHead;
                    lineHead = nullptr;

                    delete temp;
                }
            }
            else 
            {
                Node* temp_head = lineHead;
                do 
                {
                    Node* temp = temp_head;
                    while (temp != nullptr) 
                    {
                        if (temp->equals(text)) 
                        {
                            if (temp->left == nullptr)
                                temp->right->left = temp->left;
                            else if (temp->right == nullptr)
                                temp->left->right = temp->right;
                            else 
                            {
                                temp->left->right = temp->right;
                                temp->right->left = temp->left;
                            }
                            if (temp->right != nullptr) 
                            {
                                temp->top->bottom = temp->right;
                                temp->bottom->top = temp->right;
                            }
                        }
                        temp = temp->right;
                    }
                    temp_head = temp_head->bottom;
                } while (temp_head != nullptr);
            }
        }
    }
    string copyText(int x, int y, int xPrime, int yPrime)
    {
        string variable;
        if (!isEmpty()) 
        {
            int line = 1, wordCount = 0;
            Node* tempHead = lineHead;
            bool seleted = false;
            while (tempHead != nullptr)
            {
                line++;
                Node* temp = tempHead;
                while (temp != nullptr)
                {
                    wordCount++;
                    if (wordCount >= y) 
                    {
                        seleted = true;
                    }
                }
            }
        }
        return " ";
    }
    void pasteText(LinkedList* text)
    {
        if (!text->isEmpty()) 
        {
            Node* textHead = text->getHead();
            do 
            {
                Node* temp_head = textHead;
                while (temp_head != nullptr)
                {
                    addText(Right, temp_head->text);
                    temp_head = temp_head->right;
                }
                textHead = textHead->bottom;
            } while (textHead->bottom != nullptr);
        }
    }
    bool wordExists(const string& text) 
    {
        if (!isEmpty()) 
        {
            Node* tempHead = lineHead;
            while (tempHead != nullptr) 
            {
                Node* temp = tempHead;
                while (temp != nullptr) 
                {
                    if (temp->equals(text))
                        return true;
                    temp = temp->right;
                }
                tempHead = tempHead->bottom;
            }
        }
        return false;
    }

    void replaceWord(const string& oldWord) 
    {
        if (wordExists(oldWord)) 
        {
            string updatedText;
            cout << "Enter the new word: ";
            cin >> updatedText;
            int command;
            cout << "[1] Replace first appearing word\n\
                    [2] Replace all words\n" << endl;
            cin >> command;
            bool replaceOnce;
            switch (command) 
            {
            case 1:
                replaceOnce = true;
                break;
            case 2:
                replaceOnce = false;
                break;
            default:
                cout << "\t<!---Operation failed, invalid selection--->\n" << endl;
                return;
            }
            Node* tempHead = lineHead;
            bool replaced = false;
            do {
                Node* temp = tempHead;
                while (temp != nullptr)
                {
                    if (temp->equals(oldWord)) 
                    {
                        temp->text = updatedText;
                        if (replaceOnce) 
                        {
                            replaced = true;
                            break;
                        }
                        temp = temp->right;
                    }
                }
                tempHead = tempHead->bottom;
            } while (tempHead != nullptr && !replaced);
        }
        else
            cout << "\t<!---Word does not exist--->\n" << endl;
    }
    int count() 
    {
        int wordCount = 0;
        if (!isEmpty()) 
        {
            Node* temp_head = lineHead;
            do 
            {
                Node* temp = temp_head;
                while (temp != nullptr) 
                {
                    wordCount++;
                    temp = temp->right;
                }
                temp_head = temp_head->bottom;
            } while (temp_head != nullptr);
        }
        return wordCount;
    }
    void print() 
    {
        if (!isEmpty()) 
        {
            Node* temp_head = lineHead;
            do 
            {
                Node* temp = temp_head;
                while (temp != nullptr)
                {
                    cout << temp->text << " ";
                    temp = temp->right;
                }
                cout << endl;
                temp_head = temp_head->bottom;
            } while (temp_head != nullptr);
        }
        else 
        {
            cout << "\t<!--Notepad is Empty--->\n" << endl;
        }
    }
};
int mainMenu() 
{
    int command;
    cout << "\t [1] Help\n \
        [2] Add text\n \
        [3] Search Words\n \
        [4] Delete words\n \
        [5] Cppy Text\n \
        [6] Paste Text\n \
        [7] Find and Replace\n \
        [8] Count Words\n \
        [0] Exit notepad" << endl;
    cin >> command;
    return command;
}
string getText() 
{
    string text;
    cin.ignore();
    cout << "Enter text: ";
    getline(cin, text);
    return text;
}
void help() 
{
    cout << "-> if you are adding text for the first time: \n\
        - enter postion as by line number and word count \n\
        - x position is the line number, starts form 1\n \
        - y positon is the word count, starts from 1\n \
        - combine these to add location in the notepad, as follow\n \
            [positionX, text, positionY]  -> 1, 2, 'this is my text' \n " << std::endl;
}
int main(int argc, char** argv) 
{
    bool running = true;
    auto* notepad = new LinkedList();
    do 
    {
        string word, text, updatedText;
        int command = mainMenu();
        int posX, posY;
        switch (command)
        {
        case 1:
            help();
            break;
        case 2:
            /* Adding text in the notepad */
            cout << "Enter x position [line number]: ";
            cin >> posX;
            cout << "Enter y position [word index]: ";
            cin >> posY;
            word = getText();
            notepad->addText(posX, posY, word);
            break;
        case 3:
            /* searching text in the notepad */
            cout << "Enter the text to get it's location [line number, word number]: ";
            cin.ignore();
            getline(cin, text);
            notepad->searchText(text);
            break;
        case 4:
            /* Deleting text in the notepad */
            cout << "Enter the word to delete: ";
            cin.ignore();
            getline(cin, word);
            notepad->deleteText(word);
            break;
        case 5:
            /* Copying text in the notepad */
             copied = notepad->copyText();
            break;
        case 6:
            /* Pasting a copied text in the notepad */
            if (copied != nullptr)
            {

            }
            else
                cout << "\t<!---Operation failed! nothing to paste--->\n" << endl;
            break;
        case 7:
            cout << "Enter the word to replace: ";
            cin.ignore();
            getline(cin, word);
            notepad->replaceWord(word);
            break;
        case 8:
            cout << "Total Words: " << notepad->count() << endl;
            break;
        case 0:
            running = false;
            break;
        default:
            cout << "\n<!---Invalid Selection--->\n" << endl;
            break;
        }
        cout << "----------------------------------Notepad--------------------------------" << endl;
        notepad->print();
    } while (running);
    return 0;
}
