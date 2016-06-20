#ifndef CONE_H
#define CONE_H

#include "Objeto_3d.h"

class Cone : public Objeto_3D
{
public:
    Cone(int texture, float radius, float height, const Ponto_3D& center);
    ~Cone() {}

    Intersection Intercepta(const Raio &raio_camera, IntersectionMode mode, float threshold);
    Vetor_3D normal(const Ponto_3D &ponto) const;
    TexturePoint pontoTextura(const Ponto_3D &ponto) const;
};

#endif // CONE_H
