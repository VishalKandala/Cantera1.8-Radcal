/**
 * @file ReactionStoichMgr.h
 *
 * Header file declaring class ReactionStoichMgr.
 */

/*
 * $Author: hkmoffa $
 * $Revision: 1.2 $
 * $Date: 2007/06/12 14:20:02 $
 */

#ifndef CT_RXN_STOICH
#define CT_RXN_STOICH

#include "ct_defs.h"

namespace Cantera {

  class StoichManagerN;
    class ReactionData;

  /**
   * Reaction mechanism stoichiometry manager. This is an internal class used
   * by kinetics manager classes, and is not meant for direct use in
   * user programs.
   * 
   * Class ReactionStoichMgr handles the calculation of quantities involving 
   * the stoichiometry of a set of reactions. The reactions must have integer 
   * stoichiometric coefficients. Specifically, its methods compute
   * - species creation rates
   * - species destruction rates
   * - species net production rates
   * - the change in molar species properties in the reactions
   * - concentration products 
   *
   * To use this class, method 'add' is first used to add each reaction. 
   * Once all reactions have been added, the methods that compute various
   * quantities may be called.
   *
   * The nomenclature used below to document the methods is as follows.
   *
   * - \f$ N_r \f$
   *     Integer reactant stoichiometric coefficient matrix. The (k,i)
   *     element of this matrix is the stoichiometric coefficient of
   *     species \i k as a reactant in reaction \i i.
   * - \f$ N_p \f$
   *     Integer product stoichiometric coefficient matrix. The (k,i)
   *     element of this matrix is the stoichiometric coefficient of
   *     species \i k as a product in reaction \i i.
   * - \f$ Q_{\rm fwd} \f$
   *     Vector of length I of forward rates of progress.
   * - \f$ Q_{\rm rev} \f$
   *     Vector of length I of reverse rates of progress.
   * - \f$ C \f$ 
   *     Vector of K species creation rates. 
   * - \f$ D \f$ 
   *     Vector of K species destruction rates. 
   * - \f$ W = C - D \f$ 
   *     Vector of K species net production rates. 
   *     
   */
  class ReactionStoichMgr {

  public:

    /// Constructor. 
    ReactionStoichMgr();

    /// Destructor. 
    virtual ~ReactionStoichMgr();

    /**
     * Add a reaction with mass-action kinetics. Vectors
     * 'reactants' and 'products' contain the integer species
     * indices of the reactants and products, respectively.  Note
     * that if more than one molecule of a given species is
     * involved in the reaction, then its index is repeated. 
     *
     * For example, suppose a reaction mechanism involves the
     * species N2, O2, O, N, NO. N2 is assigned index number 0, O2
     * number 1, and so on through NO with number 4.  Then the
     * representation of the following reactions is as shown here.
     * 
     * - N + O = NO 
     *   - reactants: (3, 2)
     *   - products:  (4)
     *
     * - O + O = O2
     *   - reactants: (2, 2)   [ note repeated index ]
     *   - products:  (1)
     * 
     * @param rxn Reaction number. This number will be used as the index 
     * into the rate of progess vector in the methods below. 
     * @param reactants vector of integer reactant indices
     * @param products vector of integer product indices
     * @param reversible true if the reaction is reversible, false otherwise
     */
    virtual void add(int rxn, const vector_int& reactants, const vector_int& products,
	     bool reversible); 

    /**
     * Add a reaction with specified, possibly non-integral, reaction orders. 
     * @param rxn Reaction number
     * @param reactants vector of integer reactant indices
     * @param products vector of integer product indices
     * @param reversible true if the reaction is reversible, false otherwise. 
     * If the reaction is reversible, its reverse rate will be computed from 
     * the reaction stoichiometry.
     * @param fwdOrder reaction orders for the reactants. This vector must
     * be the same length as 'reactants,' and the reaction orders are for the
     * species with index in the corresponding location in 'reactants.'
     *
     */
      //    void add(int rxn, const vector_int& reactants, const vector_int& products,
      //	     bool reversible, const vector_fp& fwdOrder);


      virtual void add(int rxn, const ReactionData& r);

    /**
     * Species creation rates. 
     * Given the arrays of the forward and reverse rates of
     * progress for all reactions, compute the species creation
     * rates, given by
     * \f[
     *  C = N_p Q_f  + N_r Q_r.
     * \f]
     */
     virtual void getCreationRates(int nSpecies, 
			  const doublereal* fwdRatesOfProgress, 
			  const doublereal* revRatesOfProgress, 
			  doublereal* creationRates);


    /**
     * Species destruction rates.
     * Given the arrays of the forward and reverse rates of
     * progress for all reactions, compute the species destruction 
     * rates, given by
     * \f[
     *  D = N_r Q_f  + N_p Q_r,
     * \f]
     * Note that the stoichiometric coefficient matrices are very sparse, integer
     * matrices. 
     */
     virtual void getDestructionRates(int nSpecies, 
			     const doublereal* fwdRatesOfProgress, 
			     const doublereal* revRatesOfProgress, 
			     doublereal* destructionRates);


    /**
     * Given the array of the net rates of progress for all
     * reactions, compute the species net production rates and
     * return them in array w.
     */
    /**
     * Species net production rates.
     * Given the array of the net rates of
     * progress for all reactions, compute the species net production 
     * rates, given by
     * \f[
     *  W = (N_r - N_p) Q_{\rm net},
     * \f]
     */
      virtual void getNetProductionRates(int nsp, const doublereal* ropnet, doublereal* w);



    //! Calculates the change of a molar species property in a reaction. 
    /*!
     * Given an
     * array of species properties 'g', return in array 'dg' the
     * change in this quantity in the reactions. Array 'g' must
     * have a length at least as great as the number of species,
     * and array 'dg' must have a length as great as the total
     * number of reactions.
     *  \f[
     *      \delta g_i = \sum_k{\nu_{i,k} g_k   }
     *  \f]
     *
     * @param nReactions  Number of reactions
     * @param g           Molar property of the species.
     *                    An example would be the partial molar enthalpy
     *                    Length is equal to number of kinetic species
     * @param dg          Calculated property change of the reaction.
     *                    An example would be the delta change in enthalpy,
     *                    i.e., the enthalpy of reaction.
     */
      virtual void getReactionDelta(int nReactions, 
			  const doublereal* g, 
			  doublereal* dg);


    /**
     * Given an array of species properties 'g', return in array
     * 'dg' the change in this quantity in the reversible
     * reactions. Array 'g' must have a length at least as great
     * as the number of species, and array 'dg' must have a length
     * as great as the total number of reactions.  This method
     * only computes 'dg' for the reversible reactions, and the
     * entries of 'dg' for the irreversible reactions are
     * unaltered. This is primarily designed for use in
     * calculating reveerse rate coefficients from thermochemistry
     * for reversible reactions.
     */
      virtual void getRevReactionDelta(int nr, const doublereal* g, doublereal* dg);


    /** 
     * Given an array of concentrations C, multiply the entries in array R by 
     * the concentration products for the reactants:
     * \f[
     *  R_i = R_i * \prod_k C_k^{o_{k,i}}
     * \f]
     * Here \f$ o_{k,i} \f$ is the reaction order of species k in reaction i.
     */
      virtual void multiplyReactants(const doublereal* C, doublereal* R);


    /** 
     * Given an array of concentrations C, multiply the entries in array R by 
     * the concentration products for the products:
     * \f[
     *  R_i = R_i * \prod_k C_k^{\nu^{(p)}_{k,i}}
     * \f]
     * Here \f$ \nu^{(p)}_{k,i} \f$ is the product stoichiometric coefficient
     * of species k in reaction i.
     */
        virtual void multiplyRevProducts(const doublereal* c, doublereal* r);

      virtual void write(std::string filename);

  protected:

      void writeCreationRates(std::ostream& f);
      void writeDestructionRates(std::ostream& f);
      void writeNetProductionRates(std::ostream& f);
      void writeMultiplyReactants(std::ostream& f);
      void writeMultiplyRevProducts(std::ostream& f);
      StoichManagerN*  m_reactants;      
      StoichManagerN*  m_revproducts;
      StoichManagerN*  m_irrevproducts;
      vector_fp m_dummy;

#ifdef INCL_STOICH_WRITER
      StoichWriter* m_rwriter;
#endif
  };
}

#endif
