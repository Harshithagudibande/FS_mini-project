#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>

using namespace std;

struct Member {
    string name;
    string email;
    string role;
};

vector<Member> members;
fstream file;

void addMember();
void deleteMember();
void searchMember();
void viewMembers();
void editMember();
void closeApplication();

int main() {
    int choice;
    file.open("club_members.txt", ios::out | ios::app);
    file.close();

    while (true) {
        cout << "IT Club Management System" << endl;
        cout << "1. Add Member" << endl;
        cout << "2. Delete Member" << endl;
        cout << "3. Search Member" << endl;
        cout << "4. View Members" << endl;
        cout << "5. Edit Member" << endl;
        cout << "6. Close Application" << endl;
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1:
                addMember();
                break;
            case 2:
                deleteMember();
                break;
            case 3:
                searchMember();
                break;
            case 4:
                viewMembers();
                break;
            case 5:
                editMember();
                break;
            case 6:
                closeApplication();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }

    return 0;
}

void addMember() {
    Member newMember;
    cout << "Enter member name: ";
    getline(cin >> ws, newMember.name);
    cout << "Enter member email: ";
    getline(cin, newMember.email);
    cout << "Enter member role: ";
    getline(cin, newMember.role);

    file.open("club_members.txt", ios::out | ios::app);
    if (!file) {
        cout << "Error";
        return;
    }
    string record = newMember.name + "|" + newMember.email + "|" + newMember.role;
    file << record << endl;
    file.close();

    cout << "Member added successfully." << endl;
}

void deleteMember() {
    string searchName;
    cout << "Enter the name of the member to delete: ";
    getline(cin >> ws, searchName);

    ifstream inFile("club_members.txt");
    ofstream outFile("temp.txt");
    if (!inFile || !outFile) {
        cout << "Error";
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        size_t pos = line.find('|');
        string name = line.substr(0, pos);
        if (name == searchName) {
            found = true;
            continue;
        }
        outFile << line << endl;
    }

    inFile.close();
    outFile.close();

    if (found) {
        remove("club_members.txt");
        rename("temp.txt", "club_members.txt");
        cout << "Member deleted successfully." << endl;
    } else {
        remove("temp.txt");
        cout << "Member not found." << endl;
    }
}

void searchMember() {
    string searchName;
    cout << "Enter the name of the member to search: ";
    getline(cin >> ws, searchName);

    ifstream file("club_members.txt");
    if (!file) {
        cout << "Error";
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        size_t pos = line.find('|');
        string name = line.substr(0, pos);
        if (name == searchName) {
            found = true;
            cout << "Member found:" << endl;
            cout << line << endl;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "Member not found." << endl;
    }
}

void viewMembers() {
    ifstream file("club_members.txt");
    if (!file) {
        cout << "Error";
        return;
    }

    string line;
    cout << "Members:" << endl;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void editMember() {
    string searchName;
    cout << "Enter the name of the member to edit: ";
    getline(cin >> ws, searchName);

    ifstream inFile("club_members.txt");
    ofstream outFile("temp.txt");
    if (!inFile || !outFile) {
        cout << "Error";
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        size_t pos = line.find('|');
        string name = line.substr(0, pos);
        if (name == searchName) {
            found = true;

            Member updatedMember;
            cout << "Enter updated member name: ";
            getline(cin >> ws, updatedMember.name);
            cout << "Enter updated member email: ";
            getline(cin, updatedMember.email);
            cout << "Enter updated member role: ";
            getline(cin, updatedMember.role);

            string record = updatedMember.name + "|" + updatedMember.email + "|" + updatedMember.role;
            outFile << record << endl;
        } else {
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();

    if (found) {
        remove("club_members.txt");
        rename("temp.txt", "club_members.txt");
        cout << "Member updated successfully." << endl;
    } else {
        remove("temp.txt");
        cout << "Member not found." << endl;
    }
}

void closeApplication() {
    cout << "Closing application..." << endl;
    exit(0);
}
