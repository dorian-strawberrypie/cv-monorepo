/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#include "CCardCharacter.h"

CCardCharacter::CCardCharacter(const string& name, int mH, int h, int s, int sG, int m, int mG, int g, int gG, int sh)
    : CCard(name), maxHealth(mH) {
    health.current = h;
    stamina.current = s;
    staminaGain.current = sG;
    mana.current = m;
    manaGain.current = mG;
    gold.current = g;
    goldGain.current = gG;
    shield.current = sh;
}
CCardCharacter::CCardCharacter() : CCard("") {}

CCardCharacter::CCardCharacter(string name, Reader & r) : CCard(move(name)) {
    r.try_parse("maxHealth", maxHealth);
    health.current = maxHealth;
    r.try_parse("stamina", stamina.current);
    r.try_parse("staminaGain", staminaGain.current);
    r.try_parse("mana", mana.current);
    r.try_parse("manaGain", manaGain.current);
    r.try_parse("gold", gold.current);
    r.try_parse("goldGain", goldGain.current);
//    shield = {0,0};
}

void CCardCharacter::addChange(int h, int s, int sG, int m, int mG, int g, int gG, int sh) {
    health.update(h);
    stamina.update(s);
    staminaGain.update(sG);
    mana.update(m);
    manaGain.update(mG);
    gold.update(g);
    goldGain.update(gG);
    shield.update(sh);
}

void CCardCharacter::addChange(int healthChange, int shieldChange) {
    health.update(healthChange);
    shield.update(shieldChange);
}

/**
 * attrGain attributes are added to attr every end of their turn.
 */
void CCardCharacter::updateChar() {
    stamina.current += staminaGain.current;
    mana.current += manaGain.current;
    gold.current += goldGain.current;
}

/**
 * every start of turn attributes are normalized
 */
void CCardCharacter::normalizeAttrs() {
    setAttrMin(stamina, 0);
    setAttrMin(staminaGain, 1);
    setAttrMin(mana, 0);
    setAttrMin(manaGain, 1);
    setAttrMin(gold, 0);
    setAttrMin(goldGain, 0);
    setAttrMin(shield, 0);
    if (health.current > maxHealth) health.current = maxHealth;
}

void CCardCharacter::setAttrMin(attr & a, int min) {
    if (a.current < min)
        a.current = min;
}

int CCardCharacter::getShield() const {
    return shield.current;
}
int CCardCharacter::getHealth() const {
    return health.current;
}
int CCardCharacter::getMaxHealth() const {
    return maxHealth;
}
int CCardCharacter::getGold() const {
    return gold.current;
}
int CCardCharacter::getMana() const {
    return mana.current;
}
int CCardCharacter::getStamina() const {
    return stamina.current;
}
int CCardCharacter::getGoldGain() const {
    return goldGain.current;
}
int CCardCharacter::getManaGain() const {
    return manaGain.current;
}
int CCardCharacter::getStaminaGain() const {
    return staminaGain.current;
}
string CCardCharacter::getName() const {
    return name;
}

/**
 * handles showing change in player attributes, eg.
 * "Health: 30 (+13)", when gained or lost attribute points.
 * @param updateBy
 */
void CCardCharacter::attr::update(int updateBy) {
    current += updateBy;
    change = updateBy;
}

CCardCharacter::attr::attr() {
    current = 0;
    change = 0;
}

string CCardCharacter::stringCard() const {
    string ret;
    ret += stringName();
    ret += "health: " + printAttr(health) + "\n";
    ret += "stamina: " + printAttr(stamina);
    ret += " / " + printAttr(staminaGain) + "\n";
    ret += "mana: " + printAttr(mana);
    ret += " / " + printAttr(manaGain) + "\n";
    ret += "gold: " + printAttr(gold);
    ret += " / " + printAttr(goldGain) + "\n";
    ret += "shield: " + printAttr(shield) + "\n";
    return ret;
}

string CCardCharacter::printAttr(CCardCharacter::attr a) const {
    string ret = to_string(a.current) + " " + strChange(a);
    a.change = 0;
    return ret;
}

string CCardCharacter::strChange(CCardCharacter::attr a) const {
    if (a.change > 0)
        return "(+" + to_string(a.change) + ")";
    else if (a.change < 0)
        return "(" + to_string(a.change) + ")";
    return "";
}
