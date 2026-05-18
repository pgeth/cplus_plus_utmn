#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <concepts>
#include <type_traits>

using namespace std;

template <typename T>
concept constructor = is_constructible_v<T, ostream&>;

template <typename T>
concept can_output = requires(const T& object) {
  { cout << object };
};

template <typename Iter>
concept is_iterator = requires(Iter i) { ++i; };

template <typename T>
concept get_value = requires(T object) {
  { object.value() } -> std::same_as<int>;
};

template <typename T, typename V>
concept get_at = requires(T object, int i) {
  { object.at(i) } -> std::same_as<V>;
};

class Cube
{
  int side;
public:
  Cube(istream& in) { in >> side; }

  int value() const { return side * side; }

  Cube& operator++()
  {
    ++side;
    return *this;
  }

  void execute(const string& method, ostream& out)
  {
    if (method == "can_output")
      out << *this;
    else if (method == "is_iterator")
    {
      ++(*this);
      out << side;
    }
    else if (method == "get_value")
      out << value();
  }

  friend ostream& operator<<(ostream& os, const Cube& c)
  {
    return os << c.side;
  }
};

class Person
{
  string firstName;
  string lastName;
public:
  Person(istream& in) { in >> lastName >> firstName; }

  void execute(const string& method, ostream& out)
  {
    if (method == "can_output")
      out << *this;
  }

  friend ostream& operator<<(ostream& os, const Person& p)
  {
    return os << p.lastName;
  }
};

class Vector
{
  vector<int> data;
public:
  Vector(istream& in)
  {
    int n;
    in >> n;
    data.resize(n);
    for (int i = 0; i < n; ++i)
      in >> data[i];
  }

  int value() const
  {
    int sum = 0;
    for (int x : data)
      sum += x;
    return sum;
  }

  int at(int i) const { return data[i]; }

  Vector& operator++()
  {
    for (auto& x : data)
      ++x;
    return *this;
  }

  void execute(const string& method, ostream& out)
  {
    if (method == "can_output")
      out << *this;
    else if (method == "is_iterator")
    {
      ++(*this);
      out << *this;
    }
    else if (method == "get_value")
      out << value();
    else if (method == "get_at")
      out << at(0);
  }

  friend ostream& operator<<(ostream& os, const Vector& v)
  {
    for (int x : v.data)
      os << x << " ";
    return os;
  }
};

template <typename T>
string get_method(istream& in)
{
  string method;
  in >> method;
  if ((method == "get_at" && get_at<T, int>) ||
      (method == "get_value" && get_value<T>) ||
      (method == "can_output" && can_output<T>) ||
      (method == "is_iterator" && is_iterator<T>))
  {
    return method;
  }
  return "";
}

int main()
{
  ifstream in("input.txt");
  ofstream out("output.txt");
  string class_name;
  while (in >> class_name)
  {
    if (class_name == "Vector")
    {
      Vector v(in);
      string method = get_method<Vector>(in);
      if (method != "")
        v.execute(method, out);
      else
        out << "false";
    }
    else if (class_name == "Cube")
    {
      Cube cube(in);
      string method = get_method<Cube>(in);
      if (method != "")
        cube.execute(method, out);
      else
        out << "false";
    }
    else if (class_name == "Person")
    {
      Person person(in);
      string method = get_method<Person>(in);
      if (method != "")
        person.execute(method, out);
      else
        out << "false";
    }
    out << endl;
  }
}
