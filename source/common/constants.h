#ifndef __constants_h__
#define __constants_h__

#include <vector>

#include <Eigen/Dense>

template<class Type, int Dim> 
using Vector = Eigen::Matrix<Type, Dim, 1>;
template<class Type, int Dim>
using Matrix = Eigen::Matrix<Type, Dim, Dim>;
template<class Type>
using Array = std::vector<Type>;


#endif // !__constants_h__
