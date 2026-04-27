#include "lsfit.h"
#include "QR.h"

namespace la {

Vector lsfit(
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
    return qr.solve(b);
}

}