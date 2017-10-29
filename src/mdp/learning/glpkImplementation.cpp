/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "glpkImplementation.h"

#include <stdexcept>
extern "C"
{
 	#include <glpk.h>
}


using namespace Mdp;

double GlpkImplementation::solve(std::vector<double>& columns,
                                 std::vector<double> coeffs,
                                 std::vector<std::vector<double>> eqCoeffs,
                                 std::vector<double> eqValue,
                                 std::vector<std::vector<double>> ineqCoeffs,
                                 std::vector<double> ineqValue)
{
	double objFunc;

	size_t nbCol = columns.size();
	size_t nbEqConst = eqCoeffs.size();
	size_t nbIneqConst = ineqCoeffs.size();
	/* see 1.3 in [3]*/
	glp_prob *lp;
	const size_t nbRow = nbEqConst + nbIneqConst;
	const size_t constrSize = nbCol*nbRow;
	int *ia = new int[1 + constrSize];
	int *ja = new int[1 + constrSize];
	double *ar = new double[1 + constrSize];
	lp = glp_create_prob();
	glp_set_prob_name(lp, "MDP solver");
	glp_set_obj_dir(lp, GLP_MIN);
	glp_add_rows(lp, nbRow);
	for (size_t i = 0; i < nbEqConst; i++)
	{
		glp_set_row_name(lp, i+1, ""); //is this even necessary?
		glp_set_row_bnds(lp, i+1, GLP_FX, eqValue[i], eqValue[i]);
	}
	for (size_t i = 0; i < nbIneqConst; i++)
	{
		glp_set_row_name(lp, i+1+nbEqConst, ""); //is this even necessary?
		glp_set_row_bnds(lp, i+1+nbEqConst, GLP_UP, 0.0, ineqValue[i]);
	}
	glp_add_cols(lp, nbCol);
	for (size_t i = 0; i < nbCol; i++)
	{
		glp_set_col_name(lp, i+1, ""); //is this even necessary??
		glp_set_col_bnds(lp, i+1, GLP_LO, 0.0, 0.0);
		/*the rho are greater than 0, see [1].
		specifying this here simplifies the code, with respect to having to declare new constraints,
		but makes the code non-reusable.*/
		glp_set_obj_coef(lp, i+1, coeffs[i]);
	}
	

	int counter = 1;
	for (size_t i = 1; i <= nbEqConst; i++)
	{
		for (size_t j = 1; j <= nbCol; j++)
		{
			ia[counter] = i;
			ja[counter] = j;
			ar[counter] = eqCoeffs[i-1][j-1];
			counter++;
		}
	}
	for (size_t i = nbEqConst+1; i <= nbRow; i++)

	{
		for (size_t j = 1; j <= nbCol; j++)
		{
			ia[counter] = i;
			ja[counter] = j;
			ar[counter] = ineqCoeffs[i-1-nbEqConst][j-1];
			counter++;
		}
	}
	glp_load_matrix(lp, constrSize, ia, ja, ar);
	

	switch (algorithm)
	{	
	case LpAlgo::simplex:
		objFunc = simplexSolve(lp, columns);
		break;
	case LpAlgo::interiorPoint:
		objFunc = interiorPointSolve(lp, columns);
		break;
	default:
		throw std::runtime_error("Unknown LP algorithm");
		break;
	}

	glp_delete_prob(lp);

	delete ia;
	delete ja;
	delete ar;
	return objFunc;



}


double GlpkImplementation::simplexSolve(glp_prob *lp, std::vector<double>& columns)
{
	glp_simplex(lp, NULL);
	for (size_t i = 0; i < columns.size(); i++)
	{
		columns[i] = glp_get_col_prim(lp, i+1);
	}
	return glp_get_obj_val(lp);
}


double GlpkImplementation::interiorPointSolve(glp_prob *lp, std::vector<double>& columns)
{
	glp_interior(lp, NULL);
	for (size_t i = 0; i < columns.size(); i++)
	{
		columns[i] = glp_ipt_col_prim(lp, i+1);
	}
	return glp_ipt_obj_val(lp);	
}
