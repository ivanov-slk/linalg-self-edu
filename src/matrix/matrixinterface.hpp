#pragma once
#include <memory>
#include "../customconcepts.hpp"

/**
 * @brief Provides interface to common matrix operations.
 * 
 * The general plan about the design is the following:
 * 
 * 1. The matrix interface defines the operations that a matrix
 * implementation is expected to support.
 * 
 * 2. The interface is templated to the Number concept. The client
 * is expected to supply it on construction.
 * 
 * 3. The construction is done via "make" functions. The client chooses
 * any Number concept, but is allowed to choose from a limited number of
 * operations implementations (see below).
 * 
 * 4. The observer methods (like is_empty() or is_sparse()) are
 * implemented directly in the implementing classes.
 * 
 * 5. The operations (arithmetic, decomposition, etc.) are implemented
 * in Concept classes. These classes are required to support a pre-specified
 * (in the concept definition) operations. Each operation may have various
 * implementations. The client is allowed to choose one of these implementations
 * via template.
 * 
 * 6. The goal of this is to prevent a IMatrix implementation to become
 * bloated and hard to maintain and to encapsulate the implementation logic
 * for each group of operations in a separate class. This very much resembles
 * the Bridge pattern, where the "abstraction" is defined as, say, an
 * arithmetic operation, and the "implementation" is defined in a separate
 * class which handles the details.
 * 
 * 7. For example, there might be two main implementations of the matrix
 * interface: Dense matrix and sparse matrix. Each of them needs to receive
 * a template Number. Each of them also needs to be provided an implementation
 * for its operations.
 * 
 * 8. There is a caveat: if the client is allowed to set the operations implementation,
 * he might set a Sparse implementation for a Dense matrix. This would produce
 * erroneous code, but it would be possible since the opration implementing classes
 * are following the same concept (this could be implemented via interfaces,
 * but concepts are a good thing to know). To avoid this, the client will not
 * be able to set them explicitly, but will be provided with the necessary Factory
 * functions, which will choose for him the correct implementation.
 * 
 * 9. For example, a Dense matrix might have two implementations of the matrix
 * multiplication: the O(n^3) nested "for" loop, needed to get things started, and
 * Strassen's algorithm, which is added later. The client will be allowed (via the
 * factory functions) to choose only one of these two. He will not be able to choose
 * a Sparse implementation of the matrix multiplication.
 * 
 * 10. Formally, the O(n^3) implementation will become pretty much useless if
 * Strassen's algorithm is implemented, but, again, learning to work with concepts
 * is a productive thing to do.
 * 
 * 11. The operation implementing classes will work with raw data (const &). The matrix
 * will handle the return type given the raw data it receives from these classes. In case
 * an access to a different class's private (raw) data is needed (say, if we want to multiply
 * a sparse with a dense matrix), the other class should be declared "friend".
 * 
 * 12. The "abstracted" operations in the matrix receive as an (const &) argument only another
 * matrix. These abstracted operations then pass the (raw) data to the operation implementing
 * class, which will perform the action and return raw data, which will be converted to the
 * desired output before the "abstracted" operation returns the final output.
 * 
 */
template <Number T>
class IMatrix
{
public:
    virtual ~IMatrix() = default;
    virtual std::unique_ptr<IMatrix<T>> add(std::unique_ptr<IMatrix<T>> other) = 0;
    // virtual std::unique_ptr<IMatrix<T>> subtract(std::unique_ptr<IMatrix<T>> other) = 0;
    // virtual std::unique_ptr<IMatrix<T>> multiply(std::unique_ptr<IMatrix<T>> other) = 0;
    // virtual std::unique_ptr<IMatrix<T>> divide(std::unique_ptr<IMatrix<T>> other) = 0;
};
