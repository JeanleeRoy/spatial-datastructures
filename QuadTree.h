#pragma once

#include "SpatialTreeBase.h"

namespace utec
{
namespace spatial
{

/**
 * Point QuadTree implementation
 */
template<typename Node, typename Rectangle, typename Point>
class QuadTree : public SpatialTreeBase<Node, Rectangle, Point>{
private:
    /**
     * Función recursiva de búsqueda.
     *
     * @param target Punto a buscar
     * @param node Nodo actual
     *
     * @return Retorna referencia al Nodo que contiene o podría contener el punto buscado
     */
    std::shared_ptr<Node>& search(Point target, std::shared_ptr<Node>& node);
    
    /**
     * Función que verifica si un punto se encuentra dentro de una region.
     *
     * @param point punto a verificar
     * @param region Region delimitannte
     *
     * @return Retorna True si el punto está dentro de la región, False caso contrario
     */
    bool in_bounding_box(Point point, Rectangle region);

    /**
     * Función recursiva de la consulta por rango
     *
     * @param node Nodo a verificar
     * @param region Region delimitannte
     * @param points vector de puntos a completar
     *
     */
    void range(std::shared_ptr<Node>& node, Rectangle region, std::vector<Point>& points);

public:
    QuadTree();
    void insert(Point new_point) override;
    std::shared_ptr<Node> search(Point target) override;
    std::vector<Point> range(Rectangle region) override;
    Point nearest_neighbor(Point reference_point) override;
};

} //spatial
} //utec

#include "QuadTree.inl"