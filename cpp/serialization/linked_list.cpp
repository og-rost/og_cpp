#include <iostream>
#include <string>

// Serializing a linked list means converting the list's structure and data into a format
// that can be easily stored or transmitted, such as a binary or text format.


#include <iostream>
#include <fstream>

struct ListNode {
    int data;
    ListNode* next;
    ListNode(int data) : data(data), next(nullptr) {}
};

// Serialize the linked list to a binary file
void serialize(ListNode* head, const std::string& filename) {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        std::cerr << "Cannot open the output file." << std::endl;
        return;
    }

    while (head != nullptr) {
        ofs.write(reinterpret_cast<char*>(&head->data), sizeof(int));
        head = head->next;
    }
    ofs.close();
}

// Deserialize the linked list from a binary file
ListNode* deserialize(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) {
        std::cerr << "Cannot open the input file." << std::endl;
        return nullptr;
    }

    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    int data;

    while (ifs.read(reinterpret_cast<char*>(&data), sizeof(int))) {
        ListNode* newNode = new ListNode(data);
        if (head == nullptr) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }
    ifs.close();

    return head;
}

// Helper function to print the linked list
void printList(ListNode* head) {
    while (head != nullptr) {
        std::cout << head->data << " -> ";
        head = head->next;
    }
    std::cout << "nullptr" << std::endl;
}

int main() {
    // Create a linked list
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);

    std::cout << "Original list: ";
    printList(head);

    // Serialize the linked list
    const std::string filename = "linked_list.bin";
    serialize(head, filename);

    // Deserialize the linked list
    ListNode* deserializedList = deserialize(filename);
    std::cout << "Deserialized list: ";
    printList(deserializedList);

    return 0;
}
