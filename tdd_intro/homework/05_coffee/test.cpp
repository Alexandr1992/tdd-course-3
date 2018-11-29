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
const static size_t s_cappuccinoWaterTemp = 80;

const static size_t s_cupSizeLittle = 100;
const static size_t s_cupSizeBig = 140;

enum class CupSize
{
    Little = 0,
    Big
};

enum class DrinkType
{
    Americano = 0,
    Cappuccino
};

size_t GetCupSize(CupSize size)
{
    switch (size) {
    case CupSize::Little: return s_cupSizeLittle;
    case CupSize::Big: return s_cupSizeBig;
    default:
        throw std::runtime_error("Undefined cup size");
    }
}

class CofffeeMachine
{
public:
    explicit CofffeeMachine(ISourceOfIngredients* ingredients)
        : m_ingredients(ingredients){}

    void Prepare(DrinkType drink, CupSize size = CupSize::Little)
    {
        switch (drink)
        {
            case DrinkType::Americano:
                PrepareAmericano(size);
                break;

            case DrinkType::Cappuccino:
                PrepareCappuccino(size);
                break;

        default:
            throw std::runtime_error("Unknown dink");
        }
    }

private:
    void PrepareAmericano(CupSize size)
    {
        const size_t watterGram = GetCupSize(size) / 3;
        m_ingredients->AddWater(watterGram, s_americanoWaterTemp);

        const size_t coffeeGram = watterGram * 2;
        m_ingredients->AddCoffee(coffeeGram);
    }

    void PrepareCappuccino(CupSize size)
    {
        m_ingredients->AddWater(0, s_cappuccinoWaterTemp);

        const size_t cup_size = GetCupSize(size);
        m_ingredients->AddMilk(cup_size / 3);
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
    machine.Prepare(DrinkType::Americano);
}

TEST(CoffeeMashine, TestAmericanoWaterRatioLittleCup)
{
    MockSourceOfIngredients ingredients;
    CofffeeMachine machine(&ingredients);

    size_t watter;
    size_t coffee;
    EXPECT_CALL(ingredients, AddWater(testing::_, testing::_)).WillOnce(testing::SaveArg<0>(&watter));
    EXPECT_CALL(ingredients, AddCoffee(testing::_)).WillOnce(testing::SaveArg<0>(&coffee));

    machine.Prepare(DrinkType::Americano, CupSize::Little);
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

    machine.Prepare(DrinkType::Americano, CupSize::Big);
    EXPECT_EQ(coffee / 2, watter);
}

TEST(CoffeeMashine, TestCappuccinoWatterTemp)
{
    MockSourceOfIngredients ingredients;
    CofffeeMachine machine(&ingredients);

    EXPECT_CALL(ingredients, AddMilk(testing::_));
    EXPECT_CALL(ingredients, AddWater(testing::_, s_cappuccinoWaterTemp));
    machine.Prepare(DrinkType::Cappuccino);
}

TEST(CoffeeMashine, TestCappuccinoMilkRatioLittleCup)
{
    MockSourceOfIngredients ingredients;
    CofffeeMachine machine(&ingredients);

    size_t milkGram;
    EXPECT_CALL(ingredients, AddWater(testing::_, testing::_));
    EXPECT_CALL(ingredients, AddMilk(testing::_)).WillOnce(testing::SaveArg<0>(&milkGram));
    machine.Prepare(DrinkType::Cappuccino, CupSize::Little);

    EXPECT_EQ(s_cupSizeLittle / 3, milkGram);
}

TEST(CoffeeMashine, TestCappuccinoMilkRatioBigCup)
{
    MockSourceOfIngredients ingredients;
    CofffeeMachine machine(&ingredients);

    size_t milkGram;
    EXPECT_CALL(ingredients, AddWater(testing::_, testing::_));
    EXPECT_CALL(ingredients, AddMilk(testing::_)).WillOnce(testing::SaveArg<0>(&milkGram));
    machine.Prepare(DrinkType::Cappuccino, CupSize::Big);

    EXPECT_EQ(s_cupSizeBig / 3, milkGram);
}

TEST(CoffeeMashine, TestCappuccinoCoffeeRatio)
{
    MockSourceOfIngredients ingredients;
    CofffeeMachine machine(&ingredients);

    size_t coffeeGram;
    EXPECT_CALL(ingredients, AddCoffee(testing::_)).WillOnce(testing::SaveArg<0>(&coffeeGram));
    machine.Prepare(DrinkType::Cappuccino, CupSize::Little);

    EXPECT_EQ(s_cupSizeLittle / 3, coffeeGram);
}
