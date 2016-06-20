#include "Cylinder.h"

Cylinder::Cylinder(int texture, float radius, float height, const Ponto_3D& center) : Objeto_3D ( texture)
{
    raio = radius;
    centro = center;
    altura = height;
}

Intersection Cylinder::Intercepta(const Raio &D, Objeto_3D::IntersectionMode mode, float threshold)
{
    float a, b, c, delta, raiz1, raiz2, y0, y1;
    Intersection intersection;

    Vetor_3D E = Vetor_3D(D.X0() - centro.X(), D.Y0() - centro.Y(), D.Z0() - centro.Z());

    a = D.Dx() * D.Dx() + D.Dz() * D.Dz();
    b = 2 * E.X() * D.Dx() + 2 * E.Z() * D.Dz();
    c = E.X() * E.X() + E.Z() * E.Z() - raio * raio;

    delta = b * b - 4 * a * c;
    if (delta >= 0) {
        raiz1 = (-b + sqrt(delta)) / (2 * a);
        raiz2 = (-b - sqrt(delta)) / (2 * a);

        y0 = E.Y() + raiz1 * D.Dy();
        y1 = E.Y() + raiz2 * D.Dy();

        //testa se bateu no cilindro
        if ((centro.Y() - altura  < y0 && y0 < centro.Y() + altura) || (centro.Y() - altura  < y1 && y1 < centro.Y() + altura )) {
            intersection = Intersection::nearest(Intersection(this, raiz1), Intersection(this, raiz2), threshold);
        }
    }

    return intersection;
}

Vetor_3D Cylinder::normal(const Ponto_3D &ponto) const
{
    Vetor_3D normal;

    normal = ponto - centro;
    normal.normaliza();
    normal.setY(0);

    return normal;
}

TexturePoint Cylinder::pontoTextura(const Ponto_3D &ponto) const
{
    float s, t;
    Vetor_3D textureVector;

    textureVector = ponto - centro;
    textureVector.normaliza();

    s = (atan2(textureVector.X(), textureVector.Z()) + M_PI) / (2 * M_PI);
    t = textureVector.Y();

    return TexturePoint(s, t);
}
