#pragma once
#include "Cube.h"

class Model;
class World;

class Rule {
public:
    virtual ~Rule() {
    }

    virtual bool isSatisfied(const Model& model, const Interpretation& interpretation) const = 0;
    virtual void AddCubesToWorld(World& world) const = 0;
};

class NegatedRule: public Rule {
public:
    NegatedRule(const Rule* rule) :
            rule(rule) {
    }

    virtual bool isSatisfied(const Model& model, const Interpretation& interpretation) const;
    virtual void AddCubesToWorld(World& world) const;

protected:
    std::shared_ptr<const Rule> (rule);
};

class OnRule: public Rule {
public:
    OnRule(const BaseCube& x, const BaseCube& y) :
            x(x), y(y) {
    }

    virtual bool isSatisfied(const Model& model, const Interpretation& interpretation) const;
    virtual void AddCubesToWorld(World& world) const;
protected:
    BaseCube x;
    BaseCube y;
};

class OnTableRule: public Rule {
public:
    OnTableRule(const BaseCube& x) :
            x(x) {
    }

    virtual bool isSatisfied(const Model& model, const Interpretation& interpretation) const;
    virtual void AddCubesToWorld(World& world) const;
protected:
    BaseCube x;
};

class NothingOnTopRule: public Rule {
public:
    NothingOnTopRule(const BaseCube& x) :
            x(x) {
    }

    virtual bool isSatisfied(const Model& model, const Interpretation& interpretation) const;
    virtual void AddCubesToWorld(World& world) const;
protected:
    BaseCube x;
};

class AboveRule: public Rule {
public:
    AboveRule(const BaseCube& x, const BaseCube& y) :
            x(x), y(y) {
    }

    virtual bool isSatisfied(const Model& model, const Interpretation& interpretation) const;
    virtual void AddCubesToWorld(World& world) const;
protected:
    BaseCube x;
    BaseCube y;
};

class EqualsRule: public Rule {
public:
    EqualsRule(const BaseCube& x, const BaseCube& y) :
            x(x), y(y) {
    }

    virtual bool isSatisfied(const Model& model, const Interpretation& interpretation) const;
    virtual void AddCubesToWorld(World& world) const;
protected:
    BaseCube x;
    BaseCube y;
};
