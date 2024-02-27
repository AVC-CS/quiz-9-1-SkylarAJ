#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

const int NUMCOURSE = 2;
struct Student
{
    int id;
    string name;
    int score[NUMCOURSE];
    double sum;
    double avg;
    struct Student *next;
};
#define struct Student Student;
// typedef struct Student Student;

Student *makeStudent(int N);
void printStudent(Student *head);
int getLength(Student *head);
Student *sortStudent(Student *head, int asc);

Student *makeStudent(int N)
{
      ifstream file("students.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return nullptr;
    }

    Student *head = nullptr;
    Student *tail = nullptr;
    string line;
    for (int i = 0; i < N && getline(file, line); ++i) {
        Student *newStudent = new Student;
        if (!newStudent) {
            cerr << "Memory allocation failed." << endl;
            break;
        }
        istringstream iss(line);
        iss >> newStudent->id >> newStudent->name >> newStudent->score[0] >> newStudent->score[1];
        newStudent->sum = newStudent->score[0] + newStudent->score[1];
        newStudent->avg = newStudent->sum / NUMCOURSE;
        newStudent->next = nullptr;

        if (!head) {
            head = newStudent;
            tail = newStudent;
        } else {
            tail->next = newStudent;
            tail = newStudent;
        }
    }

    file.close();
    return head;
}

void printStudent(Student *head)
{
    Student *ptr = head;
    while (ptr != NULL)
    {
        cout << ptr->id << "\t";
        cout << ptr->name << "\t";
        cout << ptr->score[0] << "\t";
        cout << ptr->score[1] << "\t";
        cout << ptr->sum << "\t";
        cout << ptr->avg << "\n";
        ptr = ptr->next;
    }
    cout << endl;
}

int getLength(Student *head)
{
    int length = 0;

    while (head != nullptr)
    {
        length++;
        head = head->next;
    }

    return length;
}

Student *sortStudent(Student *head, int asc)
{
    if (!head || !head->next)
        return head;

    Student *current = head;
    Student *sorted = nullptr;

    while (current != nullptr) {
        Student *nextNode = current->next;
        if (asc) {
            if (sorted == nullptr || sorted->sum >= current->sum) {
                current->next = sorted;
                sorted = current;
            } else {
                Student *temp = sorted;
                while (temp->next != nullptr && temp->next->sum < current->sum) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
        } else {
            if (sorted == nullptr || sorted->sum <= current->sum) {
                current->next = sorted;
                sorted = current;
            } else {
                Student *temp = sorted;
                while (temp->next != nullptr && temp->next->sum > current->sum) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
        }
        current = nextNode;
    }

    return sorted;
}

