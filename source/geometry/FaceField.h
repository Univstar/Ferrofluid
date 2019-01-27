#ifndef __FaceField_h__
#define __FaceField_h__

#include "../common/constants.h"
#include "MacGrid.h"

template<typename Scalar, typename Float, int Dim>
class FaceField
{
private:
	
	using VectorDi = Vector<int, Dim>;

protected:

	const MacGrid<Float, Dim> &macGrid;
	Array<Scalar> mempool;

public:

	FaceField(const MacGrid<Float, Dim> &_macGrid, const Scalar &value = static_cast<Scalar>(0));

	Scalar &operator()(const int &axis, const VectorDi &face) { return mempool[macGrid.IndexFace(axis, face)]; }
	const Scalar &operator()(const int &axis, const VectorDi &face) const { return mempool[macGrid.IndexFace(axis, face)]; }
};

#endif // !__FaceField_h__
