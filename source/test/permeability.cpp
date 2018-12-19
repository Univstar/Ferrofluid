#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>

#include <Eigen/Sparse>

using namespace std;
using namespace Eigen;

template<typename Float, int xGrids, int yGrids>
class Laplacian2D
{
protected:

	Float h;
	Float grid[xGrids + 2][yGrids + 2];
	Float lineH[xGrids + 1][yGrids + 1];
	Float lineV[xGrids + 1][yGrids + 1];

	vector<Triplet<Float>> coeff;

	SparseMatrix<Float> A;
	Matrix<Float, xGrids * yGrids, 1> b;
	Matrix<Float, xGrids * yGrids, 1> x;
	SimplicialLDLT<SparseMatrix<Float>> solver;

	function<Float(Float)> kai;

public:
	
	Float &muL(int i, int j) { return lineV[i - 1][j]; }
	Float &muR(int i, int j) { return lineV[i][j]; }
	Float &muU(int i, int j) { return lineH[i][j]; }
	Float &muD(int i, int j) { return lineH[i][j - 1]; }

	int ID(int i, int j) { return (i - 1) * yGrids + j - 1; }

	Float &phiC(int i, int j) { return grid[i][j]; }
	Float &phiC(int id) { return grid[id / yGrids + 1][id % yGrids + 1]; }

	Float SolvePhi()
	{
		coeff.clear();
		for (int i = 1; i <= xGrids; i++)
			for (int j = 1; j <= yGrids; j++)
			{
				b[ID(i, j)] = 0;
				coeff.push_back(Triplet<Float>(ID(i, j), ID(i, j), muL(i, j) + muR(i, j) + muU(i, j) + muD(i, j)));
				if (i > 1) coeff.push_back(Triplet<Float>(ID(i, j), ID(i - 1, j), -muL(i, j)));
				else b[ID(i, j)] += phiC(i - 1, j) * muL(i, j);
				if (i < xGrids) coeff.push_back(Triplet<Float>(ID(i, j), ID(i + 1, j), -muR(i, j)));
				else b[ID(i, j)] += phiC(i + 1, j) * muR(i, j);
				if (j > 1) coeff.push_back(Triplet<Float>(ID(i, j), ID(i, j - 1), -muD(i, j)));
				else b[ID(i, j)] += phiC(i, j - 1) * muD(i, j);
				if (j < yGrids) coeff.push_back(Triplet<Float>(ID(i, j), ID(i, j + 1), -muU(i, j)));
				else b[ID(i, j)] += phiC(i, j + 1) * muU(i, j);
			}
		A.setFromTriplets(coeff.begin(), coeff.end());
		solver.compute(A);
		if (solver.info() != Success)
		{
			fprintf(stderr, "Decomposition failed!\n");
			return -1;
		}
		x = solver.solve(b);
		if (solver.info() != Success)
		{
			fprintf(stderr, "Solving failed!\n");
			return -1;
		}
		Float var = 0;
		for (int i = 1; i <= xGrids; i++)
			for (int j = 1; j <= yGrids; j++)
			{
				var += (x[ID(i, j)] - phiC(i, j)) * (x[ID(i, j)] - phiC(i, j));
				phiC(i, j) = x[ID(i, j)];
			}
		var /= xGrids * yGrids;
		return var;
	}

	void UpdateMu()
	{
		for (int i = 1; i <= xGrids; i++)
			for (int j = 0; j <= yGrids; j++)
				muU(i, j) = 1 + kai((phiC(i, j) - phiC(i, j + 1)) / h);
		for (int i = 0; i <= xGrids; i++)
			for (int j = 1; j <= yGrids; j++)
				muR(i, j) = 1 + kai((phiC(i, j) - phiC(i + 1, j)) / h);
	}

	Laplacian2D(Float _h, function<Float(Float)> _kai, Float phiTop, Float phiBottom, Float phiLeft, Float phiRight) :
		h(_h), kai(_kai), A(xGrids * yGrids, xGrids * yGrids)
	{
		for (int i = 1; i <= xGrids; i++)
			phiC(i, yGrids + 1) = phiTop;
		for (int i = 1; i <= xGrids; i++)
			phiC(i, 0) = phiBottom;
		for (int j = 1; j <= yGrids; j++)
			phiC(0, j) = phiLeft;
		for (int j = 1; j <= yGrids; j++)
			phiC(xGrids + 1, j) = phiRight;
		coeff.reserve(5 * xGrids * yGrids - 2 * xGrids - 2 * yGrids);
	}

	void Solve(Float eps)
	{
		Float var;
		for (int iter = 1; ; iter++)
		{
			fprintf(stderr, "Iteration %d... ", iter);
			UpdateMu();
			fprintf(stderr, "Mu has been updated!\nSolving phi... ");
			var = SolvePhi();
			fprintf(stderr, "with variance %.10lf!\n\n", var);
			if (var < eps) break;
		}
	}

	void OutputInText()
	{
		for (int j = yGrids + 1; j >= 0; j--)
		{
			for (int i = 0; i <= xGrids + 1; i++) printf("%8.2lf ", phiC(i, j));
			printf("\n");
		}
	}
};

int main()
{
	Laplacian2D<double, 30, 20> T(1, [](double H)->double { return atan(H + 0.01) / (H + 0.01); }, 20, 10, 10, 10);
	T.Solve(1e-10);
//	T.OutputInText();
	return 0;
}
