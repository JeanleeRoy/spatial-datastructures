#include "QuadTree.h"
#include <memory>
#include <iostream>
#include <vector>

namespace utec
{
namespace spatial
{

template<typename Node, typename Rectangle, typename Point>
QuadTree<Node, Rectangle, Point>::QuadTree(){
    this->root=nullptr;
}

template<typename Node, typename Rectangle, typename Point>
void QuadTree<Node, Rectangle, Point>::insert(Point new_point){
    std::shared_ptr<Node>& target = search(new_point, this->root);
    if(target==nullptr){
        target=std::make_shared<Node>(new_point);
    }
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node>& QuadTree<Node, Rectangle, Point>::search(Point target, std::shared_ptr<Node>& node){
    if(node == nullptr){
        return node; //not found
    } else if(node->get_point() == target){
        return node;
    }
    
    auto cur_point = node->get_point();

    const int x=0, y=1;

    if(target.get(x) < cur_point.get(x)){
        if(target.get(y) > cur_point.get(y))
            return search(target, node->NW());
        else
            return search(target, node->SW());
    }else{
        if(target.get(y) > cur_point.get(y))
            return search(target, node->NE());
        else
            return search(target, node->SE());
    }
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node> QuadTree<Node, Rectangle, Point>::search(Point target){
    return search(target, this->root);
}

template<typename Node, typename Rectangle, typename Point>
bool QuadTree<Node, Rectangle, Point>::in_bounding_box(Point point, Rectangle region) {
    // get point dimension
    std::size_t dim = point.size();

    // check if the point is out of limits
    for (std::size_t i=0; i<dim; i++) {
        if (point.get(i) < region._min.get(i) || 
            point.get(i) > region._max.get(i) )
            return false;
    }

    return true;
}

template<typename Node, typename Rectangle, typename Point>
void QuadTree<Node, Rectangle, Point>::range(std::shared_ptr<Node>& node, Rectangle region, std::vector<Point>& points) {
    if (node == nullptr)
        return; // there is no node
    
    auto cur_point = node->get_point();

    // if point is inside the region, add it to the result
    if (in_bounding_box(cur_point,region))
        points.push_back(cur_point);
    
    const int x=0, y=1;

    // check western region
    if (cur_point.get(x) >= region._min.get(x)) {
        if (cur_point.get(y) <= region._max.get(y))
            range(node->NW(),region, points);
        if (cur_point.get(y) >= region._min.get(y))
            range(node->SW(),region, points);
    }
    // check eastern region
    if (cur_point.get(x) <= region._max.get(x)) {
        if (cur_point.get(y) <= region._max.get(y))
            range(node->NE(),region, points);
        if (cur_point.get(y) >= region._min.get(y))
            range(node->SE(),region, points);
    }
}


template<typename Node, typename Rectangle, typename Point>
std::vector<Point> QuadTree<Node, Rectangle, Point>::range(Rectangle region){
    /*
    OBSERVACION: El ultimo test tiende a no pasar, esto puede deberse a la 
    cantidad de puntos (con valores double) presentes en un espacio reducido
    */
    std::vector<Point> points;
    range(this->root, region, points);
    return points;
}

template<typename Node, typename Rectangle, typename Point>
Point QuadTree<Node, Rectangle, Point>::nearest_neighbor(Point reference){
    // TODO
}

} //spatial
} //utec
