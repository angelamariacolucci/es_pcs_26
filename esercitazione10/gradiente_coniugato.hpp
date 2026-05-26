#pragma once 
#include <Eigen/Dense>

struct resultGC {
  bool  converge;   // true se il metodo converge
  Eigen::VectorXd   x;  // soluzione calcolata
  unsigned int  num_iter;  
}; 

resultGC gradienteConiugato (const Eigen::MatrixXd& A, 
                             const Eigen::VectorXd& b,
                             const Eigen::VectorXd& x0,
                             const double res_tol,
                             const unsigned int it_max)
{
  resultGC out;
  
  out.x = x0;

  // r_0 = A-Ax_0
  Eigen::VectorXd res = b - A * out.x;

  // p_0 = r_0
  Eigen::VectorXd p = res;

  double res_norm_0 = res.norm();
  if (res_norm_0 <= res_tol) {
    out.converge=true;
    out.num_iter=0;
    return out;
  }

  unsigned int it = 0;

  while (it < it_max &&
         res.norm() > res_tol * res_norm_0)
  {
    // Prodotto A*p_k
    const Eigen::VectorXd Ap=A*p;

    // alpha_k = (p_k^T*r_k)/(p_k^T*A*p_k)
    const double alpha_k = (p.dot(res)) / (p.dot(Ap));

    // x_k+1 = x_k + alpha_k*p_k
    out.x = out.x + alpha_k * p;

    // r_k+1 = b - A * x_k+1
    res = b - A*out.x;

    // beta_k = (p_k^T * A * r_k+1)/(p_k^T*A*p_k)
    const double beta_k = (Ap.dot(res))/(p.dot(Ap)); // (p_k^T*A=(A^T*p_k)^T=(A*p)^T)

    // p_k+1 = r_k+1 - beta_k * p_k
    p = res - beta_k*p;

    it++;
  }

  out.num_iter = it;
  out.converge = (res.norm() <= res_tol * res_norm_0);  // Convergenza raggiunta se residuo relativo minore della tolleranza

  return out;
}
