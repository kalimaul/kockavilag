#pragma once
#include "Cube.h"

class Model;
class World;

class Rule {
public:
    virtual ~Rule() {
    }

    virtual bool isSatisfied(const Model& model) const = 0;
    virtual void AddCubesToWorld(World& world) const = 0;
};

class NegatedRule: public Rule {
public:
    NegatedRule(const Rule* rule) :
            rule(rule) {
    }

    virtual bool isSatisfied(const Model& model) const;
    virtual void AddCubesToWorld(World& world) const;

protected:
    std::shared_ptr<const Rule> (rule);
};

class AndRule: public Rule {
public:
    virtual void addRule(const Rule* rule) {
        rules.push_back(std::shared_ptr<const Rule>(rule));
    }

    virtual bool isSatisfied(const Model& model) const;
    virtual void AddCubesToWorld(World& world) const;

protected:
    std::list<std::shared_ptr<const Rule>> rules;
};

class OnRule: public Rule {
public:
    OnRule(const Cube& x, const Cube& y) :
            x(x), y(y) {
    }

    virtual bool isSatisfied(const Model& model) const;
    virtual void AddCubesToWorld(World& world) const;
protected:
    Cube x;
    Cube y;
};

class OnTableRule: public Rule {
public:
    OnTableRule(const Cube& x) :
            x(x) {
    }

    virtual bool isSatisfied(const Model& model) const;
    virtual void AddCubesToWorld(World& world) const;
protected:
    Cube x;
};

class NothingOnTopRule: public Rule {
public:
    NothingOnTopRule(const Cube& x) :
            x(x) {
    }

    virtual bool isSatisfied(const Model& model) const;
    virtual void AddCubesToWorld(World& world) const;
protected:
    Cube x;
};

class AboveRule: public Rule {
public:
    AboveRule(const Cube& x, const Cube& y) :
            x(x), y(y) {
    }

    virtual bool isSatisfied(const Model& model) const;
    virtual void AddCubesToWorld(World& world) const;
protected:
    Cube x;
    Cube y;
};

