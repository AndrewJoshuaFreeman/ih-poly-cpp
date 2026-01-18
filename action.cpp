#include <cstddef>//std::size_t
#include <iostream>
#include <memory>//unique ptr
#include <vector>
#include <utility>//std::move
#include <string>

//abstract base class, needs no contructor, defines behavior not state
class Action{

public:
    //all pure virtual functions makes abstract class
    virtual ~Action() noexcept = default;//noexcept for !throwing exception
    //returns Action callsign
    virtual std::string name() const = 0;
    //Action can cost mana, hp, stamina, etc
    virtual int cost() const = 0;
    //what the Action actually does
    virtual void execute( int& hp, int& mana ) const = 0;
    //a way to copy Action, since unique_ptr is not copyable
    //ie no action2 = action1
    virtual std::unique_ptr<Action> clone() const = 0;
};


class Attack : public Action{
public:
    Attack( int dmg, int staminaCost )
    : dmg{dmg}, staminaCost{staminaCost} {}

    std::string name() const override{
        return "Attack";
    }

    int cost() const override{
         return staminaCost;
    } 

    void execute( int& hp, int& mana ) const override{
        hp -= dmg;
    }
    //like having Action* clone() {return new Action(*this);}
    //"allocate a new attack on the heap that is a copy of me"
    std::unique_ptr<Action> clone() const override{
        return std::make_unique<Attack>(*this);
    }

private:
    int dmg{};
    int staminaCost{};
};


class Heal : public Action{
public:
    Heal( int amount, int manaCost )
    : amount{amount}, manaCost{manaCost} {}

    std::string name() const override{
        return "Heal";
    }

    int cost() const override{
        return manaCost;
    }

    void execute( int& hp, int& mana ) const override{
        hp += amount;
        mana -= manaCost;
    }

    std::unique_ptr<Action> clone() const override{
        return std::make_unique<Heal>(*this);
    }

private:
    int amount{};
    int manaCost{};
};


class Fireball : public Action{
public:
    Fireball( int dmg, int manaCost )
    : dmg{dmg}, manaCost{manaCost} {}

    std::string name() const override{
        return "Fireball";
    }

    int cost() const override{
        return manaCost;
    }

    void execute( int& hp, int& mana ) const override{
        hp -= dmg;
        mana -= manaCost;
    }

    std::unique_ptr<Action> clone() const override{
        return std::make_unique<Fireball>(*this);
    }

private:
    int dmg{};
    int manaCost{};
};


class ActionBar{
public:

    //default constructor
    ActionBar() = default;

    //copy contructor: Action b = a, for existing a
    ActionBar( const ActionBar& other ){
        for( const auto& a : other.m_actions ){
            m_actions.push_back(a->clone());
        }
    }

    //copy assignment: for existing Action a and Action b, b = a
    ActionBar& operator=( const ActionBar& other ){
        if( this != &other ){
            m_actions.clear();
            for( const auto& a : other.m_actions ){
                m_actions.push_back(a->clone());
            }
        }
        return *this;
    }

    //move constructor: for Action b = std::move(a)
    ActionBar( ActionBar&& other ) noexcept
    : m_actions( std::move(other.m_actions) ) {}

    //move assignment: for existing Action a and Action b, b = std::move(a)
    ActionBar& operator=( ActionBar&& other ) noexcept{
        if( this != &other ){
            m_actions = std::move(other.m_actions);
        }
        return *this;
    }

    void add( std::unique_ptr<Action> a ){
       m_actions.push_back(std::move(a)); 
    }

    std::size_t size() const{
        return m_actions.size();
    }

    const Action& at( std::size_t i ) const{
       return *m_actions[i]; 
    }

    //iterates through all actions and prints their info out
    void runAll( int& hp, int& mana ) const{
        for( const auto& a : m_actions ){
            std::cout << "Running: "
                      << a->name()
                      << " (cost "
                      << a->cost()
                      << ")\n";
            a->execute(hp, mana);
        }
    }

private:
    std::vector<std::unique_ptr<Action>> m_actions;
};


int main(){

    int hp = 100;
    int mana = 50;

    ActionBar userBar;

    userBar.add(std::make_unique<Attack>(15, 5));
    userBar.add(std::make_unique<Heal>(10, 8));
    userBar.add(std::make_unique<Fireball>(30, 20));

    std::cout << "Start: hp = " << hp << " mana = " << mana << '\n';

    userBar.runAll(hp, mana);

    std::cout << "End: hp = " << hp << " mana = " << mana << '\n';

    return 0;
}
