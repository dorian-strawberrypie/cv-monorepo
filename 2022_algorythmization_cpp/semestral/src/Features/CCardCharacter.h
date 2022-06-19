/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#pragma once

#include "CCard.h"
#include <vector>

/**
 * Contains current attributes of player's character
 */
class CCardCharacter : public CCard {

public:
    struct attr {
        int current, change;
        void update(int updateBy);
        attr();
    };
    explicit CCardCharacter(string name, Reader & r);
    CCardCharacter(const string& name, int mH, int h, int s, int sG, int m, int mG, int g, int gG, int shield);
    CCardCharacter();
    void addChange(int h, int s, int sG, int m, int mG, int g, int gG, int shield);
    void addChange(int healthChange, int shieldChange);
    void updateChar();
    void normalizeAttrs();
    int getShield() const;
    int getGold() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getMana() const;
    int getStamina() const;
    int getGoldGain() const;
    int getManaGain() const;
    int getStaminaGain() const;
    string getName() const;
    string stringCard() const override;
    string printAttr(CCardCharacter::attr a) const;
    string strChange(attr a) const;

private:
    int maxHealth;
    attr health;
    attr stamina, staminaGain;
    attr mana, manaGain;
    attr gold, goldGain;
    attr shield;

    void setAttrMin(attr &a, int min);

};
