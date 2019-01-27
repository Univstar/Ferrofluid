#include "FaceField.h"

template<typename Scalar, typename Float, int Dim>
inline FaceField<Scalar, Float, Dim>::FaceField(const MacGrid<Float, Dim> &_macGrid, const Scalar &value) :
	macGrid(_macGrid),
	mempool(_macGrid.faceCnt, value)
{
}

template class FaceField<double, double, 2>;
template class FaceField<char, double, 2>;

template class FaceField<double, double, 3>;
template class FaceField<char, double, 3>;
