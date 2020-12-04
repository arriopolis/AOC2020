#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
using namespace std;

int main() {
  string s;
  vector<set<string>> documents;
  set<string> fields;
  while (getline(cin, s)) {
    if (s.size() == 0) {
      documents.push_back(fields);
      fields.clear();
    }
    istringstream iss(s);
    string field;
    while (iss >> field) {
      fields.insert(field.substr(0, field.find(':')));
    }
  }
  documents.push_back(fields);

  const set<string> REQ_FIELDS = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
  int ctr = 0;
  for (auto d : documents) {
    bool valid = true;
    for (string req_field : REQ_FIELDS) {
      if (d.find(req_field) == d.end()) {
        valid = false;
        break;
      }
    }
    if (valid) ctr++;
  }
  cout << ctr << endl;
}
