#include "CompactChainList.h"
#include<vector>

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
  return this -> s;
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
  bool flag1 = false, flag2;
  int count = 0, ans = 0;
  CompactChainList v2(v);
  for (list<pair<Element, int>>::iterator it1 = l.begin(); it1 != l.end() && !flag1 && !v.empty(); ++it1) {
    flag2 = false;
    if (this -> s - count < v.size()) flag1 = true;
    if (((*it1).first == v2.l.front().first && (*it1).second >= v2.l.front().second) && !flag1) {
      list<pair<Element, int>>::iterator it2 = ++it1;
      for (list<pair<Element, int>>::iterator it3 = ++v2.l.begin(); it3 != v2.l.end() && !flag2; ++it3) {
	if ((it3 == --v2.l.end() && (*it2).first == (*it3).first && (*it2).second < (*it3).second) || *it2 != *it3)
	  flag2 = true;
	++it2;
      }
      if (!flag2) ++ans;
    }
    count += (*it1).second;
  }
  return ans;
};

int CompactChainList::getIndexFirstConsecutiveOcurrence(vector<Element> &v) {
};

int CompactChainList::getOcurrences(vector<Element> &v) {
};

int CompactChainList::getIndexFirstOcurrence(vector<Element> &v) {
};

CompactChainList CompactChainList::getLexicographicFusion(CompactChainList &l2) {
};

list<Element> CompactChainList::expand() {
};

  //Operaciones modificadoras
void CompactChainList::set(int p, Element &e) {
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
bool CompactChainList::operator+(CompactChainList &oth) {
};

bool CompactChainList::operator[](CompactChainList &oth) {
  
};

bool CompactChainList::operator<(CompactChainList &oth) {
};

bool CompactChainList::operator==(const CompactChainList &oth) const {
};
