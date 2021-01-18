
#include "grandentier.hpp"
#include "cmath"

GrandEntier GrandEntier::operator*(const GrandEntier& grand_entier) const {
  // Inserez votre code ici

  //declaration variables

    GrandEntier firstNb(m_bits);
    GrandEntier secondNb(grand_entier);

    int tailleFirstNb = firstNb.m_bits.size();
    int tailleSecondNb = secondNb.m_bits.size();


    if (tailleFirstNb < tailleSecondNb ){
        for (int i =0; i < tailleSecondNb - tailleFirstNb; i++ ) {
            firstNb.m_bits.push_back(0);
        }
    }
    if (tailleFirstNb > tailleSecondNb ){
        for (int i =0; i < tailleFirstNb - tailleSecondNb; i++ ) {
            secondNb.m_bits.push_back(0);
        }
    }

    unsigned int n = firstNb.m_bits.size();
    double nPlancher = std::floor(n/2.0);

    //multiplication par zero
    if (firstNb.m_bits.size() == 0 || secondNb.m_bits.size() ==0) {
        return GrandEntier(0); }

    //multiplication par un
    if (firstNb.m_bits.size() == 1 && firstNb.m_bits.at(0) == 1) {
        return GrandEntier(secondNb.m_bits);
    }

    //multiplication par un
    if (secondNb.m_bits.size() == 1 && secondNb.m_bits.at(0) == 1) {
        return GrandEntier(firstNb.m_bits);
    }

/*    // autres multiplications triviales
    if (n==1){
        ((firstNb.m_bits.at(0) == 1) && (secondNb.m_bits.at(0) == 1)) ? GrandEntier(1) : GrandEntier(0);
    }*/

    //autres cas

    // division de self
    std::vector<bool> selfLow(firstNb.m_bits.begin(),firstNb.m_bits.begin() + nPlancher); //plancher
    std::vector<bool> selfHigh(firstNb.m_bits.begin() + nPlancher, firstNb.m_bits.end()); //plafond

    // division de grandEntier
    std::vector<bool> grandLow(secondNb.m_bits.begin(),secondNb.m_bits.begin() + nPlancher);
    std::vector<bool> grandHigh(secondNb.m_bits.begin() + nPlancher, secondNb.m_bits.end());

    //appel recursif
    GrandEntier x0(GrandEntier(selfHigh) * GrandEntier(grandHigh));
    GrandEntier x1((GrandEntier(selfLow) + GrandEntier(selfHigh)) * (GrandEntier(grandLow) + GrandEntier(grandHigh)));
    GrandEntier x2(GrandEntier(selfLow) * GrandEntier(grandLow));

    // calcul a_b+ab_
    GrandEntier x3 = (x1 - x0 - x2);

    //shifiting args
    x0.shiftBits(2 *(nPlancher)) ;
    x3.shiftBits(nPlancher);

    GrandEntier expression = x0 + x3 + x2;

    return  expression;

}

