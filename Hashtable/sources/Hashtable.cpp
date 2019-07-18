#include "../headers/Hastable.h"

using namespace std;

int main() {
    // Essential test
    Hashtable<string, int> table(100);
    table.put("Nick", 5);
    table.put("Michael", 10);
    table.put("Josh", 3);
    table.put("Roger", 8);
    cout << table.get("Michael") << "\n";
    table.remove("Michael");
    cout << table.get("Michael") << "\n";
    cout << "Has key Nick : " << table.hasKey("Nick") << "\n";
    cout << "Has key John : " << table.hasKey("John") << "\n";
    cout << "The number of keys stored is : " << table.size() << "\n";
    Hashtable<string, int> other = table;

    table.remove("Josh");
    table.remove("Roger");

    cout << "The number of keys stored is : " << table.size()
         << "(1st table)\n";
    cout << "The number of keys stored is : " << other.size()
         << "(2nd table)\n";

    cout << "The 2nd table should still have Josh : " << other.hasKey("Josh")
         << "\n";
    cout << "But also it doesn't have Michael : " << other.hasKey("Michael")
         << "\n";

    // Resizing test
    Hashtable<string, int> resize(10, 50, 4);
    resize.put("a", 1);
    resize.put("b", 2);
    resize.put("c", 3);
    resize.put("d", 4);
    resize.put("e", 5);
    resize.put("f", 6);
    resize.put("g", 7);
    resize.put("h", 8);
    resize.put("i", 9);
    resize.put("j", 10);
    std::cout << "Current size is " << resize.maxSize() << "\n";
    std::cout << "There are " << resize.size() << " elements inserted\n";

    return 0;
}