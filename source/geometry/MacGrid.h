#ifndef __MacGrid_h__
#define __MacGrid_h__

#include "../common/constants.h"

template<typename Float, int Dim>
class MacGrid
{
private:
	
	using VectorD = Vector<Float, Dim>;
	using VectorDi = Vector<int, Dim>;

protected:

	VectorDi cellCounts;
	Array<VectorDi> faceCounts;

	int cellCnt;
	Array<int> faceOffset;
	int faceCnt;

	Float dx;
	VectorD domainMin;

public:

	MacGrid(const VectorDi &_cellCounts, const Float &_dx, const VectorD &_domainMin = VectorD::Zero());

	bool IsCellValid(const VectorDi &cell) const;
	bool IsFaceValid(const int &axis, const VectorDi &face) const;

	int IndexCell(const VectorDi &cell) const;
	int IndexFace(const int &axis, const VectorDi &face) const;

	static VectorDi GetFaceLeft(const int &axis, const VectorDi &face) { return face - VectorDi::Unit(axis); }
	static VectorDi GetFaceRight(const int &axis, const VectorDi &face) { return face; }
	static VectorDi GetCellLeft(const int &axis, const VectorDi &cell) { return cell; }
	static VectorDi GetCellRight(const int &axis, const VectorDi &cell) { return cell + VectorDi::Unit(axis); }

	template<typename Scalar, typename Float, int Dim> friend class Field;
	template<typename Scalar, typename Float, int Dim> friend class FaceField;
};

#endif // !__MacGrid_h__
