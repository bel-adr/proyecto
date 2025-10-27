#include "CompactChainList.h"
#include<algorithm>

//Operaciones constructoras
CompactChainList::CompactChainList() {
  this -> s = 0;
};

CompactChainList::CompactChainList(vector<Element> &v) {
  Element aux;
  int count = 1;
  this -> s = 0;
  
  if (!v.empty()) aux = v.at(0);
  for (int i = 1; i < v.size(); ++i) {
    if (v.at(i) == aux) {
      ++count;
    } else {
      this -> l.push_back(make_pair(v.at(i - 1), count));
      count = 1;
      aux = v.at(i);
    }
    this -> s += 1;
  }
};

CompactChainList::CompactChainList(CompactChainList &l2) {
  for (list<pair<Element, int>>::iterator it = l2.l.begin(); it != l2.l.end(); ++it) {
    this -> l.push_back(*it);
    this -> s += (*it).second;
  }
};
  
//Operaciones analizadoras

int CompactChainList::size() {
  return s;
};

int CompactChainList::searchElement(Element &e) {
  int ans = 0;
  bool flag = false;
  for (list<pair<Element, int>>::iterator it = l.begin(); it != l.end() && !flag; ++it) {
    if ((*it).first == e)
      flag = true;
    else
      ++ans;
  }
  return ans;
};

int CompactChainList::getConsecutiveOcurrences(vector<Element> &v) {
  list<Element> l1 = this -> expand();
  int ans = 0, count = 0;
  bool flag1 = false, flag2;
  for (list<Element>::iterator it = l1.begin(); it != l1.end() && !v.empty() && !flag1; ++it) {
    flag2 = false;
    if (l1.size() - count < v.size()) flag1 = true;
    if (!flag1 && *it == v[0]) {
      list<Element>::iterator it2 = ++it;
      for (int i = 1; i < v.size() && !flag2; ++i) {
	if (*it2 != v[i]) flag2 = true;
	++it2;
      }
      if (!flag2) ++ans;
    }
    ++count;
  }
  return ans;
};

int CompactChainList::getIndexFirstConsecutiveOcurrence(vector<Element> &v) {
  list<Element> l1 = this -> expand();
  int ans = 0, count = 0, acc = 0;
  bool flag1 = false, flag2, flag3 = false;
  for (list<Element>::iterator it = l1.begin(); it != l1.end() && !v.empty() && !flag1 && !flag3; ++it) {
    flag2 = false;
    if (l1.size() - count < v.size()) flag1 = true;
    if (!flag1 && *it == v[0]) {
      list<Element>::iterator it2 = ++it;
      for (int i = 1; i < v.size() && !flag2; ++i) {
	if (*it2 != v[i]) flag2 = true;
	++it2;
      }
      if (!flag2) flag3 = true;
    }
    ++count;
  }
  if (!flag3)
    ans = l.size();
  else
    ans = --count;
  return ans;
};

int CompactChainList::getOcurrences(vector<Element> &v) {
};

int CompactChainList::getIndexFirstOcurrence(vector<Element> &v) {
};

CompactChainList CompactChainList::getLexicographicFusion(CompactChainList &oth) {
  CompactChainList ans;
  list<pair<Element, int>>::iterator it1 = l.begin(), it2 = oth.l.begin();
  while (it1 != l.end() && it2 != oth.l.end()) {
    if ((*it1).first == (*it2).first) {
      ans.l.push_back(make_pair((*it1).first, (*it1).second + (*it2).second));
      ++it1;
      ++it2;
    } else if ((*it1).first < (*it2).first) {
      ans.l.push_back(*it1);
      ++it1;
    } else {
      ans.l.push_back(*it2);
      ++it2;
    }
  }
  if (it1 != l.end()) {
    while (it1 != l.end()) {
      ans.l.push_back(*it1);
      ++it1;
    }
  } else if (it2 != oth.l.end()) {
    while (it2 != oth.l.end()) {
      ans.l.push_back(*it2);
      ++it2;
    }
  }
  return ans;
};

list<Element> CompactChainList::expand() {
  list<Element> ans;
  for (list<pair<Element, int>>::iterator it = l.begin(); it != l.end(); ++it)
    for (int i = 0; i < (*it).second; ++i)
      ans.push_back((*it).first);
  return ans;
};

//Operaciones modificadoras

void CompactChainList::set(int p, Element &e) {
  list<pair<Element, int>>::iterator it = l.begin();
  for (int i = 0; i < p; ++i)
    ++it;
  (*it).first = e;
};

void CompactChainList::removeFirstOcurrence(Element &e) {
  bool flag;
  for (list<pair<Element, int>>::iterator it = l.begin(); it != l.end() && !flag; ++it) {
    if ((*it).first == e) {
      flag = true;
      if ((*it).second > 1)
	--(*it).second;
      else
	l.erase(it);
    }
  }
};

void CompactChainList::removeAllOcurrences(Element &e) {
  for (list<pair<Element, int>>::iterator it = l.begin(); it != l.end(); ++it) {
    if ((*it).first == e)
      l.erase(it);
  }
};

void CompactChainList::removeBlockPosition(int p) {
  list<pair<Element, int>>::iterator it = l.begin();
  for (int i = 0; i < p; ++i)
    ++it;
  l.erase(it);
};

void CompactChainList::insertElement(int p, Element &e) {
  list<pair<Element, int>>::iterator it = l.begin();
  for (int i = 0; i < p; ++i)
    ++it;
  //l.insert(it, e);
};

void CompactChainList::modifyAllOcurrences(Element &e1, Element &e2) {
  for (list<pair<Element, int>>::iterator it = l.begin(); it != l.end(); ++it) {
    if ((*it).first == e1)
      (*it).first = e2;
  }
};

void CompactChainList::push_front(Element &e, int count) {
  if (l.front().first == e)
    l.front().second += count;
  else
    l.push_front(make_pair(e, count));
};

void CompactChainList::push_back(Element &e, int count) {
  if (l.back().first == e)
    l.back().second += count;
  else
    l.push_back(make_pair(e, count));
};

//static
void CompactChainList::sortVectirCCL(vector<CompactChainList> &v) {
  //sort(v.begin(), v.end());
};

void CompactChainList::lol() {
  //hola mundo
};

//Sobrecarga de operadores

CompactChainList CompactChainList::operator+(CompactChainList &oth) {
  CompactChainList ans = this -> getLexicographicFusion(oth);
  return ans;
};

pair<Element, int>& CompactChainList::operator[](int indx) {
  list<pair<Element, int>>::iterator it = l.begin();
  for (int i = 0; i < indx; ++i)
    ++it;
  return *it;
};

bool CompactChainList::operator<(CompactChainList &oth) {
  bool ans = this -> s == oth.s;
  list<pair<Element, int>>::iterator it2 = oth.l.begin();
  for (list<pair<Element, int>>::iterator it1 = l.begin(); it1 != l.end() && ans; ++it1)
    if ((*it1) > (*it2)) ans = false;
  return ans;
};

bool CompactChainList::operator==(const CompactChainList &oth) const {
  bool ans = this -> s == oth.s;
  list<pair<Element, int>>::const_iterator it2 = oth.l.cbegin();
  for (list<pair<Element, int>>::const_iterator it1 = l.cbegin(); it1 != l.cend() && ans; ++it1)
    if ((*it1) != (*it2)) ans = false;
  return ans;
};
