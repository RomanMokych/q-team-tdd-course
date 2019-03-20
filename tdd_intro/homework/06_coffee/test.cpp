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

using namespace testing;

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

enum CupSize{
    BIG = 140,
    LITTLE = 100
};

class CoffeeMachine
{
public:
    CoffeeMachine(ISourceOfIngredients& source)
        : m_source(source)
    {

    }
    void produceEmptyCup(CupSize size)
    {
        m_source.SetCupSize(size);
    }
    void produceCoffee(CupSize size)
    {
        m_source.SetCupSize(size);
        m_source.AddCoffee(size);
    }
    void produceAmericano(CupSize size)
    {
        m_source.SetCupSize(size);
        m_source.AddCoffee(size*2/3);
        m_source.AddWater(size/3, 60);
    }
private:
    ISourceOfIngredients& m_source;
};

TEST(CoffeeMachine, ProduceBigEmptyCup)
{
    MockSourceOfIngredients source;
    CoffeeMachine machine(source);

    EXPECT_CALL(source, SetCupSize(140)).WillOnce(Return());
    machine.produceEmptyCup(CupSize::BIG);
}

TEST(CoffeeMachine, ProduceLittleEmptyCup)
{
    MockSourceOfIngredients source;
    CoffeeMachine machine(source);

    EXPECT_CALL(source, SetCupSize(100)).WillOnce(Return());
    machine.produceEmptyCup(CupSize::LITTLE);
}

TEST(CoffeeMachine, ProduceBigCoffee)
{
    MockSourceOfIngredients source;
    CoffeeMachine machine(source);

    EXPECT_CALL(source, SetCupSize(140)).WillOnce(Return());
    EXPECT_CALL(source, AddCoffee(140)).WillOnce(Return());

    machine.produceCoffee(CupSize::BIG);
}

TEST(CoffeeMachine, ProduceLittleCoffee)
{
    MockSourceOfIngredients source;
    CoffeeMachine machine(source);

    EXPECT_CALL(source, SetCupSize(100)).WillOnce(Return());
    EXPECT_CALL(source, AddCoffee(100)).WillOnce(Return());

    machine.produceCoffee(CupSize::LITTLE);
}

TEST(CoffeeMachine, ProduceBigAmericano)
{
    MockSourceOfIngredients source;
    CoffeeMachine machine(source);

    int cupSize = 140;
    EXPECT_CALL(source, SetCupSize(cupSize)).WillOnce(Return());
    EXPECT_CALL(source, AddCoffee(cupSize*2/3)).WillOnce(Return());
    EXPECT_CALL(source, AddWater(cupSize/3, 60)).WillOnce(Return());

    machine.produceAmericano(CupSize::BIG);
}
