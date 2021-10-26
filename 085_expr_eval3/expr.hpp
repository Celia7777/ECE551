#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>

class Expression {
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
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
  virtual long evaluate() const { return number; }
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
  virtual long evaluate() const { return left->evaluate() + right->evaluate(); }
  virtual ~PlusExpression() {
    delete left;
    delete right;
  }
};

class MinusExpression : public Expression {
 private:
  Expression * left;
  Expression * right;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  virtual std::string toString() const {
    std::stringstream minus;
    minus << "(" << left->toString() << " - " << right->toString() << ")";
    return minus.str();
  }
  virtual long evaluate() const { return left->evaluate() - right->evaluate(); }
  virtual ~MinusExpression() {
    delete left;
    delete right;
  }
};

class TimesExpression : public Expression {
 private:
  Expression * left;
  Expression * right;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  virtual std::string toString() const {
    std::stringstream times;
    times << "(" << left->toString() << " * " << right->toString() << ")";
    return times.str();
  }
  virtual long evaluate() const { return left->evaluate() * right->evaluate(); }
  virtual ~TimesExpression() {
    delete left;
    delete right;
  }
};

class DivExpression : public Expression {
 private:
  Expression * left;
  Expression * right;

 public:
  DivExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  virtual std::string toString() const {
    std::stringstream div;
    div << "(" << left->toString() << " / " << right->toString() << ")";
    return div.str();
  }
  virtual long evaluate() const { return left->evaluate() / right->evaluate(); }
  virtual ~DivExpression() {
    delete left;
    delete right;
  }
};
