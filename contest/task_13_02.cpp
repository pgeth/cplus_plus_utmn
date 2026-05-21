#include <iostream>
#include <string>
#include <vector>
#include <sstream>

static bool isLatin(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static char toLow(char c) {
    return (c >= 'A' && c <= 'Z') ? (char)(c + 32) : c;
}

static bool isAsciiNonLetter(char c) {
    unsigned char uc = (unsigned char)c;
    if (uc >= 128) return false;
    return !isLatin(c);
}

int main() {
    const std::string vowels = "aeiouy";
    int vowelCount[6] = {};

    struct WordInfo {
        int length;
        std::string alphaOnly;
    };
    std::vector<WordInfo> words;

    std::string line;
    while (std::getline(std::cin, line)) {
        for (char c : line) {
            char lc = toLow(c);
            size_t pos = vowels.find(lc);
            if (pos != std::string::npos)
                vowelCount[pos]++;
        }
        std::istringstream iss(line);
        std::string tok;
        while (iss >> tok) {
            while (!tok.empty() && !isLatin(tok.back())) {
                tok.pop_back();
            }
            while (!tok.empty() && isAsciiNonLetter(tok.front())) {
                tok.erase(tok.begin());
            }
            if (tok.empty()) continue;
            std::string alphaOnly;
            for (char c : tok) {
                if (isLatin(c)) alphaOnly += toLow(c);
            }
            if (alphaOnly.empty()) continue;
            words.push_back({(int)tok.size(), alphaOnly});
        }
    }

    int bestIdx = -1, bestCount = 0;
    for (int i = 0; i < 6; i++) {
        if (vowelCount[i] > bestCount) {
            bestCount = vowelCount[i];
            bestIdx = i;
        }
    }

    if (bestIdx == -1) {
        std::cout << "No vowels\n";
        return 0;
    }

    char best = vowels[bestIdx];
    std::cout << best << "\n";

    if (words.empty()) {
        std::cout << 0 << "\n";
        return 0;
    }

    double totalLen = 0;
    for (const auto& w : words)
        totalLen += w.length;
    double avg = totalLen / words.size();

    int count = 0;
    for (const auto& w : words) {
        if ((double)w.length > avg && w.alphaOnly.find(best) != std::string::npos) {
            count++;
        }
    }

    std::cout << count << "\n";
    return 0;
}
