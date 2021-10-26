#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>

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
  virtual std::string toString() const {
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
  virtual std::string toString() const {
    std::stringstream plus;
    plus << "(" << left->toString() << " + " << right->toString() << ")";
    return plus.str();
  }
  virtual ~PlusExpression() {
    delete left;
    delete right;
  }
};

class MinusExpression : public Expression {
  Expression * left;
  Expression * right;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  virtual std::string toString() const {
    std::stringstream minus;
    minus << "(" << left->toString() << " - " << right->toString() << ")";
    return minus.str();
  }
  virtual ~MinusExpression() {
    delete left;
    delete right;
  }
};

class TimesExpression : public Expression {
  Expression * left;
  Expression * right;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  virtual std::string toString() const {
    std::stringstream time;
    time << "(" << left->toString() << " * " << right->toString() << ")";
    return time.str();
  }
  virtual ~TimesExpression() {
    delete left;
    delete right;
  }
};

class DivExpression : public Expression {
  Expression * left;
  Expression * right;

 public:
  DivExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  virtual std::string toString() const {
    std::stringstream div;
    div << "(" << left->toString() << " * " << right->toString() << ")";
    return div.str();
  }
  virtual ~DivExpression() {
    delete left;
    delete right;
  }
};
