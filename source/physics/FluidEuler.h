#ifndef __FluidEuler_h__
#define __FluidEuler_h__

#include "../common/constants.h"
#include "../geometry/MacGrid.h"
#include "../geometry/Field.h"
#include "../geometry/FaceField.h"

template<typename Float, int Dim>
class FluidEuler
{
private:

	using VectorD = Vector<Float, Dim>;

protected:
	
	enum class CellType : char { Fluid, Air, Solid };

	MacGrid<Float, Dim> macGrid;
	FaceField<Float, Float, Dim> velocity;
	Field<CellType, Float, Dim> label;

	VectorD g = VectorD::Unit(1) * static_cast<Float>(-9.8);

public:
};

#endif // !__FluidEuler_h__