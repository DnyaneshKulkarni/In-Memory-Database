#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm> 

using namespace std;

struct Student {
    string misNumber;
    string name;
    string mobileNumber;
    string email;
    int yearOfAdmission;
};

class PGDatabase {
private:
    map<string, vector<Student>> courseData;

public:
    void addData() {
        string course;
        cout << "Choose a course:\n";
        cout << "1) ECS\n";
        cout << "2) PEMD\n";
        cout << "3) PEPS\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                course = "ECS";
                break;
            case 2:
                course = "PEMD";
                break;
            case 3:
                course = "PEPS";
                break;
            default:
                cout << "Invalid choice!\n";
                return;
        }

        do {
            Student newStudent;
            cout << "Enter MIS Number: ";
            cin >> newStudent.misNumber;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, newStudent.name);
            cout << "Enter Mobile Number: ";
            cin >> newStudent.mobileNumber;
            cout << "Enter Email: ";
            cin >> newStudent.email;
            cout << "Enter Year of Admission: ";
            cin >> newStudent.yearOfAdmission;

            courseData[course].push_back(newStudent);

            cout << "Do you want to add more data? (yes/no): ";
            string choice;
            cin >> choice;
            if (choice != "yes")
                break;
        } while (true);
    }

    void readData() {
        cout << "Enter MIS Number: ";
        string misNumber;
        cin >> misNumber;
        bool found = false;
        for (auto& course : courseData) {
            for (auto& student : course.second) {
                if (student.misNumber == misNumber) {
                    found = true;
                    cout << "Course: " << course.first << endl;
                    cout << "Name: " << student.name << endl;
                    cout << "Mobile Number: " << student.mobileNumber << endl;
                    cout << "Email: " << student.email << endl;
                    cout << "Year of Admission: " << student.yearOfAdmission << endl;
                    break;
                }
            }
        }
        if (!found)
            cout << "Student not found!\n";
    }

    void reportData() {
        cout << "Report Data:\n";
        int studentCount = 1;
        for (const auto& course : courseData) {
            for (const auto& student : course.second) {
                cout << "Student " << studentCount++ << ":" << endl;
                cout << "Course: " << course.first << endl;
                cout << "MIS Number: " << student.misNumber << endl;
                cout << "Name: " << student.name << endl;
                cout << "Mobile Number: " << student.mobileNumber << endl;
                cout << "Email: " << student.email << endl;
                cout << "Year of Admission: " << student.yearOfAdmission << endl;
                cout << endl; // Add a space between student records
            }
        }
    }

    void editData() {
        cout << "Enter MIS Number to edit: ";
        string misNumber;
        cin >> misNumber;
        bool found = false;
        for (auto& course : courseData) {
            for (auto& student : course.second) {
                if (student.misNumber == misNumber) {
                    found = true;
                    cout << "Enter new Name: ";
                    cin.ignore();
                    getline(cin, student.name);
                    cout << "Enter new Mobile Number: ";
                    cin >> student.mobileNumber;
                    cout << "Enter new Email: ";
                    cin >> student.email;
                    cout << "Enter new Year of Admission: ";
                    cin >> student.yearOfAdmission;
                    cout << "Data updated successfully!\n";
                    break;
                }
            }
        }
        if (!found)
            cout << "Student not found!\n";
    }

    void deleteData() {
        cout << "Enter MIS Number to delete: ";
        string misNumber;
        cin >> misNumber;
        for (auto& course : courseData) {
            auto& students = course.second;
            students.erase(remove_if(students.begin(), students.end(),
                [&misNumber](const Student& student) { return student.misNumber == misNumber; }),
                students.end());
        }
        cout << "Data deleted successfully!\n";
    }

    bool authenticateAdmin() {
        string password;
        cout << "Enter password: ";
        cin >> password;
        return password == "project";
    }
};

int main() {
    PGDatabase database;
    cout << "COEP Technological University\n";
    cout << "Electrical Engineering Department\n";
    cout << "PG Database\n";

    while (true) {
        cout << "Are you an admin or a user? (admin/user): ";
        string userType;
        cin >> userType;
        if (userType == "admin") {
            if (!database.authenticateAdmin()) {
                cout << "Incorrect password. Please try again.\n";
                continue;
            }
            cout << "Admin Menu:\n";
            cout << "1) Add Data\n";
            cout << "2) Read Data\n";
            cout << "3) Report Data\n";
            cout << "4) Edit Data\n";
            cout << "5) Delete Data\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;
            switch (choice) {
                case 1:
                    database.addData();
                    break;
                case 2:
                    database.readData();
                    break;
                case 3:
                    database.reportData();
                    break;
                case 4:
                    database.editData();
                    break;
                case 5:
                    database.deleteData();
                    break;
                default:
                    cout << "Invalid choice!\n";
            }
        } else if (userType == "user") {
            cout << "User Menu:\n";
            cout << "1) Add Data\n";
            cout << "2) Read Data\n";
            cout << "3) Report Data\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;
            switch (choice) {
                case 1:
                    database.addData();
                    break;
                case 2:
                    database.readData();
                    break;
                case 3:
                    database.reportData();
                    break;
                default:
                    cout << "Invalid choice!\n";
            }
        } else {
            cout << "Invalid user type!\n";
        }
    }

    return 0;
}
