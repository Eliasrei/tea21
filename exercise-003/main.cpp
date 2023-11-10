#include <fmt/chrono.h>
#include <fmt/format.h>
#include <iostream>
#include <vector>
#include <memory>  // für std::make_unique
#include <algorithm>

// LinkedListNode-Klasse repräsentiert einen Knoten in der verketteten Liste
class LinkedListNode
{
public:
    std::string data;
    std::unique_ptr<LinkedListNode> next;  // Smart Pointer für automatische Ressourcenfreigabe

    // Konstruktor
    LinkedListNode(const std::string &value) : data(value), next(nullptr) {}

    // Print-Methode zum Ausgeben des Datenwerts
    void print() const
    {
        fmt::print("{} ", data);
    }
};

// LinkedList-Klasse repräsentiert die verkettete Liste
class LinkedList
{
private:
    std::unique_ptr<LinkedListNode> head;

public:
    // Fügt ein neues Element am Ende der Liste hinzu
    void insert_tail(std::unique_ptr<LinkedListNode> &newNode)
    {
        if (!head)
        {
            head = std::move(newNode);
        }
        else
        {
            LinkedListNode *current = head.get();
            while (current->next)
            {
                current = current->next.get();
            }
            current->next = std::move(newNode);
        }
    }

    // Fügt ein neues Element am Anfang der Liste hinzu
    void insert_head(std::unique_ptr<LinkedListNode> &newNode)
    {
        newNode->next = std::move(head);
        head = std::move(newNode);
    }

    // Traversiert die Liste und ruft eine Funktion für jeden Knoten auf
    void traverse(void (*func)(const std::string &)) const
    {
        LinkedListNode *current = head.get();
        while (current)
        {
            func(current->data);
            current = current->next.get();
        }
        fmt::print("\n");
    }

    // Gibt die Anzahl der Elemente in der Liste zurück
    std::size_t size() const
    {
        std::size_t count = 0;
        LinkedListNode *current = head.get();
        while (current)
        {
            ++count;
            current = current->next.get();
        }
        return count;
    }
};

void printer(const std::string &name)
{
    fmt::print("{} ", name);
}

auto main(int argc, char **argv) -> int
{
    fmt::print("Hello, {}!\n", "World");

    const std::vector<std::string> names{"Hugo", "Franz", "Elisabeth", "Anton", "Gerhard", "Maria", "Hannelore"};
    const std::vector<std::string> names2{"Ulf", "Ole", "Sepp", "Norton", "Kai", "Uschi", "Gert"};

    // Erstelle eine LinkedList-Instanz
    LinkedList list;

    fmt::print("------------------------------\n");

    // Füge Namen am Ende der Liste hinzu
    for (const auto &name : names)
    {
        auto elem = std::make_unique<LinkedListNode>(name);
        list.insert_tail(elem);
    }

    // Traversiere und drucke die Liste
    list.traverse(printer);

    fmt::print("------------------------------\n");

    // Füge Namen am Anfang der Liste hinzu
    for (const auto &name : names2)
    {
        auto elem = std::make_unique<LinkedListNode>(name);
        list.insert_head(elem);
    }

    fmt::print("------------------------------\n");

    // Traversiere und drucke die Liste erneut
    list.traverse(printer);

    fmt::print("------------------------------\n");

    fmt::print("Elements in the list: {}\n", list.size());

    fmt::print("------------------------------\n");

    // Traversiere und drucke die Liste ein letztes Mal
    list.traverse(printer);

    return 0; /* exit gracefully */
}
