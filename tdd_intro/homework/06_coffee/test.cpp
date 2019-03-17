/*
We have to develop a coffee machine with TDD. The machine uses the automated source of ingredients, which implements the interface ISourceOfIngredients.

Our machine should be able to produce the coffee accordingly to the next receipts:
- americano: water & coffee 1:2 or 1:3. Water temp 60C
- cappuccino - milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C
- latte - milk & coffee & milk foam 1:4, 1:2, 1:4. Water temp 90C
- marochino - chocolate & coffee & milk foam, 1:4, 1:4, 1:4 and 1:4 is empty

We have 2 possible sizes of the cup:
- little 100 gram
- big 140 gram

Implement worked coffee machine using ISourceOfIngredients to controll the process of coffee production.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>



class ISourceOfIngredients
{
public:
    virtual ~ISourceOfIngredients() {}
    virtual void SetCupSize(int gram) = 0;
    virtual void AddWater(int gram, int temperature) = 0;
    virtual void AddSugar(int gram) = 0;
    virtual void AddCoffee(int gram) = 0;
    virtual void AddMilk(int gram) = 0;
    virtual void AddMilkFoam(int gram) = 0;
    virtual void AddChocolate(int gram) = 0;
    virtual void AddCream(int gram) = 0;
};

class MockSourceOfIngredients : public ISourceOfIngredients
{
public:
    MOCK_METHOD1(SetCupSize, void(int));
    MOCK_METHOD2(AddWater, void(int, int));
    MOCK_METHOD1(AddSugar, void(int));
    MOCK_METHOD1(AddCoffee, void(int));
    MOCK_METHOD1(AddMilk, void(int));
    MOCK_METHOD1(AddMilkFoam, void(int));
    MOCK_METHOD1(AddChocolate, void(int));
    MOCK_METHOD1(AddCream, void(int));
};

class Cofee
{
public:
    void fillIngredients(std::unique_ptr<ISourceOfIngredients> source)
    {
        m_source.swap(source);
    }

    virtual ~Cofee(){}
    virtual const std::string drink() = 0;

private:
    std::unique_ptr<ISourceOfIngredients> m_source;
};

class Americano : public Cofee
{
public:
    const std::string drink()
    {
        return "Americano";
    }
};

class Latte : public Cofee
{
public:
    const std::string drink()
    {
        return "Latte";
    }
};

class Cappuccino : public Cofee
{
public:
    const std::string drink()
    {
        return "Cappuccino";
    }
};

class Marochino : public Cofee
{
public:
    const std::string drink()
    {
        return "Marochino";
    }
};

class CoffeeMachine
{
public:
    std::unique_ptr<Cofee> createAmericano(std::unique_ptr<ISourceOfIngredients>& source, int cupSize)
    {
        std::unique_ptr<Cofee> cofee(new Americano);
        source->AddCoffee(cupSize / 3);
        source->AddWater(cupSize, 60);
        cofee->fillIngredients(std::move(source));

        return std::move(cofee);
    }

    std::unique_ptr<Cofee> createCappuccino(std::unique_ptr<ISourceOfIngredients>& source, int cupSize)
    {
        std::unique_ptr<Cofee> cofee(new Cappuccino);
        source->AddWater(cupSize, 80);
        source->AddMilk(cupSize / 3);
        source->AddCoffee(cupSize / 3);
        source->AddMilkFoam(cupSize / 3);
        cofee->fillIngredients(std::move(source));

        return std::move(cofee);
    }

    std::unique_ptr<Cofee> createLatte(std::unique_ptr<ISourceOfIngredients>& source, int cupSize)
    {
        std::unique_ptr<Cofee> cofee(new Latte);
        source->AddWater(cupSize, 90);
        source->AddMilk(cupSize / 4);
        source->AddCoffee(cupSize / 2);
        source->AddMilkFoam(cupSize / 4);
        cofee->fillIngredients(std::move(source));

        return std::move(cofee);
    }

    std::unique_ptr<Cofee> createMarochino(std::unique_ptr<ISourceOfIngredients>& source, int cupSize)
    {
        std::unique_ptr<Cofee> cofee(new Marochino);
        source->AddWater(cupSize - (cupSize / 4), 0);
        source->AddChocolate(cupSize / 4);
        source->AddCoffee(cupSize / 4);
        source->AddMilkFoam(cupSize / 4);
        cofee->fillIngredients(std::move(source));

        return std::move(cofee);
    }
};

TEST(CofeeMachine, create_XXL_marochino)
{
    // marochino - chocolate & coffee & milk foam, 1:4, 1:4, 1:4 and 1:4 is empty
    CoffeeMachine machine;
    MockSourceOfIngredients* source = new MockSourceOfIngredients;
    std::unique_ptr<ISourceOfIngredients> ptr(source);
    EXPECT_CALL(*source, AddWater(105, 0)).Times(1);
    EXPECT_CALL(*source, AddChocolate(35)).Times(1);
    EXPECT_CALL(*source, AddCoffee(35)).Times(1);
    EXPECT_CALL(*source, AddMilkFoam(35)).Times(1);

    auto cofee = machine.createMarochino(ptr, 140);

    EXPECT_EQ(cofee->drink(), "Marochino");
}

TEST(CofeeMachine, create_small_marochino)
{
    // marochino - chocolate & coffee & milk foam, 1:4, 1:4, 1:4 and 1:4 is empty
    CoffeeMachine machine;
    MockSourceOfIngredients* source = new MockSourceOfIngredients;
    std::unique_ptr<ISourceOfIngredients> ptr(source);
    EXPECT_CALL(*source, AddWater(75, 0)).Times(1);
    EXPECT_CALL(*source, AddChocolate(25)).Times(1);
    EXPECT_CALL(*source, AddCoffee(25)).Times(1);
    EXPECT_CALL(*source, AddMilkFoam(25)).Times(1);

    auto cofee = machine.createMarochino(ptr, 100);

    EXPECT_EQ(cofee->drink(), "Marochino");
}

TEST(CofeeMachine, create_XXL_latte)
{
    // latte - milk & coffee & milk foam 1:4, 1:2, 1:4. Water temp 90C
    CoffeeMachine machine;
    MockSourceOfIngredients* source = new MockSourceOfIngredients;
    std::unique_ptr<ISourceOfIngredients> ptr(source);
    EXPECT_CALL(*source, AddWater(140, 90)).Times(1);
    EXPECT_CALL(*source, AddMilk(35)).Times(1);
    EXPECT_CALL(*source, AddCoffee(70)).Times(1);
    EXPECT_CALL(*source, AddMilkFoam(35)).Times(1);

    auto cofee = machine.createLatte(ptr, 140);

    EXPECT_EQ(cofee->drink(), "Latte");
}

TEST(CofeeMachine, create_small_latte)
{
    // latte - milk & coffee & milk foam 1:4, 1:2, 1:4. Water temp 90C
    CoffeeMachine machine;
    MockSourceOfIngredients* source = new MockSourceOfIngredients;
    std::unique_ptr<ISourceOfIngredients> ptr(source);
    EXPECT_CALL(*source, AddWater(100, 90)).Times(1);
    EXPECT_CALL(*source, AddMilk(25)).Times(1);
    EXPECT_CALL(*source, AddCoffee(50)).Times(1);
    EXPECT_CALL(*source, AddMilkFoam(25)).Times(1);

    auto cofee = machine.createLatte(ptr, 100);

    EXPECT_EQ(cofee->drink(), "Latte");
}

TEST(CofeeMachine, create_XXL_cappuccino)
{
    //cappuccino - milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C
    CoffeeMachine machine;
    MockSourceOfIngredients* source = new MockSourceOfIngredients;
    std::unique_ptr<ISourceOfIngredients> ptr(source);
    EXPECT_CALL(*source, AddWater(140, 80)).Times(1);
    EXPECT_CALL(*source, AddMilk(46)).Times(1);
    EXPECT_CALL(*source, AddCoffee(46)).Times(1);
    EXPECT_CALL(*source, AddMilkFoam(46)).Times(1);

    auto cofee = machine.createCappuccino(ptr, 140);

    EXPECT_EQ(cofee->drink(), "Cappuccino");
}

TEST(CofeeMachine, create_small_cappuccino)
{
    //cappuccino - milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C
    CoffeeMachine machine;
    MockSourceOfIngredients* source = new MockSourceOfIngredients;
    std::unique_ptr<ISourceOfIngredients> ptr(source);
    EXPECT_CALL(*source, AddWater(100, 80)).Times(1);
    EXPECT_CALL(*source, AddMilk(33)).Times(1);
    EXPECT_CALL(*source, AddCoffee(33)).Times(1);
    EXPECT_CALL(*source, AddMilkFoam(33)).Times(1);

    auto cofee = machine.createCappuccino(ptr, 100);

    EXPECT_EQ(cofee->drink(), "Cappuccino");
}

TEST(CofeeMachine, create_XXL_americano)
{
    CoffeeMachine machine;
    MockSourceOfIngredients* source = new MockSourceOfIngredients;
    std::unique_ptr<ISourceOfIngredients> ptr(source);
    EXPECT_CALL(*source, AddWater(140, 60)).Times(1);
    EXPECT_CALL(*source, AddCoffee(46)).Times(1);

    auto cofee = machine.createAmericano(ptr, 140);

    EXPECT_EQ(cofee->drink(), "Americano");
}

TEST(CofeeMachine, create_small_americano)
{
    CoffeeMachine machine;
    MockSourceOfIngredients* source = new MockSourceOfIngredients;
    std::unique_ptr<ISourceOfIngredients> ptr(source);
    EXPECT_CALL(*source, AddWater(100, 60)).Times(1);
    EXPECT_CALL(*source, AddCoffee(33)).Times(1);

    auto cofee = machine.createAmericano(ptr, 100);

    EXPECT_EQ(cofee->drink(), "Americano");
}

TEST(CofeeTest, check_that_drink_marochino)
{
    Marochino mar;
    EXPECT_EQ(mar.drink(), "Marochino");
}

TEST(CofeeTest, check_that_drink_americano)
{
    Americano amer;
    EXPECT_EQ(amer.drink(), "Americano");
}

TEST(CofeeTest, check_that_drink_latte)
{
    Latte lat;
    EXPECT_EQ(lat.drink(), "Latte");
}

TEST(CofeeTest, check_that_drink_cappuccino)
{
    Cappuccino cap;
    EXPECT_EQ(cap.drink(), "Cappuccino");
}
