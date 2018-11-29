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
    ~ISourceOfIngredients() {}
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
    MOCK_METHOD1(SetCupSize,    void(int gram));
    MOCK_METHOD2(AddWater,      void(int gram, int temperature));
    MOCK_METHOD1(AddSugar,      void(int gram));
    MOCK_METHOD1(AddCoffee,     void(int gram));
    MOCK_METHOD1(AddMilk,       void(int gram));
    MOCK_METHOD1(AddMilkFoam,   void(int gram));
    MOCK_METHOD1(AddChocolate,  void(int gram));
    MOCK_METHOD1(AddCream,      void(int gram));
};

const static size_t s_americanoWaterTemp = 60;

enum class CupSize
{
    Little = 0,
    Big
};

size_t GetCupSize(CupSize size)
{
    switch (size) {
    case CupSize::Little: return 100;
    case CupSize::Big: return 140;
    default:
        throw std::runtime_error("Undefined cup size");
    }
}

class CofffeeMachine
{
public:
    explicit CofffeeMachine(ISourceOfIngredients* ingredients)
        : m_ingredients(ingredients){}

    void PrepareAmericano(CupSize size = CupSize::Little)
    {
        const size_t watterGram = GetCupSize(size) / 3;
        m_ingredients->AddWater(watterGram, s_americanoWaterTemp);

        const size_t coffeeGram = watterGram * 2;
        m_ingredients->AddCoffee(coffeeGram);
    }

    void PrepareCappuccino(CupSize size = CupSize::Little)
    {
        m_ingredients->AddWater(0, 80);
    }

private:
    ISourceOfIngredients* m_ingredients;
};

TEST(CoffeeMashine, TestAmericanoWaterTemp)
{
    MockSourceOfIngredients ingredients;
    CofffeeMachine machine(&ingredients);

    EXPECT_CALL(ingredients, AddWater(testing::_, s_americanoWaterTemp));
    EXPECT_CALL(ingredients, AddCoffee(testing::_));
    machine.PrepareAmericano();
}

TEST(CoffeeMashine, TestAmericanoWaterRatioLittleCup)
{
    MockSourceOfIngredients ingredients;
    CofffeeMachine machine(&ingredients);

    size_t watter;
    size_t coffee;
    EXPECT_CALL(ingredients, AddWater(testing::_, testing::_)).WillOnce(testing::SaveArg<0>(&watter));
    EXPECT_CALL(ingredients, AddCoffee(testing::_)).WillOnce(testing::SaveArg<0>(&coffee));

    machine.PrepareAmericano(CupSize::Little);
    EXPECT_EQ(coffee / 2, watter);
}

TEST(CoffeeMashine, TestAmericanoWaterRatioBigCup)
{
    MockSourceOfIngredients ingredients;
    CofffeeMachine machine(&ingredients);

    size_t watter;
    size_t coffee;
    EXPECT_CALL(ingredients, AddWater(testing::_, testing::_)).WillOnce(testing::SaveArg<0>(&watter));
    EXPECT_CALL(ingredients, AddCoffee(testing::_)).WillOnce(testing::SaveArg<0>(&coffee));

    machine.PrepareAmericano(CupSize::Big);
    EXPECT_EQ(coffee / 2, watter);
}

TEST(CoffeeMashine, TestCappuccinoWatterTemp)
{
    MockSourceOfIngredients ingredients;
    CofffeeMachine machine(&ingredients);

    EXPECT_CALL(ingredients, AddWater(testing::_, 80));
    machine.PrepareCappuccino();
}
