#pragma once
#include "Cube.h"

class Model;
class World;

class Rule {
public:
    static Rule* buildRule(std::istream& stream);

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

class TableRule: public Rule {
public:
    TableRule(const Cube& x) :
            x(x) {
    }

    virtual bool isSatisfied(const Model& model) const;
    virtual void AddCubesToWorld(World& world) const;
protected:
    Cube x;
};

class EmptyRule: public Rule {
public:
    EmptyRule(const Cube& x) :
            x(x) {
    }

    virtual bool isSatisfied(const Model& model) const;
    virtual void AddCubesToWorld(World& world) const;
protected:
    Cube x;
};

class AtopRule: public Rule {
public:
    AtopRule(const Cube& x, const Cube& y) :
            x(x), y(y) {
    }

    virtual bool isSatisfied(const Model& model) const;
    virtual void AddCubesToWorld(World& world) const;
protected:
    Cube x;
    Cube y;
};

class AllOnTableAxiom: public Rule {
public:
    virtual bool isSatisfied(const Model& model) const;
    virtual void AddCubesToWorld(World& world) const {
    }

protected:
    Cube getBottom(const Cube& from, const Model& model) const;
};

