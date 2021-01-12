#include <memory>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

using Point = std::pair<int, int>;

class Object {

public:
  Object(int x, int y, string name) : position{x, y}, name{name} {}

  virtual ~Object() = default;

  Object(Object const &) = delete;

  virtual bool collide(Object const &other) const { return position == other.position; }

  Point get_position() const { return position; }

  string get_name() const { return name; }

protected:

  Point position;
  string const name;
};

class Wall : public Object {

public:
  using Object::Object;
};

class Door : public Wall {

public:
  using Wall::Wall;
};

class Movable : public Object {

public:
  using Object::Object;

  void move_to(Point new_position) { position = new_position; }

  virtual void move() = 0;
};

class Human : public Movable {

public:
    using Movable::Movable;

    // using typeid to check against one specific type. Only doing dynamic_cast<Wall*> here 
    //  will not work sice Door will also be a valid cast.
    bool collide(Object const &other) const override {
        return Object::collide(other) && typeid(other) == typeid(Wall);
    }

    void move() override { ++position.second; }
};

class Cat : public Movable {

public:
    using Movable::Movable;

    bool collide(Object const &other) const override {
        if (Object::collide(other)) {
            return dynamic_cast<Wall const *>(&other) != nullptr;
        }
        return false;
    }

    void move() override { ++position.first; }
};

bool have_collisions(Movable &obj, std::vector<unique_ptr<Object>> const &objects)
{
    return any_of(begin(objects), end(objects), [&obj](auto const & optr){ return obj.collide(*optr); });
}

void update(std::vector<unique_ptr<Object>> &objects)
{
    for (auto & obj : objects)
    {
        if (auto mov = dynamic_cast<Movable *>(obj.get()))
        {
            auto old_position{mov->get_position()};
            mov->move();
            if (have_collisions(*mov, objects))
            {
                mov->move_to(old_position);
            }
            else
            {
                cout << mov->get_name() << " moved!" << endl;
            }
        }
    }
}

int main()
{
    std::vector<unique_ptr<Object>> objects;
    objects.push_back(make_unique<Cat>(-2, 2, "the cat"));
    objects.push_back(make_unique<Wall>(4, 2, "east wall"));
    objects.push_back(make_unique<Human>(2, 0, "the human"));
    objects.push_back(make_unique<Door>(2, 2, "the front door"));
    objects.push_back(make_unique<Wall>(2, 5, "outer wall"));

    for (int i{0}; i < 10; ++i)
        update(objects);
}
