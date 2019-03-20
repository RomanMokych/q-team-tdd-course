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

class MockIngredientsProvider : public ISourceOfIngredients
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

class CoffeeMachite
{
public:
    enum CUP_SIZE
    {
        LITTLE_SIZE = 100,
        BIG_SIZE = 140,
    };

public:
    CoffeeMachite(ISourceOfIngredients& ingredientsProvider):
        m_ingredientsProvider(ingredientsProvider)
    {

    }

public:
    void MakeBigEmptyCup()
    {
        m_ingredientsProvider.SetCupSize(BIG_SIZE);
    }

    void MakeLittleEmptyCup()
    {
        m_ingredientsProvider.SetCupSize(LITTLE_SIZE);
    }

    void MakeAmericano()
    {

    }

private:
    ISourceOfIngredients& m_ingredientsProvider;
};

TEST(CoffeeMachite, expected_SetCupSize_140_for_MakeBigEmptyCup_call)
{
    MockIngredientsProvider ingrediensProvicer;
    CoffeeMachite coffeeMachine(ingrediensProvicer);

    EXPECT_CALL(ingrediensProvicer, SetCupSize(CoffeeMachite::BIG_SIZE)).WillOnce(testing::Return());
    coffeeMachine.MakeBigEmptyCup();
}

TEST(CoffeeMachite, expected_SetCupSize_100_for_MakeLittleEmptyCup_call)
{
    MockIngredientsProvider ingrediensProvicer;
    CoffeeMachite coffeeMachine(ingrediensProvicer);

    EXPECT_CALL(ingrediensProvicer, SetCupSize(CoffeeMachite::LITTLE_SIZE)).WillOnce(testing::Return());
    coffeeMachine.MakeLittleEmptyCup();
}

TEST(CoffeeMachine, make_americano_test)
{
     //americano: water & coffee 1:2 or 1:3. Water temp 60C

    MockIngredientsProvider ingrediensProvicer;
    CoffeeMachite coffeeMachine(ingrediensProvicer);

    const size_t cup_size = CoffeeMachite::LITTLE_SIZE;
    EXPECT_CALL(ingrediensProvicer, SetCupSize(cup_size)).WillOnce(testing::Return());
    EXPECT_CALL(ingrediensProvicer, AddWater(cup_size/2, 60)).WillOnce(testing::Return());
}
