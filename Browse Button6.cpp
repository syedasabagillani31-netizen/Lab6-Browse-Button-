#include <iostream>
#include <string>
#include <utility>
using namespace std;

// ========================================
// Browser Page Node
// ========================================
struct PageNode
{
    int pageID;
    string title;
    string URL;
    PageNode* next;
};

// ========================================
// Circular Linked List Class
// head points to the last node (pivot)
// head->next points to the first node
// ========================================
class CircularLinkedList
{
private:
    PageNode* head;
    int count;

    // Get node at a specific index
    PageNode* GetNodeAt(int index)
    {
        if (head == nullptr)
            return nullptr;

        PageNode* current = head->next;

        for (int i = 0; i < index; i++)
            current = current->next;

        return current;
    }

    // Swap data of two nodes
    void SwapData(PageNode* a, PageNode* b)
    {
        swap(a->pageID, b->pageID);
        swap(a->title, b->title);
        swap(a->URL, b->URL);
    }

    // Normalize index into the range 0 to count-1
    int NormalizeIndex(int index)
    {
        return ((index % count) + count) % count;
    }

public:
    // Constructor
    CircularLinkedList()
    {
        head = nullptr;
        count = 0;
    }

    // Check collection status
    bool IsEmpty()
    {
        return count == 0;
    }

    bool IsNotEmpty()
    {
        return count > 0;
    }

    // ====================================
    // Insert at the beginning
    // ====================================
    void Insert(PageNode* page)
    {
        if (page == nullptr)
            return;

        if (head == nullptr)
        {
            head = page;
            page->next = page;
        }
        else
        {
            page->next = head->next;
            head->next = page;
        }

        count++;
    }

    // ====================================
    // Remove from the beginning
    // ====================================
    PageNode* Remove()
    {
        if (IsEmpty())
            return nullptr;

        PageNode* first = head->next;

        if (first == head)
        {
            head = nullptr;
        }
        else
        {
            head->next = first->next;
        }

        first->next = nullptr;
        count--;

        return first;
    }

    // ====================================
    // Insert at a specified index
    // ====================================
    void InsertAt(PageNode* page, int index)
    {
        if (page == nullptr)
            return;

        if (count == 0)
        {
            head = page;
            page->next = page;
            count++;
            return;
        }

        if (index < 0)
            index = NormalizeIndex(index);

        if (index > count)
            index %= count;

        // Insert at beginning
        if (index == 0)
        {
            Insert(page);
            return;
        }

        // Insert at end
        if (index == count)
        {
            page->next = head->next;
            head->next = page;
            head = page;
            count++;
            return;
        }

        // Insert in the middle
        PageNode* previous = GetNodeAt(index - 1);

        page->next = previous->next;
        previous->next = page;

        count++;
    }

    // ====================================
    // Remove at a specified index
    // ====================================
    PageNode* RemoveAt(int index)
    {
        if (IsEmpty())
            return nullptr;

        index = NormalizeIndex(index);

        if (index == 0)
            return Remove();

        PageNode* previous = GetNodeAt(index - 1);
        PageNode* target = previous->next;

        previous->next = target->next;

        // Update pivot if the last node is removed
        if (target == head)
            head = previous;

        target->next = nullptr;
        count--;

        return target;
    }

    // ====================================
    // Swap two pages
    // ====================================
    void Swap(int index1, int index2)
    {
        if (IsEmpty())
            return;

        index1 = NormalizeIndex(index1);
        index2 = NormalizeIndex(index2);

        if (index1 == index2)
            return;

        PageNode* first = GetNodeAt(index1);
        PageNode* second = GetNodeAt(index2);

        SwapData(first, second);
    }

    // ====================================
    // Sort pages by ID
    // ====================================
    void Sort()
    {
        if (count < 2)
            return;

        PageNode* current = head->next;

        for (int i = 0; i < count - 1; i++)
        {
            PageNode* nextNode = current->next;

            for (int j = i + 1; j < count; j++)
            {
                if (current->pageID > nextNode->pageID)
                    SwapData(current, nextNode);

                nextNode = nextNode->next;
            }

            current = current->next;
        }
    }

    // ====================================
    // Reverse the circular linked list
    // ====================================
    void Reverse()
    {
        if (count < 2)
            return;

        PageNode* oldTail = head;
        PageNode* oldFirst = head->next;

        PageNode* previous = oldTail;
        PageNode* current = oldFirst;

        while (current != oldTail)
        {
            PageNode* nextNode = current->next;

            current->next = previous;
            previous = current;
            current = nextNode;
        }

        oldTail->next = previous;

        // Old first becomes the new last node
        head = oldFirst;
    }

    // ====================================
    // Display all pages
    // ====================================
    void Print()
    {
        if (IsEmpty())
        {
            cout << "\nBrowser history is empty.\n";
            return;
        }

        PageNode* current = head->next;

        cout << "\n========== BROWSER HISTORY ==========\n";
        cout << "Index\tID\tTitle\t\tURL\n";
        cout << "---------------------------------------------\n";

        for (int i = 0; i < count; i++)
        {
            cout << i << "\t"
                 << current->pageID << "\t"
                 << current->title << "\t\t"
                 << current->URL << endl;

            current = current->next;
        }

        cout << "Total pages: " << count << endl;
        cout << "Last page connects back to the first page.\n";
    }

    // ====================================
    // Move to the next page repeatedly
    // ====================================
    void Browse()
    {
        if (IsEmpty())
        {
            cout << "\nNo pages available to browse.\n";
            return;
        }

        PageNode* current = head->next;

        cout << "\nCircular browsing demonstration:\n";

        for (int i = 0; i < count * 2; i++)
        {
            cout << "Page: " << current->title
                 << " | URL: " << current->URL << endl;

            current = current->next;
        }

        cout << "\nThe browser has completed two circular rounds.\n";
    }

    // Destructor
    ~CircularLinkedList()
    {
        while (IsNotEmpty())
            delete Remove();
    }
};

// ========================================
// Create a new browser page
// ========================================
PageNode* CreatePage(int id, string title, string url)
{
    PageNode* page = new PageNode;

    page->pageID = id;
    page->title = title;
    page->URL = url;
    page->next = nullptr;

    return page;
}

// ========================================
// Main Function
// ========================================
int main()
{
    CircularLinkedList browser;
    int choice;
    int id, index, index1, index2;
    string title, url;
    PageNode* removed;

    // Initial sample pages
    browser.InsertAt(
        CreatePage(103, "YouTube", "www.youtube.com"), 0);

    browser.InsertAt(
        CreatePage(101, "Google", "www.google.com"), 1);

    browser.InsertAt(
        CreatePage(105, "GitHub", "www.github.com"), 2);

    browser.InsertAt(
        CreatePage(102, "Wikipedia", "www.wikipedia.org"), 3);

    do
    {
        cout << "\n========================================\n";
        cout << " CIRCULAR BROWSER HISTORY SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Display All Pages\n";
        cout << "2. Insert Page at Head\n";
        cout << "3. Remove Page from Head\n";
        cout << "4. Insert Page at Index\n";
        cout << "5. Remove Page at Index\n";
        cout << "6. Swap Pages\n";
        cout << "7. Sort Pages by ID\n";
        cout << "8. Reverse Page Collection\n";
        cout << "9. Browse Pages Repeatedly\n";
        cout << "10. Check Collection Status\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            browser.Print();
            break;

        case 2:
        {
            cout << "Enter page ID: ";
            cin >> id;

            cin.ignore(10000, '\n');

            cout << "Enter page title: ";
            getline(cin, title);

            cout << "Enter page URL: ";
            getline(cin, url);

            browser.Insert(CreatePage(id, title, url));

            cout << "Page inserted at the beginning.\n";
            break;
        }

        case 3:
            removed = browser.Remove();

            if (removed != nullptr)
            {
                cout << "Removed page: "
                     << removed->title << endl;

                delete removed;
            }
            else
            {
                cout << "Browser history is empty.\n";
            }
            break;

        case 4:
        {
            cout << "Enter page ID: ";
            cin >> id;

            cin.ignore(10000, '\n');

            cout << "Enter page title: ";
            getline(cin, title);

            cout << "Enter page URL: ";
            getline(cin, url);

            cout << "Enter index: ";
            cin >> index;

            browser.InsertAt(
                CreatePage(id, title, url), index);

            cout << "Page inserted successfully.\n";
            break;
        }

        case 5:
            cout << "Enter index to remove: ";
            cin >> index;

            removed = browser.RemoveAt(index);

            if (removed != nullptr)
            {
                cout << "Removed page: "
                     << removed->title << endl;

                delete removed;
            }
            else
            {
                cout << "Browser history is empty.\n";
            }
            break;

        case 6:
            cout << "Enter first index: ";
            cin >> index1;

            cout << "Enter second index: ";
            cin >> index2;

            browser.Swap(index1, index2);

            cout << "Swap operation completed.\n";
            break;

        case 7:
            browser.Sort();

            cout << "Pages sorted by ID.\n";
            browser.Print();
            break;

        case 8:
            browser.Reverse();

            cout << "Page collection reversed.\n";
            browser.Print();
            break;

        case 9:
            browser.Browse();
            break;

        case 10:
            if (browser.IsEmpty())
                cout << "Browser history is empty.\n";
            else
                cout << "Browser history is not empty.\n";

            break;

        case 11:
            cout << "Exiting Browser History System.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 11);

    return 0;
}