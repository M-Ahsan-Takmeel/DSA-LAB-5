#include <iostream>
#include <string>
using namespace std;
struct JobNode {
    int jobId;
    string documentName;
    int numPages;
    JobNode* next;

    JobNode(int id, string name, int pages) 
        : jobId(id), documentName(name), numPages(pages), next(nullptr) {}
};

class PrinterQueue {
private:
    JobNode* front;
    JobNode* rear;
    int jobCount;
public:
    PrinterQueue() : front(nullptr), rear(nullptr), jobCount(0) {}

    ~PrinterQueue() {
        clearQueue();
    }

    void addJob(int id, string name, int pages) {
        JobNode* newNode = new JobNode(id, name, pages);
        
        if (isEmpty()) {
            front = newNode;
            rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        jobCount++;
        cout << "[Added] Job ID " << id << ": \"" << name << "\" (" << pages << " pages).\n";
    }

    void processJob() {
        if (isEmpty()) {
            cout << "[Error] Cannot process job. The queue is empty!\n";
            return;
        }

        JobNode* temp = front;
        cout << "[Processing] Job ID " << temp->jobId << ": \"" << temp->documentName 
             << "\" (" << temp->numPages << " pages)\n";

        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        jobCount--;
    }

    void viewNextJob() const {
        if (isEmpty()) {
            cout << "[Next Job] None. The queue is empty.\n";
            return;
        }
        cout << "[Next Job] Job ID " << front->jobId << ": \"" << front->documentName 
             << "\" (" << front->numPages << " pages)\n";
    }

    void displayQueue() const {
        if (isEmpty()) {
            cout << "[Queue Status] Queue is empty.\n";
            return;
        }

        cout << "\n--- Current Print Queue (Front to Rear) ---\n";
        JobNode* current = front;
        while (current != nullptr) {
            cout << "Job ID: " << current->jobId 
                 << " | Document: " << current->documentName 
                 << " | Pages: " << current->numPages << "\n";
            current = current->next;
        }
        cout << "-------------------------------------------\n";
    }

    int countJobs() const {
        return jobCount;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void clearQueue() {
        while (!isEmpty()) {
            JobNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
        jobCount = 0;
    }
};

int main() {
    PrinterQueue pq;
    cout << "===== Populating Initial Print Queue =====\n";
    pq.addJob(101, "Assignment1.pdf", 10);
    pq.addJob(102, "Report.docx", 25);
    pq.addJob(103, "Notes.pdf", 5);
    pq.addJob(104, "LabTask.docx", 15);

    cout << "\n===== 1. Displaying All Jobs =====";
    pq.displayQueue();
    cout << "Total waiting jobs: " << pq.countJobs() << "\n";

    cout << "\n===== 2. Processing Two Jobs =====\n";
    pq.processJob();
    pq.processJob();

    cout << "\n===== 3. Displaying Remaining Jobs =====";
    pq.displayQueue();
    cout << "Total waiting jobs: " << pq.countJobs() << "\n";

    cout << "\n===== 4. Adding a New Job =====\n";
    pq.addJob(105, "ResearchPaper.pdf", 30);

    cout << "\n===== 5. Displaying Next Job =====\n";
    pq.viewNextJob();

    cout << "\n===== 6. Processing All Remaining Jobs =====\n";
    while (!pq.isEmpty()) {
        pq.processJob();
    }

    cout << "\n===== 7. Attempting to Process From Empty Queue =====\n";
    pq.processJob();
    return 0;
}
