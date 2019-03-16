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

class ICofee
{
public:
    virtual ~ICofee(){}
    virtual const std::string drink() = 0;
};

class Americano : public ICofee
{
public:
    const std::string drink()
    {
        return "Americano";
    }
};

class Latte : public ICofee
{
public:
    const std::string drink()
    {
        return "Latte";
    }
};

class Cappuccino : public ICofee
{
public:
    const std::string drink()
    {
        return "Cappuccino";
    }
};

class Marochino : public ICofee
{
public:
    const std::string drink()
    {
        return "Cappuccino";
    }
};

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
