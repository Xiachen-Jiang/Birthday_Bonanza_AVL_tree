/*
 * COMP8801 Assignment 1 - Birthday  Bonanza
 * AVL tree
 * Xiachen Jiang - jian0352
 * 31 - 5 - 2022
 */

#include <iostream>
#include <vector>

using namespace std;

typedef vector<string> nameSet;

struct person
{
    nameSet name;
    double birthday;
    int count;
    person *leftPocket;
    person *rightPocket;
    int height;
};

class AVLTree
{
public:
    person *person1;

public:
    AVLTree();
    void insert(person* &temp, double birthday,string name);
    void search(person* &temp,double birthday);
    person* leftRotate(person* temp);
    person* rightRotate(person* temp);
    int get_height(person* temp);
    int get_diff(person* temp);
    int max(int a, int b);
};

//initialization
AVLTree::AVLTree()
{
    person1 = new person;
    person1->height = 0;
    person1->count = 0;
    person1->birthday = 0;
    person1->leftPocket = nullptr;
    person1->rightPocket = nullptr;
    person1->name.clear();
}

// Compare the height of a person's left and right pockets
// return the larger value as the person's height
int AVLTree::max(int a, int b)
{
    if(a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int AVLTree::get_height(person *temp)
{
    if(temp == nullptr)
    {
        return 0;
    }
    else
    {
        return temp->height;
    }
}

//for the rotating
int AVLTree::get_diff(person *temp)
{
    if(temp == nullptr)
    {
        return 0;
    }
    else
    {
        int left = get_height(temp->leftPocket);
        int right = get_height(temp->rightPocket);
        int diff = left - right;

        return diff;
    }
}

person *AVLTree::leftRotate(person *temp)
{
    person* right = temp->rightPocket;
    person* SUB_LEFT = right->leftPocket;

    right->leftPocket = temp;
    temp->rightPocket = SUB_LEFT;

    temp->height = max(get_height(temp->leftPocket), get_height(temp->rightPocket)) + 1;
    right->height = max(get_height(right->leftPocket), get_height(right->rightPocket)) + 1;

    return right;
}

person *AVLTree::rightRotate(person *temp)
{
    person* left = temp->leftPocket;
    person* SUB_RIGHT = left->rightPocket;

    left->rightPocket = temp;
    temp->leftPocket = SUB_RIGHT;

    temp->height = max(get_height(temp->leftPocket), get_height(temp->rightPocket)) + 1;
    left->height = max(get_height(left->leftPocket), get_height(left->rightPocket)) + 1;

    return left;
}

//creat the tree
//1. if the tree is empty, create the first person's identity information, two pockets are empty
//2. if this insert person's birthday is later than the current one, using recursion method to search the current one's right pocket
//3. if the insert person's birthday is earlier than the current one, using the same method to search the current one's left pocket
//4. if the insert person's birthday is same with the current one, insert the name to the node and count + 1
void AVLTree::insert(person *&temp, double birthday, string name)
{
    if(temp == nullptr)
    {
        temp = new person;
        temp->birthday = birthday;
        temp->count = 1;
        temp->name.push_back(name);
        temp->height = 1;
        temp->leftPocket = nullptr;
        temp->rightPocket = nullptr;
    }
    else if(temp->birthday == birthday)
    {
        temp->count += 1;
        temp->name.push_back(name);
    }
    else if(temp->birthday > birthday)
    {
        insert(temp->leftPocket, birthday, name);

        temp->height = max(get_height(temp->leftPocket), get_height(temp->rightPocket)) + 1;

        if(get_diff(temp) > 1)
        {
            if(temp->leftPocket->birthday > birthday)
            {
                temp = rightRotate(temp);
            }
            else
            {
                temp->leftPocket = leftRotate(temp->leftPocket);
                temp = rightRotate(temp);
            }
        }
    }
    else if(temp->birthday < birthday)
    {
        insert(temp->rightPocket, birthday, name);

        temp->height = max(get_height(temp->leftPocket), get_height(temp->rightPocket)) + 1;

        if(get_diff(temp) < -1)
        {
            if(temp->rightPocket->birthday < birthday)
            {
                temp = leftRotate(temp);
            }
            else
            {
                temp->rightPocket = rightRotate(temp->rightPocket);
                temp = leftRotate(temp);
            }
        }
    }
}

void AVLTree::search(person *&temp, double birthday)
{
    if(temp == nullptr)
    {
        cout << "So sorry! No one's birthday is today!" << endl;
    }
    else if(temp->birthday > birthday)
    {
        search(temp->leftPocket, birthday);
    }
    else if(temp->birthday < birthday)
    {
        search(temp->rightPocket, birthday);
    }
    else if(temp->birthday == birthday)
    {
        if(temp->count == 1)
        {
            cout << "Today is one person's birthday!" << endl;
            cout << "The person is: " << endl;

            vector<string>::iterator it;
            for(auto it = temp->name.begin(); it != temp->name.end(); it++)
            {
                cout << *it << endl;
            }
        }
        else
        {
            cout << "There are " << temp->count << " people on their birthday!" << endl;
            cout << "They are: " << endl;
            vector<string>::iterator it;
            for(auto it = temp->name.begin(); it != temp->name.end(); it++)
            {
                cout << *it << endl;
            }
        }
    }
}

void menu()
{
    cout << "*************************" << endl;
    cout << "***     1. insert     ***" << endl;
    cout << "***     2. search     ***" << endl;
    cout << "***     0. exit       ***" << endl;
    cout << "*************************" << endl;
    cout << "Please select your choice." << endl;
}

void insertChoice(AVLTree *person)
{
    string name;
    cout << "Please input the first name:" << endl;
    string firstName;
    cin >> firstName;

    cout << "Please input the last name:" << endl;
    string lastName;
    cin >> lastName;

    name = firstName + " " + lastName;

    double birthday = 0;
    cout << "Please input the month: (1 - 12): ";
    int month = 0;
    while(true)
    {
        cin >> month;
        if(month >= 1 && month <= 12)
        {
            break;
        }
        cout << "Error! " << endl;
        cout << "Please input the month: (1 - 12): ";
    }

    cout << "Please input the day: (1 - 31): " << endl;
    int day;
    while (true)
    {
        cin >> day;
        if(month == 2)
        {
            if(day >= 1 && day <= 29)
            {
                break;
            }
            else
            {
                cout << "Error!" << endl;
                cout << "Please input the day: (1 - 31): " << endl;
            }
        }
        else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        {
            if(day >= 1 && day <= 31)
            {
                break;
            }
            else
            {
                cout << "Error!" << endl;
                cout << "Please input the day: (1 - 31): " << endl;
            }
        }
        else if(month == 4 || month == 6 || month == 9 || month == 11)
        {
            if(day >= 1 && day <= 30)
            {
                break;
            }
            else
            {
                cout << "Error!" << endl;
                cout << "Please input the day: (1 - 31): " << endl;
            }
        }
        else
        {
            cout << "Error!" << endl;
            cout << "Please input the day: (1 - 31): " << endl;
        }
    }

    birthday = month * 100 + day;

    person->insert(person->person1,birthday,name);

    cout << "Insert successfully!" << endl;

}

void searchChoice(AVLTree *person)
{
    double birthday;
    cout << "Please input the month: (1 - 12): " ;
    int month;
    cin >> month;

    cout << "Please input the day: (1 - 31): " << endl;
    int day;
    cin >> day;

    birthday = month * 100 + day;

    person->search(person->person1,birthday);
}

int main()
{

    AVLTree* newPerson = new AVLTree;
    int choice = 0;

    while(true)
    {
        menu();

        cin >> choice;

        switch (choice)
        {
            case 1: // insert
                insertChoice(newPerson);
            break;
            case 2:
                searchChoice(newPerson);
                break;
            case 0:
                cout << "Thanks for using!" << endl;
                return 0;
            default:
                cout << "Error!" << endl;
                cout << "Please select your choice." << endl;
                break;
        }
    }
}