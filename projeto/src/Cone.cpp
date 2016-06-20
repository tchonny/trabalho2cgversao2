#include "Cone.h"

Cone::Cone(int texture, float radius, float height, const Ponto_3D& center) : Objeto_3D (texture)
{
    raio = radius;
    altura = height;
    centro = center;
}

Intersection Cone::Intercepta(const Raio &D, Objeto_3D::IntersectionMode mode, float threshold)
{
    float a, b, c, delta, raiz1, raiz2, y0, y1;
    Intersection intersection;

    Vetor_3D E = Vetor_3D(D.X0() - centro.X(), D.Y0() - centro.Y() - altura/2, D.Z0() - centro.Z());

    a = (D.Dx() * D.Dx()) + (D.Dz() * D.Dz()) - (D.Dy() * D.Dy());
    b = (2 * E.X() * D.Dx()) + (2 * E.Z() * D.Dz()) - (2 * E.Y() * D.Dy());
    c = E.X() * E.X() + E.Z() * E.Z() - E.Y() * E.Y();

    delta = b * b - 4 * a * c;
    if (delta >= 0) {
        raiz1 = (-b + sqrt(delta)) / (2 * a);
        raiz2 = (-b - sqrt(delta)) / (2 * a);

        y0 = E.Y() + raiz1 * D.Dy();
        y1 = E.Y() + raiz2 * D.Dy();

        if ((centro.Y() - altura <= y0 && y0 < centro.Y() ) || (centro.Y() - altura  < y1 && y1 < centro.Y())) {
            intersection = Intersection::nearest(Intersection(this, raiz1), Intersection(this, raiz2), threshold);
        }
    }

    return intersection;
}

Vetor_3D Cone::normal(const Ponto_3D &ponto) const
{
    Vetor_3D normal;
    Vetor_3D tmp;

    //tmp = ponto - centro;
   // tmp.setY( ponto.Y() - centro.Y() - altura/2);
    //tmp.normaliza();
    //tmp.setY(0);

    tmp.setX(ponto.X() - centro.X());
    tmp.setY(0);
    tmp.setZ(ponto.Z() - centro.Z());
    tmp.normaliza();

    normal.setX(tmp.X()*altura/raio);
    normal.setY(raio/altura);
    normal.setZ(tmp.Z()*altura/raio);

    return normal;
}

TexturePoint Cone::pontoTextura(const Ponto_3D &ponto) const {}
