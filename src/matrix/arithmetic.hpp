

/**
 * @brief An interface exposing the four basic arithmetic operations.
 * 
 * It is meant to be implemented by classes which are used by other classes
 * as dependencies. This way, one will be able to:
 * - implement various algorithms for performing these operations;
 * - add various operations to some class (say, add arithmetic operations to
 * a matrix)
 */
template <typename T>
class ArithmeticInterface
{
public:
    virtual ~ArithmeticInterface() = default;
    virtual T add(T other) = 0;
    virtual T subtract(T other) = 0;
    virtual T multiply(T other) = 0;
    virtual T divide(T other) = 0;
};