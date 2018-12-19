#include <iostream>
#include <cstdio>
#include <functional>
#include <algorithm>

#include <Eigen/Sparse>

using namespace std;

template<typename Float, size_t xGrids, size_t yGrids>
class Laplacian2D
{
protected:

	Float h;
	Float grid[xGrids + 2][yGrids + 2];
	Float lineH[xGrids + 1][yGrids + 1];
	Float lineV[xGrids + 1][yGrids + 1];

	function<Float(Float)> kai;
	
	Float &muL(int i, int j) { return lineV[i - 1][j]; }
	Float &muR(int i, int j) { return lineV[i][j]; }
	Float &muU(int i, int j) { return lineH[i][j]; }
	Float &muD(int i, int j) { return lineH[i - 1][j]; }

	Float SolvePhi()
	{
	}

	void UpdateMu()
	{
		for (int i = 1; i <= xGrids; i++)
			for (int j = 0; j <= yGrids; j++)
				muU(i, j) = 1 + kai((grid[i][j] - grid[i][j + 1]) / h);
		for (int i = 0; i <= xGrids; i++)
			for (int j = 1; j <= yGrids; j++)
				muR(i, j) = 1 + kai((grid[i][j] - grid[i + 1][j]) / h);
	}

public:

	Laplacian2D(Float _h, function<Float(Float)> _kai, Float phiTop, Float phiBottom, Float phiLeft, Float phiRight) : h(_h), kai(_kai)
	{
		for (int i = 1; i <= xGrids; i++)
			grid[i][yGrids + 1] = phiTop;
		for (int i = 1; i <= xGrids; i++)
			grid[i][0] = phiBottom;
		for (int j = 1; j <= yGrids; j++)
			grid[0][j] = phiLeft;
		for (int j = 1; j <= yGrids; j++)
			grid[xGrids + 1][j] = phiRight;
		for (int i = 0; i <= xGrids; i++)
			for (int j = 0; j <= yGrids; j++)
				lineH[i][j] = lineV[i][j] = 1;
	}
};

int main()
{
	return 0;
}
