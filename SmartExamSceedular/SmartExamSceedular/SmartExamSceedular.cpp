#include <iostream>
#include <fstream>
#include "queue.h"
#include <vector>
#include <string>
#include "BinarySearch.h"
#include "Stack.h"
#include "mergeSort.h"

using namespace std;

class AdminMenu {
protected:
    vector<pair<vector<int>, vector<string>>> examInformation;
    Stack st;
    vector<pair<int, Stack>> regStuToExam;

    // Load exams from file
    void loadExams() {
        ifstream file("exams.txt");
        if (file.is_open()) {
            int id, room;
            string subject, date, time;

            while (file >> id >> room >> subject >> date >> time) {
                pair<vector<int>, vector<string>> examInfo;
                examInfo.first = { id, room };
                examInfo.second = { subject, date, time };
                examInformation.push_back(examInfo);
            }
            file.close();
            cout << "Exams loaded successfully!" << endl;
        }
        else {
            cout << "No saved exams found." << endl;
        }
    }

    // Save exams to file
    void saveExams() {
        ofstream file("exams.txt");
        if (file.is_open()) {
            for (const auto& exam : examInformation) {
                file << exam.first[0] << " " << exam.first[1] << " ";
                file << exam.second[0] << " " << exam.second[1] << " " << exam.second[2] << endl;
            }
            file.close();
            cout << "Exams saved successfully!" << endl;
        }
        else {
            cout << "Unable to open file for saving exams." << endl;
        }
    }

    // Load student registrations
    void loadStudentRegistrations() {
        ifstream file("registrations.txt");
        if (file.is_open()) {
            int examID, studentID;
            while (file >> examID >> studentID) {
                bool found = false;
                for (auto& reg : regStuToExam) {
                    if (reg.first == examID) {
                        reg.second.push(studentID);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    Stack s;
                    s.push(studentID);
                    regStuToExam.push_back({ examID, s });
                }
            }
            file.close();
            cout << "Student registrations loaded successfully!" << endl;
        }
        else {
            cout << "No saved student registrations found." << endl;
        }
    }

    // Save student registrations
    void saveStudentRegistrations() {
        ofstream file("registrations.txt");
        if (file.is_open()) {
            for (const auto& reg : regStuToExam) {
                Stack tempStack = reg.second;
                while (!tempStack.isEmpty()) {
                    file << reg.first << " " << tempStack.peek() << endl;
                    tempStack.pop();
                }
            }
            file.close();
            cout << "Student registrations saved successfully!" << endl;
        }
        else {
            cout << "Unable to open file for saving registrations." << endl;
        }
    }

public:
    AdminMenu() {
        loadExams();
        loadStudentRegistrations();
    }

    ~AdminMenu() {
        saveExams();
        saveStudentRegistrations();
    }

    void AddExam() {
        int id, room;
        string subject, date, time;

        cout << "Enter Exam ID: ";
        cin >> id;
        cout << "Enter Subject: ";
        cin >> subject;
        cout << "Enter Date: ";
        cin >> date;
        cout << "Enter Time: ";
        cin >> time;
        cout << "Enter Room: ";
        cin >> room;

        pair<vector<int>, vector<string>> examInfo;
        examInfo.first = { id, room };
        examInfo.second = { subject, date, time };
        examInformation.push_back(examInfo);

        cout << "Exam Added Successfully" << endl;
        saveExams(); // Save after adding an exam
    }

    void viewEnrolledStudents() {
        if (regStuToExam.empty()) {
            cout << "No students enrolled in any exam." << endl;
            return;
        }

        cout << "**************************" << endl;
        cout << "*  Enrolled Students     *" << endl;
        cout << "**************************" << endl;
        for (const auto& reg : regStuToExam) {
            cout << "**************************" << endl;
            cout << "Exam ID: " << reg.first << endl;

            Stack tempStack = reg.second;
            if (tempStack.isEmpty()) {
                cout << "No students enrolled for this exam." << endl;
            }
            else {
                cout << "Enrolled Students:" << endl;
                while (!tempStack.isEmpty()) {
                    cout << "Student ID: " << tempStack.peek() << endl;
                    tempStack.pop();
                }
            }
        }
        cout << endl;
    }


    void deleteExam() {
        if (examInformation.empty()) {
            cout << "No exams available to delete." << endl;
            return;
        }

        int id;
        cout << "Enter Exam ID to delete: ";
        cin >> id;

        // Find and delete the exam
        for (size_t i = 0; i < examInformation.size(); i++) {
            if (examInformation[i].first[0] == id) {
                examInformation.erase(examInformation.begin() + i);
                cout << "Exam Deleted Successfully" << endl;
                saveExams();

                // Now, remove registrations for this exam
                for (size_t j = 0; j < regStuToExam.size(); j++) {
                    if (regStuToExam[j].first == id) {
                        regStuToExam.erase(regStuToExam.begin() + j);
                        cout << "All registrations for Exam ID " << id << " have been deleted." << endl;
                        break;  // Exit after deleting registrations
                    }
                }

                return;
            }
        }
        cout << "Exam ID not found" << endl;
    }

    void displayExam() {
        if (examInformation.empty()) {
            cout << "No exams available to display." << endl;
            return;
        }

        cout << "**************************" << endl;
        cout << "*     Upcoming Exams     *" << endl;
        cout << "**************************" << endl;
        for (const auto& exam : examInformation) {
            cout << "**************************" << endl;
            cout << "Exam ID: " << exam.first[0] << endl;
            cout << "Room Available: " << exam.first[1] << endl;
            cout << "Subject: " << exam.second[0] << endl;
            cout << "Date: " << exam.second[1] << endl;
            cout << "Time: " << exam.second[2] << endl;
        }
        cout << endl;
    }
};

class MainMenu : public AdminMenu {
protected:
    int choice;
    bool iterUser;
    bool iterAdmin;
    string secKey;
    Queue q;
public:
    MainMenu() : q(5) { // Initialize Queue with capacity 5
        choice = 0;
        iterUser = false;
        iterAdmin = false;
        secKey = "admin123"; // Example secret key
    }

    int registerStudent() {
        pair<int, string> studentInfo;

        cout << "**************************" << endl;
        cout << "*   Student Registration *" << endl;
        cout << "**************************" << endl;
        cout << "Enter your student ID: ";
        cin >> studentInfo.first;
        cout << "Enter your student Name: ";
        cin >> studentInfo.second;

        q.enQueue(studentInfo.first, studentInfo.second);
        cout << studentInfo.second << " You have been registered Successfully" << endl;

        // Save student information to file
        ofstream outFile("students.txt", ios::app);
        if (outFile.is_open()) {
            outFile << studentInfo.first << " " << studentInfo.second << endl;
            outFile.close();
        }
        else {
            cout << "Error saving student data." << endl;
        }

        return studentInfo.first;
    }

    string adminCheck() {
        string secretKey;
        cout << "**************************" << endl;
        cout << "* Enter Secret Admin Key *" << endl;
        cout << "**************************" << endl;
        cin >> secretKey;
        return secretKey;
    }

    void displayMenuAdmin() {
        string key = adminCheck();  // Admin key check
        if (key != secKey) {
            cout << "Invalid Key" << endl;
            return;
        }

        while (true) {  // Loop until user decides to exit
            cout << "**************************" << endl;
            cout << "*      Admin Menu        *" << endl;
            cout << "**************************" << endl;
            cout << "* 1. Add Exam            *" << endl;
            cout << "* 2. Delete Exam         *" << endl;
            cout << "* 3 View Students for Exam *" << endl;
            cout << "* 4 Display Exam        *" << endl;
            cout << "* 5 Back to main menu   *" << endl;
            cout << "* 6. Exit                *" << endl;
            cout << "**************************" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 6) {
                cout << "Exiting Admin Menu..." << endl;
                break;  // Exit the loop
            }
            else if (choice == 5) {
                return; // Go back to role selection
            }
            else if (choice == 4) {
                displayExam();
            }
            else if (choice == 3) {
                viewEnrolledStudents();
            }
            else if (choice == 2) {
                deleteExam();
            }
            else if (choice == 1) {
                AddExam();
            }
            else {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
};


class StudentMenu : public MainMenu {
private:
    Stack s;
public:
    void displayMenuUser() {
        int studentID;
        string studentName;

        // Check if the student is already registered
        cout << "Enter your student ID: ";
        cin >> studentID;

        // Check the students.txt file for existing student ID
        ifstream inFile("students.txt");
        bool registered = false;
        if (inFile.is_open()) {
            int existingID;
            string existingName;
            while (inFile >> existingID >> existingName) {
                if (existingID == studentID) {
                    registered = true;
                    studentName = existingName;
                    break;
                }
            }
            inFile.close();
        }

        // If the student is not registered, prompt for registration
        if (!registered) {
            cout << "You are not registered. Please register first." << endl;
            registerStudent();
        }
        else {
            cout << "Welcome back, " << studentName << "!" << endl;
        }

        iterUser = true; // Set this so the user doesn’t get prompted again

        while (true) {  // Loop until user decides to exit
            cout << "**************************" << endl;
            cout << "*      Student Menu      *" << endl;
            cout << "**************************" << endl;
            cout << "* 1. Register for an Exam *" << endl;
            cout << "* 2. Sort Exams          *" << endl;
            cout << "* 3. Search for Exam     *" << endl;
            cout << "* 4. Back to main menu   *" << endl;
            cout << "* 5. Exit                *" << endl;
            cout << "**************************" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 5) {
                cout << "Exiting Student Menu..." << endl;
                break;  // Exit the loop
            }
            else if (choice == 4) {
                return; // Go back to role selection
            }
            else if (choice == 3) {
                searchExam();
            }
            else if (choice == 2) {
                sortExam();
            }
            else if (choice == 1) {
                registerInExam();
            }
            else {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }


    void searchExam() {
        displayExam();

        int examID;
        cout << "Enter Exam ID to search: ";
        cin >> examID;

        vector<int> examIDs;
        for (size_t i = 0; i < examInformation.size(); i++) {
            examIDs.push_back(examInformation[i].first[0]);
        }

        int index = binarySearch(examIDs, static_cast<int>(examInformation.size()), examID);
        if (index != -1) {
            cout << "**************************" << endl;
            cout << "Exam ID: " << examInformation[index].first[0] << endl;
            cout << "Room Available: " << examInformation[index].first[1] << endl;
            cout << "Subject: " << examInformation[index].second[0] << endl;
            cout << "Date: " << examInformation[index].second[1] << endl;
            cout << "Time: " << examInformation[index].second[2] << endl;
        }
        else {
            cout << "Exam ID not found" << endl;
        }
    }

    void sortExam() {
        if (examInformation.empty()) {
            cout << "No exams available to sort." << endl;
            return;
        }

        // Sort the examInformation vector using mergeSort
        mergeSort(examInformation, 0, static_cast<int>(examInformation.size()) - 1);

        cout << "Exams sorted by date successfully." << endl;
        displayExam(); // Display the sorted exams
    }

    void registerInExam() {
        displayExam();

        int examID;
        cout << "Enter Exam ID to register: ";
        cin >> examID;

        vector<int> examIDs;
        for (const auto& exam : examInformation) {
            examIDs.push_back(exam.first[0]);
        }

        int index = binarySearch(examIDs, static_cast<int>(examInformation.size()), examID);
        if (index != -1) {
            if (examInformation[index].first[1] <= 0) {
                cout << "No more slots available for this exam." << endl;
                return;
            }

            int studentID = registerStudent(); // Register student

            // Check if the student is already registered for this exam
            bool alreadyRegistered = false;
            for (auto& reg : regStuToExam) {
                if (reg.first == examID) {
                    // Check if the student ID is in the stack
                    Stack tempStack = reg.second;
                    while (!tempStack.isEmpty()) {
                        if (tempStack.peek() == studentID) {
                            alreadyRegistered = true;
                            break;
                        }
                        tempStack.pop();
                    }

                    if (!alreadyRegistered) {
                        reg.second.push(studentID); // Add student to existing exam
                        examInformation[index].first[1] -= 1; // Reduce room capacity
                    }
                    break; // Exit loop after processing
                }
            }

            // If not registered, create a new entry
            if (!alreadyRegistered) {
                Stack s;
                s.push(studentID);
                regStuToExam.push_back({ examID, s });
                examInformation[index].first[1] -= 1; // Reduce room capacity
            }

            // Save registration info to file immediately after registration
            ofstream outFile("exam_registrations.txt", ios::app);
            if (outFile.is_open()) {
                outFile << examID << " " << studentID << endl;
                outFile.close();
                cout << "Registered Successfully." << endl;
            }
            else {
                cout << "Error saving registration data." << endl;
            }
        }
        else {
            cout << "Exam ID not found" << endl;
        }
    }



};

int main() {
    MainMenu mainMenu;
    int roleChoice;

    while (true) {
        cout << "**************************" << endl;
        cout << "*   Smart Exam Scheduler *" << endl;
        cout << "**************************" << endl;
        cout << "* 1. Admin               *" << endl;
        cout << "* 2. Student             *" << endl;
        cout << "* 3. Exit                *" << endl;
        cout << "**************************" << endl;
        cout << "Enter your role (1-3): ";
        cin >> roleChoice;

        if (roleChoice == 3) {
            cout << "Exiting program..." << endl;
            break;  // Exit the program
        }

        switch (roleChoice) {
        case 1: {
            mainMenu.displayMenuAdmin();  // Admin menu
            break;
        }
        case 2: {
            StudentMenu studentMenu;
            studentMenu.displayMenuUser();  // Student menu
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}
