#include "MacGrid.h"

template<typename Float, int Dim>
inline MacGrid<Float, Dim>::MacGrid(const VectorDi &_cellCounts, const Float &_dx, const VectorD &_domainMin) :
	cellCounts(_cellCounts),
	faceCounts(Dim, _cellCounts),
	cellCnt(1),
	faceOffset(Dim, 0),
	faceCnt(0),
	dx(_dx),
	domainMin(_domainMin)
{
	for (int d = 0; d < Dim; ++d) cellCnt *= cellCounts[d];
	for (int axis = 0; axis < Dim; ++axis)
	{
		++faceCounts[axis][axis];
		int mult = 1;
		for (int d = 0; d < Dim; ++d) mult *= faceCounts[axis][d];
		if (axis != Dim - 1) faceOffset[axis + 1] = faceOffset[axis] + mult;
		faceCnt += mult;
	}
}

template<typename Float, int Dim>
inline bool MacGrid<Float, Dim>::IsCellValid(const VectorDi &cell) const
{
	for (int d = 0; d < Dim; ++d)
		if (cell[d] < 0 || cell[d] >= cellCounts[d]) return false;
	return true;
}

template<typename Float, int Dim>
inline bool MacGrid<Float, Dim>::IsFaceValid(const int &axis, const VectorDi &face) const
{
	for (int d = 0; d < Dim; ++d)
		if (face[d] < 0 || face[d] >= faceCounts[axis][d]) return false;
	return true;
}

template<typename Float, int Dim>
inline int MacGrid<Float, Dim>::IndexCell(const VectorDi &cell) const
{
	int idx = 0;
	for (int d = 0; d < Dim; ++d)
		idx = idx * cellCounts[d] + cell[d];
	return idx;
}

template<typename Float, int Dim>
inline int MacGrid<Float, Dim>::IndexFace(const int &axis, const VectorDi &face) const
{
	int idx = 0;
	for (int d = 0; d < Dim; ++d)
		idx = idx * faceCounts[axis][d] + face[d];
	return idx + faceOffset[axis];
}

template class MacGrid<double, 2>;

template class MacGrid<double, 3>;
