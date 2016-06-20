#ifndef CYLINDER_H
#define CYLINDER_H

#include "Objeto_3d.h"

class Cylinder : public Objeto_3D {

public:
    Cylinder(int texture, float radius, float height, const Ponto_3D& center);
    ~Cylinder() {}

    Intersection Intercepta(const Raio &raio_camera, IntersectionMode mode, float threshold);
    Vetor_3D normal(const Ponto_3D &ponto) const;
    TexturePoint pontoTextura(const Ponto_3D &ponto) const;
};

#endif // CYLINDER_H
