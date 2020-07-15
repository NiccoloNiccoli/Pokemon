//
// Created by Niccolò Niccoli on 12/07/2020.
//
#include "gtest/gtest.h"
#include "../Pokemon.h"
#include "SFML/Graphics.hpp"

TEST(PokemonTest, Stats) {
    Pokemon pikachu1("pikachu",1);
    Pokemon pikachu2("pikachu",100);
    Pokemon pikachu3("pikachu",-1);
    Pokemon pikachu4("pikachu",101);
    ASSERT_EQ(pikachu1.getMaxHp(), ((2*35+31)/100)+1+10);
    ASSERT_EQ(pikachu1.getAttack(), ((2*55+31)/100)+5);
    ASSERT_EQ(pikachu1.getDefense(), ((2*30+31)/100)+5);
    ASSERT_EQ(pikachu1.getSpeed(), ((2*90+31)/100)+5);

    ASSERT_EQ(pikachu2.getMaxHp(), ((2*35+31)*100/100)+100+10);
    ASSERT_EQ(pikachu2.getAttack(), ((2*55+31)*100/100)+5);
    ASSERT_EQ(pikachu2.getDefense(), ((2*30+31)*100/100)+5);
    ASSERT_EQ(pikachu2.getSpeed(), ((2*90+31)*100/100)+5);

    ASSERT_EQ(pikachu3.getMaxHp(), pikachu1.getMaxHp());
    ASSERT_EQ(pikachu3.getAttack(), pikachu1.getAttack());
    ASSERT_EQ(pikachu3.getDefense(), pikachu1.getDefense());
    ASSERT_EQ(pikachu3.getSpeed(), pikachu1.getSpeed());

    ASSERT_EQ(pikachu4.getMaxHp(), pikachu1.getMaxHp());
    ASSERT_EQ(pikachu4.getAttack(), pikachu1.getAttack());
    ASSERT_EQ(pikachu4.getDefense(), pikachu1.getDefense());
    ASSERT_EQ(pikachu4.getSpeed(), pikachu1.getSpeed());
}
TEST(PokemonTest, DamageDoneByEveryMove){
    Pokemon squirtle50("squirtle",50);
    Pokemon pikachu50("pikachu",50);
    sf::RenderWindow window;
    //TEST FLAMETHROWER
    Move flamethrower("flamethrower");
    int damageMax = (((2/5 * 50 + 2)*90 * (((2*48+31)*50/100)+5) / (((2*30+31)*50/100)+5) + 2 )/50 * 1.5*1.1);
    int damageMin = (((2/5 * 50 + 2)*90 * (((2*48+31)*50/100)+5) / (((2*30+31)*50/100)+5) + 2 )/50 * 0.85);
    int realDamage = squirtle50.doMove(flamethrower,pikachu50,window);
    ASSERT_TRUE(realDamage <= damageMax && realDamage >= damageMin);
    //TEST HYDROPUMP
    Move hydroPump("hydro_pump");
    damageMax = (((2/5 * 50 + 2)*110 * (((2*48+31)*50/100)+5) / (((2*30+31)*50/100)+5) + 2 )/50 * 1.5*1.1*1.5);
    damageMin = (((2/5 * 50 + 2)*110 * (((2*48+31)*50/100)+5) / (((2*30+31)*50/100)+5) + 2 )/50 * 0.85*1.5);
    realDamage = squirtle50.doMove(hydroPump,pikachu50,window);
    ASSERT_TRUE(realDamage <= damageMax && realDamage >= damageMin);
    //TEST THUNDER
    Move thunder("thunder");
    damageMax = (((2/5 * 50 + 2)*120 * (((2*48+31)*50/100)+5) / (((2*30+31)*50/100)+5) + 2 )/50 * 1.5*1.1*0.5);
    damageMin = (((2/5 * 50 + 2)*120 * (((2*48+31)*50/100)+5) / (((2*30+31)*50/100)+5) + 2 )/50 * 0.85*0.5);
    realDamage = squirtle50.doMove(thunder,pikachu50,window);
    ASSERT_TRUE(realDamage <= damageMax && realDamage >= damageMin);
    //TEST QUICK ATTACK
    Move quickAttack("quick_attack");
    damageMax = (((2/5 * 50 + 2)*40 * (((2*48+31)*50/100)+5) / (((2*30+31)*50/100)+5) + 2 )/50 * 1.5*1.1);
    damageMin = (((2/5 * 50 + 2)*40 * (((2*48+31)*50/100)+5) / (((2*30+31)*50/100)+5) + 2 )/50 * 0.85);
    realDamage = squirtle50.doMove(thunder,pikachu50,window);
    ASSERT_TRUE(realDamage <= damageMax && realDamage >= damageMin);
}
