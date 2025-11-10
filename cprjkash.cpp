#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
using namespace std;

// ----- COLOR FUNCTION -----
void setColor(int color) {
    switch (color) {
        case 10: cout << "\033[32m"; break; // green
        case 11: cout << "\033[36m"; break; // cyan
        case 12: cout << "\033[31m"; break; // red
        case 14: cout << "\033[33m"; break; // yellow
        case 3:  cout << "\033[35m"; break; // magenta
        case 7:  cout << "\033[0m";  break; // reset
        default: cout << "\033[0m";  break;
    }
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
    void display() const;
    int getRollNo() const { return rollNo; }
    float getAverage() const { return average; }
    string getName() const { return name; }
};

// ----- INPUT -----
void Student::input() {
    setColor(11);
    line('=');
    cout << ">> ENTER STUDENT DETAILS" << endl;
    line('=');
    setColor(14);

    cout << "Enter Roll No: ";
    cin >> rollNo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Marks in 3 Subjects (separated by spaces): ";
    for (int i = 0; i < 3; i++)
        cin >> marks[i];

    calculate();
}

// ----- CALCULATION -----
void Student::calculate() {
    total = marks[0] + marks[1] + marks[2];
    average = total / 3.0f;

    if (average >= 90.0f) grade = 'A';
    else if (average >= 75.0f) grade = 'B';
    else if (average >= 60.0f) grade = 'C';
    else if (average >= 50.0f) grade = 'D';
    else grade = 'F';

    if (grade == 'A') performance = "Excellent";
    else if (grade == 'B') performance = "Very Good";
    else if (grade == 'C') performance = "Good";
    else if (grade == 'D') performance = "Average";
    else performance = "Needs Improvement";
}

// ----- DISPLAY FUNCTION -----
void Student::display() const {
    setColor(10);
    cout << left << setw(8) << rollNo
         << setw(20) << name
         << setw(10) << fixed << setprecision(2) << average
         << setw(8) << grade
         << setw(20) << performance << endl;
    setColor(7);
}

// ----- GLOBAL VECTOR TO STORE STUDENTS -----
vector<Student> students;

// ----- ADD STUDENT -----
void addStudent() {
    Student s;
    s.input();
    students.push_back(s);

    setColor(10);
    cout << "\n✔ Student Added Successfully!\n";
    setColor(7);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Press Enter to continue...";
    cin.get();
}

// ----- VIEW ALL STUDENTS -----
void viewAll() {
    if (students.empty()) {
        setColor(12);
        cout << "\n⚠ No Data Found!\n";
        setColor(7);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    setColor(11);
    line('=');
    cout << "📘 ALL STUDENT RECORDS" << endl;
    line('=');
    setColor(14);

    cout << left << setw(8) << "RollNo"
         << setw(20) << "Name"
         << setw(10) << "Average"
         << setw(8) << "Grade"
         << setw(20) << "Performance" << endl;
    line('-');

    for (const auto& s : students)
        s.display();

    setColor(7);
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// ----- SEARCH STUDENT -----
void searchStudent() {
    int roll;
    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;

    bool found = false;
    for (const auto& s : students) {
        if (s.getRollNo() == roll) {
            setColor(10);
            cout << "\n✔ Student Found:\n";
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
            break;
        }
    }

    if (!found) {
        setColor(12);
        cout << "\n⚠ Student Not Found!\n";
    }

    setColor(7);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Press Enter to continue...";
    cin.get();
}

// ----- TOP PERFORMER -----
void topPerformer() {
    if (students.empty()) {
        setColor(12);
        cout << "\n⚠ No Records Found!\n";
        setColor(7);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    const Student* top = &students[0];
    for (const auto& s : students) {
        if (s.getAverage() > top->getAverage())
            top = &s;
    }

    setColor(11);
    line('=');
    cout << "🏆 TOP PERFORMER" << endl;
    line('=');
    setColor(14);
    cout << left << setw(8) << "RollNo"
         << setw(20) << "Name"
         << setw(10) << "Average"
         << setw(8) << "Grade"
         << setw(20) << "Performance" << endl;
    line('-');
    top->display();

    setColor(7);
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// ----- MAIN FUNCTION -----
int main() {
    int choice;
    do {
        setColor(3);
        line('=');
        cout << "🎓 STUDENT PERFORMANCE ANALYZER 🎓" << endl;
        line('=');
        setColor(11);
        cout << "1️⃣  Add New Student\n";
        cout << "2️⃣  View All Students\n";
        cout << "3️⃣  Search Student by Roll No\n";
        cout << "4️⃣  Top Performer\n";
        cout << "5️⃣  Exit\n";
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
                cout << "\n✅ Exiting... Thank you!\n";
                setColor(7);
                break;
            default:
                setColor(12);
                cout << "\n⚠ Invalid Choice! Try Again.\n";
                setColor(7);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Press Enter to continue...";
                cin.get();
        }
    } while (choice != 5);

    return 0;
}
