#include "lsfit.h"
#include "QR.h"
#include <tuple>

namespace la {

std::tuple<Vector, Matrix> lsfit(
    const std::vector<Func>& fs,
    const Vector& x,
    const Vector& y,
    const Vector& dy
) {
    int n = x.size();
    int m = fs.size();

    Matrix A(n, m);
    Vector b(n);

    for (int i = 0; i < n; ++i) {
        b[i] = y[i] / dy[i];
        for (int k = 0; k < m; ++k) {
            A(i, k) = fs[k](x[i]) / dy[i];
        }
    }

    QR qr(A);
    Vector c = qr.solve(b);

    Matrix AtA = transpose(A) * A;
    QR qr_cov(AtA);
    Matrix cov = qr_cov.inverse();

    return {c, cov};
}

}