// Copyright 2019 Grama Nicolae
#include "../headers/Trie.h"

int main() {
    Trie<std::string> dictionary;
    dictionary.insert("abase", "something");
    dictionary.insert("abash", "something");
    dictionary.insert("abate", "something");
    dictionary.insert("abuse", "something");
    dictionary.insert("awash", "something");
    dictionary.insert("abash", "something");
    dictionary.insert("abate", "something");
    dictionary.insert("agate", "something");
    dictionary.insert("abide", "something");
    dictionary.insert("abode", "something");
    dictionary.insert("abide", "something");
    dictionary.insert("amide", "something");
    dictionary.insert("aside", "something");

    std::cout << "Contains - abase : " << dictionary.contains("abase") << "\n";
    std::cout << "Contains - aba : " << dictionary.contains("aba") << "\n";
    std::cout << "Contains - abash : " << dictionary.contains("abash") << "\n";
    std::cout << "Contains - abashi : " << dictionary.contains("abashi") << "\n\n";

    std::cout << "Definition - agate : " << dictionary.search("agate") << "\n";
    std::cout << "Definition - asaki : " << dictionary.search("asaki") << "\n\n";

    std::cout << "Contains - aside : " << dictionary.contains("aside") << "\n";
    std::cout << "Definition - aside : " << dictionary.search("aside") << "\n\n";

    dictionary.remove("asaki");
    dictionary.remove("aside");

    std::cout << "Contains - aside : " << dictionary.contains("aside") << "\n";
    std::cout << "Definition - aside : " << dictionary.search("aside") << "\n";

    return 0;
}
