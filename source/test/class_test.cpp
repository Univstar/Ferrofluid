#include <iostream>
#include <cstdlib>

#include "../common/constants.h"
#include "../geometry/MacGrid.h"
#include "../geometry/Field.h"
#include "../geometry/FaceField.h"

int main()
{
	Vector<int, 2> cellCounts = { 3, 4 };
	MacGrid<double, 2> macGrid(cellCounts, 0.1);
	Field<char, double, 2> field(macGrid);
	FaceField<char, double, 2> faceField(macGrid);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << macGrid.IndexCell(Vector<int, 2>(i, j)) << ' ';
		}
		std::cout << std::endl;
	}
	system("pause");
	return 0;
}
