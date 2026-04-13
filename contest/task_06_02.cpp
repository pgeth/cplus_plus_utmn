#include <algorithm>
#include <cctype>
#include <fstream>
#include <string>
#include <vector>

bool is_vowel(char c)
{
  c = std::tolower(static_cast<unsigned char>(c));
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

int main()
{
  std::ifstream in("input.txt");
  std::ofstream out("output.txt");

  int word_count = 0;
  int freq[26] = {0};

  std::string line;
  while (std::getline(in, line))
  {
    std::size_t i = 0;
    while (i < line.size())
    {
      if (!std::isalpha(static_cast<unsigned char>(line[i])))
      {
        ++i;
        continue;
      }
      std::size_t j = i;
      while (j < line.size() && std::isalpha(static_cast<unsigned char>(line[j])))
        ++j;
      char first = line[i];
      if (std::isupper(static_cast<unsigned char>(first)) && !is_vowel(first))
      {
        ++word_count;
        for (std::size_t k = i; k < j; ++k)
        {
          char c = std::tolower(static_cast<unsigned char>(line[k]));
          ++freq[c - 'a'];
        }
      }
      i = j;
    }
  }

  if (word_count == 0)
  {
    out << "No words";
    return 0;
  }

  out << word_count << '\n';

  std::vector<std::pair<int, int>> letters;
  for (int i = 0; i < 26; ++i)
    if (freq[i] > 0)
      letters.push_back({-freq[i], i});
  std::sort(letters.begin(), letters.end());

  int top = std::min(3, static_cast<int>(letters.size()));
  for (int i = 0; i < top; ++i)
  {
    if (i > 0)
      out << ' ';
    out << static_cast<char>('A' + letters[i].second);
  }
  return 0;
}
