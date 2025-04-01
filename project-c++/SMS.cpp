#include <iostream>
#include <unordered_map>
#include <fstream>
#include <iomanip>
using namespace std;

class Student {
private:
    int id;
    string name;
    int age;

public:
    Student() {}
    Student(int id, const string& name, int age) : id(id), name(name), age(age) {}

    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }

    void setName(const string& newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }

    void display() const {
        cout << left << setw(10) << id << setw(20) << name << setw(5) << age << endl;
    }
};

class StudentManagement {
private:
    unordered_map<int, Student> students;
    const string filename = "students.txt";

public:
    StudentManagement() { loadFromFile(); }
    ~StudentManagement() { saveToFile(); }

    void addStudent(int id, const string& name, int age) {
        if (students.find(id) != students.end()) {
            cout << "Student with ID " << id << " already exists!\n";
            return;
        }
        students[id] = Student(id, name, age);
        cout << "Student added successfully!\n";
    }

    void displayStudents() const {
        if (students.empty()) {
            cout << "No students available!\n";
            return;
        }
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(5) << "Age" << endl;
        cout << string(35, '-') << endl;
        for (const auto& pair : students) {
            pair.second.display();
        }
    }

    void searchStudent(int id) const {
        auto it = students.find(id);
        if (it != students.end()) {
            cout << "Student found:\n";
            it->second.display();
        } else {
            cout << "Student not found!\n";
        }
    }

    void updateStudent(int id, const string& newName, int newAge) {
        auto it = students.find(id);
        if (it != students.end()) {
            it->second.setName(newName);
            it->second.setAge(newAge);
            cout << "Student details updated!\n";
        } else {
            cout << "Student not found!\n";
        }
    }

    void deleteStudent(int id) {
        if (students.erase(id)) {
            cout << "Student deleted successfully!\n";
        } else {
            cout << "Student not found!\n";
        }
    }

    void saveToFile() {
        ofstream file(filename);
        for (const auto& pair : students) {
            file << pair.first << " " << pair.second.getName() << " " << pair.second.getAge() << endl;
        }
    }

    void loadFromFile() {
        ifstream file(filename);
        int id, age;
        string name;
        while (file >> id) {
            file.ignore();
            getline(file, name, ' ');
            file >> age;
            students[id] = Student(id, name, age);
        }
    }
};

void showMenu() {
    cout << "\nSTUDENT MANAGEMENT SYSTEM\n";
    cout << "1. Add Student\n";
    cout << "2. Display Students\n";
    cout << "3. Search Student\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    StudentManagement sm;
    int choice, id, age;
    string name;

    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;
                if (age < 0) {
                    cout << "Invalid Age! Must be non-negative.\n";
                    break;
                }
                sm.addStudent(id, name, age);
                break;
            case 2:
                sm.displayStudents();
                break;
            case 3:
                cout << "Enter Student ID to search: ";
                cin >> id;
                sm.searchStudent(id);
                break;
            case 4:
                cout << "Enter Student ID to update: ";
                cin >> id;
                cin.ignore();
                cout << "Enter New Name: ";
                getline(cin, name);
                cout << "Enter New Age: ";
                cin >> age;
                if (age < 0) {
                    cout << "Invalid Age! Must be non-negative.\n";
                    break;
                }
                sm.updateStudent(id, name, age);
                break;
            case 5:
                cout << "Enter Student ID to delete: ";
                cin >> id;
                sm.deleteStudent(id);
                break;
            case 6:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);
    return 0;
}
