#ifndef __Field_h__
#define __Field_h__

#include "../common/constants.h"
#include "MacGrid.h"

template<typename Scalar, typename Float, int Dim>
class Field
{
private:
	
	using VectorDi = Vector<int, Dim>;

protected:

	const MacGrid<Float, Dim> &macGrid;
	Array<Scalar> mempool;

public:

	Field(const MacGrid<Float, Dim> &_macGrid, const Scalar &value = static_cast<Scalar>(0));

	Scalar &operator()(const VectorDi &cell) { return mempool[macGrid.IndexCell(cell)]; }
	const Scalar &operator()(const VectorDi &cell) const { return mempool[macGrid.IndexCell(cell)]; }
};

#endif // !__Field_h__
