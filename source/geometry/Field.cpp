#include "Field.h"

template<typename Scalar, typename Float, int Dim>
inline Field<Scalar, Float, Dim>::Field(const MacGrid<Float, Dim> &_macGrid, const Scalar &value) :
	macGrid(_macGrid),
	mempool(_macGrid.cellCnt, value)
{
}

template class Field<double, double, 2>;
template class Field<char, double, 2>;

template class Field<double, double, 3>;
template class Field<char, double, 3>;
