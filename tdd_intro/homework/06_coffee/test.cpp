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

enum class CoffeeCupSize
{
    Small,
    Big
};

class CoffeeMachine
{
public:
    CoffeeMachine(ISourceOfIngredients* sourceOfIngredients):
        m_sourceOfIngredients(sourceOfIngredients)
    {}

    void GetAmericano(const CoffeeCupSize cupSize)
    {
        int cupSizeGramm = GetCupSizeInGramms(cupSize);

        m_sourceOfIngredients->SetCupSize(cupSizeGramm);
        m_sourceOfIngredients->AddCoffee(cupSizeGramm * 1/3);
        m_sourceOfIngredients->AddWater(cupSizeGramm * 2/3, 60);
    }

private:

    int GetCupSizeInGramms(const CoffeeCupSize cupSize)
    {
        return cupSize == CoffeeCupSize::Small ? 100 : 140;
    }

private:
    ISourceOfIngredients* m_sourceOfIngredients;
};

// TESTS LIST and PLAN
// - big/small americano
// - add ability to set sugar
// - add tests for methods that must not be called (on this step for americano)
// - add test for other coffee types
// - try to avoid code duplications

TEST(CoffeeMachine, getSmallAmericano)
{
    MockSourceOfIngredients sourceOfIngredientsMock;
    CoffeeMachine coffeeMachine(&sourceOfIngredientsMock);

    EXPECT_CALL(sourceOfIngredientsMock, SetCupSize(100)).WillOnce(Return());
    EXPECT_CALL(sourceOfIngredientsMock, AddWater(100*2/3, 60)).WillOnce(Return());
    EXPECT_CALL(sourceOfIngredientsMock, AddCoffee(100*1/3)).WillOnce(Return());
    EXPECT_CALL(sourceOfIngredientsMock, AddMilk(_)).Times(0);
    EXPECT_CALL(sourceOfIngredientsMock, AddMilkFoam(_)).Times(0);
    EXPECT_CALL(sourceOfIngredientsMock, AddChocolate(_)).Times(0);
    EXPECT_CALL(sourceOfIngredientsMock, AddCream(_)).Times(0);

    coffeeMachine.GetAmericano(CoffeeCupSize::Small);
}

