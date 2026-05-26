#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include <cstdlib>

#include "gradiente_coniugato.hpp"

// Condizionamento di una matrice A spd è il rapporto tra
// valore singolare massimo e minimo
double condA(const Eigen::MatrixXd& A)
{
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
  Eigen::VectorXd singularValuesA = svd.singularValues();
  return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
}

int main(int argc, char **argv)
{
  const double tol = 1.0e-15;
  unsigned int n = 3;

  // Costruzione matrice simmetrica definita positiva A=B^T*B,
  // dove B invertibile, controllato dal determinante
  Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);

  if (std::abs(B.determinant()) < tol)
    return EXIT_FAILURE;

  Eigen::MatrixXd A = B.transpose() * B;

  // Soluzione esatta e termine noto: x_ex=(1,...,1), b=A*x_ex
  Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);
  Eigen::VectorXd b = A * x_ex;

  // Parametri del metodo iterativo
  const Eigen::VectorXd x0 = Eigen::VectorXd::Zero(n);  // Vettore arbitrario
  const double res_tol = 1.0e-12;
  const unsigned int it_max = 10000;

  std::cout.precision(2);
  std::cout << std::scientific << "Matrix Cond: " << condA(A) << std::endl;

  // Chiamata Gradiente Coniugato: ritorna una struct con converge, x, num_iter
  const resultGC risultato = gradienteConiugato(A, b, x0, res_tol, it_max);

  const bool  convergenza = risultato.converge;
  const Eigen::VectorXd&  x = risultato.x;
  const unsigned int  it = risultato.num_iter;

  // Residuo finale e errore relativo rispetto alla soluzione esatta
  const Eigen::VectorXd res_final = b - A * x;
  const double res_norm_0 = (b - A * x0).norm();

  // Si usa una soglia tol (invece di == 0.0) perche' in floating point
  // confrontare un double con zero esatto e' fragile.
  const double res_rel = (res_norm_0 < tol) ? res_final.norm()
                                            : res_final.norm() / res_norm_0;

  const double err_rel = (x_ex.norm() < tol) ? (x - x_ex).norm()
                                             : (x - x_ex).norm() / x_ex.norm();

  // double res_rel;
  // if (res_norm_0 == 0.0)
  //     res_rel = res_final.norm();              // norma assoluta
  // else
  //     res_rel = res_final.norm() / res_norm_0; // norma relativa

  std::cout.precision(4);
  std::cout << std::scientific << "convergenza: " << (convergenza ? "SI" : "NO") << std::endl;
  std::cout << std::scientific << "it" << "/" << "it_max" << std::endl;
  std::cout << it << "/" << it_max << std::endl;
  std::cout << std::scientific << "res" << "/" << "res_tol" << std::endl;
  std::cout << std::scientific << res_rel << "/" << res_tol << std::endl;
  std::cout << std::scientific << "err_rel" << std::endl;
  std::cout << std::scientific << err_rel << std::endl;
  std::cout << std::scientific << "soluzione" << std::endl;
  std::cout << std::scientific << x << std::endl;

  const double test_tol = 1.0e-8;
  if (!convergenza || err_rel > test_tol)
  {
    std::cerr << "TEST FALLITO: err_rel = " << err_rel
              << " (tol = " << test_tol << ")" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "TEST SUPERATO" << std::endl;
  return EXIT_SUCCESS;
}
