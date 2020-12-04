#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <vector>
using namespace std;

int main() {
  string s;
  vector<map<string,string>> documents;
  map<string,string> fields;
  while (getline(cin, s)) {
    if (s.size() == 0) {
      documents.push_back(fields);
      fields.clear();
    }
    istringstream iss(s);
    string field;
    while (iss >> field) {
      fields[field.substr(0, field.find(':'))] = field.substr(field.find(':')+1);
    }
  }
  documents.push_back(fields);

  const set<string> EYE_COLORS = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
  int ctr = 0;
  for (auto d : documents) {
    if (d.find("byr") == d.end() || stoi(d["byr"]) < 1920 || stoi(d["byr"]) > 2002) continue;
    if (d.find("iyr") == d.end() || stoi(d["iyr"]) < 2010 || stoi(d["iyr"]) > 2020) continue;
    if (d.find("eyr") == d.end() || stoi(d["eyr"]) < 2020 || stoi(d["eyr"]) > 2030) continue;
    if (d.find("hgt") == d.end()) continue;
    int hgt = stoi(d["hgt"].substr(0,d["hgt"].size()-2));
    if (d["hgt"].substr(d["hgt"].size()-2) == "cm") {
      if (hgt < 150 || hgt > 193) continue;
    } else {
      if (hgt < 59 || hgt > 76) continue;
    }
    if (d.find("hcl") == d.end() || d["hcl"].size() != 7 || d["hcl"].substr(0,1) != "#") continue;
    bool valid = true;
    for (char c : d["hcl"].substr(1)) {
      if ((c < '0' || c > '9') && (c < 'a' && c > 'f')) {
        valid = false;
        break;
      }
    }
    if (!valid) continue;
    if (d.find("ecl") == d.end() || EYE_COLORS.find(d["ecl"]) == EYE_COLORS.end()) continue;
    if (d.find("pid") == d.end() || d["pid"].size() != 9) continue;
    valid = true;
    for (char c : d["pid"]) {
      if (c < '0' || c > '9') {
        valid = false;
        break;
      }
    }
    if (!valid) continue;
    ctr++;
  }
  cout << ctr << endl;
}
