#include <iostream>
#include <iterator>
#include <utility>
#include <iomanip>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

class Student
{
public:
  Student() = default;
  Student(string const& name, string const& surname, string const& pnr,
          int result, char grade)
      : name{name},
        surname{surname},
        pnr{pnr},
        result{result},
        grade{grade},
        gn{}
  {
    if (grade != 'U')
    {
      gn = grade - '0';
    }
  }

  bool operator<(Student const& rhs) const
  {
    if (gn < rhs.gn)
    {
      return false;
    }
    else if (gn > rhs.gn)
    {
      return true;
    }
    return (surname + name) < (rhs.surname + rhs.name);
  }

  string to_string() const
  {
    ostringstream oss;
    oss << setw(30) << left << (surname + ", " + name) << pnr << right
        << setw(8) << grade << " (" << setw(2) << result << ")";
    return oss.str();
  }

private:
  string name{};
  string surname{};
  string pnr{};
  int result{};
  char grade{};
  int gn{};
};

istream& operator>>(istream& is, Student& s)
{
  string name, surname, pnr;
  int result;
  char grade;
  getline(is, name, ':');
  getline(is, surname, ':');
  getline(is, pnr, ':');
  is >> result;
  is.ignore();
  is.get(grade);
  is.ignore();
  s = Student(name, surname, pnr, result, grade);
  return is;
}

ostream& operator<<(ostream& os, Student const& s)
{
  return os << s.to_string();
}

int main()
{
  vector<Student> students{istream_iterator<Student>{cin},
                           istream_iterator<Student>{}};
  sort(begin(students), end(students));
  copy(begin(students), end(students),
       ostream_iterator<Student>{cout, "\n"});
}
