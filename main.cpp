#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

/* =========================
   STUDENT CLASS
========================= */
class Student {
private:
    string indexNumber;
    string name;

public:
    Student(string idx = "", string nm = "") {
        indexNumber = idx;
        name = nm;
    }

    string getIndexNumber() const { return indexNumber; }
    string getName() const { return name; }

    void display() const {
        cout << "Index: " << indexNumber << " | Name: " << name << endl;
    }
};

/* =========================
   GLOBAL STUDENT LIST
========================= */
vector<Student> students;

/* =========================
   FILE FUNCTIONS
========================= */
void saveStudents() {
    ofstream file("students.txt");
    for (const Student &s : students) {
        file << s.getIndexNumber() << "," << s.getName() << endl;
    }
    file.close();
}

void loadStudents() {
    ifstream file("students.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string index, name;

        getline(ss, index, ',');
        getline(ss, name);

        students.push_back(Student(index, name));
    }
    file.close();
}

/* =========================
   STUDENT MANAGEMENT
========================= */
void registerStudent() {
    string index, name;

    cout << "Enter Index Number: ";
    cin >> index;
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, name);

    students.push_back(Student(index, name));
    saveStudents();

    cout << "Student Registered Successfully!\n";
}

void viewStudents() {
    if (students.empty()) {
        cout << "No students registered.\n";
        return;
    }

    for (const Student &s : students) {
        s.display();
    }
}

void searchStudent() {
    string index;
    cout << "Enter Index Number to search: ";
    cin >> index;

    for (const Student &s : students) {
        if (s.getIndexNumber() == index) {
            s.display();
            return;
        }
    }

    cout << "Student not found.\n";
}

/* =========================
   ATTENDANCE SESSION
========================= */
void createSession() {
    if (students.empty()) {
        cout << "No students registered.\n";
        return;
    }

    string courseCode, date, startTime;
    int duration;

    cout << "Enter Course Code: ";
    cin >> courseCode;

    cout << "Enter Date (YYYY_MM_DD): ";
    cin >> date;

    cout << "Enter Start Time: ";
    cin >> startTime;

    cout << "Enter Duration (minutes): ";
    cin >> duration;

    string filename = "session_" + courseCode + "_" + date + ".txt";
    ofstream sessionFile(filename);

    int present = 0, absent = 0, late = 0;

    for (const Student &s : students) {
        string status;
        cout << "Attendance for " << s.getName()
             << " (Present/Absent/Late): ";
        cin >> status;

        transform(status.begin(), status.end(), status.begin(), ::tolower);

        if (status == "present") present++;
        else if (status == "absent") absent++;
        else if (status == "late") late++;
        else {
            cout << "Invalid input. Marked Absent.\n";
            status = "absent";
            absent++;
        }

        sessionFile << s.getIndexNumber() << ","
                    << s.getName() << ","
                    << status << endl;
    }

    sessionFile.close();

    cout << "\nSession Saved Successfully!\n";
    cout << "Summary:\n";
    cout << "Present: " << present << endl;
    cout << "Absent : " << absent << endl;
    cout << "Late   : " << late << endl;
}

/* =========================
   MAIN MENU
========================= */
int main() {
    loadStudents();

    int choice;

    do {
        cout << "\n===== DIGITAL ATTENDANCE SYSTEM =====\n";
        cout << "1. Register Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Create Attendance Session\n";
        cout << "5. Exit\n";
        cout << "Select Option: ";
        cin >> choice;

        switch (choice) {
            case 1: registerStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: createSession(); break;
            case 5: cout << "Exiting Program...\n"; break;
            default: cout << "Invalid Option!\n";
        }

    } while (choice != 5);

    return 0;
}
