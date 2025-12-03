#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <memory>

class Student {
private:
    int id;
    std::string name;
    int age;
    double gpa;
    
public:
    // Constructor
    Student(int id = 0, std::string name = "", int age = 0, double gpa = 0.0)
        : id(id), name(std::move(name)), age(age), gpa(gpa) {}
    
    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    int getAge() const { return age; }
    double getGPA() const { return gpa; }
    
    // Setters
    void setName(const std::string& newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }
    void setGPA(double newGPA) { gpa = newGPA; }
    
    // Display student info
    void display() const {
        std::cout << std::setw(6) << id 
                  << std::setw(20) << name 
                  << std::setw(6) << age 
                  << std::setw(8) << std::fixed << std::setprecision(2) << gpa << "\n";
    }
};

class StudentManager {
private:
    std::vector<Student> students;
    int nextId;
    
    // Memory tracking
    size_t memoryUsed() const {
        // Approximate memory calculation
        size_t studentSize = sizeof(Student);
        size_t vectorCapacity = students.capacity() * studentSize;
        
        // Add string memory (approximate)
        size_t stringMemory = 0;
        for (const auto& student : students) {
            stringMemory += student.getName().capacity();
        }
        
        return vectorCapacity + stringMemory;
    }
    
public:
    StudentManager() : nextId(1) {
        students.reserve(10);  // Pre-allocate memory for 10 students
        std::cout << "Initial memory allocated for 10 students\n";
    }
    
    // Add a new student
    void addStudent(const std::string& name, int age, double gpa) {
        Student newStudent(nextId++, name, age, gpa);
        students.push_back(newStudent);
        
        std::cout << "Student added successfully! (ID: " << newStudent.getId() << ")\n";
        displayMemoryUsage();
    }
    
    // Display all students
    void displayAllStudents() const {
        if (students.empty()) {
            std::cout << "No students in the system.\n";
            return;
        }
        
        std::cout << "\n" << std::string(60, '=') << "\n";
        std::cout << std::setw(6) << "ID" 
                  << std::setw(20) << "Name" 
                  << std::setw(6) << "Age" 
                  << std::setw(8) << "GPA" << "\n";
        std::cout << std::string(60, '-') << "\n";
        
        for (const auto& student : students) {
            student.display();
        }
        
        std::cout << std::string(60, '=') << "\n";
        std::cout << "Total students: " << students.size() << "\n";
        displayMemoryUsage();
    }
    
    // Find student by ID (using binary search after sorting)
    Student* findStudentById(int id) {
        // Sort by ID for binary search
        std::sort(students.begin(), students.end(), 
                  [](const Student& a, const Student& b) { return a.getId() < b.getId(); });
        
        auto it = std::lower_bound(students.begin(), students.end(), id,
            [](const Student& s, int id) { return s.getId() < id; });
        
        if (it != students.end() && it->getId() == id) {
            return &(*it);
        }
        return nullptr;
    }
    
    // Update student information
    bool updateStudent(int id, const std::string& name = "", int age = -1, double gpa = -1.0) {
        Student* student = findStudentById(id);
        if (!student) {
            std::cout << "Student with ID " << id << " not found.\n";
            return false;
        }
        
        if (!name.empty()) student->setName(name);
        if (age != -1) student->setAge(age);
        if (gpa != -1.0) student->setGPA(gpa);
        
        std::cout << "Student updated successfully!\n";
        return true;
    }
    
    // Remove student by ID
    bool removeStudent(int id) {
        auto it = std::remove_if(students.begin(), students.end(),
                                [id](const Student& s) { return s.getId() == id; });
        
        if (it != students.end()) {
            students.erase(it, students.end());
            
            // Shrink vector if too much unused capacity
            if (students.capacity() > students.size() * 2) {
                students.shrink_to_fit();
                std::cout << "Memory optimized (vector shrunk to fit)\n";
            }
            
            std::cout << "Student removed successfully!\n";
            displayMemoryUsage();
            return true;
        }
        
        std::cout << "Student with ID " << id << " not found.\n";
        return false;
    }
    
    // Find students by name
    std::vector<Student*> findStudentsByName(const std::string& name) {
        std::vector<Student*> results;
        
        for (auto& student : students) {
            if (student.getName().find(name) != std::string::npos) {
                results.push_back(&student);
            }
        }
        
        return results;
    }
    
    // Calculate average GPA
    double calculateAverageGPA() const {
        if (students.empty()) return 0.0;
        
        double total = 0.0;
        for (const auto& student : students) {
            total += student.getGPA();
        }
        
        return total / students.size();
    }
    
    // Sort students by GPA (descending)
    void sortByGPA() {
        std::sort(students.begin(), students.end(),
                  [](const Student& a, const Student& b) { return a.getGPA() > b.getGPA(); });
        std::cout << "Students sorted by GPA (highest first)\n";
    }
    
    // Sort students by name
    void sortByName() {
        std::sort(students.begin(), students.end(),
                  [](const Student& a, const Student& b) { return a.getName() < b.getName(); });
        std::cout << "Students sorted by name\n";
    }
    
    // Clear all students
    void clearAllStudents() {
        // Efficient clearing using swap with empty vector
        std::vector<Student>().swap(students);
        nextId = 1;
        std::cout << "All students removed. Memory freed.\n";
        displayMemoryUsage();
    }
    
    // Display memory usage
    void displayMemoryUsage() const {
        size_t currentMemory = memoryUsed();
        std::cout << "\n--- Memory Usage ---\n";
        std::cout << "Students stored: " << students.size() << "\n";
        std::cout << "Vector capacity: " << students.capacity() << "\n";
        std::cout << "Memory used: " << currentMemory << " bytes (" 
                  << currentMemory / 1024.0 << " KB)\n";
        std::cout << "Element size: " << sizeof(Student) << " bytes\n";
        
        if (!students.empty()) {
            double loadFactor = static_cast<double>(students.size()) / students.capacity();
            std::cout << "Load factor: " << std::fixed << std::setprecision(2) 
                      << (loadFactor * 100) << "%\n";
        }
        std::cout << "--------------------\n";
    }
    
    // Get statistics
    void displayStatistics() const {
        if (students.empty()) {
            std::cout << "No data for statistics.\n";
            return;
        }
        
        double minGPA = students[0].getGPA();
        double maxGPA = students[0].getGPA();
        double totalAge = 0;
        
        for (const auto& student : students) {
            double gpa = student.getGPA();
            if (gpa < minGPA) minGPA = gpa;
            if (gpa > maxGPA) maxGPA = gpa;
            totalAge += student.getAge();
        }
        
        std::cout << "\n=== Statistics ===\n";
        std::cout << "Total students: " << students.size() << "\n";
        std::cout << "Average GPA: " << std::fixed << std::setprecision(2) 
                  << calculateAverageGPA() << "\n";
        std::cout << "Minimum GPA: " << minGPA << "\n";
        std::cout << "Maximum GPA: " << maxGPA << "\n";
        std::cout << "Average age: " << std::fixed << std::setprecision(1) 
                  << (totalAge / students.size()) << "\n";
        std::cout << "=================\n";
    }
};

// Menu functions
void displayMenu() {
    std::cout << "\n=== Student Management System ===\n";
    std::cout << "1. Add New Student\n";
    std::cout << "2. Display All Students\n";
    std::cout << "3. Find Student by ID\n";
    std::cout << "4. Find Students by Name\n";
    std::cout << "5. Update Student Information\n";
    std::cout << "6. Remove Student\n";
    std::cout << "7. Sort Students by GPA\n";
    std::cout << "8. Sort Students by Name\n";
    std::cout << "9. Display Statistics\n";
    std::cout << "10. Display Memory Usage\n";
    std::cout << "11. Clear All Students\n";
    std::cout << "12. Exit\n";
    std::cout << "Enter your choice (1-12): ";
}

int main() {
    StudentManager manager;
    int choice;
    
    // Add some sample data
    manager.addStudent("John Doe", 20, 3.5);
    manager.addStudent("Jane Smith", 21, 3.8);
    manager.addStudent("Bob Johnson", 19, 3.2);
    
    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore();  // Clear newline
        
        switch (choice) {
            case 1: {
                std::string name;
                int age;
                double gpa;
                
                std::cout << "Enter student name: ";
                std::getline(std::cin, name);
                std::cout << "Enter age: ";
                std::cin >> age;
                std::cout << "Enter GPA: ";
                std::cin >> gpa;
                std::cin.ignore();
                
                manager.addStudent(name, age, gpa);
                break;
            }
            
            case 2:
                manager.displayAllStudents();
                break;
                
            case 3: {
                int id;
                std::cout << "Enter student ID: ";
                std::cin >> id;
                std::cin.ignore();
                
                Student* student = manager.findStudentById(id);
                if (student) {
                    std::cout << "\nStudent found:\n";
                    std::cout << std::setw(6) << "ID" 
                              << std::setw(20) << "Name" 
                              << std::setw(6) << "Age" 
                              << std::setw(8) << "GPA" << "\n";
                    student->display();
                } else {
                    std::cout << "Student not found.\n";
                }
                break;
            }
            
            case 4: {
                std::string name;
                std::cout << "Enter name to search: ";
                std::getline(std::cin, name);
                
                auto results = manager.findStudentsByName(name);
                if (!results.empty()) {
                    std::cout << "\nFound " << results.size() << " student(s):\n";
                    std::cout << std::setw(6) << "ID" 
                              << std::setw(20) << "Name" 
                              << std::setw(6) << "Age" 
                              << std::setw(8) << "GPA" << "\n";
                    for (auto student : results) {
                        student->display();
                    }
                } else {
                    std::cout << "No students found with name containing: " << name << "\n";
                }
                break;
            }
            
            case 5: {
                int id;
                std::string name;
                int age;
                double gpa;
                char updateName, updateAge, updateGPA;
                
                std::cout << "Enter student ID to update: ";
                std::cin >> id;
                std::cin.ignore();
                
                std::cout << "Update name? (y/n): ";
                std::cin >> updateName;
                std::cin.ignore();
                if (updateName == 'y' || updateName == 'Y') {
                    std::cout << "Enter new name: ";
                    std::getline(std::cin, name);
                }
                
                std::cout << "Update age? (y/n): ";
                std::cin >> updateAge;
                std::cin.ignore();
                if (updateAge == 'y' || updateAge == 'Y') {
                    std::cout << "Enter new age: ";
                    std::cin >> age;
                    std::cin.ignore();
                }
                
                std::cout << "Update GPA? (y/n): ";
                std::cin >> updateGPA;
                std::cin.ignore();
                if (updateGPA == 'y' || updateGPA == 'Y') {
                    std::cout << "Enter new GPA: ";
                    std::cin >> gpa;
                    std::cin.ignore();
                }
                
                manager.updateStudent(id, 
                    (updateName == 'y' || updateName == 'Y') ? name : "",
                    (updateAge == 'y' || updateAge == 'Y') ? age : -1,
                    (updateGPA == 'y' || updateGPA == 'Y') ? gpa : -1.0);
                break;
            }
            
            case 6: {
                int id;
                std::cout << "Enter student ID to remove: ";
                std::cin >> id;
                std::cin.ignore();
                manager.removeStudent(id);
                break;
            }
            
            case 7:
                manager.sortByGPA();
                manager.displayAllStudents();
                break;
                
            case 8:
                manager.sortByName();
                manager.displayAllStudents();
                break;
                
            case 9:
                manager.displayStatistics();
                break;
                
            case 10:
                manager.displayMemoryUsage();
                break;
                
            case 11:
                std::cout << "Are you sure you want to clear all students? (y/n): ";
                char confirm;
                std::cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    manager.clearAllStudents();
                }
                break;
                
            case 12:
                std::cout << "Exiting program. Goodbye!\n";
                break;
                
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
        
    } while (choice != 12);
    
    return 0;
}