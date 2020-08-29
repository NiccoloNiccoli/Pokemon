//
// Created by Niccolò Niccoli on 12/07/2020.
//
#include "gtest/gtest.h"
#include "../Pokemon.h"
#include "SFML/Graphics.hpp"
#include "tools.h"
TEST(PokemonTest, Stats) {
    Pokemon pikachu1("pikachu",1);
    Pokemon pikachu2("pikachu",100);
    Pokemon pikachu3("pikachu",-1);
    Pokemon pikachu4("pikachu",101);
    ASSERT_EQ(pikachu1.getMaxHp(), ((2*35+48)/100)+1+10);
    ASSERT_EQ(pikachu1.getAttack(), ((2*55+48)/100)+5);
    ASSERT_EQ(pikachu1.getDefense(), ((2*30+48)/100)+5);
    ASSERT_EQ(pikachu1.getSpeed(), ((2*90+48)/100)+5);

    ASSERT_EQ(pikachu2.getMaxHp(), ((2*35+48)*100/100)+100+10);
    ASSERT_EQ(pikachu2.getAttack(), ((2*55+48)*100/100)+5);
    ASSERT_EQ(pikachu2.getDefense(), ((2*30+48)*100/100)+5);
    ASSERT_EQ(pikachu2.getSpeed(), ((2*90+48)*100/100)+5);

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
    Pokemon blastoise50("blastoise",50);
    Pokemon pikachu50("pikachu",50);
    sf::RenderWindow window;
    //TEST FLAMETHROWER
    Move flamethrower("flamethrower");
    int damageMax = -1;
    int damageMin = 2;
    int realDamage = -1;
    do {
        realDamage = blastoise50.doMove(&flamethrower, pikachu50);
    }while(realDamage < 1);
    doDamage(50, 50, 85, 30, 90, 1, 1, damageMax, damageMin);
    ASSERT_TRUE(realDamage <= damageMax && realDamage >= damageMin);
    //TEST HYDROPUMP
    Move hydroPump("hydro_pump");
    doDamage(50, 50, 85, 30, 110, 1, 1.5,damageMax, damageMin);
    do{
    realDamage = blastoise50.doMove(&hydroPump, pikachu50);
    }while(realDamage < 1);
    ASSERT_TRUE(realDamage <= damageMax && realDamage >= damageMin);
    //TEST THUNDER
    Move thunder("thunder");
    doDamage(50,50,85,30,120, 0.5,1,damageMax,damageMin);
    do{
    realDamage = blastoise50.doMove(&thunder, pikachu50);
    }while(realDamage < 1);
    ASSERT_TRUE(realDamage <= damageMax && realDamage >= damageMin);
    //TEST QUICK ATTACK
    Move quickAttack("quick_attack");
    doDamage(50,50,85,30,40,1,1,damageMax,damageMin);
    realDamage = blastoise50.doMove(&quickAttack, pikachu50);
    ASSERT_TRUE(realDamage <= damageMax && realDamage >= damageMin);
    //TEST BRAVE BIRD
    Move braveBird("brave_bird");
    doDamage(50,50,85,30,120,0.5,1,damageMax,damageMin);
    realDamage = blastoise50.doMove(&braveBird, pikachu50);
    ASSERT_TRUE(realDamage <= damageMax && realDamage >= damageMin);
    //TEST DARK PULSE
    Move darkPulse("dark_pulse");
    doDamage(50,50,85,30,85,1,1,damageMax,damageMin);
    realDamage = blastoise50.doMove(&darkPulse, pikachu50);
    ASSERT_TRUE(realDamage <= damageMax && realDamage >= damageMin);
    //TEST DRACO METEOR
    Move dracoMeteor("draco_meteor");
    doDamage(50,50,85,30,130,1,1,damageMax,damageMin);
    do{
    realDamage = blastoise50.doMove(&dracoMeteor, pikachu50);
    }while(realDamage < 1);
    ASSERT_TRUE(realDamage <= damageMax && realDamage >= damageMin);
    //TEST GIGA DRAIN
    Move gigaDrain("giga_drain");
    doDamage(50,50,85,30,75,1,1,damageMax,damageMin);
    realDamage = blastoise50.doMove(&gigaDrain, pikachu50);
    ASSERT_TRUE(realDamage <= damageMax && realDamage >= damageMin);
    //TEST HYPER BEAM
    Move hyperBeam("hyper_beam");
    doDamage(50,50,85,30,150,1,1,damageMax,damageMin);
    do{
    realDamage = blastoise50.doMove(&hyperBeam, pikachu50);
    }while(realDamage < 1);
    ASSERT_TRUE(realDamage <= damageMax && realDamage >= damageMin);
    //TEST SHADOW BALL
    Move shadowBall("shadow_ball");
    doDamage(50,50,85,30,80,1,1,damageMax,damageMin);
    realDamage = blastoise50.doMove(&shadowBall, pikachu50);
    ASSERT_TRUE(realDamage <= damageMax && realDamage >= damageMin);
}
