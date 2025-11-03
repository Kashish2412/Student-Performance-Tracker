# Student-Performance-Tracker
A simple C++ project for tracking student performance
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <windows.h>
using namespace std;

// ----- COLOR FUNCTION -----
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ----- DESIGN LINE -----
void line(char ch, int n = 60) {
    for (int i = 0; i < n; i++) cout << ch;
    cout << endl;
}

// ----- CLASS DEFINITION -----
class Student {
    int rollNo;
    string name;
    float marks[3];
    float total, average;
    char grade;
    string performance;

public:
    void input();
    void calculate();
    void display();
    int getRollNo() { return rollNo; }
    float getAverage() { return average; }
    string getName() { return name; }
};

// ----- INPUT -----
void Student::input() {
    system("cls");
    setColor(11);
    line('=');
    cout << "?? ENTER STUDENT DETAILS" << endl;
    line('=');
    setColor(14);

    cout << "Enter Roll No: ";
    cin >> rollNo;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Marks in 3 Subjects: ";
    for (int i = 0; i < 3; i++)
        cin >> marks[i];

    calculate();
}

// ----- CALCULATION -----
void Student::calculate() {
    total = marks[0] + marks[1] + marks[2];
    average = total / 3.0;

    if (average >= 90) grade = 'A';
    else if (average >= 75) grade = 'B';
    else if (average >= 60) grade = 'C';
    else if (average >= 50) grade = 'D';
    else grade = 'F';

    if (grade == 'A') performance = "Excellent ??";
    else if (grade == 'B') performance = "Very Good ??";
    else if (grade == 'C') performance = "Good ??";
    else if (grade == 'D') performance = "Average ??";
    else performance = "Needs Improvement ??";
}

// ----- DISPLAY FUNCTION -----
void Student::display() {
    setColor(10);
    cout << left << setw(8) << rollNo
         << setw(20) << name
         << setw(10) << fixed << setprecision(2) << average
         << setw(8) << grade
         << setw(20) << performance << endl;
    setColor(7);
}

// ----- FILE OPERATIONS -----
void addStudent() {
    ofstream fout("students.dat", ios::binary | ios::app);
    Student s;
    s.input();
    fout.write((char*)&s, sizeof(s));
    fout.close();
    setColor(10);
    cout << "\n? Student Added Successfully!\n";
    setColor(7);
    system("pause");
}

void viewAll() {
    ifstream fin("students.dat", ios::binary);
    if (!fin) {
        setColor(12);
        cout << "\n? No Data Found!\n";
        setColor(7);
        system("pause");
        return;
    }

    Student s;
    system("cls");
    setColor(11);
    line('=');
    cout << "?? ALL STUDENT RECORDS" << endl;
    line('=');
    setColor(14);

    cout << left << setw(8) << "RollNo"
         << setw(20) << "Name"
         << setw(10) << "Average"
         << setw(8) << "Grade"
         << setw(20) << "Performance" << endl;
    line('-');

    while (fin.read((char*)&s, sizeof(s)))
        s.display();

    fin.close();
    system("pause");
}

void searchStudent() {
    int roll;
    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;

    ifstream fin("students.dat", ios::binary);
    Student s;
    bool found = false;

    while (fin.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == roll) {
            setColor(10);
            cout << "\n? Student Found:\n";
            line('-');
            setColor(14);
            cout << left << setw(8) << "RollNo"
                 << setw(20) << "Name"
                 << setw(10) << "Average"
                 << setw(8) << "Grade"
                 << setw(20) << "Performance" << endl;
            line('-');
            s.display();
            found = true;
        }
    }

    if (!found) {
        setColor(12);
        cout << "\n? Student Not Found!\n";
    }

    setColor(7);
    fin.close();
    system("pause");
}

void topPerformer() {
    ifstream fin("students.dat", ios::binary);
    if (!fin) {
        setColor(12);
        cout << "\n? No Records Found!\n";
        setColor(7);
        system("pause");
        return;
    }

    Student s, top;
    bool first = true;

    while (fin.read((char*)&s, sizeof(s))) {
        if (first || s.getAverage() > top.getAverage()) {
            top = s;
            first = false;
        }
    }

    fin.close();
    system("cls");
    setColor(11);
    line('=');
    cout << "?? TOP PERFORMER ??" << endl;
    line('=');
    setColor(14);
    cout << left << setw(8) << "RollNo"
         << setw(20) << "Name"
         << setw(10) << "Average"
         << setw(8) << "Grade"
         << setw(20) << "Performance" << endl;
    line('-');
    top.display();
    setColor(7);
    system("pause");
}

// ----- MAIN FUNCTION -----
int main() {
    int choice;
    do {
        system("cls");
        setColor(3);
        line('=');
        cout << "?? STUDENT PERFORMANCE ANALYZER ??" << endl;
        line('=');
        setColor(11);
        cout << "1??  Add New Student\n";
        cout << "2??  View All Students\n";
        cout << "3??  Search Student by Roll No\n";
        cout << "4??  Top Performer\n";
        cout << "5??  Exit\n";
        line('-');
        setColor(14);
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewAll(); break;
            case 3: searchStudent(); break;
            case 4: topPerformer(); break;
            case 5:
                setColor(10);
                cout << "\n?? Exiting... Thank you!\n";
                setColor(7);
                break;
            default:
                setColor(12);
                cout << "\n?? Invalid Choice! Try Again.\n";
                setColor(7);
                system("pause");
        }
    } while (choice != 5);

    return 0;
}
