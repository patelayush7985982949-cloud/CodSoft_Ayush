#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string description;
    bool completed;
};

void showMenu() {
    cout << "\n===== TO-DO LIST MENU =====\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Delete Task\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

void addTask(vector<Task>& tasks) {
    cin.ignore(); // clear buffer
    Task newTask;
    cout << "Enter task description: ";
    getline(cin, newTask.description);
    newTask.completed = false;
    tasks.push_back(newTask);
    cout << "Task added successfully!\n";
}

void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available!\n";
        return;
    }
    cout << "\n===== YOUR TASKS =====\n";
    for (size_t i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". " << tasks[i].description;
        if (tasks[i].completed)
            cout << " ✅";
        cout << endl;
    }
}

void markTaskCompleted(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks to mark!\n";
        return;
    }
    int taskNo;
    cout << "Enter task number to mark completed: ";
    cin >> taskNo;

    if (taskNo < 1 || taskNo > (int)tasks.size()) {
        cout << "Invalid task number!\n";
    } else {
        tasks[taskNo - 1].completed = true;
        cout << "Task marked as completed!\n";
    }
}

void deleteTask(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks to delete!\n";
        return;
    }
    int taskNo;
    cout << "Enter task number to delete: ";
    cin >> taskNo;

    if (taskNo < 1 || taskNo > (int)tasks.size()) {
        cout << "Invalid task number!\n";
    } else {
        tasks.erase(tasks.begin() + (taskNo - 1));
        cout << "Task deleted successfully!\n";
    }
}

int main() {
    vector<Task> tasks;
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: addTask(tasks); break;
            case 2: viewTasks(tasks); break;
            case 3: markTaskCompleted(tasks); break;
            case 4: deleteTask(tasks); break;
            case 5: cout << "Exiting... Goodbye!\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
