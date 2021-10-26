
#include <cstdlib>
#include <iostream>
#include <sstream>

class Expression {
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long number;

 public:
  NumExpression(long n) : number(n) {}
  std::string toString() const {
    std::stringstream num;
    num << number;
    return num.str();
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * left;
  Expression * right;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  std::string toString() const {
    std::stringstream plus;
    plus << "(" << left->toString() << " + " << right->toString() << ")";
    return plus.str();
  }
  ~PlusExpression() {
    delete left;
    delete right;
  }
};
