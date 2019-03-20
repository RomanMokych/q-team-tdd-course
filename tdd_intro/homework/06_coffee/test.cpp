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

    void MakeAmericano(int gramm)
    {
        m_ingredientsProvider.SetCupSize(gramm);
        m_ingredientsProvider.AddWater(gramm/2, 60);
        m_ingredientsProvider.AddCoffee(gramm/2);
    }

    void MakeCappuccino(int gramm)
    {
       m_ingredientsProvider.SetCupSize(gramm);
        m_ingredientsProvider.AddWater(gramm, 80);
        m_ingredientsProvider.AddMilk(gramm/3);
        m_ingredientsProvider.AddCoffee(gramm/3);
        m_ingredientsProvider.AddMilkFoam(gramm/3);
    }

    void MakeLatte(int gramm)
    {
        m_ingredientsProvider.SetCupSize(gramm);
        m_ingredientsProvider.AddWater(gramm, 90);
        m_ingredientsProvider.AddMilk(gramm/4);
        m_ingredientsProvider.AddCoffee(gramm/2);
        m_ingredientsProvider.AddMilkFoam(gramm/4);
    }

    void MakeMarochino(int gramm)
    {

    }

private:
    ISourceOfIngredients& m_ingredientsProvider;
};

TEST(CoffeeMachine, expected_SetCupSize_140_for_MakeBigEmptyCup_call)
{
    MockIngredientsProvider ingredientsProvicer;
    CoffeeMachite coffeeMachine(ingredientsProvicer);

    EXPECT_CALL(ingredientsProvicer, SetCupSize(CoffeeMachite::BIG_SIZE)).WillOnce(testing::Return());
    coffeeMachine.MakeBigEmptyCup();
}

TEST(CoffeeMachine, expected_SetCupSize_100_for_MakeLittleEmptyCup_call)
{
    MockIngredientsProvider ingredientsProvicer;
    CoffeeMachite coffeeMachine(ingredientsProvicer);

    EXPECT_CALL(ingredientsProvicer, SetCupSize(CoffeeMachite::LITTLE_SIZE)).WillOnce(testing::Return());
    coffeeMachine.MakeLittleEmptyCup();
}

TEST(CoffeeMachine, make_americano_test)
{
     //americano: water & coffee 1:2 or 1:3. Water temp 60C

    MockIngredientsProvider ingredientsProvicer;
    CoffeeMachite coffeeMachine(ingredientsProvicer);

    const size_t cup_size = CoffeeMachite::LITTLE_SIZE;
    EXPECT_CALL(ingredientsProvicer, SetCupSize(cup_size)).WillOnce(testing::Return());
    EXPECT_CALL(ingredientsProvicer, AddWater(cup_size/2, 60)).WillOnce(testing::Return());
    EXPECT_CALL(ingredientsProvicer, AddCoffee(cup_size/2)).WillOnce(testing::Return());

    coffeeMachine.MakeAmericano(cup_size);
}

TEST(CoffeeMachine, make_big_cappuccino_test)
{
    //cappuccino - milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C

    MockIngredientsProvider ingredientsProvicer;
    CoffeeMachite coffeeMachine(ingredientsProvicer);

    const size_t cup_size = CoffeeMachite::BIG_SIZE;
    EXPECT_CALL(ingredientsProvicer, SetCupSize(cup_size)).WillOnce(testing::Return());
    EXPECT_CALL(ingredientsProvicer, AddWater(cup_size, 80)).WillOnce(testing::Return());
    EXPECT_CALL(ingredientsProvicer, AddMilk(cup_size/3)).WillOnce(testing::Return());
    EXPECT_CALL(ingredientsProvicer, AddCoffee(cup_size/3)).WillOnce(testing::Return());
    EXPECT_CALL(ingredientsProvicer, AddMilkFoam(cup_size/3)).WillOnce(testing::Return());

    coffeeMachine.MakeCappuccino(cup_size);
}

TEST(CoffeeMachine, make_little_cappuccino_test)
{
    //cappuccino - milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C

    MockIngredientsProvider ingredientsProvicer;
    CoffeeMachite coffeeMachine(ingredientsProvicer);

    const size_t cup_size = CoffeeMachite::LITTLE_SIZE;
    EXPECT_CALL(ingredientsProvicer, SetCupSize(cup_size)).WillOnce(testing::Return());
    EXPECT_CALL(ingredientsProvicer, AddWater(cup_size, 80)).WillOnce(testing::Return());
    EXPECT_CALL(ingredientsProvicer, AddMilk(cup_size/3)).WillOnce(testing::Return());
    EXPECT_CALL(ingredientsProvicer, AddCoffee(cup_size/3)).WillOnce(testing::Return());
    EXPECT_CALL(ingredientsProvicer, AddMilkFoam(cup_size/3)).WillOnce(testing::Return());

    coffeeMachine.MakeCappuccino(cup_size);
}


TEST(CoffeeMachine, make_big_latte_test)
{
    //latte - milk & coffee & milk foam 1:4, 1:2, 1:4. Water temp 90C

    MockIngredientsProvider ingredientsProvicer;
    CoffeeMachite coffeeMachine(ingredientsProvicer);

    const size_t cup_size = CoffeeMachite::BIG_SIZE;
    EXPECT_CALL(ingredientsProvicer, SetCupSize(cup_size)).WillOnce(testing::Return());
    EXPECT_CALL(ingredientsProvicer, AddWater(cup_size, 90)).WillOnce(testing::Return());
    EXPECT_CALL(ingredientsProvicer, AddMilk(cup_size/4)).WillOnce(testing::Return());
    EXPECT_CALL(ingredientsProvicer, AddCoffee(cup_size/2)).WillOnce(testing::Return());
    EXPECT_CALL(ingredientsProvicer, AddMilkFoam(cup_size/4)).WillOnce(testing::Return());
    coffeeMachine.MakeLatte(cup_size);
}


TEST(CoffeeMachine, make_big_marochino_test)
{
    //marochino - chocolate & coffee & milk foam, 1:4, 1:4, 1:4 and 1:4 is empty

    MockIngredientsProvider ingredientsProvicer;
    CoffeeMachite coffeeMachine(ingredientsProvicer);

    const size_t cup_size = CoffeeMachite::BIG_SIZE;
    EXPECT_CALL(ingredientsProvicer, SetCupSize(cup_size)).WillOnce(testing::Return());
    EXPECT_CALL(ingredientsProvicer, AddChocolate(cup_size/4)).WillOnce(testing::Return());
    EXPECT_CALL(ingredientsProvicer, AddCoffee(cup_size/4)).WillOnce(testing::Return());
    EXPECT_CALL(ingredientsProvicer, AddMilkFoam(cup_size/4)).WillOnce(testing::Return());

    //EXPECT_CALL(ingredientsProvicer, AddWater(_, _)).Times(0);

    coffeeMachine.MakeMarochino(cup_size);
}

